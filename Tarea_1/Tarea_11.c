#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
/* 
ARITO DE CBOLLA

1.- cortar en aritos y separar en aritos individuales
2.- hacemos un masita, textura-> liquido espeso 
            harina
            especias -paprika-
            sal
            agua con gas o alguna wea carbonatada
            



 */
#define BSIZE 1024
#define TRUE 1
#define FALSE 0

typedef struct columnas { //es necesario definir la longitud?
    char titulo[100];           //Asumimos que el titulo y el autor no pueden tener más de 100 caracteres :)
    char autor[100];
    char anio[100];               //el año no puede tener más de 4 números (char v int?)
    char estante_numero[100];
    char estante_seccion[100];
    char piso[100];
    char edificio[100];          //No tendrá más de 20 caracteres
    char sede[100];              //No tendrá más de 15 cáracteres

}dict;

void mostrar_valores(dict values[], int len){

    for(int i=0; i<len-1; i=i+1){
        printf(" Titulo: %s\n Autor: %s\n Anio: %s\n Estante Numero: %s\n Estante Seccion: %s\n Piso: %s\n Edificio: %s\n Sede:%s\n\n",
         values[i].titulo,
         values[i].autor,
         values[i].anio,
         values[i].estante_numero,
         values[i].estante_seccion, 
         values[i].piso,
         values[i].edificio,
         values[i].sede);        
    }
}

int buscar_libro(dict values[], int len){
    //CREAR UN MATCH ENTRE EN EL ARREGLO
    //Primero realizaremos un buscar por TITULO
    char input_titulo[100];
    char *auxiliar;
    int ch[100];
    fflush(stdout);
    printf("Ingrese el titulo del libro que desea buscar:\n");

    
    fgets(input_titulo,100,stdin);                       //Usamos Fgets para obtener toda la frase y no unicamente la primera palabra
    input_titulo[strlen(input_titulo)-1]='\0';          /* 
                                                        fgets tiene una forma partituclar de expresar las cadenas, al obtener una este la almacena siempre terminandola
                                                        en un \n es decir, con un salto de linea que si nosotros almacenamos la cadena "hola" C la leera como:

                                                        {"h","o","l","a","\n"}

                                                        Sin embargo, las cadenas que almacenamos por el csv estan almacenadas con el termino'\0' la cual expresa un termino de cadena
                                                        de ello hemos de cambiar el final de fgets con:

                                                        input_titulo[strlen(input_titulo)-1]='\0';
                                        
                                                        */


    
    //Comprobando como funciona el strcmp(), veamos si funciona con listas 

      /* 
      BUSCAR LIBRO MEDIANTE TITULO

      creamos un for con el largo de nustro array, y nuestro objetivo es comparar nuestro input con cada valor
      i del titulo que ya ha sido almacenado. de ello crearemos una variable auxiliar que almacene el titulo
      temporal con el cual queremos comparar
      lo que logramos hacer es comparar el titulo[i] con el input y cuando este se encuentre el match pasar al 
      if demostrar que hemos encontrado el libro

      EXISTE UN PROBLEMA!
        unicamente podemos hacer match con el primer libro que encontremos
        Si aun no me hago entender es que no podemos demostrar que se han encontrado dos libros iguales /ediiones distintas

             :))
        
    
    
     */

    //EN ESTRICTO RIGOR ESTO DEBERIA ESTAR DENTRO DE UN WHILE HASTA QUE EL USUARIO QUIERA SALIR DEL LOOP
    //CONDICIÓN A AGREGAR.
    for(int i=0; i<len-1; i=i+1){
        auxiliar = values[i].titulo;
        if ((strcmp( auxiliar, input_titulo)==0)){
            printf("\nHEMOS ENCONTRADO TU LIBRO!\n");
            printf("\nTitulo: %s\n Autor: %s\n Anio: %s\n Estante Numero: %s\n Estante Seccion: %s\n Piso: %s\n Edificio: %s\n Sede:%s\n\n",
            values[i].titulo,
            values[i].autor,
            values[i].anio,
            values[i].estante_numero,
            values[i].estante_seccion, 
            values[i].piso,
            values[i].edificio,
            values[i].sede);
            return i;
            
        }
    }
    if((strcmp(auxiliar, input_titulo ))!=0){
            printf("Lo sentimos, tu libro no es parte de nuestro repositorio");
            printf("\nauxiliar= %s\n   \ninput_titulo: %s",auxiliar,input_titulo);
            return -1;
        }
    
}

