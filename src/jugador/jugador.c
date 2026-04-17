#include"../partida/partida.h"
#include"jugador.h"

/**
 * @brief Carga los jugadores del fichero.
 * @par CABECERA
 * jugadores *player_loadplayer(char path[])
 * @pre Que haya jugadores en el fichero.
 * @post Devuelve un puntero a la estructura jugadores, la cual contiene un array con los jugadores y el total que se han leido.
 */
jugadores *player_loadplayer(char path[]) {
    
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
            if (token) strcpy((cargados_jugadores->arr_jugadores)[cont].id, token);

            token = strtok(NULL, "-");
            if (token) strcpy((cargados_jugadores->arr_jugadores)[cont].Nomb_jugador, token);

            token = strtok(NULL, "-");
            if (token) strcpy((cargados_jugadores->arr_jugadores)[cont].Jugador, token);

            token = strtok(NULL, "-");
            if (token) strcpy((cargados_jugadores->arr_jugadores)[cont].Contrasena, token);

            token = strtok(NULL, "\0");
            if (token) strcpy((cargados_jugadores->arr_jugadores)[cont].Inventario_como_string, token);
            else (cargados_jugadores->arr_jugadores)[cont].Inventario_como_string[0] = '\0';

            

            cont++;

        }

        fclose(f);
        (cargados_jugadores->total_leidos) = cont;
        return cargados_jugadores;

    }

}
/**
 * @brief Guarda a un nuevo jugador con la estructura de jugador dentro del array de jugadores
 * @par CABECERA
 * void player_registerplayer(GameState *game_state, char *nom, char *contrasena, char *nom_completo)
 * @pre Que exista un array de jugadores y una estructura la cual los defina.
 * @post admite un jugador extra en el array de jugadores con un realloc e incrementa en 1 el total leidos.
 */
void player_registerplayer(GameState *game_state, char *nom, char *contrasena, char *nom_completo){
    
    game_state->players->arr_jugadores = realloc(game_state->players->arr_jugadores, (game_state->players->total_leidos + 1)*sizeof(jugador));

    if(game_state->players->arr_jugadores == NULL){
        printf("ERROR: No se pudo reservar memoria para el nuevo jugador.\n");
        exit(1);
    }
    
    else{

        game_state->players->total_leidos += 1;
        //! EL ID del jugador se calcula en este punto
        snprintf((game_state->players->arr_jugadores)[game_state->players->total_leidos-1].id, 3, "%02d", game_state->players->total_leidos);
        strcpy((game_state->players->arr_jugadores)[game_state->players->total_leidos-1].Jugador, nom);
        strcpy((game_state->players->arr_jugadores)[game_state->players->total_leidos-1].Nomb_jugador, nom_completo);
        strcpy((game_state->players->arr_jugadores)[game_state->players->total_leidos-1].Contrasena, contrasena);
        strcpy((game_state->players->arr_jugadores)[game_state->players->total_leidos-1].Inventario_como_string, "\0");

    }

}

/** 
 * @brief Guarda el array de jugadores en el fichero de jugadores.txt
 * @par CABECERA
 * void player_saveplayer(GameState *game_state, char *path)
 * @pre Debe haber jugadores creados en el array para poder guardarlos.
 * @post Los jugadores añadidos recientemente se guardan dentro de jugadores.txt.
 */
void player_saveplayer(GameState *game_state, char *path){
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
        strcpy((game_state->players->arr_jugadores)[i].id, player_id);

        if(strlen((game_state->players->arr_jugadores)[i].Inventario_como_string) >= 1){
            fprintf(f, "%s-%s-%s-%s-%s", player_id, (game_state->players->arr_jugadores)[i].Nomb_jugador, (game_state->players->arr_jugadores)[i].Jugador, (game_state->players->arr_jugadores)[i].Contrasena, (game_state->players->arr_jugadores)[i].Inventario_como_string);
        }
        else{
            fprintf(f, "%s-%s-%s-%s", player_id, (game_state->players->arr_jugadores)[i].Nomb_jugador, (game_state->players->arr_jugadores)[i].Jugador, (game_state->players->arr_jugadores)[i].Contrasena);
        }
    }
    fclose(f);
}
/** 
 * @brief Va buscando en el array de jugadores el jugador el cual se desea encontrar
 * @par CABECERA
 * jugador* player_findplayer(char name[21], char pass[9], jugadores* all_players)
 * @pre Debe de existir un array de jugadores y el jugador que se quiera buscar.
 * @post Si el susuario y la contraseña coinciden con un jugador le devuelve un puntero
 */
jugador* player_findplayer(char name[21], char pass[9], jugadores* all_players){
    int i;

    for (i = 0; i < all_players->total_leidos; i++) {
        if (strcmp(all_players->arr_jugadores[i].Nomb_jugador, name) == 0 
            && strcmp(all_players->arr_jugadores[i].Contrasena, pass) == 0)
            return &all_players->arr_jugadores[i];
    }

    return 0;
}

/** 
 * @brief Vacia el array de jugadores
 * @par CABECERA
 * void player_freeplayer(jugadores *jugadores_borrar)
 * @pre Debe de existir un array de jugadores y que tenga al menos un jugador.
 * @post Vacia el aaray de jugadores
 */
void player_freeplayer(jugadores *jugadores_borrar) {
    if ((jugadores_borrar) != NULL) {
        if ((jugadores_borrar->arr_jugadores) != NULL) {
            free(jugadores_borrar->arr_jugadores);
        }
        free(jugadores_borrar);
    }
}