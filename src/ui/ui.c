#include "ui.h"
#include "../inventario/inventario.h"
#include "../salas/salas.h"

void ui_graphic_show_game_name(){

    char graphic_game_name[604] = "\n _______  _______  ___          _______  _______  _______  _______  _______  _______ \n|       ||       ||   |        |       ||       ||       ||   _   ||       ||       |\n|    ___||  _____||   |  ____  |    ___||  _____||       ||  |_|  ||    _  ||    ___|\n|   |___ | |_____ |   | |____| |   |___ | |_____ |       ||       ||   |_| ||   |___ \n|    ___||_____  ||   |        |    ___||_____  ||      _||       ||    ___||    ___|\n|   |___  _____| ||   |        |   |___  _____| ||     |_ |   _   ||   |    |   |___ \n|_______||_______||___|        |_______||_______||_______||__| |__||___|    |_______|\n";
    printf("%s\n", graphic_game_name);

}

void ui_graphic_show_screen_separation(){

    char graphic_screen_separation[65] = "________________________________________________________________";

    printf("\n\n%s\n\n", graphic_screen_separation);

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
    while(getchar() != '\n');
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

int ui_game_loop_start_menu(GameState *game_state){

    Menu menu_game_loop_start;
    int answer;

    Menu_Entry Menu_Entry_describir_sala;
    strcpy(Menu_Entry_describir_sala.name, "Describir sala");
    Menu_Entry_describir_sala.action = NULL;
    
    Menu_Entry Menu_Entry_examinar;
    strcpy(Menu_Entry_examinar.name, "Examinar (objetos y salidas)");
    Menu_Entry_examinar.action = NULL;
    
    Menu_Entry Menu_Entry_entrar_en_otra_sala;
    strcpy(Menu_Entry_entrar_en_otra_sala.name, "Entrar en otra sala");
    Menu_Entry_entrar_en_otra_sala.action = NULL;

    Menu_Entry Menu_Entry_coger_objeto;
    strcpy(Menu_Entry_coger_objeto.name, "Coger objeto");
    Menu_Entry_coger_objeto.action = NULL;

    Menu_Entry Menu_Entry_soltar_objeto;
    strcpy(Menu_Entry_soltar_objeto.name, "Soltar objeto");
    Menu_Entry_soltar_objeto.action = NULL;

    Menu_Entry Menu_Entry_inventario;
    strcpy(Menu_Entry_inventario.name, "Inventario");
    Menu_Entry_inventario.action = NULL;

    Menu_Entry Menu_Entry_usar_objeto;
    strcpy(Menu_Entry_usar_objeto.name, "Usar objeto");
    Menu_Entry_usar_objeto.action = NULL;

    Menu_Entry Menu_Entry_puzle_codigo;
    strcpy(Menu_Entry_puzle_codigo.name, "Resolver puzle / introducir codigo");
    Menu_Entry_puzle_codigo.action = NULL;

    Menu_Entry Menu_Entry_guardar_partida;
    strcpy(Menu_Entry_guardar_partida.name, "Guardar partida");
    Menu_Entry_guardar_partida.action = NULL;
    
    Menu_Entry Menu_Entry_volver;
    strcpy(Menu_Entry_volver.name, "Volver");
    Menu_Entry_volver.action = NULL;

    menu_game_loop_start.entries = (Menu_Entry*)malloc(sizeof(Menu_Entry)*10);
    menu_game_loop_start.entries[0] = Menu_Entry_describir_sala;
    menu_game_loop_start.entries[1] = Menu_Entry_examinar;
    menu_game_loop_start.entries[2] = Menu_Entry_entrar_en_otra_sala;
    menu_game_loop_start.entries[3] = Menu_Entry_coger_objeto;
    menu_game_loop_start.entries[4] = Menu_Entry_soltar_objeto;
    menu_game_loop_start.entries[5] = Menu_Entry_inventario;
    menu_game_loop_start.entries[6] = Menu_Entry_usar_objeto;
    menu_game_loop_start.entries[7] = Menu_Entry_puzle_codigo;
    menu_game_loop_start.entries[8] = Menu_Entry_guardar_partida;
    menu_game_loop_start.entries[9] = Menu_Entry_volver;
    menu_game_loop_start.number_of_entries = 10;

    ui_graphic_show_screen_separation();
    printf("\nSala: %s\n\n", game_state->current_sala->sala_name);

    switch(ui_menu_create(menu_game_loop_start)){

        case 0:
            ui_describe_sala(game_state->current_sala, game_state);
            break;

        case 9:
            game_state->game_is_playing = 0;
            break;

    }

    free(menu_game_loop_start.entries);

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
    printf("Descripción: %s\n", sala_to_describe->sala_desc);

    switch(sala_to_describe->sala_type){

        case INICIAL:
            printf("Te encuentras en la sala inicial.");
            ui_anykey_press();
            break;
        case NORMAL:
            printf("Te encuentras en una sala normal.");
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

void ui_show_inventory(Inventory* inv){

    ui_graphic_show_screen_separation();
    
    int i;
    for(i = 0; i < inv->size; i++){

        printf("Item %d\t%s\t%s\tDesc: %s\tLoc: %s\n", i, inv->slot[i].id, inv->slot[i].name, inv->slot[i].description, inv->slot[i].location);

    }

    ui_anykey_press();

}

/*
int ui_solve_puzle(){

    char input_player[50];

    fgets(input_player, 51, stdin);

}
*/