int leer_csv(dict values[]){
  /* DEFINIMOS VARIABLES PARA LEER EL CSV */
    int contador_filas = 0;
    int contador_celda = 0;
    char buffer[BSIZE];  //para leer el csv
    FILE *archivo = fopen("inventario.csv","r");  //puntero con la dirección del csv, con el caracter "r" -> read

    /* CONDICION EN CASO DE QUE NO PODAMOS LEER EL ARCHIVO */
    if (archivo == NULL){                       //condición en caso de que se presente algun problema al tratar de leer el archivo 
        perror("No es posible abrir el archivo, revise el formato y/o su directorio.");
        exit(1);
    }

    /* PROCESO PARA LEER EL CSV */
    
    int i = 0;  //variable que nos ayudará a recorrer las filas y colocarlas en el array. Comenzamos en 1 para saltarnos indice de csv.
    while(fgets(buffer, BSIZE , archivo)){
        contador_filas++;
        if(i == 0){
            i++;
            continue;} //se salta el primer fgets
        
        contador_celda = 0;
        int comillas = 0;
        for (int j = 0; j < strlen(buffer); j++) //Se quitan las , que no sean separadores reales
        {
            if (buffer[j] == '"' && comillas == 0){
                comillas = 1;
                continue;
            }
            if (buffer[j] == '"' && comillas == 1){
                comillas = 0;
                continue;
            }
            if (buffer[j] == ',' && comillas == 0){
                buffer[j] = '~';
            }
        }
        char *celda = strtok(buffer, "~");      //leemos la cadena y separamos por excelencia ","

        for(contador_celda = 0; contador_celda < 8; contador_celda++){ //creamos el otro while para el cual ira incluyendo cada elemento leido en el csv en el array
                                                                        /* 
                                                                        Definamos un concepto, llamaremos celda a cada atributo encerrados por "," de aquel modo, -> ,titulo, es una celda.

                                                                        De ello, el primer while itera entre las filas del dataframe, leyendo mediante la funcion fgets y el buffer
                                                                        Sin embargo, esto nos permite unicamente leer el csv entero y no clasificarlo. Con ello hemos de crear otro while 
                                                                        que se expresa mediante la definición de "celda". Entonces, como sabemos que existen 8 campos por los cuales nos interesa
                                                                                                                                                                        
                                                                        */
            if (contador_celda == 0){
                strcpy(values[i-1].titulo, celda);       //strcpy(valor1,valor2) reemplazamos/agregamos el valor1 por el valor2
            }
            if (contador_celda == 1){
                strcpy(values[i-1].autor, celda);       
            }
            if (contador_celda == 2){
                strcpy(values[i-1].anio, celda);       
            }
            if (contador_celda == 3){
                strcpy(values[i-1].estante_numero, celda);       
            }
            if (contador_celda == 4){
                strcpy(values[i-1].estante_seccion, celda);       
            }
            if (contador_celda == 5){
                strcpy(values[i-1].piso, celda);       
            }
            if (contador_celda == 6){
                strcpy(values[i-1].edificio, celda);       
            }
            if (contador_celda == 7){
                strcpy(values[i-1].sede, celda);       
            }
            celda = strtok(NULL, "~");
        }
        i++;
    }
    fclose(archivo); //cerramos el archivo ahora que tenemos todo el array

    return(contador_filas);       
}

