#ifndef SALAS

#define SALAS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inventario/inventario.h"

/**
 * @defgroup salas Módulo Salas
 * @brief Gestión de las salas y las conexiones entre salas, y funciones relacionadas.
 * @{
 */

//!SALAS

/** @brief Representa los tipos de sala en forma de enum. */
typedef enum {INICIAL, NORMAL, SALIDA} type_sala;

/** @brief Representa la estructura que almacena la información de cada sala. */
typedef struct{

    char sala_id[3];        //!2 CARACTERES
    char sala_name[31];     //!30 CARACTERES MÁX
    char sala_desc[151];    //!150 CARACTERES MÁX
    type_sala sala_type;    //!INICIAL, NORMAL, SALIDA
    Inventory sala_inventory;

} Sala;

/** @brief Representa la estructura que almacena el conjunto de todas las salas cargadas y el número de éstas. */
typedef struct{

    Sala *salas;
    int number_of_salas;

} Salas;

//!CONEXIONES

/** @brief Representa la estructura que almacena la información de cada conexión. */
typedef struct{

    char conn_id[4];             //!3 CARACTERES
    char conn_sala_from_id[3];   //!2 CARACTERES
    char conn_sala_to_id[3];     //!2 CARACTERES
    int conn_block;              //!1 SI BLOQUEADO, 0 SI NO
    char conn_id_cond[5];        //!ID DEL OBJETO O PUZLE A RESOLVER PARA PODER ATRAVESAR LA CONEXION

} Conn;

/** @brief Representa la estructura que almacena el conjunto de todas las conexiones cargadas y el número de éstas. */
typedef struct{

    Conn *conns;
    int number_of_conns;

} Conns;

/**
 * @par CABECERA
 * Sala* salas_get_sala_from_id(char* id_to_search, Salas* salas)
 * @pre char y salas preinicializado
 * @post devuelve un puntero a la sala dentro de un conjunto de salas con el id especificado en los argumentos.
 */
Sala* salas_get_sala_from_id(char*, Salas*);

/**
 * @par CABECERA
 * Sala* salas_get_sala_inicial(Salas* arr_salas)
 * @pre arr_salas preinicializada
 * @post Devuelve un puntero a la sala inicial
 */
Sala* salas_get_sala_inicial(Salas*);

/**
 * @par CABECERA
 * Salas salas_load_salas(char *file_path)
 * @pre Que exista el archivo de file_path
 * @post Que devuelva un puntero a un array con todas las salas cargadas desde su archivo
 */ 
Salas salas_load_salas(char*);

/**
 * @par CABECERA
 * Conns salas_load_conns(char *file_path)
 * @pre Que exista el archivo de Conexiones.txt
 * @post Que devuelva un puntero a un array con todas las conexiones cargadas desde su archivo
 */
Conns salas_load_conns(char*);

/**
 * @par CABECERA
 * Conn* salas_find_conn_by_id(char* wanted_id, Conns* conns)
 * @pre wanted_id y conns preinicializados
 * @post Devuelve un puntero a la Conn con el id especificado, o NULL si no existe
 */
Conn* salas_find_conn_by_id(char*, Conns*);

/**
 * @par CABECERA
 * void salas_free_salas(Salas* salas)
 * @pre (Ninguna)
 * @post libera la memoria dinámica de las salas cargadas
 */
void salas_free_salas(Salas*);


/**
 * @par CABECERA
 * void salas_free_conns(Conns* conns)
 * @pre (Ninguna)
 * @post libera la memoria dinámica de las conexiones cargadas
 */
void salas_free_conns(Conns*);

#endif