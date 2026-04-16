#ifndef UI

#define UI

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../salas/salas.h"
#include "../inventario/inventario.h"
#include "../partida/partida.h"
#include "../puzles/puzles.h"

/**
 * @defgroup ui Módulo Interfaz de Usuario
 * @brief Gestión de los menus y de la interfaz de usuario y funciones útiles para mostrar y pedir información.
 * @{
 */

/** @brief Representa las entradas del menú. */
typedef struct{

    char name[128];
    void (*action)();

} Menu_Entry;

/** @brief Representa los menús al completo. */
typedef struct{

    Menu_Entry* entries;
    int number_of_entries;
    int type;

} Menu;

/**
 * @par CABECERA
 * void ui_clean_buffer()
 * @pre (Ninguna)
 * @post Limpia el buffer de entrada
 */
void ui_clean_buffer();

/**
 * @par CABECERA
 * void ui_graphic_show_game_name()
 * @pre (Ninguna)
 * @post Imprime el nombre del juego "ESI-ESCAPE" en pantalla
 */
void ui_graphic_show_game_name();

/**
 * @par CABECERA
 * void ui_graphic_show_screen_separation()
 * @pre (Ninguna)
 * @post Muestra en pantalla una separación horizontal
 */
void ui_graphic_show_screen_separation();

/**
 * @par CABECERA
 * int ui_menu_create(Menu menu_to_show)
 * @pre menu_to_show preinicializado
 * @post mostrará en pantalla el menú cargado en menu_to_show, y devolverá el índice de la opción elegida, y ejecutará una función si esta no está definida como nula.
 */
int ui_menu_create(Menu);

/**
 * @par CABECERA
 * int ui_confirmation(char text[200])
 * @pre (Ninguna)
 * @post Devuelve 1 si el usuario introduce S o s, y 0 si el usuario introduce N o n. Repetirá la solicitud hasta obtener una respuesta válida.
 */
int ui_confirmation(char text[200]);

/**
 * @par CABECERA
 * void ui_anykey_press()
 * @pre (Ninguna)
 * @post Hace que el programa espera una entrada del teclado para poder visualizar información sin que pase sola.
 */
void ui_anykey_press();

/**
 * @par CABECERA
 * void ui_exit_game(GameState *game_state, int save_to_jugadores)
 * @pre game_state y save_to_jugadores preinicializados
 * @post Muestra los créditos y cierra el juego, guardando cuando save_to_jugadores esté a 1 los objetos y códigos poseídos, además de liberar la memoria dinámica
 */
void ui_exit_game(GameState*, int);

/**
 * @par CABECERA
 * void ui_user_initial_menu(GameState* game_state)
 * @pre game_state preinicializado
 * @post Se le pide al usuario usuario y contraseña. Si se encuentran, se comienza con ese mismo jugador. Si no se encuentra un usuario con dicha contraseña, se ofrece hacer un registro con un nombre completo.
 */
void ui_user_initial_menu(GameState*);

/**
 * @par CABECERA
 * int ui_main_menu()
 * @pre (Ninguna)
 * @post Llama y muestra el main menu, llamando a las acciones correspondientes si las hay, y devolviendo el índice del elemento elegido.
 */
int ui_main_menu();

/**
 * @par CABECERA
 * void ui_describe_sala(Sala* sala_to_describe, GameState *game_state)
 * @pre sala_to_describe y game_state preinicializado
 * @post Describe la sala especificada por el argumento. Si se trata de la sala final, se da la enhorabuena al jugador, y se le pregunta si quiere volver al menu principal.
 */
void ui_describe_sala(Sala*, GameState*);

/**
 * @par CABECERA
 * void ui_show_filter_connections(Conns *conns, Salas *salas, char *sala_id_filter)
 * @pre Conns y sala_id_filter preinicializados
 * @post Muestra las conexiones que tienen como partida la sala con id sala_id_filter
 */
void ui_show_filter_connections(Conns*, Salas*, char*);

/**
 * @par CABECERA
 * void ui_show_filter_inventory(Inventory* inv, char *location_filter)
 * @pre Inventario al que apunta inv y location_filter preinicializados
 * @post Muestra en pantalla los elementos del inventario que esten en la localizacion especificada en location_filter
 */
void ui_show_filter_inventory(Inventory*, char*);

/**
 * @par CABECERA
 * void ui_examine_sala(Sala* sala_to_examine, GameState *game_state)
 * @pre sala_to_examine y game_state preinicializado
 * @post muestra los objetos y las salidas disponibles en la sala especificada
 */
void ui_examine_sala(Sala*, GameState*);

/**
 * @par CABECERA
 * void ui_enter_sala(GameState *game_state)
 * @pre game_state preinicializado
 * @post permitirá al jugador ir a otra sala si la salida hacia esta no está bloqueada
 */
void ui_enter_sala(GameState*);

/**
 * @par CABECERA
 * void ui_pick_drop_object(GameState* game_state, int pick)
 * @pre game_state preinicializado
 * @post permite al jugador añadir uno de los objetos de la sala actual a su inventario si pick 1, si es 0, suelta objetos
 */
void ui_pick_drop_object(GameState*, int);


/**
 * @par CABECERA
 * void ui_show_player_inventory(GameState* game_state)
 * @pre game_state preinicializado
 * @post muestra el inventario del jugador actualmente
 */
void ui_show_player_inventory(GameState*);

/**
 * @par CABECERA
 * void ui_use_object(GameState* game_state)
 * @pre game_state preinicializado
 * @post se usa el objeto que el usuario pida si se puede aplicar. Si no se puede aplicar, se informa al jugador
 */
void ui_use_object(GameState*);

/**
 * @par CABECERA
 * void ui_solve_puzzle(GameState* game_state)
 * @pre game_state preinicializado
 * @post le pide al usuario resolver uno de los puzles de la sala, y entonces, el jugador intentará resolverlo, y si acierta, se desbloquearan las salidas bloquedas que lo requirieran
 */
void ui_solve_puzzle(GameState*);

#endif