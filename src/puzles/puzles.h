#ifndef puzles
#define puzles

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char id_puzle[4];
    char nomb_puz[16];
    char id_sala[3];
    char tipo[20];
    char descrip[151];
    char sol[51];
    int resuelto;
}puzle;

typedef struct{
    puzle *unidad;
    int total_leidos;
}array_puz;

//!Cabecera: array_puz* puzzle_loadpuzzles(char path[])
//!Precondicion:
//!Postcondicion: Devuelve puntero a la estructura array_puz y actualiza el contador total leidos
array_puz* puzzle_loadpuzzles(char path[]);

//!Cabecera: Comprueba si la respuesta del jugador coincide con la solución del puzle.
//!Precondicion: El array de puzles debe estar inicializado y los parámetros no ser nulos.
//!Postcondicion: Si la respuesta es correcta, cambia 'resuelto' a 1 y devuelve 1. 
int puzzle_check_solution(array_puz *arr_puzles, char *id_puzle_objetivo, char *respuesta_jugador);

//!Cabecera: puzle* puzzle_find_by_id(char* wanted_id, array_puz* arr)
//!Precondicion: wanted_id y arr preinicializados
//!Postcondicion: Devuelve un puntero al puzle con el id especificado, o NULL si no existe
puzle* puzzle_find_by_id(char*, array_puz*);

//!Cabecera: void puzzle_freepuzzles(array_puz *)
//!Precondicion:
//!Postcondicion: Vacia la memoria del array de los puzles 
void puzzle_freepuzzles(array_puz *);

#endif