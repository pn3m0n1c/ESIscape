#include <stdio.h>

/* Recibe un archivo y comprueba si puede abrirse */
int check_file(FILE *file){
    if (file == NULL) {
        printf("Error al abrir el fichero\n");
        return 0;
    }
    
    return 1;
}