#include"jugador.h"

jugador* cargar_jugador(char path[], int *total_leidos) {
    FILE *f = fopen(path, "r"); 
    if (f == NULL) {
        printf("ERROR: No se pudo abrir %s\n", path);
        *total_leidos = 0;
        return NULL;
    }

jugador *array_jugador = NULL;
    int cont = 0;
    char linea[300];

    while (fgets(linea, sizeof(linea), f)) {
        linea[strcspn(linea, "\r\n")] = 0;
        if (strlen(linea) == 0) continue;

    array_jugador = realloc(array_jugador, (cont + 1) * sizeof(jugador));


        char *token = strtok(linea, "-");
        if (token) strcpy(array_jugador[cont].Id_jugador, token);

        token = strtok(NULL, "-");
        if (token) strcpy(array_jugador[cont].Nomb_jugador, token);

        token = strtok(NULL, "-");
        if (token) strcpy(array_jugador[cont].Jugador, token);

        token = strtok(NULL, "-");
        if (token) strcpy(array_jugador[cont].Contrasena, token);

        array_jugador[cont].inv=inv_create_empty_inventory();
        token = strtok(NULL, "-");
        while (token != NULL){
            Item objeto_temporal;
            strcpy(objeto_temporal.id, token);
            strcpy(objeto_temporal.location, "Inventario");
            inv_add_item(objeto_temporal, &array_jugador[cont].inv);
            
            token = strtok(NULL, "-");
        }



        cont++;
    }

    fclose(f);
    *total_leidos = cont;
    return array_jugador;
}

    void liberar_jugador(jugador *array_jugador) {
    if (array_jugador != NULL) {
    
        free(array_jugador);
    }
}