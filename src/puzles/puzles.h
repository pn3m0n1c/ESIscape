#ifndef puzles
#define puzles

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** @brief Estructura que contiene cada puzle */
typedef struct{
    char id_puzle[4];
    char nomb_puz[16];
    char id_sala[3];
    char tipo[20];
    char descrip[151];
    char sol[51];
    int resuelto;
}puzle;

/** @brief Estructura de todos los puzles */
typedef struct{
    puzle *unidad;
    int total_leidos;
}array_puz;


/**
 * @brief Carga los puzles del fichero
 * @par CABECERA
 * array_puz* puzzle_loadpuzzles(char path[])
 * @pre Que haya puzles en el fichero.
 * @post Devuelve puntero a la estructura array_puz y actualiza el contador total leidos
 */
array_puz* puzzle_loadpuzzles(char path[]);

/**
 * @brief Comprueba si la solucion de un puzle es correcta o no
 * @par CABECERA
 * int puzzle_check_solution(array_puz *arr_puzles, char *id_puzle_objetivo, char *respuesta_jugador)
 * @pre Que exista un array de puzles y que haya al menos 1
 * @post Si la respuesta es correcta devuelve 1, si no, devuelve 0
 */
int puzzle_check_solution(array_puz *arr_puzles, char *id_puzle_objetivo, char *respuesta_jugador);

/**
 * @brief Busca el puzle en base a su ID
 * @par CABECERA
 * puzle* puzzle_find_by_id(char*, array_puz*)
 * @pre Que exista un array de puzles y que haya al menos 1
 * @post Devuelve un puntero al puzle con el id especificado, o NULL si no existe
 */
puzle* puzzle_find_by_id(char*, array_puz*);
 
/**
 * @brief Libera el aaray de puzles y lo deja vacio
 * @par CABECERA
 * void puzzle_freepuzzles(array_puz *)
 * @pre Que exista un array de puzles y que haya al menos 1
 * @post Devuelve el array de puzles vacio
 */
void puzzle_freepuzzles(array_puz *);

#endif