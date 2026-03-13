#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "salas.h"

Sala* get_sala_from_id(char* id_to_search, Salas* arr_salas){

    int i;
    Sala* Sala_return = NULL;

    for(i=0; i<(arr_salas->number_of_salas); i++){

        if(strcmp(arr_salas->salas[i].sala_id, id_to_search) == 0){

            Sala_return = &(arr_salas->salas[i]);
            
        }

    }

    return(Sala_return);

}

Salas* load_salas(char* filepath){

    FILE* f;
    Salas* loaded_salas;
    loaded_salas = (Salas*)malloc(sizeof(Salas));
    loaded_salas->salas = NULL;
    loaded_salas->number_of_salas = 0;
    
    //OBTENGO Salas.txt
    if((f=fopen(filepath, "r")) == NULL){

        printf("Error al cargar salas. Archivo de texto no cargado.");
        exit(1);

    }

    else{

        char current_row[512];  //FILA ACTUAL EN LECTURA

        while(fgets(current_row, 512, f) != NULL){ //LEO FILA A FILA

            if(current_row[0] != '\n'){

                printf("\n\nFila leida: %s: ", current_row);

                loaded_salas->number_of_salas++;
                loaded_salas->salas = (Sala*)realloc(loaded_salas->salas, sizeof(Sala)*loaded_salas->number_of_salas);

                Sala sala_currentlyreading;
                strcpy(sala_currentlyreading.sala_id, strtok(current_row, "-")); //ID
                strcpy(sala_currentlyreading.sala_name, strtok(NULL, "-")); //NOMBRE

                char sala_string_type[100]; //TIPO DE SALA EN FORMA DE CADENA, NO DE ENUM
                strcpy(sala_string_type, strtok(NULL, "-"));

                //TIPO DE SALA EN FORMA DE ENUM
                if(strcmp(sala_string_type, "INICIAL") == 0){
                    sala_currentlyreading.sala_type = INICIAL;
                }
                else if(strcmp(sala_string_type, "NORMAL") == 0){
                    sala_currentlyreading.sala_type = NORMAL;
                }
                else if(strcmp(sala_string_type, "SALIDA") == 0){
                    sala_currentlyreading.sala_type = SALIDA;
                }
                
                strcpy(sala_currentlyreading.sala_desc, strtok(NULL, "-")); //DESCRIPCIÓN
                if(sala_currentlyreading.sala_desc[strlen(sala_currentlyreading.sala_desc)-1] == '\n'){

                    sala_currentlyreading.sala_desc[strlen(sala_currentlyreading.sala_desc)-1] = '\0'; //ELIMINO EL \n DEL FINAL DE LÍNEA
                    
                }

                loaded_salas->salas[loaded_salas->number_of_salas-1] = sala_currentlyreading;

                //TEST PRINT
                printf("\nID: %s", loaded_salas->salas[loaded_salas->number_of_salas-1].sala_id);
                printf("\nNombre: %s", loaded_salas->salas[loaded_salas->number_of_salas-1].sala_name);
                printf("\nDesc: %s", loaded_salas->salas[loaded_salas->number_of_salas-1].sala_desc);
                printf("\nTipo en num: %i", loaded_salas->salas[loaded_salas->number_of_salas-1].sala_type);

            }

        }

    }

    return loaded_salas;

}