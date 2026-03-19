#ifndef UI

#define UI

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../salas/salas.h"
#include "../inventario/inventario.h"

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

//GAMESTATE
typedef struct{

    int game_is_playing;
    Salas salas;
    Conns conns;
    Sala *current_sala;

} GameState;

//CABECERA void ui_graphic_show_game_name()
//PRECONDICIÓN
//POSTCONDICIÓN imprime el nombre del juego "ESI-ESCAPE" en pantalla
void ui_graphic_show_game_name();

//CABECERA: int ui_menu_create(menu menu_to_show)
//PRECONDICIÓN: menu_to_show preinicializado
//POSTCONDICIÓN: mostrará en pantalla el menú cargado en menu_to_show, y devolverá el índice de la opción elegida, y ejecutará una función si esta no está definida como nula.
int ui_menu_create(Menu);

//CABECERA: int ui_confirmation()
//PRECONDICIÓN:
//POSTCONDICIÓN: Devuelve 1 si el usuario introduce S o s, y 0 si el usuario introduce N o n. Repetirá la solicitud hasta obtener una respuesta válida.
int ui_confirmation();

//CABECERA: void ui_exit_game()
//PRECONDICIÓN: 
//POSTCONDICIÓN: Muestra los créditos y cierra el juego
void ui_exit_game();

//CABECERA: int ui_main_menu()
//PRECONDICIÓN: 
//POSTCONDICIÓN: Llama y muestra el main menu, llamando a las acciones correspondientes si las hay, y devolviendo el índice del elemento elegido.
int ui_main_menu();

//CABECERA: int ui_game_loop_start_menu(GameState *game_state)
//PRECONDICIÓN: game_state preinicializado
//POSTCONDICIÓN: Llama y muestra el menu de comienzo del bucle de juego, y ejecuta las acciones correspondientes si las hay, y devolviendo el índice del elemento elegido.
int ui_game_loop_start_menu(GameState*);

//CABECERA: void ui_ask_for_player_info()
//PRECONDICIÓN:
//POSTCONDICIÓN: Lee la información del jugador, y posteriormente llama a la función de creado de jugadores de su módulo correspondiente
void ui_ask_for_player_info();

//CABECERA: void ui_describe_sala(Sala* sala_to_describe, GameState *game_state)
//PRECONDICIÓN: sala_to_describe y game_state preinicializado
//POSTCONDICIÓN: Describe la sala especificada por el argumento. Si se trata de la sala final, se da la enhorabuena al jugador, y se le pregunta si quiere volver al menu principal
void ui_describe_sala(Sala*, GameState*);

//CABECERA: void ui_show_inventory(Inventory* inv)
//PRECONDICIÓN: Inventario al que apunta inv preinicializado
//POSTCONDICIÓN: Muestra en pantalla los elementos del inventario
void ui_show_inventory(Inventory*);

//CABECERA: void ui_game_start()
//PRECONDICIÓN
//POSTCONDICIÓN: Es la función que comienza
void ui_game_start();

#endif