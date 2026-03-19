#ifndef jugador.h
#define jugador.h


typedef struct{
    int *Id_jugador;
    char *Nomb_jugador;
    char *Jugador;
    char *Contraseña;
    char *Id_objeto;
}jugador;

jugador* cargar_jugador(const char *"jugadores.txt", int *total_leidos);
void liberar_jugador(puzle *array_jugador, int total_leidos);








#endif