void editar_libro(dict values[], int len){
    
    //para editar un libro primero hay verificar si este existe, para ello usaremos la función buscar libro
    int pos_editar_libro;
    int pos_editar_libro = buscar_libro(values, len);       //basicamente este es nuestro values
    
    if (pos_editar_libro != -1){  //para cualquier valor que sea distinto a -1 querrá decir que se ha encontrado el libro, entonces, hemos de elegir que es lo que queremos editar

        //Dejamos al usuario elegir sobre que quiere editar
        int editar_elegir;
        char editar_input;
        printf("1.- Titulo\n");
        printf("2.- Autor\n");
        printf("3.- Año\n");
        printf("4.- estante_numero\n");
        printf("5.- estante_seccion\n");
        printf("6.- piso;\n");
        printf("7.- edificio;\n");
        printf("8.- sede;\n");
        printf("Seleccione el campo del libro que desea editar: ");
        scanf("%i",&editar_elegir);

        if (editar_elegir == 1){ //editamos el titulo

            printf("El titulo libro actualmente es:\n");
            printf("%s\n", values[pos_editar_libro].titulo);
            printf("Ingrese el titulo que desea:\n");
            scanf("%s", &editar_input);
            strcpy(values[pos_editar_libro].titulo, editar_input);
            printf("Se ha cambiado");
        }
        if (editar_elegir == 2){ //editamos autor

            printf("El autor libro actualmente es:\n");
            printf("%s\n", values[pos_editar_libro].autor);
            printf("Ingrese el autor que desea:\n");
            scanf("%s", &editar_input);
            strcpy(values[pos_editar_libro].autor, editar_input);
            printf("Se ha cambiado");

        }
        if (editar_elegir == 3){ //editamos el anio

            printf("El año libro actualmente es:\n");
            printf("%s\n", values[pos_editar_libro].anio);
            printf("Ingrese el año que desea:\n");
            scanf("%s", &editar_input);
            strcpy(values[pos_editar_libro].anio, editar_input);
            printf("Se ha cambiado!");
        }
        if (editar_elegir == 4){ //editamos el estante_numero

            printf("El estante numero del libro actualmente es:\n");
            printf("%s\n", values[pos_editar_libro].estante_numero);
            printf("Ingrese el estante_numero que desea:\n");
            scanf("%s", &editar_input);
            strcpy(values[pos_editar_libro].estante_numero, editar_input);
            printf("Se ha cambiado!");
        }
        if (editar_elegir == 5){ //editamos el esatnte_seccion

            printf("el estante seccion del libro actualmente es:\n");
            printf("%s\n", values[pos_editar_libro].estante_seccion);
            printf("Ingrese el estante_seccion que desea:\n");
            scanf("%s", &editar_input);
            strcpy(values[pos_editar_libro].estante_seccion, editar_input);
            printf("Se ha cambiado!");
        }
        if (editar_elegir == 6){ //editamos el piso
            printf("el piso del libro actualmente es:\n");
            printf("%s\n", values[pos_editar_libro].piso);
            printf("Ingrese el piso que desea:\n");
            scanf("%s", &editar_input);
            strcpy(values[pos_editar_libro].piso, editar_input);
            printf("Se ha cambiado!");
        }
        if (editar_elegir == 7){ //editamos el edificio

            printf("el edificio del libro actualmente es:\n");
            printf("%s\n", values[pos_editar_libro].edificio);
            printf("Ingrese el edificio que desea:\n");
            scanf("%s", &editar_input);
            strcpy(values[pos_editar_libro].edificio, editar_input);
            printf("Se ha cambiado!");
        }
        if (editar_elegir == 8){ //editamos la sede

            printf("el estante seccion del libro actualmente es:\n");
            printf("%s\n", values[pos_editar_libro].estante_seccion);
            printf("Ingrese el titulo que desea:\n");
            scanf("%s", &editar_input);
            strcpy(values[pos_editar_libro].estante_seccion, editar_input);
            printf("Se ha cambiado!");
        }
    }
}




