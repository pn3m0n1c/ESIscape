#ifndef jugador_h
#define jugador_h

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../inventario/inventario.h"
#include "../salas/salas.h"

typedef struct GameState GameState;

typedef struct{

    char Nomb_jugador[21];
    char Jugador[11];
    char Contrasena[9];
    char Inventario_como_string[512];

} jugador;

typedef struct{

    jugador* arr_jugadores;
    int total_leidos;

} jugadores;

jugadores *cargar_jugadores(char path[]);

void registrar_jugador(GameState *game_state, char *nom, char *contrasena, char *nom_completo);
void guardar_jugador(GameState *game_state, char *path);

void liberar_jugador(jugador *array_jugador);



#endif
