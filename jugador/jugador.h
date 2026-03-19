#ifndef jugador.h
#define jugador.h
#include "inventario.h"

typedef struct{
    int Id_jugador[3];
    char Nomb_jugador[21];
    char Jugador[11];
    char Contraseña[9];
    //char Id_obj[5];
    Inventory inv; 
}jugador;

jugador* cargar_jugador(char path[], int *total_leidos);
void liberar_jugador(puzle *array_jugador, int total_leidos);

#endif
