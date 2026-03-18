#include "ui/ui.h"
#include "salas/salas.h"

int main(){

    while(1==1){

        int game_is_playing = 1;

        //WE LOAD DATA FROM ROOM AND CONNECTION FILES
        Salas salas = salas_load_salas();
        Conns conns = salas_load_conns();

        Sala *currentsala = salas_get_sala_inicial(&salas);
        
        switch(ui_main_menu()){

            case 0:

                //EN ESTE HUECO SE CREARÍA LA NUEVA PARTIDA

                while(game_is_playing){
                    ui_game_loop_start_menu(&game_is_playing, currentsala);
                }

                break;

            case 1:

                //EN ESTE HUECO SE CARGARÍA LA PARTIDA

                while(game_is_playing){
                    ui_game_loop_start_menu(&game_is_playing, currentsala);
                }

                break;

            case 2:

                ui_exit_game();

                break;

        }

    }
    
    return(0);

}