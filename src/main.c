#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui/ui.h" //INCLUIDO SOLO PARA EL EJEMPLO, PROBABLEMENTE LOS MENUS LOS LLAMAREMOS FUERA DEL MAIN -Josemi
#include "salas/salas.h" //INCLUIDO PARA PROBAR

int main(){

    Salas* salas_loaded = load_salas();
    Conns* conns_loaded = load_conns();

    switch(ui_main_menu()){

        case 0:
            //NUEVA PARTIDA
            break;
        case 1:
            //CARGAR PARTIDA
            break;
        case 2:
            //SALIR
            printf("\nESI-Escape creado por Christian Romero Oliva, Javier Munoz Arillo y Jose Miguel Perez Tejero. 2026.\n\n");
            exit(0);
            break;

    }
    
    return(0);

}