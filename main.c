#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

typedef enum {false, true} bool;
//declaraciones

#define LSIZ 128
#define RSIZ 10

void menuPrincipal();
void menuProfesores();
void leerArchivo();
void transformarArchivo(FILE *archivo);
void salir();



int main(){
    menuPrincipal();
    return 0;
}

void menuPrincipal(){

    char opcion;
    char repetir = 1;
    do{
        
        printf("_____ Menú principal _____ \n\n");
        printf("1.Información de aulas. \n");
        printf("2.Información de profesores. \n");
        printf("3.Información de cursos. \n");
        printf("4.Cursos por periodo. \n");
        printf("5.Reservación de aula \n");
        printf("6.Cancelar reservación. \n");
        printf("7.Estadisticas. \n");
        printf("8.Salir.\n");
        printf("#############################\n");
        printf("Seleccione una opcion del 1 al 8:\t");

        scanf(" %c", &opcion);
        switch (opcion)
        {
        case '1':
            
            printf("opcion 1\n");
            leerArchivo();
            break;
        
        case '2':
            printf("\n======\nopcion 2\n");
            menuProfesores();
            break;
        
        case '3':
            printf("\n======\nopcion 3\n");
            break;
        
        case '4':
            printf("opcion 4\n");
            break;
        
        case '5':
            printf("opcion 5\n");
            break;
        
        case '6':
            printf("opcion 6\n");
            break;
        
        case '7':
            printf("opcion 7\n");
            break;
    
        case '8':
            repetir = 0;
            break;
        
        default:
            printf("test\n");
            break;
        }
    }while(repetir);
    printf("saliendo......\n");
    salir();
    

    return;
}


void menuProfesores(){

    char opcion;
    char repetir = 1;
    do{
        
        printf("#####   Información de profesores   #####\n\n");
        printf("1.Incluir profesor. \n");
        printf("2.Listar profesores. \n");
        printf("3.Borrar todos los profesores\n");
        printf("4.Volver al menú principal\n");
        printf("5.Salir\n");
        printf("#############################\n");
        printf("Seleccione una opcion del 1 al 5:\t");

        scanf(" %c", &opcion);
        switch (opcion)
        {
        case '1':
            
            printf("opcion 1\n");
            leerArchivo();
            break;
        
        case '2':
            printf("\n======\nopcion 2\n");
            break;
        
        case '3':
            printf("\n======\nopcion 3\n");
            break;
        
        case '4':
            repetir = 0;
            break;
    
        case '5':
            salir();
        
        default:
            printf("test\n");
            break;
        }
    }while(repetir);
    return;
}
void leerArchivo(){

    FILE *archivo;
    int tamanio;
    int cantidadLineas = 0;
    char ultimoCaracter;
    
    archivo = fopen("test.txt", "r+");
    
    if(archivo == NULL) exit(1);
    else{
        fseek(archivo, 0L, SEEK_END);
        tamanio = ftell(archivo);
        fseek(archivo, tamanio-1, SEEK_SET);
        
        ultimoCaracter = fgetc(archivo);
        
        if(ultimoCaracter!='\n') fputc('\n', archivo);

        fseek(archivo, 0L, SEEK_SET); 

        transformarArchivo(archivo);
        // int i = 0;
        // int tot = 0;       
        // while(fgets(line[i], LSIZ, archivo)){
        //     line[i][strlen(line[i])-1]='\0';
        //     i++;
        // }
        // tot = i;
        // printf("contenido del archivo\n");
        // for(i = 0; i<tot; ++i){
        //     printf(" %s\n", line[i]);
        // }
        // printf("------------------------------------\n");
    }
    fclose(archivo);
    
    return;    
}

void transformarArchivo(FILE *archivo){
    char lineas[RSIZ][LSIZ];
    int i = 0;
    int j = 0;
    
    while(fgets(lineas[i], LSIZ, archivo)){
        lineas[i][strlen(lineas[i])-1]='\0';
        i++;
    }
    j = i;
    printf("contenido del archivo\n");
    for(i = 0; i<j; ++i){
        printf("\n%d",i);
        printf("%s===>", lineas[i]);
    }
    printf("------------------------------------\n");
    return;

}


void salir(){
    exit(0);
}