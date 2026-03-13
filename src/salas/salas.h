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

    char con_id[4];             //3 CARACTERES
    char con_sala_from_id[3];   //2 CARACTERES
    char con_sala_to_id[3];     //2 CARACTERES
    int con_block;              //1 SI BLOQUEADO, 0 SI NO
    char con_id_cond[5];        //ID DEL OBJETO O PUZLE A RESOLVER PARA PODER ATRAVESAR LA CONEXION

} Conn;

//CABECERA: sala* get_sala_from_id(char* id_to_search)
//PRECONDICIÓN: char y salas preinicializado
//POSTCONDICIÓN: devuelve un puntero a la sala dentro de un conjunto de salas con el id especificado en los argumentos.
Sala* get_sala_from_id(char*, Salas*);

//CABECERA:         Salas* load_salas(char* filepath)
//PRECONDICIÓN:     Que exista el archivo en la ruta relativa de filepath
//POSTCONDICIÓN:    Que devuelva un puntero a un array con todas las salas cargadas desde su archivo
Salas* load_salas(char*);

#endif