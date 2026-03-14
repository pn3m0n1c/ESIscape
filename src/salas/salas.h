#ifndef SALAS

#define SALAS

//SALAS

typedef enum {INICIAL, NORMAL, SALIDA} type_sala;

typedef struct{

    char sala_id[3];        //2 CARACTERES
    char sala_name[31];     //30 CARACTERES MÁX
    char sala_desc[151];    //150 CARACTERES MÁX
    type_sala sala_type;    //INICIAL, NORMAL, SALIDA
    //AQUÍ IRÁ EL "INVENTARIO DE LA SALA" Y LOS PUZLES QUE TENDRÁ

} Sala;

typedef struct{

    Sala *salas;
    int number_of_salas;

} Salas;

//CONEXIONES

typedef struct{

    char conn_id[4];             //3 CARACTERES
    char conn_sala_from_id[3];   //2 CARACTERES
    char conn_sala_to_id[3];     //2 CARACTERES
    int conn_block;              //1 SI BLOQUEADO, 0 SI NO
    char conn_id_cond[5];        //ID DEL OBJETO O PUZLE A RESOLVER PARA PODER ATRAVESAR LA CONEXION

} Conn;

typedef struct{

    Conn *conns;
    int number_of_conns;

} Conns;

//CABECERA: sala* get_sala_from_id(char* id_to_search)
//PRECONDICIÓN: char y salas preinicializado
//POSTCONDICIÓN: devuelve un puntero a la sala dentro de un conjunto de salas con el id especificado en los argumentos.
Sala* get_sala_from_id(char*, Salas*);

//CABECERA:         Salas* load_salas()
//PRECONDICIÓN:     Que exista el archivo de salas.txt
//POSTCONDICIÓN:    Que devuelva un puntero a un array con todas las salas cargadas desde su archivo
Salas* load_salas();

//CABECERA:         Conns* load_conns()
//PRECONDICIÓN:     Que exista el archivo de Conexiones.txt
//POSTCONDICIÓN:    Que devuelva un puntero a un array con todas las conexiones cargadas desde su archivo
Conns* load_conns();

#endif