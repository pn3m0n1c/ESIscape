#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"puzles.h"

array_puz* cargar_puzles(char path[]) {
    FILE *f = fopen(path, "r");
    if (f == NULL) {
        printf("ERROR: No se pudo abrir %s\n", path);
    int  total_leidos = 0;
        return NULL;
    }

puzle *array_puzles = NULL;
    int cont = 0;
    char linea[300];

    while (fgets(linea, sizeof(linea), f)) {
        linea[strcspn(linea, "\r\n")] = 0;
        if (strlen(linea) == 0) continue;

        array_puzles = realloc(array_puzles, (cont + 1) * sizeof(puzle));

        char *token = strtok(linea, "-");
        if (token) strcpy(array_puzles[cont].id_puzle, token);

        token = strtok(NULL, "-");
        if (token) strcpy(array_puzles[cont].nomb_puz, token);

        token = strtok(NULL, "-");
        if (token) strcpy(array_puzles[cont].id_sala, token);

        token = strtok(NULL, "-");
        if (token) strcpy(array_puzles[cont].tipo, token);

        token = strtok(NULL, "-");
        if (token) strcpy(array_puzles[cont].descrip, token);

        token = strtok(NULL, "-");
        if (token) strcpy(array_puzles[cont].sol, token);

        cont++;
    }

    fclose(f);
    array_puz todos_puzles;
    todos_puzles.total_leidos= cont;
    todos_puzles.unidad= array_puzles;


}


void liberar_puzles(puzle *array_puzles, int total_leidos) {
    if (array_puzles != NULL) {
        free(array_puzles);
    }
}