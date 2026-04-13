#ifndef PARTIDA
#define PARTIDA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../salas/salas.h"
#include "../inventario/inventario.h"
#include "../puzles/puzles.h"
#include "../jugador/jugador.h"

/** @brief Estado global del juego. Agrupa todos los datos necesarios durante una partida activa. */
typedef struct GameState{
    int game_is_playing;         /**< 1 si la partida está en curso, 0 si debe terminar */
    int structs_already_loaded;  /**< 1 si las estructuras del juego ya han sido cargadas */
    jugador *player;             /**< Jugador activo */
    jugadores *players;          /**< Lista de todos los jugadores cargados */
    array_puz *arr_puzles;       /**< Array de puzles del juego */
    Salas salas;                 /**< Conjunto de salas del juego */
    Sala* current_sala;          /**< Sala en la que se encuentra el jugador actualmente */
    Inventory* all_items;        /**< Todos los objetos del juego (location actualizada en tiempo de ejecución) */
    Conns conns;                 /**< Conjunto de conexiones entre salas */
} GameState;

/**
 * @par CABECERA
 * int game_hud(GameState *game_state)
 * @pre PRECONDICION: game_state preinicializado
 * @post POSTCONDICION: Muestra el menú del bucle de juego y ejecuta la acción elegida. Devuelve el índice del elemento elegido
 */
int game_hud(GameState*);

/**
 * @par CABECERA
 * int game_update_sala(GameState *game_state, Conn salida_destino)
 * @pre PRECONDICION: game_state preinicializado, salida_destino es una conexión válida
 * @post POSTCONDICION: Si la salida no está bloqueada, actualiza current_sala y devuelve 1. Si está bloqueada devuelve 0
 */
int game_update_sala(GameState* game_state, Conn salida_destino);

/**
 * @par CABECERA
 * void game_start()
 * @pre PRECONDICION: ninguna
 * @post POSTCONDICION: Es la función que comienza el juego
 */
void game_start();

/**
 * @par CABECERA
 * void game_initial_struct_loading(GameState* game_state)
 * @pre PRECONDICION: game_state preinicializado
 * @post POSTCONDICION: Carga los contenidos básicos de una partida antes de cargarla o comenzar una nueva
 */
void game_initial_struct_loading(GameState*);

/**
 * @par CABECERA
 * void game_loop(GameState* game_state)
 * @pre PRECONDICION: game_state preinicializado
 * @post POSTCONDICION: Es la función que contiene el bucle del juego tras entrar en un jugador
 */
void game_loop(GameState*);

#endif
