#include "ui/ui.h"
#include "salas/salas.h"

int main(){

    Salas test_salas = salas_load_salas("./data/Salas.txt");
    Conns test_conns = salas_load_conns("./data/Conexiones.txt");
    ui_show_filter_connections(&test_conns, &test_salas, "");
    
    return(0);

}