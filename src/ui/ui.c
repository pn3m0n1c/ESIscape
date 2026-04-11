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

    int i, k, is_number = 1, decision_to_number;
    char decision[128];

    //MOSTRAR ENTRIES U OPCIONES
    for(i = 0; i < menu_to_show.number_of_entries; i++){

        printf("%i:\t%s\n", i+1, menu_to_show.entries[i].name);

    }

    //PEDIR UNA OPCIÓN AL USUARIO DENTRO DEL RANGO DE OPCIONES POSIBLES
    
    do{

        printf("\nElige dentro del rango de opciones > ");

        fgets(decision, 128, stdin);

        decision_to_number = atoi(decision);
        decision_to_number--;


    } while(!((decision_to_number >= 0) && (decision_to_number <= menu_to_show.number_of_entries-1)));
    
    //EJECUTAR UNA ACCIÓN SI ÉSTA NO ES NULA
    if(menu_to_show.entries[decision_to_number].action != NULL){

        menu_to_show.entries[decision_to_number].action();

    }

    //DEVOLVER EL ÍNDICE DE LA DECISIÓN TOMADA
    return decision_to_number;

}

int ui_confirmation(){

    char answer_char;
    do{

        printf("\n(S/N) > ");
        scanf(" %c", &answer_char);
        getchar();
        answer_char = tolower(answer_char);

    }while(!(answer_char == 's' || answer_char == 'n'));

    return(answer_char == 's');

}

void ui_anykey_press(){

    printf("\n\nPulsa cualquier tecla... ");
    getchar();

}

void ui_exit_game(GameState *game_state, int save_to_jugadores){

    int obj_playersave_idx;

    if(save_to_jugadores && game_state->structs_already_loaded){

        strcpy(((game_state->player)->Inventario_como_string), "\0");

        for(obj_playersave_idx = 0; obj_playersave_idx<((game_state->all_items)->size); obj_playersave_idx++){

            if(strcmp(((game_state->all_items)->slot)[obj_playersave_idx].location, "Inventario") == 0){

                strcat(((game_state->player)->Inventario_como_string), ((game_state->all_items)->slot)[obj_playersave_idx].id);
                strcat(((game_state->player)->Inventario_como_string), "-");

            }

        }

        if(((game_state->player)->Inventario_como_string)[strlen(((game_state->player)->Inventario_como_string))-1] == '-'){

            ((game_state->player)->Inventario_como_string)[strlen(((game_state->player)->Inventario_como_string))-1] = '\0';

        }

        guardar_jugador(game_state, "./data/Jugadores.txt");

    }

    printf("\nESI-Escape creado por Christian Romero Oliva, Javier Munoz Arillo y Jose Miguel Perez Tejero | 2026\n\n");
    exit(0);

}

