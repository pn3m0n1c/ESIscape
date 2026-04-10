#include"../partida/partida.h"
#include"jugador.h"
/*Carga los jugadores y sus respectivos objetos*/
jugadores *cargar_jugadores(char path[]) {
    
    FILE *f = fopen(path, "r"); 
    
    jugadores *cargados_jugadores = (jugadores*)malloc(sizeof(jugadores));

    if (f == NULL) {
        printf("ERROR: No se pudo abrir %s\n", path);
        cargados_jugadores->total_leidos = 0;
        return NULL;
    }

    else{

        cargados_jugadores->arr_jugadores = NULL;
        int cont = 0;
        char linea[512];

        while (fgets(linea, sizeof(linea), f)){

            linea[strcspn(linea, "\r\n")] = 0;
            if (strlen(linea) == 0) continue;

            (cargados_jugadores->arr_jugadores) = realloc((cargados_jugadores->arr_jugadores), (cont + 1) * sizeof(jugador));

            char *token = strtok(linea, "-");

            token = strtok(NULL, "-");
            if (token) strcpy((cargados_jugadores->arr_jugadores)[cont].Nomb_jugador, token);

            token = strtok(NULL, "-");
            if (token) strcpy((cargados_jugadores->arr_jugadores)[cont].Jugador, token);

            token = strtok(NULL, "-");
            if (token) strcpy((cargados_jugadores->arr_jugadores)[cont].Contrasena, token);

            token = strtok(NULL, "\0");
            if (token) strcpy((cargados_jugadores->arr_jugadores)[cont].Inventario_como_string, token);
            else (cargados_jugadores->arr_jugadores)[cont].Inventario_como_string[0] = '\0';

            /*(cargados_jugadores->arr_jugadores)[cont].inv=inv_create_empty_inventory();
            token = strtok(NULL, "-");
            while (token != NULL){
                Item objeto_temporal;
                strcpy(objeto_temporal.id, token);
                strcpy(objeto_temporal.location, "Inventario");
                inv_add_item(objeto_temporal, &(cargados_jugadores->arr_jugadores)[cont].inv);
                
                token = strtok(NULL, "-");
            }*/

            cont++;

        }

        fclose(f);
        (cargados_jugadores->total_leidos) = cont;
        return cargados_jugadores;

    }

}

void registrar_jugador(GameState *game_state, char *nom, char *contrasena, char *nom_completo){
    
    game_state->players->arr_jugadores = realloc(game_state->players->arr_jugadores, (game_state->players->total_leidos + 1)*sizeof(jugador));

    if(game_state->players->arr_jugadores == NULL){
        printf("ERROR: No se pudo reservar memoria para el nuevo jugador.\n");
        exit(1);
    }
    
    else{

        game_state->players->total_leidos += 1;

        strcpy((game_state->players->arr_jugadores)[game_state->players->total_leidos-1].Jugador, nom);
        strcpy((game_state->players->arr_jugadores)[game_state->players->total_leidos-1].Nomb_jugador, nom_completo);
        strcpy((game_state->players->arr_jugadores)[game_state->players->total_leidos-1].Contrasena, contrasena);
        strcpy((game_state->players->arr_jugadores)[game_state->players->total_leidos-1].Inventario_como_string, "\0");

    }

}

/*Guarda jugadores dentro del array de jugadores  mirando primero si hay jugadores para guardar dentro del fichero "Jugadores.txt"*/
void guardar_jugador(GameState *game_state, char *path){
    if((game_state->players->arr_jugadores) == NULL){
        printf("No se puede guardar jugadores porque no hay jugadores disponibles.");
        return;
    }
    FILE *f = fopen(path, "w");
    if(f == NULL){
        printf("No se ha podido guardar el jugador o jugadores");
        exit(1);
    }
    int i;
    for(i = 0; i < game_state->players->total_leidos; i++){
        if(i>0){ fprintf(f, "\n"); }
        
        char player_id[3];
        snprintf(player_id, sizeof(player_id), "%02d", i+1);

        if(strlen((game_state->players->arr_jugadores)[i].Inventario_como_string) >= 1){
            fprintf(f, "%s-%s-%s-%s-%s", player_id, (game_state->players->arr_jugadores)[i].Nomb_jugador, (game_state->players->arr_jugadores)[i].Jugador, (game_state->players->arr_jugadores)[i].Contrasena, (game_state->players->arr_jugadores)[i].Inventario_como_string);
        }
        else{
            fprintf(f, "%s-%s-%s-%s", player_id, (game_state->players->arr_jugadores)[i].Nomb_jugador, (game_state->players->arr_jugadores)[i].Jugador, (game_state->players->arr_jugadores)[i].Contrasena);
        }
    }
    fclose(f);
}
    /*Introduces un ID y busca a ese jugador comparandolo con la ID real del jugador que está en la string de jugadores
    dentro de un blucle for el cual va buscando al jugador pasando por todos*/
    /*void estado_jugador(jugador *array_jugador, int total_leidos){
        char comparador[3];
        printf("Escribe el ID de tu jugador para ver los detalles de tu jugador: ");
        fgets(comparador, sizeof(comparador), stdin);
        comparador[strcspn(comparador, "\n")] = 0;
        
        int i;
        for(i = 0; i < total_leidos; i++){
            if(strcmp(comparador, array_jugador[i].Id_jugador) == 0){
                printf("----DETALLES DE TU JUGADOR----");
                printf("El nombre de tu usuario es: %s", array_jugador[i].Nomb_jugador);
                printf("El nombre de tu jugador es: %s", array_jugador[i].Jugador);
               // printf("Tienes una cantidad de %i objetos", ); //Preguntar en clase
               // printf("Estas en la sala %s", ); //Preguntar en clase
            }
        }
    }*/

//Borra el array de jugadores y lo deja vacio
void liberar_jugador(jugador *array_jugador) {
    if (array_jugador != NULL) {
        free(array_jugador);
    }
}