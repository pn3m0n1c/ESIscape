#ifndef jugador_h
#define jugador_h

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../inventario/inventario.h"
#include "../salas/salas.h"

/**
 * @defgroup jugador Módulo Jugador
 * @brief Gestión de los jugadores del juego.
 * @{
 */

//! @brief Gamestate
typedef struct GameState GameState;

//! @brief Estructura que contiene cada jugador
typedef struct{
    char id[3];
    char Nomb_jugador[21];
    char Jugador[11];
    char Contrasena[9];
    char Inventario_como_string[512];

} jugador;

//! @brief Estructura de todos los jugadores
typedef struct{

    jugador* arr_jugadores;
    int total_leidos;

} jugadores;


/**
 * @brief Carga los jugadores del fichero.
 * @par CABECERA
 * jugadores *player_loadplayer(char path[])
 * @pre Que haya jugadores en el fichero.
 * @post Devuelve un puntero a la estructura jugadores, la cual contiene un array con los jugadores y el total que se han leido.
 */
jugadores *player_loadplayer(char path[]);


/**
 * @brief Guarda a un nuevo jugador con la estructura de jugador dentro del array de jugadores
 * @par CABECERA
 * void player_registerplayer(GameState *game_state, char *nom, char *contrasena, char *nom_completo)
 * @pre Que exista un array de jugadores y una estructura la cual los defina.
 * @post admite un jugador extra en el array de jugadores con un realloc e incrementa en 1 el total leidos.
 */
void player_registerplayer(GameState *game_state, char *nom, char *contrasena, char *nom_completo);

/** 
 * @brief Guarda el array de jugadores en el fichero de jugadores.txt
 * @par CABECERA
 * void player_saveplayer(GameState *game_state, char *path)
 * @pre Debe haber jugadores creados en el array para poder guardarlos.
 * @post Los jugadores añadidos recientemente se guardan dentro de jugadores.txt.
 */
void player_saveplayer(GameState *game_state, char *path);


/** 
 * @brief Va buscando en el array de jugadores el jugador el cual se desea encontrar
 * @par CABECERA
 * jugador* player_findplayer(char name[21], char pass[9], jugadores* all_players)
 * @pre Debe de existir un array de jugadores y el jugador que se quiera buscar.
 * @post Si el susuario y la contraseña coinciden con un jugador le devuelve un puntero
 */
jugador* player_findplayer(char name[21], char pass[9], jugadores* all_players);

 
/** 
 * @brief Vacia el array de jugadores
 * @par CABECERA
 * void player_freeplayer(jugadores *jugadores_borrar)
 * @pre Debe de existir un array de jugadores y que tenga al menos un jugador.
 * @post Vacia el aaray de jugadores
 */
void player_freeplayer(jugadores *jugadores_borrar);


#endif
