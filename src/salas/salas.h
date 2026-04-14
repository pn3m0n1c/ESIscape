#ifndef SALAS

#define SALAS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inventario/inventario.h"

//!SALAS

typedef enum {INICIAL, NORMAL, SALIDA} type_sala;

typedef struct{

    char sala_id[3];        //!2 CARACTERES
    char sala_name[31];     //!30 CARACTERES MÁX
    char sala_desc[151];    //!150 CARACTERES MÁX
    type_sala sala_type;    //!INICIAL, NORMAL, SALIDA
    Inventory sala_inventory;

} Sala;

typedef struct{

    Sala *salas;
    int number_of_salas;

} Salas;

//!CONEXIONES

typedef struct{

    char conn_id[4];             //!3 CARACTERES
    char conn_sala_from_id[3];   //!2 CARACTERES
    char conn_sala_to_id[3];     //!2 CARACTERES
    int conn_block;              //!1 SI BLOQUEADO, 0 SI NO
    char conn_id_cond[5];        //!ID DEL OBJETO O PUZLE A RESOLVER PARA PODER ATRAVESAR LA CONEXION

} Conn;

typedef struct{

    Conn *conns;
    int number_of_conns;

} Conns;

//!CABECERA: sala* salas_get_sala_from_id(char* id_to_search)
//!PRECONDICIÓN: char y salas preinicializado
//!POSTCONDICIÓN: devuelve un puntero a la sala dentro de un conjunto de salas con el id especificado en los argumentos.
Sala* salas_get_sala_from_id(char*, Salas*);

//!CABECERA: Sala* salas_get_sala_inicial(Salas* arr_salas)
//!PRECONDICIÓN: arr_salas preinicializada
//!POSTCONDICIÓN: Devuelve un puntero a la sala inicial
Sala* salas_get_sala_inicial(Salas*);

//!CABECERA:         Salas salas_load_salas(char *file_path)
//!PRECONDICIÓN:     Que exista el archivo de file_path
//!POSTCONDICIÓN:    Que devuelva un puntero a un array con todas las salas cargadas desde su archivo
Salas salas_load_salas(char*);

//!CABECERA:         Conns salas_load_conns(char *file_path)
//!PRECONDICIÓN:     Que exista el archivo de Conexiones.txt
//!POSTCONDICIÓN:    Que devuelva un puntero a un array con todas las conexiones cargadas desde su archivo
Conns salas_load_conns(char*);

//!CABECERA: Conn* salas_find_conn_by_id(char* wanted_id, Conns* conns)
//!PRECONDICIÓN: wanted_id y conns preinicializados
//!POSTCONDICIÓN: Devuelve un puntero a la Conn con el id especificado, o NULL si no existe
Conn* salas_find_conn_by_id(char*, Conns*);

//!CABECERA:         void salas_free_salas(Salas* salas)
//!PRECONDICIÓN:     
//!POSTCONDICIÓN:    libera la memoria dinámica de las salas cargadas
void salas_free_salas(Salas*);

//!CABECERA:         void salas_free_conns(Conns* conns)
//!PRECONDICIÓN:     
//!POSTCONDICIÓN:    libera la memoria dinámica de las conexiones cargadas
void salas_free_conns(Conns*);

#endif