#include <stdio.h>
#include "inventario.h"

/* Fichero Objetos.txt
- Identificador del objeto (Id_obj), 4 caracteres. 
- Nombre del objeto (Nomb_obj), 15 caracteres máximo.
- Descripción del objeto (Describ), 50 caracteres máximo.
- Localización del objeto (Localiz): Id_sala o Inventario.
*/

/* Parsea una línea "Id-Nombre-Descripcion-Localizacion" de Objetos.txt.
 * Usa el último guión para separar la localización, por si la descripción tiene guiones.
 * Devuelve 1 si ok, 0 si la línea tiene formato incorrecto. */
static int read_items() {
}

/* Crea un inventario vacío, útil para crear un jugador 
 * en una Nueva partida*/
Inventory create_empty_inventory(){
    Inventory inventory;

    inventory.slots = NULL;
    inventory.size = 0;

    return inventory;
}

/*Add item*/