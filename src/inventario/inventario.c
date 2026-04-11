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

int check_file(FILE *file){
    if (file == NULL) {
        printf("Error al abrir el fichero\n");
        return 0;
    }
    
    return 1;
}

/* Recibe una línea, extrae sus componentes y rellena item.
 * Devuelve 1 si tuvo éxito, 0 si la línea está mal formada (faltan campos). */
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

/* Lee los objetos del inventario del archivo correspondiente y devuelve un
 * "Inventario" con todos los objetos ya extraidos y organizados en forma 
 * de Item. */
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

        /*Añadelo e indica el nuevo tamaño*/
        if(!build_item(line, &all_items->slot[i])){
            printf("Error: objeto mal formado en línea %d de Objetos.txt. El objeto NO se incluirá\n", i + 1);
            all_items->slot = realloc(all_items->slot, i * sizeof(Item));
            continue;
        }
        all_items->size = i + 1;

        i++;
    }

    /* Pendiente un free, entiendo que será al final del juego - Christian*/
    
    fclose(file);
    return all_items;
}

/* Al igual que strcmp(), devuelve 1 si dos items NO son iguales y 0 si efectivamente lo son. */
int inv_itemcmp(Item item_1, Item item_2){
    if(
        strcmp(item_1.id, item_2.id) == 0 && 
        strcmp(item_1.name, item_2.name) == 0 &&
        strcmp(item_1.description, item_2.description) == 0 &&
        strcmp(item_1.location, item_2.location) == 0
    ) return 0;

    return 1;
}

/* Busca un item en un inventario. En caso de encontrarlo devuelve su posición en el array, de no encontrarlo 
 * devuelve "-1", en lugar de 0, por si el item está en la posición 0. 
 * Al devolver la posición creo que se le puede sacar mas 
 * provecho a esta función. */
int inv_find_item(Item item, Inventory *inv){
    int i;

    for (int i = 0; i < inv->size; i++) {
        if(inv_itemcmp(item, inv->slot[i]) == 0) return i;
    }

    return -1;
}

/* Escribe las líneas OBJETO de todos los items al fichero abierto recibido,
 * con el formato de Partida.txt: "OBJETO: Id_obj-Localiz\n"
 * Devuelve 1 si se escribió todo con éxito, 0 en otro caso. */
int inv_write_items(FILE *file, Inventory *all_items){
    if(file == NULL || all_items == NULL) return 0;

    int i;

    for(i = 0; i < all_items->size; i++){
        if(strcmp(all_items->slot[i].location, "Inventario") == 0){
            if(fprintf(file, "OBJETO: %s-%s\n",
                all_items->slot[i].id,
                all_items->slot[i].location) < 0) return 0;
        }
    }

    return 1;
}

/* Busca un item en un inventario en base a su ID. Si lo encuentra devuelve
 * un puntero al Item. Si no lo encuentra, devuelve NULL. */
Item* inv_find_item_by_id(char wanted_id[5], Inventory *inv){
    int i;

    for (i = 0; i < inv->size; i++) {
        if (strcmp(inv->slot[i].id, wanted_id) == 0)
            return &inv->slot[i];
    }

    return NULL;
}

/* Crea un inventario vacío, útil para crear un jugador 
 * en una Nueva partida*/
Inventory inv_create_empty_inventory(){
    Inventory inventory;

    inventory.slot = NULL;
    inventory.size = 0;

    return inventory;
}

/* Intenta añadir un Item a un Inventory. Devuelve 1 si lo añadió con éxito o 0 en otro caso */
int inv_add_item(Item item, Inventory *inv){
    inv->slot = realloc(
        inv->slot, 
        (inv->size + 1) *sizeof(item)
    );

    inv->slot[inv->size] = item;

    if(inv_itemcmp(inv->slot[inv->size], item) == 0){
        inv->size++;
        return 1;
    }

    return 0;
}

/* Para eliminar el item, tengo que primero buscarlo. Si está, se debe copiar los datos 
 * del último item a él, y reducir la memoria a 1 para marcar como basura el último item.
 * En caso de haber 2 items iguales, que quizá no debería, elimina el primero que encuentra. */
int inv_remove_item(Item item, Inventory *inv){

    int wanted_item = inv_find_item(item, inv);

    if(wanted_item > -1){ /* Si es > -1, ha debido encontrarlo, debe ser un índice */

        strcpy(inv->slot[wanted_item].id, inv->slot[inv->size - 1].id);
        strcpy(inv->slot[wanted_item].name, inv->slot[inv->size - 1].name);
        strcpy(inv->slot[wanted_item].description, inv->slot[inv->size - 1].description);
        strcpy(inv->slot[wanted_item].location, inv->slot[inv->size - 1].location);

        inv->slot = realloc(
            inv->slot, 
            (inv->size - 1) * sizeof(item)
        );

        inv->size--;

        return 1;
    };

    return 0;
}