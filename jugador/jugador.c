#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<jugador.h>

jugador* cargar_jugador(char path[], int *total_leidos) {
    FILE *f = fopen(char path[], "r"); 
    if (f == NULL) {
        printf("ERROR: No se pudo abrir %s\n", path[]);
        *total_leidos = 0;
        return NULL;
    }
}

jugador *array_jugador = NULL;
    int cont = 0;
    char linea[512];

    while (fgets(linea, sizeof(linea), f)) {
        linea[strcspn(linea, "\r\n")] = 0;
        if (strlen(linea) == 0) continue;

        array_jugador = realloc(array_jugador, (cont + 1) * sizeof(jugador));

        array_jugador[cont].inventario = NULL;
        array_jugador[cont].num_objetos = 0;

        char *token = strtok(linea, "-");
        if (token) strcpy(array_jugador[cont].Id_jugador, token);

        token = strtok(NULL, "-");
        if (token) strcpy(array_jugador[cont].Nomb_jugador, token);

        token = strtok(NULL, "-");
        if (token) strcpy(array_jugador[cont].Jugador, token);

        token = strtok(NULL, "-");
        if (token) strcpy(array_jugador[cont].Contrasena, token);

        //Falta inventario aqui y en el .h


        cont++;
    }

    fclose(f);
    *total_leidos = cont;
    return array_jugador;

    void liberar_jugador(jugador *array_jugador, int total_leidos) {
    if (array_jugador != NULL) {
        for (int i = 0; i < total_leidos; i++) {
            for (int j = 0; j < array_jugador[i].num_objetos; j++) {
                free(array_jugador[i].inventario[j]);
            }
            free(array_jugador[i].inventario);
        }
        free(array_jugador);
    }
}