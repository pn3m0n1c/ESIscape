#ifndef puzles.h
#define puzles.h

typedef struct{
    char *id_puzle;
    char *nomb_puz;
    int id_sala;
    char *tipo;
    char *descrip;
    char *sol;
}puzle;

puzle* cargar_puzles(char path[], int *total_leidos);

void liberar_puzles(puzle *array_puzles, int total_leidos);

#endif