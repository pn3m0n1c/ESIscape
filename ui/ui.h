#ifndef UI

#define UI

//GRÁFICOS
extern const char graphic_game_name[604];

//ENTRADAS DE MENÚ
typedef struct{

    char name[128];
    void (*action)();

} menu_entry;

//MENUS
typedef struct{

    menu_entry* entries;
    int number_of_entries;
    int type;

} menu;

//CABECERA void show_game_name()
//PRECONDICIÓN
//POSTCONDICIÓN imprime el nombre del juego "ESI-ESCAPE" en pantalla
void show_game_name();

//CABECERA: int create_menu(menu menu_to_show)
//PRECONDICIÓN: menu_to_show preinicializado
//POSTCONDICIÓN: mostrará en pantalla el menú cargado en menu_to_show, y devolverá el índice de la opción elegida, y ejecutará una función si esta no está definida como nula.
int create_menu(menu);

#endif