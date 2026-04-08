#include "partida.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../aux/aux.h"
#include "../ui/ui.h"

/* Recibe la ruta del fichero de la partida, y un puntero a
 * la dirección de memoria de un gamestate. Intenta parsearlo y devuelve 0 
 * si hay error o 1 si ha conseguido introducir los datos en el gamestate */
int gm_load_game(char path[], Gamestate *game_state) {
    FILE *file = fopen(path, "r");

    if(!check_file(file)) return 0;

    int i = 0;
    char line[200];

    malloc(sizeof(Gamestate));

    while(fgets(line,200,file) != NULL){
        i++;
    }

    /* Pendiente un free, entiendo que será al final del juego - Christian*/
    
    fclose(file);
    return 1;
}

/* Guarda el estado actual de la partida en Partida.txt.
 * Devuelve 1 si guardó con éxito, 0 en otro caso. */
int gm_save_game(char path[], Gamestate *game_state){
    FILE *file = fopen(path, "w");

    if(!check_file(file)) return 0;

    /* JUGADOR y SALA */
    fprintf(file, "JUGADOR: %s\n", game_state->player.id);       /* TODO: ajustar al nombre de campo id del struct jugador */
    fprintf(file, "SALA: %s\n",    game_state->current_sala->sala_id);

    /* OBJETOS — delega en inventario */
    inv_write_items(file, &game_state->all_items);

    /* TODO: iterar conexiones desbloqueadas → fprintf(file, "CONEXIÓN: %s-%s\n", ...) */
    /* TODO: iterar puzles resueltos          → fprintf(file, "PUZLE: %s-%s\n",    ...) */

    fclose(file);
    return 1;
}

void gm_gameloop(){

    Gamestate game_state;
    game_state.game_is_playing = 1;

    //WE LOAD DATA FROM ROOM AND CONNECTION FILES
    game_state.salas = salas_load_salas("./data/Salas.txt");
    game_state.conns = salas_load_conns("./data/Conexiones.txt");

int partida_game_loop_start_menu(GameState *game_state){

    Menu menu_game_loop_start;
    int answer;

    Menu_Entry Menu_Entry_describir_sala;
    strcpy(Menu_Entry_describir_sala.name, "Describir sala");
    Menu_Entry_describir_sala.action = NULL;
    
    Menu_Entry Menu_Entry_examinar;
    strcpy(Menu_Entry_examinar.name, "Examinar (objetos y salidas)");
    Menu_Entry_examinar.action = NULL;
    
    Menu_Entry Menu_Entry_entrar_en_otra_sala;
    strcpy(Menu_Entry_entrar_en_otra_sala.name, "Entrar en otra sala");
    Menu_Entry_entrar_en_otra_sala.action = NULL;

    Menu_Entry Menu_Entry_coger_objeto;
    strcpy(Menu_Entry_coger_objeto.name, "Coger objeto");
    Menu_Entry_coger_objeto.action = NULL;

    Menu_Entry Menu_Entry_soltar_objeto;
    strcpy(Menu_Entry_soltar_objeto.name, "Soltar objeto");
    Menu_Entry_soltar_objeto.action = NULL;

    Menu_Entry Menu_Entry_inventario;
    strcpy(Menu_Entry_inventario.name, "Inventario");
    Menu_Entry_inventario.action = NULL;

    Menu_Entry Menu_Entry_usar_objeto;
    strcpy(Menu_Entry_usar_objeto.name, "Usar objeto");
    Menu_Entry_usar_objeto.action = NULL;

    Menu_Entry Menu_Entry_puzle_codigo;
    strcpy(Menu_Entry_puzle_codigo.name, "Resolver puzle / introducir codigo");
    Menu_Entry_puzle_codigo.action = NULL;

    Menu_Entry Menu_Entry_guardar_partida;
    strcpy(Menu_Entry_guardar_partida.name, "Guardar partida");
    Menu_Entry_guardar_partida.action = NULL;
    
    Menu_Entry Menu_Entry_volver;
    strcpy(Menu_Entry_volver.name, "Volver");
    Menu_Entry_volver.action = NULL;

    menu_game_loop_start.entries = (Menu_Entry*)malloc(sizeof(Menu_Entry)*10);
    menu_game_loop_start.entries[0] = Menu_Entry_describir_sala;
    menu_game_loop_start.entries[1] = Menu_Entry_examinar;
    menu_game_loop_start.entries[2] = Menu_Entry_entrar_en_otra_sala;
    menu_game_loop_start.entries[3] = Menu_Entry_coger_objeto;
    menu_game_loop_start.entries[4] = Menu_Entry_soltar_objeto;
    menu_game_loop_start.entries[5] = Menu_Entry_inventario;
    menu_game_loop_start.entries[6] = Menu_Entry_usar_objeto;
    menu_game_loop_start.entries[7] = Menu_Entry_puzle_codigo;
    menu_game_loop_start.entries[8] = Menu_Entry_guardar_partida;
    menu_game_loop_start.entries[9] = Menu_Entry_volver;
    menu_game_loop_start.number_of_entries = 10;

    ui_graphic_show_screen_separation();
    printf("\nSala: %s\n\n", game_state->current_sala->sala_name);

    switch(ui_menu_create(menu_game_loop_start)){

        case 0:
            ui_describe_sala(game_state->current_sala, game_state);
            break;

        case 1:
            ui_examine_sala(game_state->current_sala, game_state);
            break;

        case 2:
            ui_enter_sala(game_state);
            break;

        case 3:
            ui_grab_pick_object(game_state, 1);
            break;

        case 4:
            ui_grab_pick_object(game_state, 0);
            break;

        case 5:
            ui_show_player_inventory(game_state);
            break;

        case 6:
            ui_use_object(game_state);
            break;

        case 7:
            ui_solve_puzzle(game_state);
            break;
            
        case 9:
            game_state->game_is_playing = 0;
            break;

    }

    free(menu_game_loop_start.entries);

    return(answer);

}

void partida_game_start(){

    GameState game_state;
    game_state.game_is_playing = 1;

    //WE LOAD DATA FROM FILES
    game_state.salas = salas_load_salas("./data/Salas.txt");
    game_state.conns = salas_load_conns("./data/Conexiones.txt");
    game_state.inventory = inv_read_items("./data/Objetos.txt");
    game_state.arr_puzles = cargar_puzles("./data/Puzles.txt");

    game_state.current_sala = salas_get_sala_inicial(&game_state.salas);
    
    switch(ui_main_menu()){
        case 0:
            while(game_state.game_is_playing){
                ui_game_loop_start_menu(game_state);
            }
            break;
        case 1:

            //EN ESTE HUECO SE CARGARÍA LA PARTIDA

            while(game_state.game_is_playing){
                ui_game_loop_start_menu(game_state);
            }

            break;
        case 2:
            ui_exit_game();
            break;
    }
}