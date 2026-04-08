#include "puzles.h"

array_puz* cargar_puzles(char path[]){
    
    FILE *f = fopen(path, "r");
    if (f == NULL) {
        printf("ERROR: No se pudo abrir %s\n", path);
        return NULL;
    }

    array_puz *arr_puzles = (array_puz *)malloc(sizeof(array_puz));

    if(arr_puzles != NULL){

        arr_puzles->unidad = NULL;
        arr_puzles->total_leidos = 0;
        char linea[300];

        while (fgets(linea, sizeof(linea), f) != NULL) {
            linea[strcspn(linea, "\r\n")] = 0;
            if (strlen(linea) == 0) continue;

            arr_puzles->unidad = realloc(arr_puzles->unidad, (arr_puzles->total_leidos + 1) * sizeof(puzle));

            char *token = strtok(linea, "-");
            if (token) strcpy((arr_puzles->unidad)[(arr_puzles->total_leidos)].id_puzle, token);

            token = strtok(NULL, "-");
            if (token) strcpy((arr_puzles->unidad)[(arr_puzles->total_leidos)].nomb_puz, token);

            token = strtok(NULL, "-");
            if (token) strcpy((arr_puzles->unidad)[(arr_puzles->total_leidos)].id_sala, token);

            token = strtok(NULL, "-");
            if (token) strcpy((arr_puzles->unidad)[(arr_puzles->total_leidos)].tipo, token);

            token = strtok(NULL, "-");
            if (token) strcpy((arr_puzles->unidad)[(arr_puzles->total_leidos)].descrip, token);

            token = strtok(NULL, "-");
            if (token) strcpy((arr_puzles->unidad)[(arr_puzles->total_leidos)].sol, token);

            (arr_puzles->unidad)[(arr_puzles->total_leidos)].resuelto = 0;

            (arr_puzles->total_leidos)++;
        }

    }

    fclose(f);

    return arr_puzles;

}

void liberar_puzles(array_puz *arr_puzles) {
    if ((arr_puzles) != NULL) {
        if ((arr_puzles->unidad) != NULL) {
            free(arr_puzles->unidad);
        }
        free(arr_puzles);
    }
}