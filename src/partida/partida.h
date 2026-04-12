#ifndef PARTIDA
#define PARTIDA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../salas/salas.h"
#include "../inventario/inventario.h"
#include "../puzles/puzles.h"
#include "../jugador/jugador.h"

//!GAMESTATE
typedef struct GameState{
    int game_is_playing;
    int structs_already_loaded;
    jugador *player;
    jugadores *players;
    array_puz *arr_puzles;
    Salas salas;
    Sala* current_sala;
    Inventory* all_items;  /* Todos los objetos del juego (location actualizada en tiempo de ejecución) */
    Conns conns;
} GameState;

//!CABECERA: int game_hud(GameState *game_state)
//!PRECONDICIÓN: game_state preinicializado
//!POSTCONDICIÓN: Muestra el menú del bucle de juego y ejecuta la acción elegida. Devuelve el índice del elemento elegido
int game_hud(GameState*);

//!CABECERA: int game_update_sala(GameState *game_state, Conn salida_destino)
//!PRECONDICIÓN: game_state preinicializado, salida_destino es una conexión válida
//!POSTCONDICIÓN: Si la salida no está bloqueada, actualiza current_sala y devuelve 1. Si está bloqueada devuelve 0
int game_update_sala(GameState* game_state, Conn salida_destino);

//!CABECERA: void game_start()
//!PRECONDICIÓN:
//!POSTCONDICIÓN: Es la función que comienza el juego
void game_start();

//!CABECERA: void game_initial_struct_loading(GameState* game_state)
//!PRECONDICIÓN: game_state preinicializado
//!POSTCONDICIÓN: Carga los contenidos básicos de una partida antes de cargarla o comenzar una nueva
void game_initial_struct_loading(GameState*);

//!CABECERA: void game_loop(GameState* game_state)
//!PRECONDICIÓN: game_state preinicializado
//!POSTCONDICIÓN: Es la función que contiene el bucle del juego tras entrar en un jugador
void game_loop(GameState*);

#endif
