#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui/ui.h" //INCLUIDO SOLO PARA EL EJEMPLO, PROBABLEMENTE LOS MENUS LOS LLAMAREMOS FUERA DEL MAIN -Josemi
#include "salas/salas.h" //INCLUIDO PARA PROBAR

int main(){

    load_salas("./data/Salas.txt");

    //EJEMPLO DE MENÚ, PROBABLEMENTE SE MOVERÁ A OTRO SITIO -Josemi

    Menu menu_start;

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

    graphic_show_game_name();
    printf("%i", ui_menu_create(menu_start));

    free(menu_start.entries);
    return(0);

}