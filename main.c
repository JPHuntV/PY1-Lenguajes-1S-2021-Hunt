#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"
#include "server.h"


//typedef enum {false, true} bool;
//declaraciones

#define LSIZ 128
#define RSIZ 10

void menuPrincipal();

void menuProfesores();
void incluirProfesor();
void listarProfesores();
void borrarProfesores();


void menuCursosXPeriodo();
void incluirCursosXPeriodo();
void listarCursosXPeriodo();
void borrarCursosXPeriodo();

void getStructCursos(struct CursoXPeriodo *pCursosXPeriodo);
void informacionDeCursos();
void leerArchivo();
void transformarArchivo(FILE *archivo);

void pausa();
void salir();



int main(){
    conectarServidor();
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
            informacionDeCursos();
            break;
        
        case '4':
            menuCursosXPeriodo();
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
    system("clear");
    printf("\n\nmenuProfesores()....\n\n");
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
            incluirProfesor();
            break;
        
        case '2':
            listarProfesores();
            break;
        
        case '3':
            borrarProfesores();
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

///////////////////////PROFESORES///////////////////////
void incluirProfesor()
{
    system("clear");
    printf("\n\nincluirProfesor().......\n\n\n");
    struct Profesor pProfesor;

    printf("\nIngrese el número de cédula del profesor:\t");
    while(scanf("%d", &pProfesor.cedula)!=1){
        while((getchar()!='\n'));
        printf("El valor ingresado es incorrecto\nPor favor intentelo de nuevo\n");
        printf("\nIngrese el número de cédula del profesor:\t");
    }

    printf("\nIngrese el nombre del profesor:\t");
    scanf(" %[^\n]", pProfesor.nombre);

    insertProfesor(&pProfesor);
    getchar();
    pausa();
    freeMysql();
    return;
}


void listarProfesores(){
    system("clear");
    printf("\n\ninformacionDeProfesores()....\n\n");
    getInfoProfesores();

    printf("\tCédula\t\tNombre\n");
    int i=0;
    while ((row = mysql_fetch_row(res)) != NULL)
    {
        printf("%d.\t%s\t%s\t\t\n",i,row[0], row[1]);
        i++;
    }
    freeMysql();
    pausa();
    return;
}


void borrarProfesores(){
    system("clear");
    printf("\n\nborrarProfesores()....\n\n");
    delProfesores();
    freeMysql();
    pausa();
    return;
}
/////////////////////////////////////////////////////////



void informacionDeCursos(){
    system("clear");
    printf("\n\ninformacionDeCursos()....\n\n");
    getInfoCursos();
    printf("\tID Curso\tID Carrera\tNombre\n");
    int i=0;
    while ((row = mysql_fetch_row(res)) != NULL)
    {
        printf("%d.\t%s\t\t%s\t\t%s\n",i,row[0], row[1], row[2]);
        i++;
    }
    pausa();
    freeMysql();
    return;
}
//////////////////////////////////////////////////////////////////////

void menuCursosXPeriodo(){
    system("clear");
    printf("\n\nmenuCursosXPeriodo()....\n\n");
    char opcion;
    char repetir = 1;
    do{
        
        printf("#####   Cursos por periodo  #####\n\n");
        printf("1.Incluir curso por periodo. \n");
        printf("2.Listar cursos por periodo. \n");
        printf("3.Borrar cursos por periodo\n");
        printf("4.Volver al menú principal\n");
        printf("5.Salir\n");
        printf("#############################\n");
        printf("Seleccione una opcion del 1 al 5:\t");

        scanf(" %c", &opcion);
        switch (opcion)
        {
        case '1':
            incluirCursosXPeriodo();
            break;
        
        case '2':
            listarCursosXPeriodo();
            pausa();
            break;
        
        case '3':
            borrarCursosXPeriodo();
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

void incluirCursosXPeriodo(){
    system("clear");
    printf("\n\nIncluirCursosXPeriodo()...... \n");
    int cantidadCursos = getInfoCursos();
    //printf("Cantidad:%d\n", cantidadCursos);//
    struct CursoXPeriodo pCursoXPeriodo;
    char* cursos[cantidadCursos];

    if(cantidadCursos == 0){
        printf("\n\nAun no existen cursos registrados.\nRegistre un curso en intente de nuevo\n");
        freeMysql();
        return;
    }
    int i=0;
    while ((row = mysql_fetch_row(res)) != NULL)
    {
        printf("%d.\t%s\t\t%s\t\t%s\n",i,row[0], row[1], row[2]);
        cursos[i] = row[0];
        i++;
    }
    int numCurso;
    printf("\nDigite el numero de curso que quiere asociar:\t");
    scanf("%d", &numCurso);
    pCursoXPeriodo.codigoCurso=cursos[numCurso];
    //printf("elemento\n%s",pCursoXPeriodo.codigoCurso);

    freeMysql();

    printf("\nDigite el año en el que se va a cursar:\t");
    scanf("%d", &pCursoXPeriodo.anio);
   // printf("Año%d\n",pCursoXPeriodo.anio);

    printf("\nDigite el periodo en el que se va a cursar:\t");
    scanf("%d", &pCursoXPeriodo.periodo);
//    printf("Año%d\n",pCursoXPeriodo.periodo);

    printf("\nDigite el numero del grupo:\t");
    scanf("%d", &pCursoXPeriodo.grupo);
   // printf("Año%d\n",pCursoXPeriodo.grupo);

    int cantidadProfesores = getInfoProfesores();
    if(cantidadProfesores ==0){
        printf("\nAun no existen profesores registrados.\nRegistre un profesor e intente de nuevo.\n");
        freeMysql();
        return;
    }
    printf("\tCédula\t\tNombre\n");
    char *profesores[cantidadProfesores];
    i=0;
    while ((row = mysql_fetch_row(res)) != NULL)
    {
        printf("%d.\t%s\t%s\t\t\n",i,row[0], row[1]);
        profesores[i] = row[0];
        i++;
    }

    int numProf;
    printf("\nDigite el numero del profresor que quiere asociar:\t");
    scanf("%d", &numProf);
    pCursoXPeriodo.cedProfesor=profesores[numProf];
    //printf("profe\n%s",pCursoXPeriodo.cedProfesor);

    freeMysql();

    printf("\nDigite la cantidad de estudiantes que admitirá el curso:\t");
    scanf("%d", &pCursoXPeriodo.cantidadEstudiantes);
    //printf("CantEstudiantes:%d\n",pCursoXPeriodo.cantidadEstudiantes);
    

    printf("\nStruct:\nCodigoCurso:%s\tAño:%d\tPeriodo:%d\tGrupo:\t%dProfesor:%s\tCantidad:%d\n", 
        pCursoXPeriodo.codigoCurso, pCursoXPeriodo.anio, pCursoXPeriodo.periodo, pCursoXPeriodo.grupo, 
        pCursoXPeriodo.cedProfesor, pCursoXPeriodo.cantidadEstudiantes);

    insertCursoXPeriodo(&pCursoXPeriodo);
    freeMysql();
    pausa();
    return;
}

void listarCursosXPeriodo(){
    system("clear");
    printf("\n\nListaCursosXPeriodo()....\n\n");
    int cantidad = getInfoCursosXPeriodo();
    printf("  Codigo Curso\tNombre Curso\t\tAño\tPeriodo\tGrupo\tProfesor\tCantidad de estudiantes\n");
    int i=1;
    while ((row = mysql_fetch_row(res)) != NULL)
    {
        printf("%d.%s\t%s\t%s\t%s\t%s\t%s\t%s\n",i,row[0], row[1], row[2], row[3], row[4], row[5], row[6]);
        i++;
    }
    freeMysql();
    
    return;
}
void borrarCursosXPeriodo(){
    system("clear");
    printf("\n\nBorrarCursoxPeriodo()......");
    listarCursosXPeriodo();
    int id;
    printf("\nDigite el numero del curso por periodo que desea eliminar:\t");
    scanf("%d", &id);

    return;
}


void pausa(){
    getchar();
    printf("\n\nPresione enter para continuar....");
    getchar();
    return;
}
void salir(){
    exit(0);
}