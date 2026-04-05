#ifndef puzles
#define puzles

typedef struct{
    char id_puzle[4];
    char nomb_puz[16];
    char id_sala[3];
    char tipo[20];
    char descrip[151];
    char sol[51];
}puzle;

typedef struct{
    puzle *unidad;
    int total_leidos;
}array_puz;

array_puz* cargar_puzles(char path[]);

void liberar_puzles(puzle *array_puzles, int total_leidos);

#endif