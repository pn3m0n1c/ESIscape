#ifndef INVENTARIO_H
#define INVENTARIO_H

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
Inventory inv_create_empty_inventory();

#endif /* INVENTARIO_H */
