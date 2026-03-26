#include "ui.h"

void ui_clean_buffer(){

    int c;
    while((c = getchar()) != '\n' && c != EOF);

}

void ui_graphic_show_game_name(){

    char graphic_game_name[604] = "\n _______  _______  ___          _______  _______  _______  _______  _______  _______ \n|       ||       ||   |        |       ||       ||       ||   _   ||       ||       |\n|    ___||  _____||   |  ____  |    ___||  _____||       ||  |_|  ||    _  ||    ___|\n|   |___ | |_____ |   | |____| |   |___ | |_____ |       ||       ||   |_| ||   |___ \n|    ___||_____  ||   |        |    ___||_____  ||      _||       ||    ___||    ___|\n|   |___  _____| ||   |        |   |___  _____| ||     |_ |   _   ||   |    |   |___ \n|_______||_______||___|        |_______||_______||_______||__| |__||___|    |_______|\n";
    printf("%s\n", graphic_game_name);

}

void ui_graphic_show_screen_separation(){

    char graphic_screen_separation[65] = "________________________________________________________________";

    printf("\n%s\n\n", graphic_screen_separation);

}

int ui_menu_create(Menu menu_to_show){

    int i, decision;

    //MOSTRAR ENTRIES U OPCIONES
    for(i = 0; i < menu_to_show.number_of_entries; i++){

        printf("%i:\t%s\n", i+1, menu_to_show.entries[i].name);

    }

    //PEDIR UNA OPCIÓN AL USUARIO DENTRO DEL RANGO DE OPCIONES POSIBLES
    do{

        printf("\nElige dentro del rango de opciones > ");
        scanf("%i", &decision);
        decision--;

    } while(!((decision >= 0) && (decision <= menu_to_show.number_of_entries-1)));
    
    //EJECUTAR UNA ACCIÓN SI ÉSTA NO ES NULA
    if(menu_to_show.entries[decision].action != NULL){

        menu_to_show.entries[decision].action();

    }

    //DEVOLVER EL ÍNDICE DE LA DECISIÓN TOMADA
    return decision;

}

int ui_confirmation(){

    char answer_char;
    do{

        printf("\n(S/N) > ");
        scanf(" %c", &answer_char);
        answer_char = tolower(answer_char);

    }while(!(answer_char == 's' || answer_char == 'n'));

    return(answer_char == 's');

}

void ui_anykey_press(){

    printf("\n\nPulsa cualquier tecla... ");
    getchar();

}

void ui_exit_game(){

    printf("\nESI-Escape creado por Christian Romero Oliva, Javier Munoz Arillo y Jose Miguel Perez Tejero | 2026\n\n");
    exit(0);

}

int ui_main_menu(){

    Menu menu_start;
    int answer;

    Menu_Entry Menu_Entry_nueva_partida;
    strcpy(Menu_Entry_nueva_partida.name, "Nueva partida");
    Menu_Entry_nueva_partida.action = NULL;

    Menu_Entry Menu_Entry_cargar_partida;
    strcpy(Menu_Entry_cargar_partida.name, "Cargar partida");
    Menu_Entry_cargar_partida.action = NULL;

    Menu_Entry Menu_Entry_salir;
    strcpy(Menu_Entry_salir.name, "Salir");
    Menu_Entry_salir.action = NULL;

    menu_start.entries = (Menu_Entry*)malloc(sizeof(Menu_Entry)*3);
    menu_start.entries[0] = Menu_Entry_nueva_partida;
    menu_start.entries[1] = Menu_Entry_cargar_partida;
    menu_start.entries[2] = Menu_Entry_salir;
    menu_start.number_of_entries = 3;

    ui_graphic_show_screen_separation();
    ui_graphic_show_game_name();
    
    answer = ui_menu_create(menu_start);
    free(menu_start.entries);

    return(answer);

}

void ui_ask_for_player_info(){

    ui_graphic_show_screen_separation();

    char InfoPlayer_FullName[21];
    char InfoPlayer_AccessName[11];
    char InfoPlayer_Password[9];

    printf("Introduce el nombre completo para el jugador: ");
    fgets(InfoPlayer_FullName, 21, stdin);
    printf("Introduce el nombre de acceso para el jugador: ");
    fgets(InfoPlayer_AccessName, 11, stdin);
    printf("Introduce una contrasena para el jugador: ");
    fgets(InfoPlayer_Password, 9, stdin);
    
}

void ui_describe_sala(Sala* sala_to_describe, GameState *game_state){

    ui_graphic_show_screen_separation();

    printf("Sala: %s\n", sala_to_describe->sala_name);
    printf(" - Descripción: %s\n", sala_to_describe->sala_desc);

    switch(sala_to_describe->sala_type){

        case INICIAL:
            printf(" - Te encuentras en la sala inicial.");
            ui_clean_buffer();
            ui_anykey_press();
            break;
        case NORMAL:
            printf(" - Te encuentras en una sala normal.");
            ui_clean_buffer();
            ui_anykey_press();
            break;
        case SALIDA:
            printf("\n##     ## ####  ######  ########  #######  ########  ####    ###    #### \n##     ##  ##  ##    ##    ##    ##     ## ##     ##  ##    ## ##   #### \n##     ##  ##  ##          ##    ##     ## ##     ##  ##   ##   ##  #### \n##     ##  ##  ##          ##    ##     ## ########   ##  ##     ##  ##  \n ##   ##   ##  ##          ##    ##     ## ##   ##    ##  #########      \n  ## ##    ##  ##    ##    ##    ##     ## ##    ##   ##  ##     ## #### \n   ###    ####  ######     ##     #######  ##     ## #### ##     ## #### ");
            printf("\n\nHas completado ESI-Escape!!!");
            printf("\nQuieres regresar al menu principal?");
            
            if(ui_confirmation()){

                game_state->game_is_playing = 0;

            }

            else{

                ui_exit_game();

            }

            break;

    }

}

