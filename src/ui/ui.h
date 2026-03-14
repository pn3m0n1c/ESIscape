#ifndef UI

#define UI

#include "../salas/salas.h"

//ENTRADAS DE MENÚ
typedef struct{

    char name[128];
    void (*action)();

} Menu_Entry;

//MENUS
typedef struct{

    Menu_Entry* entries;
    int number_of_entries;
    int type;

} Menu;

//CABECERA void graphic_show_game_name()
//PRECONDICIÓN
//POSTCONDICIÓN imprime el nombre del juego "ESI-ESCAPE" en pantalla
void graphic_show_game_name();

//CABECERA: int ui_menu_create(menu menu_to_show)
//PRECONDICIÓN: menu_to_show preinicializado
//POSTCONDICIÓN: mostrará en pantalla el menú cargado en menu_to_show, y devolverá el índice de la opción elegida, y ejecutará una función si esta no está definida como nula.
int ui_menu_create(Menu);

//CABECERA: void ui_exit_game()
//PRECONDICIÓN: 
//POSTCONDICIÓN: Muestra los créditos y cierra el juego
void ui_exit_game();

//CABECERA: void ui_main_menu()
//PRECONDICIÓN: 
//POSTCONDICIÓN: Llama y muestra el main menu, llamando a las acciones correspondientes
void ui_main_menu();

//CABECERA: int game_loop_start_menu()
//PRECONDICIÓN: 
//POSTCONDICIÓN: Llama y muestra el menu de comienzo del bucle de juego, y devuelve el índice de la opción elegida.
int game_loop_start_menu();

//CABECERA: void ui_ask_for_player_info()
//PRECONDICIÓN:
//POSTCONDICIÓN: Lee la información del jugador, y posteriormente llama a la función de creado de jugadores de su módulo correspondiente
void ui_ask_for_player_info();

//CABECERA: void describe_sala(Sala* sala_to_describe)
//PRECONDICIÓN: Sala preinicializado
//POSTCONDICIÓN: Describe la sala especificada por el argumento. Si se trata de la sala final, se da la enhorabuena al jugador, y se le pregunta si quiere volver al menu principal
void describe_sala(Sala*);

#endif