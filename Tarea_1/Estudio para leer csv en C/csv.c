/* Incluimos las bibliotecas necesarias */

#include <stdio.h>
#include <stdlib.h> // Preguntar para que sirve, entiendo que es para trabajar como se les de la gana con la memoria
#include <string.h> //Libreria para manejar cadenas, la usaremos para leer el csv

#define BSIZE 80 

/* 
Respecto al buffer esta algo cringe.
Resulta que las variables de C tienen limites de bytes para almacenar, por lo que el buffer size [BSIZE] unicamente apunta a decirle al compilador
"OE ESTA VARIABLE ES VIP" y con ello tiene automaticamente barra libre del tamaño que le indiques.

Si quieres leer sobre esto aqui te dejo un link.
https://stackoverflow.com/questions/1759960/buffer-size-in-c

*/


void leer_csv(){
        //Importamos el archivo que deseamos leer
        char filename[] = "weather_data.csv";
        char buffer[BSIZE];
        //definimos algunos punteros -basicamente una variable, solo que C complica todo, mañoso.-
        FILE *archivo;
        char *campo;                            // Y nuestros campos que iran de acuerdo al csv, en este caso:
        int anio,mes,dia;
        float temp_max,temp_min;                //temperatura maxima y minima, se encuentra dentro del csv

        //creamos un array con los meses para reemplazar en el csv.
        char *meses[]= {"Enero","Febrero","Marzo","Abril","Mayo","Junio","Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre"};

        /* 
        Como todo buen lindo codigo de phyton, esto es lo mismo, Acabamos de definir nuestras variables, ahora toca jugar con legos -Trabajar con lo que acabamos de crear-
        */

        //abrimos el csv
        archivo = fopen(filename,"r");          //intuitivo fopen(nombrearchivo,accion a realizar) r-> read w->write a-> append aun debo estudiar que hacen las ultimas dos
        if (archivo == NULL){                   //creamos alguna condicion en caso de que no se pueda abrir el archivo.
            //función de stdio.h perror /output de la forma ERROR: str
            perror("No es posible abrir el archivo, revise el formato y/o su directorio.");
            /* 
                Exit(0) indica que se ha terminado el programa con exito.
                Exit(1) indica que el programa se ha terminado de forma anormal.
            */
            exit(1);
        }
        
        /* 
        Toca el procesamiento de los datos, sabemos que el csv tiene los siguientes 5 campos en orden:
        [anio,mes,dia,temp_max,temp_min]
        y que todos estan separados por ","
        */

       while (fgets(buffer,BSIZE, archivo)){ //fgets() necesita tres parametros fgets(nombre_parametro_que_queremos_guardar,  maximo_de_caracteres_que_puede_tener,  la_fuente_de_donde_proviene)
            
            /*
             Ok, para no marearnos, primero definiremos que hace cada funcion que utilizaremos
            strtok() -> Rompe/corta el string bajo la condición que uno le entregue o el bien llamado token. strtok(string,cortador) -> strtok(buffer,",") 
            atoi() -> convierte el string en int atoi(campo_que_queremos_convertir_en_string)
            atof() -> convierte el string en un float atof(campo_que_queremos_convertir_en_float)
            
            Con ello claro, sigamos con el cuerpo del while.
            */

           //Año
           campo = strtok(buffer,",");
           anio = atoi(campo);
           //mes
           campo = strtok(NULL,",");    //Si entiendo bien, tener un NULL en strtok hace que salte esa palabra del cortador, por ello no corta bajo las "," y sigue a la siguiente palabra
           mes = atoi(campo);
           mes--;                       //agregamos al array de mes[]
           //dia
           campo = strtok(NULL,",");
           dia= atoi(campo);
           //temperatura maxima
           campo = strtok(NULL,",");
           temp_max = atof(campo);
           //temperatura minima
           campo = strtok(NULL,",");
           temp_min = atof(campo);

           //ahora que todas las variables han sido almacenadas, hemos de unicamente imprimirlas asi pues:
            /* 
            Dado el formato de impresion de nuestro amigo mañoso -c- hemos de definir las variables que queremos que se impriman en el siguiente orden
            dado que queremos el formato
            año -> %s
            mes -> meses[mes]
            dia -> &d
            temp-max -> %f
            temp-min -> &f
            */
           printf(" %d  %10s  %2d:  \tMax %.1f  \tMin %.1f \n",
                                        anio,
                                        meses[mes],
                                        dia,
                                        temp_max,
                                        temp_min);

            //Y TERMINAMOS EL WHILE INFINITO, LUEGO DE EXPLICAR TODAS LAS COSAS ESTAMOS LISTOS    

       }
    //cerramos el archivo.
        fclose(archivo);

        return ;
}



int main(){
    leer_csv();
    return 0;
}