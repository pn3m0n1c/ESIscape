#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "salas.h"

salas arr_salas;

sala* get_sala_from_id(char* id_a_buscar){

    int i;
    sala* sala_return = NULL;

    for(i=0; i<arr_salas.number_of_salas; i++){

        if(strcmp(arr_salas.salas[i].sala_id, id_a_buscar) == 0){

            sala_return = &arr_salas.salas[i];
            
        }

    }

    return(sala_return);

}