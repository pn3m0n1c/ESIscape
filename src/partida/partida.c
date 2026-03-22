#include "partida.h"

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

    game_state.current_sala = salas_get_sala_inicial(&game_state.salas);
    
    switch(ui_main_menu()){

        case 0:

            //EN ESTE HUECO SE CREARÍA LA NUEVA PARTIDA

            while(game_state.game_is_playing){
                partida_game_loop_start_menu(&game_state);
            }

            break;

        case 1:

            //EN ESTE HUECO SE CARGARÍA LA PARTIDA

            while(game_state.game_is_playing){
                partida_game_loop_start_menu(&game_state);
            }

            break;

        case 2:

            ui_exit_game();

            break;

    }

}