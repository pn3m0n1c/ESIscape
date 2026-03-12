#ifndef UI

#define UI

//GRÁFICOS
extern const char graphic_game_nombre[604];

//ENTRADAS DE MENÚ
typedef struct{

    char nombre[128];
    void (*accion)();

} menu_entrada;

//MENUS
typedef struct{

    menu_entrada* entradas;
    int number_of_entradas;
    int type;

} menu;

//CABECERA void show_game_nombre()
//PRECONDICIÓN
//POSTCONDICIÓN imprime el nombre del juego "ESI-ESCAPE" en pantalla
void show_game_nombre();

//CABECERA: int crear_menu(menu menu_to_show)
//PRECONDICIÓN: menu_to_show preinicializado
//POSTCONDICIÓN: mostrará en pantalla el menú cargado en menu_to_show, y devolverá el índice de la opción elegida, y ejecutará una función si esta no está definida como nula.
int crear_menu(menu);

#endif