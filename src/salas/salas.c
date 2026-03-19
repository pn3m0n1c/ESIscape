#include "salas.h"

Sala* salas_get_sala_from_id(char* id_to_search, Salas* arr_salas){

    int i;
    Sala* Sala_return = NULL;

    for(i=0; i<(arr_salas->number_of_salas); i++){

        if(strcmp(arr_salas->salas[i].sala_id, id_to_search) == 0){

            Sala_return = &(arr_salas->salas[i]);
            
        }

    }

    return(Sala_return);

}

Sala* salas_get_sala_inicial(Salas* arr_salas){

    int i;
    Sala* Sala_inicial = NULL;

    for(i=0; i<(arr_salas->number_of_salas); i++){

        if(arr_salas->salas[i].sala_type == INICIAL){

            Sala_inicial = &(arr_salas->salas[i]);
            
        }

    }

    return(Sala_inicial);

}

Salas salas_load_salas(){

    FILE* f;
    Salas loaded_salas;
    loaded_salas.salas = NULL;
    loaded_salas.number_of_salas = 0;
    
    //OBTENGO Salas.txt
    if((f=fopen("./data/Salas.txt", "r")) == NULL){

        printf("Error al cargar salas. Archivo de texto de salas no cargado.");
        exit(1);

    }

    else{

        //printf("\n##### SALAS #####\n");

        char current_row[512];  //FILA ACTUAL EN LECTURA

        while(fgets(current_row, 512, f) != NULL){ //LEO FILA A FILA

            if(current_row[0] != '\n'){

                //printf("\n\nFila leida: %s: ", current_row);

                //AÑADIMOS HUECO PARA LA NUEVA SALA
                loaded_salas.number_of_salas++;
                loaded_salas.salas = (Sala*)realloc(loaded_salas.salas, sizeof(Sala)*loaded_salas.number_of_salas);

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
                else{

                    printf("Formato incorrecto de tipo de sala.");
                    exit(1);

                }
                
                strcpy(sala_currentlyreading.sala_desc, strtok(NULL, "-")); //DESCRIPCIÓN
                if(sala_currentlyreading.sala_desc[strlen(sala_currentlyreading.sala_desc)-1] == '\n'){

                    sala_currentlyreading.sala_desc[strlen(sala_currentlyreading.sala_desc)-1] = '\0'; //ELIMINO EL \n DEL FINAL DE LÍNEA
                    
                }

                loaded_salas.salas[loaded_salas.number_of_salas-1] = sala_currentlyreading;

            }

        }

    }

    return loaded_salas;

}

Conns salas_load_conns(){

    FILE* f;
    Conns loaded_conns;
    loaded_conns.conns = NULL;
    loaded_conns.number_of_conns = 0;
    
    //OBTENGO Salas.txt
    if((f=fopen("./data/Conexiones.txt", "r")) == NULL){

        printf("Error al cargar salas. Archivo de texto de conexiones no cargado.");
        exit(1);

    }

    else{

        //printf("\n##### CONEXIONES #####\n");

        char current_row[512];  //FILA ACTUAL EN LECTURA

        while(fgets(current_row, 512, f) != NULL){ //LEO FILA A FILA

            if(current_row[0] != '\n'){

                //printf("\n\nFila leida: %s: ", current_row);

                //AÑADIMOS HUECO PARA LA NUEVA CONEXIÓN
                loaded_conns.number_of_conns++;
                loaded_conns.conns = (Conn*)realloc(loaded_conns.conns, sizeof(Conn)*loaded_conns.number_of_conns);

                Conn conn_currentlyreading;
                strcpy(conn_currentlyreading.conn_id, strtok(current_row, "-")); //ID
                strcpy(conn_currentlyreading.conn_sala_from_id, strtok(NULL, "-")); //ID FROM
                strcpy(conn_currentlyreading.conn_sala_to_id, strtok(NULL, "-")); //ID TO

                char blocked_string[11];
                strcpy(blocked_string, strtok(NULL, "-")); //ACTIVA O BLOQUEDA EN FORMATO STRING
                //ACTIVA O BLOQUEDA EN 0 SI ACTIVA Y 1 SI BLOQUEADA
                if(strcmp(blocked_string, "Bloqueada") == 0){

                    conn_currentlyreading.conn_block = 1;

                }
                else if(strcmp(blocked_string, "Activa") == 0){

                    conn_currentlyreading.conn_block = 0;

                }
                else{

                    printf("Formato incorrecto de bloqueo o activacion de conexion.");
                    exit(1);

                }
                
                strcpy(conn_currentlyreading.conn_id_cond, strtok(NULL, "-")); //ID DEL OBJETO O PUZLE PARA DESBLOQUEAR
                if(conn_currentlyreading.conn_id_cond[strlen(conn_currentlyreading.conn_id_cond)-1] == '\n'){

                    conn_currentlyreading.conn_id_cond[strlen(conn_currentlyreading.conn_id_cond)-1] = '\0'; //ELIMINO EL \n DEL FINAL DE LÍNEA
                    
                }

                loaded_conns.conns[loaded_conns.number_of_conns-1] = conn_currentlyreading;

            }

        }

    }

    return loaded_conns;

}