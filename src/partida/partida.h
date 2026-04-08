#ifndef PARTIDA

#define PARTIDA

#include "../salas/salas.h"
#include "../inventario/inventario.h"
#include "../puzles/puzles.h"

//GAMESTATE
typedef struct{

    int game_is_playing;
    Salas salas;
    Conns conns;
    Sala *current_sala;
    Inventory all_items;  /* Todos los objetos del juego (location actualizada en tiempo de ejecución) */
    Inventory player_inv; /* Subconjunto: objetos con location == "Inventario" */
    jugador player;
} Gamestate;
    Inventory *inventory;
    array_puz *arr_puzles;

} GameState;



//CABECERA: int partida_game_loop_start_menu(GameState *game_state)
//PRECONDICIÓN: game_state preinicializado
//POSTCONDICIÓN: Llama y muestra el menu de comienzo del bucle de juego, y ejecuta las acciones correspondientes si las hay, y devolviendo el índice del elemento elegido.
int partida_game_loop_start_menu(GameState*);

//CABECERA: void partida_game_start()
//PRECONDICIÓN:
//POSTCONDICIÓN: Es la función que comienza el juego
void partida_game_start();

#endif