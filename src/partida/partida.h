#ifndef PARTIDA
#define PARTIDA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../salas/salas.h"
#include "../inventario/inventario.h"
#include "../puzles/puzles.h"
#include "../jugador/jugador.h"

#define SAVE_PATH "./data/Partida.txt"

/**
 * @defgroup partida Módulo Partida
 * @brief Gestión del estado y flujo de la partida
 * @{
 */

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

/** @brief Estructura auxiliar para parsear líneas del fichero de partida guardada. */
typedef struct{
    char player_id[3];           /**< ID del jugador leído de una línea JUGADOR */
    char sala_id[3];             /**< ID de sala leído de una línea SALA */
    char obj_id[MAX_ID_ITEM];    /**< ID de objeto leído de una línea OBJETO */
    char obj_location[MAX_LOCATION]; /**< Localización del objeto leída de una línea OBJETO */
    char conn_id[4];             /**< ID de conexión leído de una línea CONEXION */
    char conn_state[10];         /**< Estado de conexión ("Bloqueada" o "Activa") */
    char puzz_id[4];             /**< ID de puzle leído de una línea PUZLE */
    char puzz_state[10];         /**< Estado del puzle ("Resuelto" o "Pendiente") */
} Savegame;

/**
 * @par CABECERA
 * int game_hud(GameState *game_state)
 * @pre game_state preinicializado
 * @post Muestra el menú del bucle de juego y ejecuta la acción elegida. Devuelve el índice del elemento elegido
 */
int game_hud(GameState*);

/**
 * @par CABECERA
 * int game_update_sala(GameState *game_state, Conn salida_destino)
 * @pre game_state preinicializado, salida_destino es una conexión válida
 * @post Si la salida no está bloqueada, actualiza current_sala y devuelve 1. Si está bloqueada devuelve 0
 */
int game_update_sala(GameState* game_state, Conn salida_destino);

/**
 * @par CABECERA
 * void game_start()
 * @pre ninguna
 * @post Es la función que comienza el juego
 */
void game_start();

/**
 * @par CABECERA
 * void game_initial_struct_loading(GameState* game_state)
 * @pre game_state preinicializado
 * @post Carga los contenidos básicos de una partida antes de cargarla o comenzar una nueva
 */
void game_initial_struct_loading(GameState*);

/**
 * @par CABECERA
 * void game_loop(GameState* game_state)
 * @pre game_state preinicializado
 * @post Es la función que contiene el bucle del juego tras entrar en un jugador
 */
void game_loop(GameState*);

/**
 * @par CABECERA
 * int save_exists(char *player_id)
 * @pre player_id preinicializado
 * @post Devuelve 1 si existe partida guardada para ese jugador, 0 si no
 */
int save_exists(char *player_id);

/**
 * @par CABECERA
 * int game_load(GameState *gamestate)
 * @pre gamestate con player y estructuras preinicializadas
 * @post Restaura sala, objetos, conexiones y puzles al estado guardado. Devuelve 1 si éxito, 0 si no existe partida
 */
int game_load(GameState *gamestate);

/** @} */

#endif
