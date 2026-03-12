#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"

const char graphic_game_nombre[604] = "\n _______  _______  ___          _______  _______  _______  _______  _______  _______ \n|       ||       ||   |        |       ||       ||       ||   _   ||       ||       |\n|    ___||  _____||   |  ____  |    ___||  _____||       ||  |_|  ||    _  ||    ___|\n|   |___ | |_____ |   | |____| |   |___ | |_____ |       ||       ||   |_| ||   |___ \n|    ___||_____  ||   |        |    ___||_____  ||      _||       ||    ___||    ___|\n|   |___  _____| ||   |        |   |___  _____| ||     |_ |   _   ||   |    |   |___ \n|_______||_______||___|        |_______||_______||_______||__| |__||___|    |_______|\n";

int crear_menu(menu menu_to_show){

    int i, decision;

    printf("\n");

    //MOSTRAR ENTRADAS U OPCIONES
    for(i = 0; i < menu_to_show.number_of_entradas; i++){

        printf("%i: %s\n", i+1, menu_to_show.entradas[i].nombre);

    }

    //PEDIR UNA OPCIÓN AL USUARIO DENTRO DEL RANGO DE OPCIONES POSIBLES
    do{

        printf("\nElige dentro del rango de opciones > ");
        scanf("%i", &decision);
        decision--;

    } while(!((decision >= 0) && (decision <= menu_to_show.number_of_entradas-1)));
    
    //EJECUTAR UNA ACCIÓN SI ÉSTA NO ES NULA
    if(menu_to_show.entradas[decision].accion != NULL){

        menu_to_show.entradas[decision].accion();

    }

    //DEVOLVER EL ÍNDICE DE LA DECISIÓN TOMADA
    return decision;

}

//RESOLUCIÓN DE PUZLES, TOMARÁ COMO ARGUMENTO UNA ESTRUCTURA "PUZLE" Y DEVOLVERÁ 1 o 0 SI SE HA RESUELTO O NO
int resolver_puzle(){

    char input_jugador[50];

    fgets(input_jugador, 51, stdin);

}