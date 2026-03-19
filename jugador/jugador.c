#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<jugador.h>

jugador* cargar_jugador(char path[], int *total_leidos) {
    FILE *f = fopen(char path[], "r"); 
    if (f == NULL) {
        *total_leidos = 0;
        return NULL;
    }
}
