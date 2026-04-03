#ifndef INVENTARIO
#define INVENTARIO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ID_ITEM    5   /* "OB01" + '\0' */
#define MAX_NAME_ITEM  21 /* 20 caracteres + '\0' */
#define MAX_DESC_ITEM  100  /* 99 caracteres + '\0' */
#define MAX_LOCATION   13  /* "Inventario" o Id_sala (00) + '\0' */

typedef struct {
    char id[MAX_ID_ITEM];
    char name[MAX_NAME_ITEM];
    char description[MAX_DESC_ITEM];
    char location[MAX_LOCATION]; /* Id_sala o "Inventario" */
} Item;

typedef struct {
    Item *slot; /* *slot <=> Array de slots */
    int size;
} Inventory;

Inventory* inv_read_items(char path[]);

Item* inv_find_item_by_id(char wanted_id[5], Inventory *inv);

int inv_write_items(FILE *file, Inventory *all_items);

Inventory inv_create_empty_inventory();

int inv_itemcmp(Item item_1, Item item_2);

int inv_find_item(Item item, Inventory *inv);

Item* inv_find_item_by_id(char wanted_id[4], Inventory *inv);

int inv_write_items(FILE *file, Inventory *all_items);

int inv_add_item(Item item, Inventory *inv);

int inv_remove_item(Item item, Inventory *inv);

#endif
