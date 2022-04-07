/* Incluimos las bibliotecas necesarias */

#include <stdio.h>
#include <stdlib.h> // Preguntar para que sirve, entiendo que es para trabajar como se les de la gana con la memoria
#include <string.h> //Libreria para manejar cadenas, la usaremos para leer el csv



void mostrar_todos_los_datos(){


    //llamamos a la función FILE y nombramos nuestra variable luego del "*" , fopen= fileopen(nombre de nuestro archivo csv, acción a realizar r for read/ w for write)
    FILE *libros = fopen("inventario.csv","r");
        //En el supuesto en que no podamos abrir el archivo, mostraremos el error en pantalla.
        if (libros == NULL ){


            //función de stdio.h perror /output de la forma ERROR: str
            perror("No es posible abrir el archivo, revise el formato y/o su directorio.");


            /* 
                Exit(0) indica que se ha terminado el programa con exito.
                Exit(1) indica que el programa se ha terminado de forma anormal.
            */
            exit(1);
        }
    //creamos una variable de 200 caracteres para poder inscribir nuestra busqueda del libro
    char line[200];

    //fgets() obtiene una linea y la guarda en algun string.
    while (fgets(line, sizeof(line), libros)){

            //definiremos el separador del csv como token, el cual será ","

            char *token;
            // strtok rompe la cadena str por el parametro que se le indique dentro.
            token= strtok(line,";");
            //Sin embargo, hasta ahora solo tenemos el primer separador del csv, ahora hemos el resto de separadores que se encuentran.
           
            while(token != NULL ){
                printf("%-15s", token);     //restamos solo para dar espacio entre las columnas
                token=strtok(NULL, ";");
            }
            printf("\n");


    }
}


void buscar_match_libros(){

}


int main(){
    mostrar_todos_los_datos();
    return 0;
}