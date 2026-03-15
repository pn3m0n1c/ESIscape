#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventario.h"

/* Fichero Objetos.txt
- Identificador del objeto (Id_obj), 4 caracteres. 
- Nombre del objeto (Nomb_obj), 15 caracteres máximo.
- Descripción del objeto (Describ), 50 caracteres máximo.
- Localización del objeto (Localiz): Id_sala o Inventario.
*/

/* Debug (Main):     
    Inventory* all_items = inv_read_items("data/Objetos.txt");
    ui_show_inventory(all_items); 
*/

/* Recibe una línea, extrae sus componentes y devuelve el item "construido" */
Item build_item(char line[]) {
    Item item;

    strcpy(item.id, strtok(line, "-"));
    strcpy(item.name, strtok(NULL, "-"));
    strcpy(item.description, strtok(NULL, "-"));
    strcpy(item.location, strtok(NULL, "-"));

    return item;
}

/* Recibe un archivo y comprueba si puede abrirse */
int check_file(FILE *file){
    if (file == NULL) {
        printf("Error al abrir el fichero\n");
        return 0;
    }
    
    return 1;
}

/* Lee los objetos del inventario del archivo correspondiente y devuelve un
 * "Inventario" con todos los objetos ya extraidos y organizados en forma 
 * de Item. */
Inventory* inv_read_items(char path[]) {
    FILE *file = fopen(path, "r");

    if(!check_file(file)) return NULL;

    int i = 0;
    char line[200];

    Inventory *all_items = malloc(sizeof(Inventory));
    all_items->slot = NULL;
    all_items->size = 0;

    while(fgets(line,200,file) != NULL){
        all_items->slot = realloc(
            all_items->slot, 
            (i+1) * sizeof(Item)
        );

        /*Añadelo e indica el nuevo tamaño*/
        all_items->slot[i] = build_item(line);
        all_items->size = i + 1;

        i++;
    }

    /* Pendiente un free, entiendo que será al final del juego - Christian*/
    
    fclose(file);
    return all_items;
}

/* Crea un inventario vacío, útil para crear un jugador 
 * en una Nueva partida*/
Inventory inv_create_empty_inventory(){
    Inventory inventory;

    inventory.slot = NULL;
    inventory.size = 0;

    return inventory;
}

/*Add item*/

/*Remove item*/