#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<jugador.h>

jugador* cargar_jugador(const char *"jugadores.txt", int *total_leidos) {
    FILE *f = fopen("jugadores.txt", "r"); 
    if (f == NULL) {
        *total_leidos = 0;
        return NULL;
    }
}
