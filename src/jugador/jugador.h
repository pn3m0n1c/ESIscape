#ifndef jugador_h
#define jugador_h

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../inventario/inventario.h"
#include "../salas/salas.h"

typedef struct GameState GameState;

typedef struct{
    char id[3];
    char Nomb_jugador[21];
    char Jugador[11];
    char Contrasena[9];
    char Inventario_como_string[512];

} jugador;

typedef struct{

    jugador* arr_jugadores;
    int total_leidos;

} jugadores;

//!Cabecera: jugadores *player_loadplayer(char path[])
//!Precondicion:
//!Postcondicion: Devuelve un puntero a la estructura jugadores, la cual contiene un array con los jugadores y el total que se han leido.
jugadores *player_loadplayer(char path[]);

//!Cabecera: void player_registerplayer(GameState *game_state, char *nom, char *contrasena, char *nom_completo)
//!Precondicion:
//!Postcondicion: admite un jugador extra en el array de jugadores con un realloc e incrementa en 1 el total leidos.
void player_registerplayer(GameState *game_state, char *nom, char *contrasena, char *nom_completo);

//!Cabecera: void player_saveplayer(GameState *game_state, char *path)
//!Precondicion: Debe haber jugadores creados en el array para poder guardarlos
//!Postcondicion: Los jugadores añadidos recientemente se guardan dentro de jugadores.txt.
void player_saveplayer(GameState *game_state, char *path);

//!Cabecera:  jugador* player_findplayer(char name[21], char pass[9], jugadores* all_players)
//!Precondicion: Debe de existir el jugador previamente
//!Postcondicion: Si el susuario y la contraseña coinciden con un jugador le devuelve un puntero
jugador* player_findplayer(char name[21], char pass[9], jugadores* all_players);

//!Cabecera:  void player_freeplayer(jugadores *jugadores_borrar)
//!Precondicion:
//!Postcondicion: Vacia la memoria de arr_jugadores 
void player_freeplayer(jugadores *jugadores_borrar);


#endif
