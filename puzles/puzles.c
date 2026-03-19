#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"puzles.h"

puzle* cargar_puzles(char path[], int *total_leidos) {
    FILE *f = fopen(path, "r");
    if (f == NULL) {
        *total_leidos = 0;
        return NULL;
    }
}

int capacidad= 2; 
int contador= 0;

puzle *array_puzles = (puzle*) malloc(capacidad * sizeof(puzle));
    if (array_puzles == NULL) {
        fclose(archivo);
        return NULL;
    }


    char *trozo;

        trozo= strtok(linea, "-");
        if (trozo != NULL) {
            array_puzles[contador].id_puzle = (char*) malloc(strlen(trozo) + 1);
            strcpy(array_puzles[contador].id_puzle, trozo);
        }

        trozo= strtok(NULL, "-");
        if (trozo != NULL) {
            array_puzles[contador].nomb_puz = (char*) malloc(strlen(trozo) + 1);
            strcpy(array_puzles[contador].nomb_puz, trozo);
        } 
        
        trozo = strtok(NULL, "-");
        if (trozo != NULL) {
            array_puzles[contador].id_sala = atoi(trozo);
        }

        trozo = strtok(NULL, "-");
        if (trozo != NULL) {
            array_puzles[contador].tipo = (char*) malloc(strlen(trozo) + 1);
            strcpy(array_puzles[contador].tipo, trozo);
        }

        trozo = strtok(NULL, "-");
        if (trozo != NULL) {
            array_puzles[contador].descrip = (char*) malloc(strlen(trozo) + 1);
            strcpy(array_puzles[contador].descrip, trozo);
        }

        trozo = strtok(NULL, "-");
        if (trozo != NULL) {
            array_puzles[contador].sol = (char*) malloc(strlen(trozo) + 1);
            strcpy(array_puzles[contador].sol, trozo);
        }


        fclose(archivo);
    *total_leidos = contador; 
    return array_puzles; 




    
    void liberar_puzles(Puzle *array_puzles, int total_leidos) {
    if (array_puzles == NULL) return;

    for (int i = 0; i < total_leidos; i++) {
        if (array_puzles[i].id_puzle != NULL) {
            free(array_puzles[i].id_puzle)
        }
        if (array_puzles[i].nomb_puz != NULL){
            free(array_puzles[i].nomb_puz)
        }
        if (array_puzles[i].tipo != NULL){
            free(array_puzles[i].tipo)
        }
        if (array_puzles[i].descrip != NULL){

            free(array_puzles[i].descrip)
        }
        if (array_puzles[i].sol != NULL){
             free(array_puzles[i].sol)
        }
    }

    free(array_puzles);
}