#ifndef puzles
#define puzles

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char id_puzle[4];
    char nomb_puz[16];
    char id_sala[3];
    char tipo[20];
    char descrip[151];
    char sol[51];
    int resuelto;
}puzle;

typedef struct{
    puzle *unidad;
    int total_leidos;
}array_puz;

array_puz* cargar_puzles(char path[]);
void liberar_puzles(array_puz *);

#endif