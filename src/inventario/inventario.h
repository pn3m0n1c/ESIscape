#ifndef INVENTARIO
#define INVENTARIO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
 * @par CABECERA
 * inv_load_items(char path[])
 * @pre PRECONDICION: path es una ruta válida a un fichero de objetos con formato Id-Nombre-Descripción-Localización
 * @post POSTCONDICION: Devuelve un Inventory* con todos los objetos cargados, o NULL si no se pudo abrir el fichero
 */
Inventory* inv_load_items(char path[]);

/**
 * @par CABECERA
 * inv_find_item_by_id(char wanted_id[5], Inventory *inv)
 * @pre PRECONDICION: wanted_id e inv preinicializados
 * @post POSTCONDICION: Devuelve un puntero al Item con ese ID, o NULL si no existe
 */
Item* inv_find_item_by_id(char wanted_id[5], Inventory *inv);

/**
 * @par CABECERA
 * inv_write_items(FILE *file, Inventory *all_items)
 * @pre PRECONDICION: file abierto en escritura, all_items preinicializado
 * @post POSTCONDICION: Escribe todos los items en el fichero con formato "OBJETO: Id-Localización". Devuelve 1 si éxito, 0 si error
 */
int inv_write_items(FILE *file, Inventory *all_items);

/**
 * @par CABECERA
 * inv_create_empty_inventory()
 * @pre PRECONDICION: ninguna
 * @post POSTCONDICION: Devuelve un Inventory vacío con slot NULL y size 0
 */
Inventory inv_create_empty_inventory();

/**
 * @par CABECERA
 * inv_itemcmp(Item item_1, Item item_2)
 * @pre PRECONDICION: item_1 e item_2 preinicializados
 * @post POSTCONDICION: Devuelve 0 si los dos items son iguales, 1 si no lo son
 */
int inv_itemcmp(Item item_1, Item item_2);

/**
 * @par CABECERA
 * inv_find_item(Item item, Inventory *inv)
 * @pre PRECONDICION: item e inv preinicializados
 * @post POSTCONDICION: Devuelve la posición del item en el inventario, o -1 si no se encuentra
 */
int inv_find_item(Item item, Inventory *inv);

/**
 * @par CABECERA
 * inv_add_item(Item item, Inventory *inv)
 * @pre PRECONDICION: item e inv preinicializados
 * @post POSTCONDICION: Intenta añadir un Item al Inventory. Devuelve 1 si lo añadió con éxito o 0 en otro caso
 */
int inv_add_item(Item item, Inventory *inv);

/**
 * @par CABECERA
 * inv_remove_item(Item item, Inventory *inv)
 * @pre PRECONDICION: item e inv preinicializados
 * @post POSTCONDICION: Elimina la primera ocurrencia del item en el inventario. Devuelve 1 si se eliminó, 0 si no se encontró
 */
int inv_remove_item(Item item, Inventory *inv);

/**
 * @par CABECERA
 * inv_free_inventory(Inventory *inv_to_free)
 * @pre PRECONDICION: inv_to_free preinicializado
 * @post POSTCONDICION: Libera la memoria del inventario
 */
void inv_free_inventory(Inventory *);

#endif
