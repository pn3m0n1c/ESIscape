#ifndef INVENTARIO
#define INVENTARIO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ID_ITEM    5   /*! "OB01" + '\0' */
#define MAX_NAME_ITEM  21 /*! 20 caracteres + '\0' */
#define MAX_DESC_ITEM  100  /*! 99 caracteres + '\0' */
#define MAX_LOCATION   13  /*! "Inventario" o Id_sala (00) + '\0' */

typedef struct {
    char id[MAX_ID_ITEM];
    char name[MAX_NAME_ITEM];
    char description[MAX_DESC_ITEM];
    char location[MAX_LOCATION]; /*! Id_sala o "Inventario" */
} Item;

typedef struct {
    Item *slot; /*! *slot <=> Array de slots */
    int size;
} Inventory;

//!CABECERA: Inventory* inv_load_items(char path[])
//!PRECONDICIÓN: path es una ruta válida a un fichero de objetos con formato Id-Nombre-Descripción-Localización
//!POSTCONDICIÓN: Devuelve un Inventory* con todos los objetos cargados, o NULL si no se pudo abrir el fichero
Inventory* inv_load_items(char path[]);

//!CABECERA: Item* inv_find_item_by_id(char wanted_id[5], Inventory *inv)
//!PRECONDICIÓN: wanted_id e inv preinicializados
//!POSTCONDICIÓN: Devuelve un puntero al Item con ese ID, o NULL si no existe
Item* inv_find_item_by_id(char wanted_id[5], Inventory *inv);

//!CABECERA: int inv_write_items(FILE *file, Inventory *all_items)
//!PRECONDICIÓN: file abierto en escritura, all_items preinicializado
//!POSTCONDICIÓN: Escribe todos los items en el fichero con formato "OBJETO: Id-Localización". Devuelve 1 si éxito, 0 si error
int inv_write_items(FILE *file, Inventory *all_items);

//!CABECERA: Inventory inv_create_empty_inventory()
//!PRECONDICIÓN: ninguna
//!POSTCONDICIÓN: Devuelve un Inventory vacío con slot NULL y size 0
Inventory inv_create_empty_inventory();

//!CABECERA: int inv_itemcmp(Item item_1, Item item_2)
//!PRECONDICIÓN: item_1 e item_2 preinicializados
//!POSTCONDICIÓN: Devuelve 0 si los dos items son iguales, 1 si no lo son
int inv_itemcmp(Item item_1, Item item_2);

//!CABECERA: int inv_find_item(Item item, Inventory *inv)
//!PRECONDICIÓN: item e inv preinicializados
//!POSTCONDICIÓN: Devuelve la posición del item en el inventario, o -1 si no se encuentra
int inv_find_item(Item item, Inventory *inv);

Item* inv_find_item_by_id(char wanted_id[5], Inventory *inv);

int inv_write_items(FILE *file, Inventory *all_items);

int inv_add_item(Item item, Inventory *inv);

//!CABECERA: int inv_remove_item(Item item, Inventory *inv)
//!PRECONDICIÓN: item e inv preinicializados
//!POSTCONDICIÓN: Elimina la primera ocurrencia del item en el inventario. Devuelve 1 si se eliminó, 0 si no se encontró
int inv_remove_item(Item item, Inventory *inv);

//!CABECERA: void inv_free_inventory(Inventory *inv_to_free)
//!PRECONDICIÓN: 
//!POSTCONDICIÓN: Libera la memoria del inventario
void inv_free_inventory(Inventory *);

#endif