void ui_show_filter_connections(Conns *conns, Salas *salas, char *sala_id_filter){

    int i;
    for(i = 0; i<conns->number_of_conns; i++){

        if(strcmp((conns->conns)[i].conn_sala_from_id, sala_id_filter) == 0){

            Sala *sala_destino = salas_get_sala_from_id((conns->conns)[i].conn_sala_to_id, salas);

            char condicion_texto[128] = "";
            if(strcmp((conns->conns)[i].conn_id_cond, "0") != 0){
                
                char *bloqueado_texto = ((conns->conns)[i].conn_block) ? " | Salida BLOQUEADA\t" : " | Salida no bloqueada\t";
                strcat(condicion_texto, bloqueado_texto);
                strcat(condicion_texto, " | IDcondicion_secambiaraporloquees: ");
                strcat(condicion_texto, (conns->conns)[i].conn_id_cond);
            }

            printf(" - Salida a: %s (ID DE SALA: \"%s\")\t%s\n", sala_destino->sala_name, sala_destino->sala_id, condicion_texto);

        }

    }

}

void ui_show_filter_inventory(Inventory* inv, char *location_filter){

    int i, count = 0;

    for(i = 0; i < inv->size; i++){

        if(strcmp(inv->slot[i].location, location_filter) == 0 || strcmp(location_filter, "") == 0){

            count++;
            printf(" - Item %s - %s\t | Desc: %s\n", inv->slot[i].id, inv->slot[i].name, inv->slot[i].description);

        }
        
    }

    if(count == 0){

        printf(" - VACIO - \n");

    }

}

void ui_examine_sala(Sala* sala_to_examine, GameState *game_state){

    ui_graphic_show_screen_separation();

    printf("OBJETOS: #################\n\n");

    ui_show_filter_inventory(game_state->inventory, sala_to_examine->sala_id);
    
    printf("\n\nSALIDAS: #################\n\n");

    ui_show_filter_connections(&(game_state->conns), &(game_state->salas), sala_to_examine->sala_id);

    ui_clean_buffer();
    ui_anykey_press();

}

void ui_enter_sala(GameState *game_state){

    ui_graphic_show_screen_separation();

    printf("\n\nSALIDAS: #################\n\n");

    ui_show_filter_connections(&(game_state->conns), &(game_state->salas), game_state->current_sala->sala_id);

    int salida_exists_here = 0, skip_enter_sala = 0, i;
    Conn salida_destino;
    char sala_id_destino[3];

    printf("\n\nIntroduce el ID de la sala a la que quieres dirigirte (escribe \'n\' para salir de esta decision) > ");
    ui_clean_buffer();

    fgets(sala_id_destino, 3, stdin);
    if(sala_id_destino[strlen(sala_id_destino)-1] == '\n'){

        sala_id_destino[strlen(sala_id_destino)-1] = '\0';

    }

    if(strcmp(sala_id_destino, "n") == 0 || strcmp(sala_id_destino, "") == 0){

        skip_enter_sala = 1;

    }

    if(!skip_enter_sala){

        for(i = 0; i<((game_state->conns).number_of_conns); i++){

            //COMPROBAMOS SI LA SALIDA POR LA QUE QUEREMOS SALIR EXISTE
            if(strcmp(((game_state->conns).conns)[i].conn_sala_from_id, game_state->current_sala->sala_id) == 0 && 
            strcmp(((game_state->conns).conns)[i].conn_sala_to_id, sala_id_destino) == 0){

                salida_exists_here = 1;
                salida_destino = ((game_state->conns).conns)[i];

            }

        }

        if(salida_exists_here){

            if(salida_destino.conn_block){

                printf("\n\nSALIDA BLOQUEADA!\nSe requiere %s. (QUIZAS SE PONDRA MAS BONITA LA CONDICION)", salida_destino.conn_id_cond);
                ui_anykey_press();

            }
            else{

                game_state->current_sala = salas_get_sala_from_id(salida_destino.conn_sala_to_id, &(game_state->salas));

            }

        }
        else{

            printf("\n\nNO HAY NINGUNA SALIDA A ESA SALA, O NO EXISTE!");
            ui_anykey_press();

        }

    }

}

void ui_show_player_inventory(GameState* game_state){

    ui_graphic_show_screen_separation();

    printf("INVENTARIO: #################\n\n");

    ui_show_filter_inventory(game_state->inventory, "Inventario");

    ui_clean_buffer();
    ui_anykey_press();

}

/*
int ui_solve_puzle(){

    char input_player[50];

    fgets(input_player, 51, stdin);

}
*/