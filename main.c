#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui/ui.h" //INCLUIDO SOLO PARA EL EJEMPLO, PROBABLEMENTE LOS MENUS LOS LLAMAREMOS FUERA DEL MAIN -Josemi

int main(){

    //EJEMPLO DE MENÚ, PROBABLEMENTE SE MOVERÁ A OTRO SITIO -Josemi

    menu menu_start;

    menu_entrada menu_entrada_nueva_partida;
    strcpy(menu_entrada_nueva_partida.nombre, "Nueva partida");
    menu_entrada_nueva_partida.accion = NULL;

    menu_entrada menu_entrada_cargar_partida;
    strcpy(menu_entrada_cargar_partida.nombre, "Cargar partida");
    menu_entrada_cargar_partida.accion = NULL;

    menu_entrada menu_entrada_salir;
    strcpy(menu_entrada_salir.nombre, "Salir");
    menu_entrada_salir.accion = NULL;

    menu_start.entradas = (menu_entrada*)malloc(sizeof(menu_entrada)*3);
    menu_start.entradas[0] = menu_entrada_nueva_partida;
    menu_start.entradas[1] = menu_entrada_cargar_partida;
    menu_start.entradas[2] = menu_entrada_salir;
    menu_start.number_of_entradas = 3;

    printf("%s", graphic_game_nombre);
    printf("%i", crear_menu(menu_start));

    return(0);

}