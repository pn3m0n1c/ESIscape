#include "partida.h"
#include "../ui/ui.h"
#include <cstdio>


/**
 * @brief Imprime por pantalla el estado completo del GameState para depuración.
 * @par CABECERA
 * void game_print_debug(GameState *gs)
 * @pre gs preinicializado
 * @post Imprime por pantalla el estado completo del GameState para depuración
 */
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

/**
 * @brief Actualiza la sala actual del jugador si la conexión no está bloqueada.
 * @par CABECERA
 * int game_update_sala(GameState *game_state, Conn salida_destino)
 * @pre game_state preinicializado, salida_destino es una conexión válida
 * @post Si la salida no está bloqueada, actualiza current_sala y devuelve 1. Si está bloqueada devuelve 0
 */
int game_update_sala(GameState* game_state, Conn salida_destino){
    if(salida_destino.conn_block){
        return 0;
    } else {
        game_state->current_sala = salas_get_sala_from_id(salida_destino.conn_sala_to_id, &(game_state->salas));
        return 1;
    }
}

/**
 * @brief Escribe la partida del jugador actual a SAVE_PATH en modo append.
 * @par CABECERA
 * int game_write(GameState *gamestate)
 * @pre gamestate con player y current_sala preinicializados
 * @post Añade al fichero una entrada con los datos del jugador actual. Devuelve 1 si éxito, 0 si error
 */
int game_write(GameState *gamestate){

    //! Mínima salvaguarda para evitar crasheos.
    if(gamestate->player == NULL || gamestate->current_sala == NULL){
        printf("Error: no hay partida activa para guardar\n");
        ui_anykey_press();
        return 0;
    }

    FILE *savegame = fopen(SAVE_PATH, "a");
    int i;

    fprintf(savegame, "\n\nJUGADOR: %s\n", gamestate->player->id);
    fprintf(savegame, "SALA: %s\n", gamestate->current_sala->sala_id);
    inv_write_items(savegame, gamestate->all_items);
    for(i = 0; i < gamestate->conns.number_of_conns; i++){
        Conn c = gamestate->conns.conns[i];
        fprintf(savegame, "CONEXION: %s-%s\n", c.conn_id, c.conn_block ? "Bloqueada" : "Activa");
    }
    for(i = 0; i < gamestate->arr_puzles->total_leidos; i++){
        puzle p = gamestate->arr_puzles->unidad[i];
        fprintf(savegame, "PUZLE: %s-%s\n", p.id_puzle, p.resuelto ? "Resuelto" : "Pendiente");
    }

    fclose(savegame);
    return 1;
}

/**
 * @brief Sobreescribe la partida del jugador activo eliminando su bloque anterior y guardando el estado actual.
 * @par CABECERA
 * int game_overwrite(GameState *gamestate)
 * @pre gamestate con player preinicializado
 * @post Elimina el bloque del jugador activo de SAVE_PATH y guarda la partida actualizada con game_write
 */
int game_overwrite(GameState *gamestate){
    char savegame_path[20] = "./data/save.txt";

    //! Crea un fichero llamado save.txt
    FILE *new_save = fopen(savegame_path, "w");
    //! Escribe línea a línea saltando los contenidos del jugador buscado
    FILE *old_save = fopen(SAVE_PATH, "r");

    char old_line[150];
    char found_id[3] = "";

    //! Leer el fichero entero hasta encontrar el jugador.
    while(fgets(old_line, sizeof(old_line), old_save) != NULL){
        //! Truco para buscar el patrón "JUGADOR: id" con sscanf
        sscanf(old_line, "JUGADOR: %s", found_id);
        if (strcmp(found_id, gamestate->player->id) != 0) {
            /*! Mientras el id de jugador encontrado y el id del jugador actual
            sean distintos, escribimos en save.txt. Es decir, cuando sean iguales,
            No se escribirá
            */
            fputs(old_line, new_save);
        }
    }

    fclose(old_save);
    fclose(new_save);

    //! Al terminar de escribir, elimina partida.txt usando su path.
	if(remove(SAVE_PATH) != 0){
    	puts("remove falló");
	}
	//! Renombrar save.txt a partida.txt
	if(rename(savegame_path, SAVE_PATH) != 0){
		puts("rename falló");
	}

    //! Usar game_write para guardar partida al final
    game_write(gamestate);

    return 0;
}

