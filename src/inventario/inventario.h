#ifndef INVENTARIO
#define INVENTARIO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @defgroup inventario Módulo Inventario
 * @brief Gestión del inventario y objetos del juego
 * @{
 */

#define MAX_ID_ITEM    5   /**< "OB01" + '\0' */
#define MAX_NAME_ITEM  21  /**< 20 caracteres + '\0' */
#define MAX_DESC_ITEM  100 /**< 99 caracteres + '\0' */
#define MAX_LOCATION   13  /**< "Inventario" o Id_sala (00) + '\0' */

/** @brief Representa un objeto del juego. */
typedef struct {
    char id[MAX_ID_ITEM];            /**< Identificador único del objeto */
    char name[MAX_NAME_ITEM];        /**< Nombre del objeto */
    char description[MAX_DESC_ITEM]; /**< Descripción del objeto */
    char location[MAX_LOCATION];     /**< Id_sala o "Inventario" */
} Item;

/** @brief Contenedor dinámico de items, usado como inventario de sala o jugador. */
typedef struct {
    Item *slot; /**< Array dinámico de slots */
    int size;   /**< Número de items actualmente almacenados */
} Inventory;

/**
 * @brief Lee los objetos del fichero indicado y los devuelve organizados en un Inventory.
 * @par CABECERA
 * inv_load_items(char path[])
 * @pre path es una ruta válida a un fichero de objetos con formato Id-Nombre-Descripción-Localización
 * @post Devuelve un Inventory* con todos los objetos cargados, o NULL si no se pudo abrir el fichero
 */
Inventory* inv_load_items(char path[]);

/**
 * @brief Busca un item en un inventario en base a su ID.
 * @par CABECERA
 * inv_find_item_by_id(char wanted_id[5], Inventory *inv)
 * @pre wanted_id e inv preinicializados
 * @post Devuelve un puntero al Item con ese ID, o NULL si no existe
 */
Item* inv_find_item_by_id(char wanted_id[5], Inventory *inv);

/**
 * @brief Escribe las líneas OBJETO de todos los items al fichero abierto recibido.
 * @par CABECERA
 * inv_write_items(FILE *file, Inventory *all_items)
 * @pre file abierto en escritura, all_items preinicializado
 * @post Escribe todos los items en el fichero con formato "OBJETO: Id-Localización". Devuelve 1 si éxito, 0 si error
 */
int inv_write_items(FILE *file, Inventory *all_items);

/**
 * @brief Crea un inventario vacío, útil para inicializar un jugador en una nueva partida.
 * @par CABECERA
 * inv_create_empty_inventory()
 * @pre ninguna
 * @post Devuelve un Inventory vacío con slot NULL y size 0
 */
Inventory inv_create_empty_inventory();

/**
 * @brief Compara dos items campo a campo, al igual que strcmp().
 * @par CABECERA
 * inv_itemcmp(Item item_1, Item item_2)
 * @pre item_1 e item_2 preinicializados
 * @post Devuelve 0 si los dos items son iguales, 1 si no lo son
 */
int inv_itemcmp(Item item_1, Item item_2);

/**
 * @brief Busca un item en un inventario y devuelve su posición.
 * @par CABECERA
 * inv_find_item(Item item, Inventory *inv)
 * @pre item e inv preinicializados
 * @post Devuelve la posición del item en el inventario, o -1 si no se encuentra
 */
int inv_find_item(Item item, Inventory *inv);

/**
 * @brief Intenta añadir un Item a un Inventory.
 * @par CABECERA
 * inv_add_item(Item item, Inventory *inv)
 * @pre item e inv preinicializados
 * @post Intenta añadir un Item al Inventory. Devuelve 1 si lo añadió con éxito o 0 en otro caso
 */
int inv_add_item(Item item, Inventory *inv);

/**
 * @brief Elimina la primera ocurrencia de un item en el inventario.
 * @par CABECERA
 * inv_remove_item(Item item, Inventory *inv)
 * @pre item e inv preinicializados
 * @post Elimina la primera ocurrencia del item en el inventario. Devuelve 1 si se eliminó, 0 si no se encontró
 */
int inv_remove_item(Item item, Inventory *inv);

/**
 * @brief Libera la memoria del inventario y de su array de slots.
 * @par CABECERA
 * inv_free_inventory(Inventory *inv_to_free)
 * @pre inv_to_free preinicializado
 * @post Libera la memoria del inventario
 */
void inv_free_inventory(Inventory *);

void inv_update_item_loc(Item* item, char location[13]);

/** @} */

#endif
