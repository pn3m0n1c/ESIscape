#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "salas.h"

sala* get_sala_from_id(char* id_to_search, salas* arr_salas){

    int i;
    sala* sala_return = NULL;

    for(i=0; i<(arr_salas->number_of_salas); i++){

        if(strcmp(arr_salas->salas[i].sala_id, id_to_search) == 0){

            sala_return = &(arr_salas->salas[i]);
            
        }

    }

    return(sala_return);

}