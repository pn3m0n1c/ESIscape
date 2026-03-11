#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui/ui.h" //INCLUIDO SOLO PARA EL EJEMPLO, PROBABLEMENTE LOS MENUS LOS LLAMAREMOS FUERA DEL MAIN -Josemi

int main(){

    //EJEMPLO DE MENÚ, PROBABLEMENTE SE MOVERÁ A OTRO SITIO -Josemi

    menu menu_start;

    menu_entry menu_entry_nueva_partida;
    strcpy(menu_entry_nueva_partida.name, "Nueva partida");
    menu_entry_nueva_partida.action = NULL;

    menu_entry menu_entry_cargar_partida;
    strcpy(menu_entry_cargar_partida.name, "Cargar partida");
    menu_entry_cargar_partida.action = NULL;

    menu_entry menu_entry_salir;
    strcpy(menu_entry_salir.name, "Salir");
    menu_entry_salir.action = NULL;

    menu_start.entries = (menu_entry*)malloc(sizeof(menu_entry)*3);
    menu_start.entries[0] = menu_entry_nueva_partida;
    menu_start.entries[1] = menu_entry_cargar_partida;
    menu_start.entries[2] = menu_entry_salir;
    menu_start.number_of_entries = 3;

    printf("%s", graphic_game_name);
    printf("%i", create_menu(menu_start));

    return(0);

}