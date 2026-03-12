#ifndef SALAS

#define SALAS

//SALAS

typedef enum {INICIAL, NORMAL, SALIDA} tipo_sala;

typedef struct{

    char sala_id[3]; //2 CARACTERES
    char sala_nombre[31]; //30 CARACTERES MÁX
    char sala_desc[151]; //150 CARACTERES MÁX
    tipo_sala sala_tipo; //INICIAL, NORMAL, SALIDA
    //AQUÍ IRÁ EL "INVENTARIO DE LA SALA" Y LOS PUZLES QUE TENDRÁ

} sala;

//CONEXIONES

typedef struct{

    char con_id[4]; //3 CARACTERES
    char con_sala_from_id[3]; //2 CARACTERES
    char con_sala_to_id[3]; //2 CARACTERES
    int con_block; //1 SI BLOQUEADO, 0 SI NO
    char con_id_cond[5]; //ID DEL OBJETO O PUZLE A RESOLVER PARA PODER ATRAVESAR LA CONEXION

} conexion;

#endif