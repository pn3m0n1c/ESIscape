#include <locale.h>
#ifdef _WIN32
    #include <windows.h>
#endif
#include "partida/partida.h"

int main(){

    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);   /* salida en UTF-8 */
        SetConsoleCP(CP_UTF8);         /* entrada en UTF-8 */
    #endif
    
    setlocale(LC_ALL,"");
    
    game_start();
    
    return(0);

}