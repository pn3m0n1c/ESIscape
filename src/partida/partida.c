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