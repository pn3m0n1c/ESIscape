#ifndef PARTIDA
#define PARTIDA

#include "../salas/salas.h"
#include "../inventario/inventario.h"
#include "../puzles/puzles.h"
#include "../jugador/jugador.h"

//GAMESTATE
typedef struct{
    int game_is_playing;
    jugador player;
    array_puz *arr_puzles;
    Salas salas;
    Sala* current_sala;
    Inventory* all_items;  /* Todos los objetos del juego (location actualizada en tiempo de ejecución) */
    Conns conns;
} GameState;

//CABECERA: int partida_game_loop_start_menu(GameState *game_state)
//PRECONDICIÓN: game_state preinicializado
//POSTCONDICIÓN: Llama y muestra el menu de comienzo del bucle de juego, y ejecuta las acciones correspondientes si las hay, y devolviendo el índice del elemento elegido.
int game_hud(GameState*);

int game_update_sala(GameState* game_state, Conn salida_destino);

//CABECERA: void partida_game_start()
//PRECONDICIÓN:
//POSTCONDICIÓN: Es la función que comienza el juego
void game_start();

#endif