void ui_user_initial_menu(GameState* game_state){

    //printf("\x1B[2J\x1B[H"); //ANSI Escape Code para vaciar la pantalla

    char nombre_acceso[11];
    char password[9];
    char regis_nombrecompleto[21];

    ui_graphic_show_screen_separation();

    printf(" - REGISTRO / INICIO DE SESION - \n\n");

    printf("Introduce tu usuario > ");
    fgets(nombre_acceso, 11, stdin);
    if(nombre_acceso[strlen(nombre_acceso)-1] == '\n'){

        nombre_acceso[strlen(nombre_acceso)-1] = '\0';

    }
    
    else{
    
        ui_clean_buffer();
        
    }

    printf("Introduce tu contrasena > ");
    fgets(password, 9, stdin);
    if(password[strlen(password)-1] == '\n'){

        password[strlen(password)-1] = '\0';

    }
    
    else{
    
        ui_clean_buffer();
        
    }

    //VEMOS SI EL JUGADOR YA ESTÁ REGISTRADO

    int playeridx, encontrado = 0;

    for(playeridx = 0; playeridx < game_state->players->total_leidos; playeridx++){

        if(strcmp((game_state->players->arr_jugadores)[playeridx].Jugador, nombre_acceso) == 0 && strcmp((game_state->players->arr_jugadores)[playeridx].Contrasena, password) == 0){

            encontrado = 1;
            game_state->player = &((game_state->players->arr_jugadores)[playeridx]);

        }

    }

    if(encontrado){

        printf("\nJugador con contrasena ENCONTRADO!!");

    }

    else{

        printf("\nJugador NO ENCONTRADO!!!\n\nTe quieres registrar?");

        if(ui_confirmation()){

            printf("\nIntroduce tu nombre completo > ");
            fgets(regis_nombrecompleto, 21, stdin);
            if(regis_nombrecompleto[strlen(regis_nombrecompleto)-1] == '\n'){

                regis_nombrecompleto[strlen(regis_nombrecompleto)-1] = '\0';

            }
            
            else{
            
                ui_clean_buffer();
                
            }

            registrar_jugador(game_state, nombre_acceso, password, regis_nombrecompleto);
            game_state->player = &((game_state->players)->arr_jugadores[(game_state->players)->total_leidos - 1]);
            guardar_jugador(game_state, "./data/Jugadores.txt");

        }

        else{

            ui_exit_game(game_state, 0);

        }

    }

    printf("\nTe damos la bienvenida a:\n");

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

void ui_describe_sala(Sala* sala_to_describe, GameState *game_state){

    ui_graphic_show_screen_separation();

    printf("Sala: %s\n", sala_to_describe->sala_name);
    printf(" - Descripcion: %s\n", sala_to_describe->sala_desc);

    switch(sala_to_describe->sala_type){

        case INICIAL:
            printf(" - Te encuentras en la sala inicial.");
            ui_anykey_press();
            break;
        case NORMAL:
            printf(" - Te encuentras en una sala normal.");
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

                ui_exit_game(game_state, 1);

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
                strcat(condicion_texto, " | Condicion: ");
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


void ui_show_filter_puzles(array_puz* arr_puzles, char *location_filter){

    int i, count = 0;

    for(i = 0; i < arr_puzles->total_leidos; i++){

        if(strcmp((arr_puzles->unidad)[i].id_sala, location_filter) == 0 || strcmp(location_filter, "") == 0){

            count++;
            printf(" - Puzle %s: %s\t | Tipo: %s\n", (arr_puzles->unidad)[i].id_puzle, (arr_puzles->unidad)[i].nomb_puz, (arr_puzles->unidad)[i].tipo);

        }
        
    }

    if(count == 0){

        printf(" - VACIO - \n");

    }

}

void ui_examine_sala(Sala* sala_to_examine, GameState *game_state){

    ui_graphic_show_screen_separation();

    printf("OBJETOS EN LA SALA ACTUAL: #################\n\n");

    ui_show_filter_inventory(game_state->all_items, sala_to_examine->sala_id);
    
    printf("\n\nSALIDAS DE LA SALA ACTUAL: #################\n\n");

    ui_show_filter_connections(&(game_state->conns), &(game_state->salas), sala_to_examine->sala_id);

    ui_anykey_press();

}

void ui_enter_sala(GameState *game_state){

    ui_graphic_show_screen_separation();

    printf("\nSALIDAS DE LA SALA ACTUAL: #################\n\n");

    ui_show_filter_connections(&(game_state->conns), &(game_state->salas), game_state->current_sala->sala_id);

    int salida_exists_here = 0, skip_enter_sala = 0, i;
    Conn salida_destino;
    char sala_id_destino[3];

    printf("\n\nIntroduce el ID de la sala a la que quieres dirigirte (escribe \'n\' para salir de esta decision) > ");
    
    fgets(sala_id_destino, 3, stdin);
    
    if(sala_id_destino[strlen(sala_id_destino)-1] == '\n'){

        sala_id_destino[strlen(sala_id_destino)-1] = '\0';

    }
    
    else{
    
        ui_clean_buffer();
        
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

            if(!game_update_sala(game_state, salida_destino)){

                printf("\n\nSALIDA BLOQUEADA!\nSe requiere %s.", salida_destino.conn_id_cond);
                ui_anykey_press();

            }
        }
        else{

            printf("\n\nNO HAY NINGUNA SALIDA A ESA SALA, O NO EXISTE!");
            ui_anykey_press();

        }

    }

}

void ui_pick_drop_object(GameState* game_state, int pick){

    ui_graphic_show_screen_separation();

    char id_from[256];
    char id_to[256];

    if(pick){
        strcpy(id_from, game_state->current_sala->sala_id);
        strcpy(id_to, "Inventario");
    }
    else{
        strcpy(id_from, "Inventario");
        strcpy(id_to, game_state->current_sala->sala_id);
    }

    if(pick) printf("OBJETOS EN LA SALA ACTUAL: #################\n\n");
    else printf("OBJETOS EN TU INVENTARIO: #################\n\n");

    ui_show_filter_inventory(game_state->all_items, id_from);

    char id_object_to_pick[5];
    Item *object_found;
    int skip_dothethings_object = 0;

    if(pick) printf("\nIntroduce el ID del objeto que quieres agarrar (escribe \'n\' para salir de esta decision) > ");
    else printf("\nIntroduce el ID del objeto que quieres soltar (escribe \'n\' para salir de esta decision) > ");

    fgets(id_object_to_pick, 5, stdin);

    if(id_object_to_pick[strlen(id_object_to_pick)-1] == '\n'){

        id_object_to_pick[strlen(id_object_to_pick)-1] = '\0';

    }

    else{

        ui_clean_buffer();

    }

    if(strcmp(id_object_to_pick, "n") == 0 || strcmp(id_object_to_pick, "") == 0){

        skip_dothethings_object = 1;

    }

    if(!skip_dothethings_object){

        object_found = inv_find_item_by_id(id_object_to_pick, game_state->all_items);

        if(object_found == NULL){

            if(pick) printf("\n\nESTE OBJETO NO EXISTE!");
            else printf("\n\nNO TIENES ESTE OBJETO!");
            ui_anykey_press();

        }

        else{

            if(strcmp(object_found->location, id_from) != 0){

                if(pick) printf("\n\nESTE OBJETO NO ESTA EN ESTA SALA!");
                else printf("\n\nESTE OBJETO NO EXISTE!");
                ui_anykey_press();

            }

            else{

                strcpy(object_found->location, id_to);

            }

        }

    }

}

void ui_show_player_inventory(GameState* game_state){

    ui_graphic_show_screen_separation();

    printf("INVENTARIO: #################\n\n");

    ui_show_filter_inventory(game_state->all_items, "Inventario");

    ui_anykey_press();

}

void ui_use_object(GameState* game_state){

    ui_graphic_show_screen_separation();

    printf("OBJETOS EN TU INVENTARIO: #################\n\n");
    ui_show_filter_inventory(game_state->all_items, "Inventario");

    char id_object_to_use[5];
    Item *object_found;
    int skip_dothethings_object = 0;

    printf("\nIntroduce el ID del objeto que quieres usar (escribe \'n\' para salir de esta decision) > ");

    fgets(id_object_to_use, 5, stdin);

    if(id_object_to_use[strlen(id_object_to_use)-1] == '\n'){

        id_object_to_use[strlen(id_object_to_use)-1] = '\0';

    }

    else{

        ui_clean_buffer();

    }

    if(strcmp(id_object_to_use, "n") == 0 || strcmp(id_object_to_use, "") == 0){

        skip_dothethings_object = 1;

    }

    if(!skip_dothethings_object){

        object_found = inv_find_item_by_id(id_object_to_use, game_state->all_items);

        if(object_found == NULL){

            printf("\n\nNO EXISTE ESTE OBJETO!");
            ui_anykey_press();

        }

        else{

            int i, vecesaplicadas = 0;

            if(strcmp(object_found->location, "Inventario") != 0){

                printf("\n\nNO TIENES ESTE OBJETO!");
                ui_anykey_press();

            }

            else{

                printf("\n\n");

                for(i = 0; i < (game_state->conns).number_of_conns; i++){

                    if(strcmp(((game_state->conns).conns)[i].conn_id_cond, object_found->id) == 0 && strcmp(((game_state->conns).conns)[i].conn_sala_from_id, game_state->current_sala->sala_id) == 0){

                        vecesaplicadas++;
                        if(((game_state->conns).conns)[i].conn_block == 1){

                            Sala *sala_destino = salas_get_sala_from_id(((game_state->conns).conns)[i].conn_sala_to_id, &(game_state->salas));

                            ((game_state->conns).conns)[i].conn_block = 0;
                            printf("- La salida a la sala %s (ID: %s) HA SIDO DESBLOQUEADA!\n", sala_destino->sala_name, sala_destino->sala_id);

                        }

                    }

                }

                if(vecesaplicadas == 0){

                    printf("ESTE OBJETO NO LO PUEDES APLICAR AQUI!");

                }

                ui_anykey_press();

            }

        }

    }

}

void ui_solve_puzzle(GameState* game_state){

    ui_graphic_show_screen_separation();

    printf("PUZLES EN ESTA SALA: #################\n\n");
    ui_show_filter_puzles(game_state->arr_puzles, game_state->current_sala->sala_id);

    char id_puzzle_to_solve[4];
    puzle *puzzle_found = NULL;
    int skip_dothethings_puzle = 0;

    printf("\nIntroduce el ID del puzle que quieres resolver (escribe \'n\' para salir de esta decision) > ");

    fgets(id_puzzle_to_solve, 4, stdin);

    if(id_puzzle_to_solve[strlen(id_puzzle_to_solve)-1] == '\n'){

        id_puzzle_to_solve[strlen(id_puzzle_to_solve)-1] = '\0';

    }
    
    else{

        ui_clean_buffer();

    }

    if(strcmp(id_puzzle_to_solve, "n") == 0 || strcmp(id_puzzle_to_solve, "") == 0){

        skip_dothethings_puzle = 1;

    }

    if(!skip_dothethings_puzle){

        int puzidx;

        for(puzidx = 0; puzidx < game_state->arr_puzles->total_leidos; puzidx++){

            if(strcmp((game_state->arr_puzles->unidad)[puzidx].id_puzle, id_puzzle_to_solve) == 0){

                puzzle_found = &((game_state->arr_puzles->unidad)[puzidx]);

            }

        }

        if(puzzle_found == NULL){

            printf("\n\nNO EXISTE ESE PUZLE!");
            ui_anykey_press();

        }

        else{

            int i;

            if(strcmp(puzzle_found->id_sala, game_state->current_sala->sala_id) != 0){

                printf("\n\nESE PUZLE NO SE ENCUENTRA EN ESTA SALA!");
                ui_anykey_press();

            }

            else if(puzzle_found->resuelto == 1){

                printf("\n\nESE PUZLE YA ESTA RESUELTO!");
                ui_anykey_press();

            }

            else{

                printf("\n");

                printf("%s\n\nIntroduce la solucion > ", puzzle_found->descrip);

                char soluc[51];
                fgets(soluc, 51, stdin);
                if(soluc[strlen(soluc)-1] == '\n'){

                    soluc[strlen(soluc)-1] = '\0';
                    
                }

                else{

                    ui_clean_buffer();

                }

                printf("\n\n");

                if(strcmp(soluc, puzzle_found->sol) != 0){

                    printf("- SOLUCION INCORRECTA.\n");

                }

                else{

                    for(i = 0; i < (game_state->conns).number_of_conns; i++){

                        if(strcmp(((game_state->conns).conns)[i].conn_id_cond, puzzle_found->id_puzle) == 0){

                            if(((game_state->conns).conns)[i].conn_block == 1){

                                Sala *sala_destino = salas_get_sala_from_id(((game_state->conns).conns)[i].conn_sala_to_id, &(game_state->salas));

                                ((game_state->conns).conns)[i].conn_block = 0;
                                printf("- La salida a la sala %s (ID: %s) HA SIDO DESBLOQUEADA!\n", sala_destino->sala_name, sala_destino->sala_id);

                                puzzle_found->resuelto = 1;

                            }

                        }

                    }

                }

                ui_anykey_press();

            }

        }

    }

}