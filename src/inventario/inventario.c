#include "inventario.h"

/* Fichero Objetos.txt
- Identificador del objeto (Id_obj), 4 caracteres.
- Nombre del objeto (Nomb_obj), 15 caracteres máximo.
- Descripción del objeto (Describ), 50 caracteres máximo.
- Localización del objeto (Localiz): Id_sala o Inventario.
*/

/* Debug (Main):
    Inventory* all_items = inv_read_items("data/Objetos.txt");
    ui_show_filter_inventory(all_items);
*/

/**
 * @brief Comprueba si un fichero se ha podido abrir correctamente.
 * @par CABECERA
 * check_file(FILE *file)
 * @pre file es el resultado de un fopen()
 * @post Devuelve 1 si el fichero es válido, 0 si es NULL
 */
int check_file(FILE *file){
    if (file == NULL) {
        printf("Error al abrir el fichero\n");
        return 0;
    }

    return 1;
}

/**
 * @brief Parsea una línea del fichero de objetos y rellena un Item.
 * @par CABECERA
 * build_item(char line[], Item *item)
 * @pre line tiene formato Id-Nombre-Descripción-Localización, item preinicializado
 * @post Devuelve 1 si tuvo éxito, 0 si la línea está mal formada (faltan campos)
 */
int build_item(char line[], Item *item) {
    if(line[strlen(line)-1] == '\n'){
        line[strlen(line)-1] = '\0';
    }

    char *tok;

    tok = strtok(line, "-"); if(tok == NULL) return 0; strcpy(item->id, tok);
    tok = strtok(NULL, "-"); if(tok == NULL) return 0; strcpy(item->name, tok);
    tok = strtok(NULL, "-"); if(tok == NULL) return 0; strcpy(item->description, tok);
    tok = strtok(NULL, "-"); if(tok == NULL) return 0; strcpy(item->location, tok);

    return 1;
}

/**
 * @brief Lee los objetos del fichero indicado y los devuelve organizados en un Inventory.
 * @par CABECERA
 * inv_load_items(char path[])
 * @pre path es una ruta válida a un fichero con formato Id-Nombre-Descripción-Localización
 * @post Devuelve un Inventory* con todos los objetos ya extraídos y organizados en forma de Item, o NULL si no se pudo abrir el fichero
 */
Inventory* inv_load_items(char path[]) {
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

        /*!Añadelo e indica el nuevo tamaño*/
        if(!build_item(line, &all_items->slot[i])){
            printf("Error: objeto mal formado en línea %d de Objetos.txt. El objeto NO se incluirá\n", i + 1);
            all_items->slot = realloc(all_items->slot, i * sizeof(Item));
            continue;
        }
        all_items->size = i + 1;

        i++;
    }

    fclose(file);
    return all_items;
}

/**
 * @brief Escribe las líneas OBJETO de todos los items al fichero abierto recibido.
 * @par CABECERA
 * inv_write_items(FILE *file, Inventory *all_items)
 * @pre file abierto en escritura, all_items preinicializado
 * @post Escribe las líneas OBJETO de todos los items al fichero con formato "OBJETO: Id_obj-Localiz". Devuelve 1 si éxito, 0 en otro caso
 */
int inv_write_items(FILE *file, Inventory *all_items){
    if(file == NULL || all_items == NULL) return 0;

    int i;

    for(i = 0; i < all_items->size; i++){
		if(fprintf(file, "OBJETO: %s-%s\n",
			all_items->slot[i].id,
			all_items->slot[i].location) < 0) return 0;
    }

    return 1;
}

/**
 * @brief Busca un item en un inventario en base a su ID.
 * @par CABECERA
 * inv_find_item_by_id(char wanted_id[5], Inventory *inv)
 * @pre wanted_id e inv preinicializados
 * @post Busca un item en un inventario en base a su ID. Devuelve un puntero al Item, o NULL si no lo encuentra
 */
Item* inv_find_item_by_id(char wanted_id[5], Inventory *inv){
    int i;

    for (i = 0; i < inv->size; i++) {
        if (strcmp(inv->slot[i].id, wanted_id) == 0)
            return &inv->slot[i];
    }

    return NULL;
}

/**
 * @brief Libera la memoria del inventario y de su array de slots.
 * @par CABECERA
 * inv_free_inventory(Inventory *inv_to_free)
 * @pre inv_to_free preinicializado
 * @post Libera la memoria del inventario y de su array de slots
 */
void inv_free_inventory(Inventory *inv_to_free){

    if ((inv_to_free) != NULL) {
        if ((inv_to_free->slot) != NULL) {
            free(inv_to_free->slot);
        }
        free(inv_to_free);
    }

}

void inv_update_item_loc(Item* item, char location[13]){
    strcpy(item->location, location);
}
