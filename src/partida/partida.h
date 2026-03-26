#ifndef PARTIDA_H

#include "../salas/salas.h"
#include "../jugador/jugador.h"
#include "../inventario/inventario.h"


typedef struct{
    int game_is_playing;
    Salas salas;
    Conns conns;
    Sala *current_sala;
    Inventory all_items;  /* Todos los objetos del juego (location actualizada en tiempo de ejecución) */
    Inventory player_inv; /* Subconjunto: objetos con location == "Inventario" */
    jugador player;
} Gamestate;

#endif