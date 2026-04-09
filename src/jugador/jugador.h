#ifndef jugador_h
#define jugador_h

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "inventario.h"

typedef struct{
    char Id_jugador[3];
    char Nomb_jugador[21];
    char Jugador[11];
    char Contrasena[9];
    Inventory inv; 
}jugador;

jugador* cargar_jugador(char path[], int *total_leidos);
void liberar_jugador(jugador *array_jugador);
int iniciar_sesion(jugador *array_jugador, int total_leidos);
jugador *registrar_jugador(jugador *array_jugador, int *total_leidos);
void guardar_jugador(jugador *array_jugador, char *path, int total_leidos);
void estado_jugador(jugador *array_jugador, int total_leidos);


#endif