/**
 * @brief Comprueba si existe una partida guardada para el ID de jugador indicado.
 * @par CABECERA
 * int save_exists(char id[3])
 * @pre id preinicializado
 * @post Devuelve el número de línea donde se encontró el ID del jugador en SAVE_PATH, o 0 si no existe
 */
int save_exists(char id[3]){
    FILE *file = fopen(SAVE_PATH, "r");

    int line_number = 0;
    char line_content[100];
    char current_id[3];

    while(fgets(line_content, 100, file) != NULL){
        current_id[0] = '\0';
        line_number++;

        //! Busca la cadena que empieza por JUGADOR, la cual contiene el ID del mismo.
        sscanf(line_content, "JUGADOR: %s", current_id);

        if(strcmp(current_id, id) == 0){
            return line_number;
        }
    }

	fclose(file);

    return 0;
}

/**
 * @brief Gestiona el guardado de partida, preguntando si sobreescribir en caso de que ya exista.
 * @par CABECERA
 * int game_save(GameState *gamestate)
 * @pre gamestate con player preinicializado
 * @post Si ya existe partida guardada pregunta si sobreescribir. Si no existe, crea una nueva entrada en SAVE_PATH
 */
int game_save(GameState* gamestate){

    if(save_exists(gamestate->player->id) > 0){
        if(ui_confirmation("ATENCIÓN: Ya existe una partida guardada, ¿Sobreescribir?")){
            game_overwrite(gamestate);
            puts("¡Partida sobreescrita con éxito!");
            ui_anykey_press();
        }
    } else {
        //! Si no existe crea una nueva entrada con los datos
        puts("No existe partida guardada. Guardando partida...");
        if(game_write(gamestate) == 1 ){
            puts("¡Partida guardada con éxito!");
            ui_anykey_press();
        };
    }

    return 0;
}

/**
 * @brief Carga la partida guardada del jugador activo y restaura el estado del juego.
 * @par CABECERA
 * int game_load(GameState *gamestate)
 * @pre gamestate con player y estructuras preinicializadas
 * @post Restaura sala, objetos, conexiones y puzles al estado guardado. Devuelve 0 siempre
 */
int game_load(GameState* gamestate){
    FILE *saves_file = fopen(SAVE_PATH, "r");
    
    char line[150];
	Savegame data;
    
    //! Leer el fichero hasta encontrar el jugador.
    while(fgets(line, sizeof(line), saves_file) != NULL){
        //! De nuevo el truquito para buscar el patrón "JUGADOR: id" con sscanf
        sscanf(line, "JUGADOR: %s", data.player_id);
        if (strcmp(data.player_id, gamestate->player->id) == 0) {
            //! Jugador encontrado, vamos actualizando el gamestate
            //! Por cada "tipo de línea" que encuentres, actualizala.
			if(sscanf(line, "SALA: %s", data.sala_id) == 1){
				gamestate->current_sala = salas_get_sala_from_id(data.sala_id, &gamestate->salas);
			}
			else if(sscanf(line, "OBJETO: %[^-]-%s", data.obj_id, data.obj_location) == 2){
				Item* item = inv_find_item_by_id(data.obj_id, gamestate->all_items);
				inv_update_item_loc(item, data.obj_location);
    		}
			else if(sscanf(line, "CONEXION: %[^-]-%s", data.conn_id, data.conn_state) == 2){
				Conn* conn = salas_find_conn_by_id(data.conn_id, &gamestate->conns);
				if(conn != NULL) conn->conn_block = strcmp(data.conn_state, "Bloqueada") == 0 ? 1 : 0;
			}
			else if(sscanf(line, "PUZLE: %[^-]-%s", data.puzz_id, data.puzz_state) == 2){
				puzle* puzz = puzzle_find_by_id(data.puzz_id, gamestate->arr_puzles);
				if(puzz != NULL) puzz->resuelto = strcmp(data.puzz_state, "Resuelto") == 0 ? 1 : 0;
			}
        }
    }

	return 0;
}

