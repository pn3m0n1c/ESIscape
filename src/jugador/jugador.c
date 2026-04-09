#include"jugador.h"
#include"inventario.h"
#include"salas.h"
//Carga los jugadores
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
    //Entra en un jugador ya creado anteriormente, devuelve un numero si existe, si no existe devuelve 0
    int iniciar_sesion(jugador *array_jugador, int total_leidos){
        if(array_jugador == NULL){
            printf("No hay jugadores disponibles");
            return 0;
        }else{
            char nombre_usuario[11];
            char contra_usuario[9];

            printf("Escribe el nombre de usuario: ");
            fgets(nombre_usuario, sizeof(nombre_usuario), stdin);

            printf("Escribe la clave del usuario: ");
            fgets(contra_usuario, sizeof(contra_usuario), stdin);

            int i;
            for(i = 0; i < total_leidos; i++){
                if (strcmp(array_jugador[i].Jugador, nombre_usuario) == 0 && strcmp(array_jugador[i].Contrasena, contra_usuario) == 0) {
            return i;
            }
        }
        
    }    
}
    //Añade un nuevo jugador al array de jugadores
    jugador *registrar_jugador(jugador *array_jugador, int *total_leidos){
    int num_usr = *total_leidos; 
    
    (*total_leidos)++; 

    jugador *reserva = realloc(array_jugador, (*total_leidos) * sizeof(jugador));
        (*total_leidos)++;
    if (reserva == NULL) {
        printf("ERROR: No se pudo reservar memoria para el nuevo jugador.\n");
        (*total_leidos)--; 
        return array_jugador; 
    }else{

        array_jugador = reserva; 

        printf("\n----- REGISTRATE -----\n");
    
        printf("Introduce un ID (2 numeros): ");
        fgets(array_jugador[num_usr].Id_jugador, sizeof(array_jugador[num_usr].Id_jugador), stdin);
        array_jugador[num_usr].Id_jugador[strcspn(array_jugador[num_usr].Id_jugador, "\n")] = 0; 

        printf("Introduce tu nombre: ");
        fgets(array_jugador[num_usr].Nomb_jugador, sizeof(array_jugador[num_usr].Nomb_jugador), stdin);
        array_jugador[num_usr].Nomb_jugador[strcspn(array_jugador[num_usr].Nomb_jugador, "\n")] = 0;

        printf("Elige un nombre de usuario (max 10 letras): ");
        fgets(array_jugador[num_usr].Jugador, sizeof(array_jugador[num_usr].Jugador), stdin);
        array_jugador[num_usr].Jugador[strcspn(array_jugador[num_usr].Jugador, "\n")] = 0;

        printf("Elige una contrasena (max 8 letras/numeros): ");
        fgets(array_jugador[num_usr].Contrasena, sizeof(array_jugador[num_usr].Contrasena), stdin);
        array_jugador[num_usr].Contrasena[strcspn(array_jugador[num_usr].Contrasena, "\n")] = 0;

        array_jugador[num_usr].inv = inv_create_empty_inventory();

        printf("\n¡Registro completado con exito! Bienvenido a ESI-ESCAPE.\n");

        return array_jugador;

    
    }
}
    //Guarda jugadores dentro del array de jugadores dentro del fichero "Jugadores.txt"
    void guardar_jugador(jugador *array_jugador, char *path, int total_leidos){
        if(array_jugador == NULL){
            printf("No se puede guardar jugadores porque no hay jugadores disponibles.");
        }
        FILE *f = fopen(path, "w");
        if(f == NULL){
            printf("No se ha podido guardar el jugador o jugadores");
        }
        int i;
        for(i = 0; i < total_leidos; i++){
            fprintf(f, "%s-%s-%s-%s", array_jugador[i].Id_jugador, array_jugador[i].Nomb_jugador, array_jugador[i].Jugador, array_jugador[i].Contrasena);
            fprintf(f, "\n");
        }
        fclose(f);
    }
    
    void estado_jugador(jugador *array_jugador, int total_leidos){
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
    }

    //Borra el array de jugadores y lo deja vacio
    void liberar_jugador(jugador *array_jugador) {
    if (array_jugador != NULL) {
    
        free(array_jugador);
    }
}