// void menu_principal()
// {
//     int opcion;
//     char repetir = TRUE;

//     do
//     {
//         system("cls");

//         printf("\n\n\t\t\tMENU PRINCIPAL\n");
//         printf("\t\t\t--------------\n");
//         printf("\n\t1. Agregar\n");
//         printf("\t2. Quitar\n");
//         printf("\t3. Editar\n");
//         printf("\t0. SALIR\n");

//         printf("\n\tIngrese una opcion: ");
//         scanf("%d", &opcion);

//         switch (opcion)
//         {
//         case 1:
//             menu_agregar();
//             break;

//         case 2:
//             menu_quitar();
//             break;

//         case 3:
//             menu_editar();
//             break;  

//         case 0:
//             repetir = FALSE;
//             break;
//         }
//     } while (repetir);
// }

// // Definiciones de las funciones

void menu_agregar(dict values[],int cantidad_filas_variable){
    int opcion;
    char repetir = TRUE;

    char titulo_agregar[100];           
    char autor_agregar[100];
    char anio_agregar[100];               
    char estante_numero_agregar[100];
    char estante_seccion_agregar[100];
    char piso_agregar[100];
    char edificio_agregar[100];          
    char sede_agregar[100];   

    do{
        

        printf("\n\n\t\t\tMENU AGREGAR\n");
        printf("\t\t\t------------------------\n");
        printf("\n\t1. Libro\n");
        printf("\t2. Sección\n");
        printf("\t3. Piso\n");
        printf("\t4. Sede\n");
        printf("\t0. REGRESAR\n");

        printf("\n\tIngrese una opcion: ");
        scanf("%i", &opcion);
     
        switch (opcion){
            case 1:
                
                printf("Nombre del libro que quiere agregar");
                scanf("%s\n",titulo_agregar);

                printf("Nombre del autor del libro");
                scanf("%s\n",autor_agregar);
                
                printf("Año del libro");
                scanf("%s\n",anio_agregar);    

                printf("En que estante lo quieres poner");
                scanf("%s\n",estante_numero_agregar);        

                printf("En que sección lo quieres poner");
                scanf("%s\n",estante_seccion_agregar);
                
                printf("En que piso lo quieres poner");
                scanf("%s\n",piso_agregar);

                printf("En que edificio quieres ponerlo");
                scanf("%s\n",edificio_agregar);
                
                printf("¿En que sede?");
                scanf("%s\n",sede_agregar);

                for (int i = 0; i<cantidad_filas_variable; i++){
                    if ((values[i].titulo == "$Vacio$") && (values[i].autor == autor_agregar || values[i].autor == "$Vacio$") && (values[i].anio == anio_agregar || values[i].anio == "$Vacio$") && (values[i].estante_numero == estante_numero_agregar || values[i].estante_numero == "$Vacio$") && (values[i].estante_seccion == estante_seccion_agregar || values[i].estante_seccion == "$Vacio$") && (values[i].piso == piso_agregar || values[i].piso == "$Vacio$") && (values[i].edificio == edificio_agregar || values[i].edificio == "$Vacio$") && (values[i].sede == sede_agregar || values[i].sede == "$Vacio$")){
                        values[i].titulo= titulo_agregar;
                        values[i].autor=autor_agregar;
                        values[i].anio=anio_agregar;
                        values[i].estante_numero=estante_numero_agregar;
                        values[i].estante_seccion=estante_seccion_agregar;
                        values[i].piso=piso_agregar;
                        values[i].edificio=edificio_agregar;
                        values[i].sede=sede_agregar;
                        break;                
                    }
                    if (i == (cantidad_filas_variable-1)){
                        values[cantidad_filas_variable].titulo = titulo_agregar;
                        values[cantidad_filas_variable].autor=autor_agregar;
                        values[cantidad_filas_variable].anio=anio_agregar;
                        values[cantidad_filas_variable].estante_numero=estante_numero_agregar;
                        values[cantidad_filas_variable].estante_seccion=estante_seccion_agregar;
                        values[cantidad_filas_variable].piso=piso_agregar;
                        values[cantidad_filas_variable].edificio=edificio_agregar;
                        values[cantidad_filas_variable].sede= sede_agregar;

                        cantidad_filas_variable+=1;          
                    }
                }
                break;

            case 2:
                printf("¿Que piso quieres agregar?");
                scanf("%s\n",piso_agregar);

                printf("En que edificio quieres ponerlo");
                scanf("%s\n",edificio_agregar);
                
                printf("¿En que sede?");
                scanf("%s\n",sede_agregar);

                for (int i = 0; i < cantidad_filas_variable; ++i){
                    if ((values[i].piso == "$Vacio$")&&(values[i].edificio == edificio_agregar || values[i].edificio == "$Vacio$")&&(values[i].sede == sede_agregar || values[i].sede == "$Vacio$")){
                        values[i].piso=piso_agregar;
                        values[i].edificio=edificio_agregar;
                        values[i].sede= sede_agregar;
                        break;                
                    }
                    if (i == (cantidad_filas_variable-1)){
                        values[cantidad_filas_variable].titulo = "$Vacio$";
                        values[cantidad_filas_variable].autor="$Vacio$";
                        values[cantidad_filas_variable].anio="$Vacio$";
                        values[cantidad_filas_variable].estante_numero="$Vacio$";
                        values[cantidad_filas_variable].estante_seccion="$Vacio$";
                        values[cantidad_filas_variable].piso=piso_agregar;
                        values[cantidad_filas_variable].edificio=edificio_agregar;
                        values[cantidad_filas_variable].sede= sede_agregar;   
                        cantidad_filas_variable+=1;    
                    }
                }
                break;

            case 3:

                printf("En que sección lo quieres poner");
                scanf("%s\n",estante_seccion_agregar);
                
                printf("En que piso lo quieres poner");
                scanf("%s\n",piso_agregar);

                printf("En que edificio quieres ponerlo");
                scanf("%s\n",edificio_agregar);
                
                printf("¿En que sede?");
                scanf("%s\n",sede_agregar);

                for (int i = 0; i < cantidad_filas_variable; ++i){
                    if ((values[i].estante_seccion == "$Vacio$")
                    &&(values[i].piso == piso_agregar || values[i].piso == "$Vacio$")
                    &&(values[i].edificio == edificio_agregar || values[i].edificio == "$Vacio$")
                    &&(values[i].sede == sede_agregar || values[i].sede == "$Vacio$")){
                        values[i].estante_seccion=estante_seccion_agregar;
                        values[i].piso=piso_agregar;
                        values[i].edificio=edificio_agregar;
                        values[i].sede= sede_agregar;
                        break;                
                    }
                    if (i == (cantidad_filas_variable-1)){
                        values[cantidad_filas_variable].titulo = "$Vacio$";
                        values[cantidad_filas_variable].autor="$Vacio$";
                        values[cantidad_filas_variable].anio="$Vacio$";
                        values[cantidad_filas_variable].estante_numero="$Vacio$";
                        values[cantidad_filas_variable].estante_seccion=estante_seccion_agregar;
                        values[cantidad_filas_variable].piso=piso_agregar;
                        values[cantidad_filas_variable].edificio=edificio_agregar;
                        values[cantidad_filas_variable].sede= sede_agregar;
                        cantidad_filas_variable+=1;          
                    }
                }
                break;

            case 4:   
                printf("¿Que sede quiere agregar?");
                scanf("%s\n",sede_agregar);
                values[cantidad_filas_variable].titulo="$Vacio$";
                values[cantidad_filas_variable].autor="$Vacio$";
                values[cantidad_filas_variable].anio="$Vacio$";
                values[cantidad_filas_variable].estante_numero="$Vacio$";
                values[cantidad_filas_variable].estante_seccion="$Vacio$";
                values[cantidad_filas_variable].piso="$Vacio$";
                values[cantidad_filas_variable].edificio="$Vacio$";
                values[cantidad_filas_variable].sede= sede_agregar;
                cantidad_filas_variable+=1;          
                break;
    

            case 0:
                repetir = FALSE;
                break;
            }
        }while (repetir);
}

