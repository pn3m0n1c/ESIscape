#ifndef puzles.h
#define puzles.h

typedef struct{
    char id_puzle[4];
    char nomb_puz[16];
    char id_sala[3];
    char tipo[20];
    char descrip[151];
    char sol[50];
}puzle;

puzle* cargar_puzles(char path[], int *total_leidos);   //Dinamico esto

void liberar_puzles(puzle *array_puzles, int total_leidos);

#endif