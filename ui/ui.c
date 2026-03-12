#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"

const char graphic_game_name[604] = "\n _______  _______  ___          _______  _______  _______  _______  _______  _______ \n|       ||       ||   |        |       ||       ||       ||   _   ||       ||       |\n|    ___||  _____||   |  ____  |    ___||  _____||       ||  |_|  ||    _  ||    ___|\n|   |___ | |_____ |   | |____| |   |___ | |_____ |       ||       ||   |_| ||   |___ \n|    ___||_____  ||   |        |    ___||_____  ||      _||       ||    ___||    ___|\n|   |___  _____| ||   |        |   |___  _____| ||     |_ |   _   ||   |    |   |___ \n|_______||_______||___|        |_______||_______||_______||__| |__||___|    |_______|\n";

int ui_crear_menu(menu menu_to_show){

    int i, decision;

    printf("\n");

    //MOSTRAR entries U OPCIONES
    for(i = 0; i < menu_to_show.number_of_entries; i++){

        printf("%i: %s\n", i+1, menu_to_show.entries[i].name);

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

//PEDIR INFORMACION DEL JUGADOR
void ui_pedir_info_jugador(){



}

//RESOLUCIÓN DE PUZLES, TOMARÁ COMO ARGUMENTO UNA ESTRUCTURA "PUZLE" Y DEVOLVERÁ 1 o 0 SI SE HA RESUELTO O NO
int ui_resolver_puzle(){

    char input_jugador[50];

    fgets(input_jugador, 51, stdin);

}