// void menu_editar()
// {
//     int opcion;
//     char repetir = TRUE;

//     do
//     {
//         system("cls");

//         printf("\n\n\t\t\tMENU EDITAR\n");
//         printf("\t\t\t------------------------\n");
//         printf("\n\t1. Titulo Libro\n");
//         printf("\t2. Autor Libro\n");
//         printf("\t3. Año Libro\n");
//         printf("\t4. Número estante Libro\n");
//         printf("\t5. Sección estante Libro\n");
//         printf("\t6. Piso Libro\n");
//         printf("\t7. Edificio Libro\n");
//         printf("\t8. Sede Libro\n");
//         printf("\t0. REGRESAR\n");

//         printf("\n\tIngrese una opcion: ");
//         scanf("%d", &opcion);

//         switch (opcion)
//         {
//         case 1:
//             //editar_titulo();
//             break;

//         case 2:
//             //editar_autor();
//             break;

//         case 3:
//             //editar_anio();
//             break;

//         case 4:
//             //editar_estante_numero();
//             break;

//         case 5:
//             //editar_estante_seccion();
//             break;

//         case 6:
//             //editar_piso();
//             break;

//         case 7:
//            // editar_edificio();
//             break;

//         case 8:
//             //editar_sede();
//             break;
          
//         case 0:
//             repetir = FALSE;
//             break;
//         }
//     } while (repetir);
// }

