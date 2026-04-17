#include "puzles.h"

/**
 * @brief Carga los puzles del fichero
 * @par CABECERA
 * array_puz* puzzle_loadpuzzles(char path[])
 * @pre Que haya puzles en el fichero.
 * @post Devuelve puntero a la estructura array_puz y actualiza el contador total leidos
 */
array_puz* puzzle_loadpuzzles(char path[]){
    
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
/**
 * @brief Busca el puzle en base a su ID
 * @par CABECERA
 * puzle* puzzle_find_by_id(char*, array_puz*)
 * @pre Que exista un array de puzles y que haya al menos 1
 * @post Devuelve un puntero al puzle con el id especificado, o NULL si no existe
 */
puzle* puzzle_find_by_id(char* wanted_id, array_puz* arr){
    int i;
    for(i = 0; i < arr->total_leidos; i++){
        if(strcmp(arr->unidad[i].id_puzle, wanted_id) == 0)
            return &arr->unidad[i];
    }
    return NULL;
}

/**
 * @brief Comprueba si la solucion de un puzle es correcta o no
 * @par CABECERA
 * int puzzle_check_solution(array_puz *arr_puzles, char *id_puzle_objetivo, char *respuesta_jugador)
 * @pre Que exista un array de puzles y que haya al menos 1
 * @post Si la respuesta es correcta devuelve 1, si no, devuelve 0
 */
int puzzle_check_solution(array_puz *arr_puzles, char *id_puzle_objetivo, char *respuesta_jugador){
    
    if (arr_puzles == NULL || arr_puzles->unidad == NULL) {
         return -1;
    }

    int i;
    for (i = 0; i < arr_puzles->total_leidos; i++) {
        
        if (strcmp(arr_puzles->unidad[i].id_puzle, id_puzle_objetivo) == 0) {
            
            if (arr_puzles->unidad[i].resuelto == 1) {
                return 1; 
            }

            if (strcmp(arr_puzles->unidad[i].sol, respuesta_jugador) == 0) {
                
                arr_puzles->unidad[i].resuelto = 1;
                return 1; 
                
            } else {
                return 0; 
            }
        }
    }

    return -1; 
}


/**
 * @brief Libera el aaray de puzles y lo deja vacio
 * @par CABECERA
 * void puzzle_freepuzzles(array_puz *)
 * @pre Que exista un array de puzles y que haya al menos 1
 * @post Devuelve el array de puzles vacio
 */
void puzzle_freepuzzles(array_puz *arr_puzles) {
    if ((arr_puzles) != NULL) {
        if ((arr_puzles->unidad) != NULL) {
            free(arr_puzles->unidad);
        }
        free(arr_puzles);
    }
}