/**
 * @brief Muestra el menú del bucle de juego y ejecuta la acción elegida.
 * @par CABECERA
 * int game_hud(GameState *game_state)
 * @pre game_state preinicializado
 * @post Muestra el menú del bucle de juego y ejecuta la acción elegida. Devuelve el índice del elemento elegido
 */
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
            game_save(game_state);
            break;

        case 9:
            game_state->game_is_playing = 0;
            break;

    }

    free(menu_game_loop_start.entries);

    return(answer);
}

/**
 * @brief Establece la sala inicial y entra en el bucle de juego.
 * @par CABECERA
 * void game_new(GameState *gamestate)
 * @pre gamestate con salas preinicializadas
 * @post Establece la sala inicial y entra en el bucle de juego hasta que game_is_playing sea 0
 */
void game_new(GameState* gamestate){

    gamestate->current_sala = salas_get_sala_inicial(&(gamestate->salas));

    while(gamestate->game_is_playing){
        game_hud(gamestate);
    }
}

/**
 * @brief Inicializa el GameState, carga los jugadores y arranca el bucle principal del juego.
 * @par CABECERA
 * void game_start()
 * @pre ninguna
 * @post Inicializa el GameState, carga los jugadores y arranca el bucle principal del juego
 */
void game_start(){

    GameState gamestate;
    gamestate.game_is_playing = 1;

    gamestate.players = player_loadplayer("./data/Jugadores.txt");
    gamestate.structs_already_loaded = 0; //!PARA EL CASO EN EL QUE EL JUGADOR SE SALGA DEL JUEGO SIN HABER CARGADO ANTES LOS OBJETOS, COMPROBAREMOS QUE SEA NULL PARA QUE ASI NO SE BLOQUEE EL PROGRAMA

    ui_user_initial_menu(&gamestate);

    while(1==1){

        game_loop(&gamestate);

    }

}

/**
 * @brief Carga salas, conexiones, objetos y puzles en el GameState desde sus ficheros.
 * @par CABECERA
 * void game_initial_struct_loading(GameState *game_state)
 * @pre game_state preinicializado
 * @post Carga salas, conexiones, objetos y puzles en el GameState desde sus ficheros correspondientes
 */
void game_initial_struct_loading(GameState* game_state){

    game_state->salas = salas_load_salas("./data/Salas.txt");
    game_state->conns = salas_load_conns("./data/Conexiones.txt");
    game_state->all_items = inv_load_items("./data/Objetos.txt");
    game_state->arr_puzles = puzzle_loadpuzzles("./data/Puzles.txt");

    game_state->structs_already_loaded = 1;

}

/**
 * @brief Muestra el menú principal y gestiona las opciones de nueva partida, cargar partida y salir.
 * @par CABECERA
 * void game_loop(GameState *game_state)
 * @pre game_state preinicializado
 * @post Muestra el menú principal y gestiona las opciones de nueva partida, cargar partida y salir
 */
void game_loop(GameState* game_state){

    switch(ui_main_menu()){
        case 0:
            game_initial_struct_loading(game_state);
            game_new(game_state);
            break;
        case 1:
            game_initial_struct_loading(game_state);

            if(save_exists(game_state->player->id) == 0){
				puts("¡No existen datos que cargar para este jugador!");
				ui_anykey_press();
				break;
            }

            if(game_load(game_state) ==  0)
				puts("¡Partida cargada con éxito!");

            while(game_state->game_is_playing){
                game_hud(game_state);
            }
            break;
        case 2:
            ui_exit_game(game_state, 1);
            break;
    }

}