// void menu_quitar()
// {
//     int opcion;
//     char repetir = TRUE;

//     do
//     {
//         system("cls");

//         printf("\n\n\t\t\tMENU QUITAR\n");
//         printf("\t\t\t------------------------\n");
//         printf("\n\t1. Libro\n");
//         printf("\t2. Sección\n");
//         printf("\t3. Piso\n");
//         printf("\t4. Sede\n");
//         printf("\t0. REGRESAR\n");

//         printf("\n\tIngrese una opcion: ");
//         scanf("%d", &opcion);

//         switch (opcion)
//         {
//         case 1:
//             //quitar_libro();
//             break;

//         case 2:
//             //quitar_seccion();
//             break;

//         case 3:
//             //quitar_piso();
//             break;

//         case 4:
//             //quitar_sede();
//             break;

//         case 0:
//             repetir = FALSE;
//             break;
//         }
//     } while (repetir);
// }

// // _________________Funciones que alteran el csv________________________________
// void quitar_libro()
// {
//     char libro_quitar[100];
//     printf("¿Qué libro deseas quitar? ");
//     scanf("%s", libro_quitar);

//     // int i;
//     // for (i = 0; i < ARRAY_SIZE; i++)
//     // {
//     //     if (strcmp(myPs[i].name, myName) == 0)
//     //     {
//     //         return myPs[i].age;
//     //     }
//     // }
//     // return -1;

// }
//______________________________________________________________________________

int main(){

    dict values[999];
    int contador_filas = leer_csv(values);


    int cantidad_filas_variable = contador_filas;
    int *puntero_cantidad_fila_var;
    int puntero_cantidad_fila_var = cantidad_filas_variable;

    menu_agregar(values, cantidad_filas_variable);
    mostrar_valores(values, contador_filas);
    buscar_libro(values, contador_filas);
    
    // menu_agregar(puntero_cantidad_fila_var);
    // menu_principal() 
    return 0;
}
