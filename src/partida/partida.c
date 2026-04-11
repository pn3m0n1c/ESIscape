#include "partida.h"
#include "../ui/ui.h"


void game_print_debug(GameState *gs) {
    printf("=== GAMESTATE DEBUG ===\n");
    printf("game_is_playing: %d\n", gs->game_is_playing);
    printf("structs_already_loaded: %d\n", gs->structs_already_loaded);

    if (gs->player) {
        printf("player->id: %s\n", gs->player->id);
        printf("player->Jugador: %s\n", gs->player->Jugador);
        printf("player->Nomb_jugador: %s\n", gs->player->Nomb_jugador);
        printf("player->Inventario_como_string: %s\n", gs->player->Inventario_como_string);
    } else {
        printf("player: NULL\n");
    }

    if (gs->current_sala) {
        printf("current_sala->sala_id: %s\n", gs->current_sala->sala_id);
        printf("current_sala->sala_nombre: %s\n", gs->current_sala->sala_name);
    } else {
        printf("current_sala: NULL\n");
    }

    printf("total jugadores cargados: %d\n", gs->players ? gs->players->total_leidos : -1);
    printf("=======================\n");
}

int game_update_sala(GameState* game_state, Conn salida_destino){
    if(salida_destino.conn_block){
        return 0;
    } else {
        game_state->current_sala = salas_get_sala_from_id(salida_destino.conn_sala_to_id, &(game_state->salas));
        return 1;
    }
}

/*Recibe un gamestate y un archivo que va a escanear. Si encuentra el id del jugador 
 * que está intentando guardar la partida devolverá 1, significando que ese jugador tiene
 * una partida guardada. De lo contrario, devolverá 0. */
int game_save_exists(GameState *gamestate, FILE *file){
    puts("Comprobando si existe la partida");
    ui_anykey_press();
    char line[100];
    char current_id[3];

    game_print_debug(gamestate);

    while(fgets(line, 100, file) != NULL){
        current_id[0] = '\0';
        
        // Busca la cadena que empieza por JUGADOR, la cual contiene el ID del mismo.
        sscanf(line, "JUGADOR: %s", current_id);

        if(strcmp(current_id, gamestate->player->id) == 0){
            return 1;
        }
    }

    return 0;
}


int game_save(GameState* gamestate, char path[200]){
    FILE *file = fopen(path, "r");

    if(file == NULL) {
        printf("Error, no se ha podido abrir %s", path);
        ui_anykey_press();
        return 0;
    }  

    if(game_save_exists(gamestate, file) == 1){
        if(ui_confirmation("ATENCIÓN: Ya existe una partida guardada, ¿Sobreescribir?")){
            puts("Aqui se sobreescribe la partida");
        }
    }
    
    // Si no existe crea una nueva entrada con los datos
    printf("%s", "No existe partida guardada");

    fclose(file);
    return 0;
}

int game_hud(GameState *game_state){

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

    answer = ui_menu_create(menu_game_loop_start);

    switch(answer){

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
            ui_pick_drop_object(game_state, 1);
            break;

        case 4:
            ui_pick_drop_object(game_state, 0);
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
        
        case 8:
            game_save(game_state, "./data/Partida.txt");
            break;
            
        case 9:
            game_state->game_is_playing = 0;
            break;

    }

    free(menu_game_loop_start.entries);

    return(answer);
}

void game_new(GameState* gamestate){

    gamestate->current_sala = salas_get_sala_inicial(&(gamestate->salas));
    
    while(gamestate->game_is_playing){
        game_hud(gamestate);
    }
}

void game_start(){
    
    GameState gamestate;
    gamestate.game_is_playing = 1;

    gamestate.players = cargar_jugadores("./data/Jugadores.txt");
    gamestate.structs_already_loaded = 0; //PARA EL CASO EN EL QUE EL JUGADOR SE SALGA DEL JUEGO SIN HABER CARGADO ANTES LOS OBJETOS, COMPROBAREMOS QUE SEA NULL PARA QUE ASI NO SE BLOQUEE EL PROGRAMA

    ui_user_initial_menu(&gamestate);

    while(1==1){

        game_loop(&gamestate);

    }
    
}

void game_initial_struct_loading(GameState* game_state){

    game_state->salas = salas_load_salas("./data/Salas.txt");
    game_state->conns = salas_load_conns("./data/Conexiones.txt");
    game_state->all_items = inv_load_items("./data/Objetos.txt");
    game_state->arr_puzles = cargar_puzles("./data/Puzles.txt");

    game_state->structs_already_loaded = 1;

}

void game_loop(GameState* game_state){

    switch(ui_main_menu()){
        case 0:
            game_initial_struct_loading(game_state);
            game_new(game_state);
            break;
        case 1:
            game_initial_struct_loading(game_state);

            //EN ESTE HUECO SE CARGARÍA LA PARTIDA

            while(game_state->game_is_playing){
                game_hud(game_state);
            }
            break;
        case 2:
            ui_exit_game(game_state, 1);
            break;
    }

}