#ifndef jugador_h
#define jugador_h
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

#endif
