# ESI-ESCAPE

## Compilación con Makefile

Para poder compilar el proyecto con todos sus módulos hemos creado un archivo makefile que se usa de la siguiente forma:

1. Nos situamos con una terminal o cmd en el directorio raíz del proyecto, que contenga `/src` y `makefile`
2. Ejecutamos: 

    ```
    make
    ``` 
    o bien
    ```
    mingw32-make
    ```
3. Nuestro makefile debería crear un ejecutable `esi-escape` o `esi-escape.exe` en un directorio `/bin` en la raíz del proyecto, además de crear el directorio `/build` que contendrá archivos `.o` intermedios de la compilación.
4. Lanzamos el ejecutable y deberíamos obtener una terminal con la pantalla de título de "*ESI-ESCAPE*".