#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "structs.h"
#include "server.h"


//typedef enum {false, true} bool;
//declaraciones

#define LSIZ 128
#define RSIZ 10
#define MAX_YR 2222
#define MIN_YR 2021


typedef struct{
    int yyyy;
    int mm;
    int dd;
} Date;

typedef struct{
    int MM;
    int HH;
} Time;

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

void reservarAula();
void cancelarReservacion();

bool esNumero(char *token);
int IsLeapYear(int year);
int isValidDate(Date *validDate);
int validarHora(Time *pHora);
int validarHoraInicioFin(Time *pInicio, Time *pFin);


void menuEstadisticas();
void topAulas();
void topProfesores();
void reservasMesAnio();


void opcionesGenerales();
void consultaDia();
void consultaAula();
void consultaCurso();
void pausa();
void salir();



int main(){
    system("clear");
    conectarServidor();
    menuPrincipal();
    return 0;
}

void menuPrincipal(){

    char opcion;
    char repetir = 1;
    do{
        
        printf("\n#####  Menú principal  #####\n\n");
        printf("1.Información de aulas. \n");
        printf("2.Información de profesores. \n");
        printf("3.Información de cursos. \n");
        printf("4.Cursos por periodo. \n");
        printf("5.Reservación de aula \n");
        printf("6.Cancelar reservación. \n");
        printf("7.Estadisticas. \n");
        printf("8.Opciones generales.\n");
        printf("9.Salir.\n");
        printf("#############################\n");
        printf("Seleccione una opcion del 1 al 9:\t");

        scanf(" %c", &opcion);
        switch (opcion)
        {
        case '1':
            leerArchivo();
            break;
        
        case '2':
            menuProfesores();
            break;
        
        case '3':
            informacionDeCursos();
            break;
        
        case '4':
            menuCursosXPeriodo();
            break;
        
        case '5':
            reservarAula();
            break;
        
        case '6':
            cancelarReservacion();
            break;
        
        case '7':
            menuEstadisticas();
            break;
    
        case '8':
            opcionesGenerales();
            break;

        case '9':
            repetir = 0;
            break;
        
        default:
            break;
        }
    }while(repetir);
    printf("saliendo......\n");
    salir();
    

    return;
}

void leerArchivo(){

    FILE *archivo;
    int tamanio;
    int cantidadLineas = 0;
    char ultimoCaracter;
    char ruta[200];
    printf("\nPorfavor indique la ruta del archivo:");
    scanf("%s",ruta);
    archivo = fopen(ruta, "r+");
    while((getchar()!='\n'));
    if(archivo == NULL){
        printf("\n\nLa ruta indicada no existe o no está disponible.\n");
        return;
    }
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
    printf("\nSe incluiran las siguientes aulas\n");
    struct Aula Aulas[i];
    for(i = 0; i<j; ++i){
        char *str = lineas[i];
        char *token = strtok(str,",");
        token = strtok(NULL,",");

        if(token != NULL && esNumero(token) ==true){
            struct Aula pAula;
            pAula.nombre = str;
            pAula.capacidad= token;
            printf("\nAula:%s\tCapacidad:%s", pAula.nombre, pAula.capacidad);
            insertAula(&pAula);
        }  
    }
    printf("------------------------------------\n");
    pausa();

    return;

}


bool esNumero(char *token){
    bool res = true;
    for(int i = 0 ; token[i]!='\0';i++){
        if(!isdigit(token[i])){res = false;}
    }

    return res;
}
///////////////////////PROFESORES///////////////////////
void menuProfesores(){
    system("clear");
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
            break;
        }
    }while(repetir);
    return;
}

void incluirProfesor()
{
    system("clear");
    struct Profesor pProfesor;

    printf("\nIngrese el número de cédula del profesor:\t");
    while(scanf("%d", &pProfesor.cedula)!=1){
        while((getchar()!='\n'));
        printf("\nEl valor ingresado es incorrecto\nPor favor intentelo de nuevo\n");
        printf("\nIngrese el número de cédula del profesor:\t");
    }

    printf("\nIngrese el nombre del profesor:\t");
    scanf(" %[^\n]", pProfesor.nombre);

    insertProfesor(&pProfesor);
    pausa();
    freeMysql();
    return;
}


void listarProfesores(){
    system("clear");
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
    delProfesores();
    freeMysql();
    pausa();
    return;
}
/////////////////////////////////////////////////////////



void informacionDeCursos(){
    system("clear");
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
            break;
        }
    }while(repetir);
    return;
}

void incluirCursosXPeriodo(){
    system("clear");
    int cantidadCursos = getInfoCursos();
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

    freeMysql();

    printf("\nDigite el año en el que se va a cursar:\t");
    scanf("%d", &pCursoXPeriodo.anio);

    printf("\nDigite el periodo en el que se va a cursar:\t");
    scanf("%d", &pCursoXPeriodo.periodo);

    printf("\nDigite el numero del grupo:\t");
    scanf("%d", &pCursoXPeriodo.grupo);

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

    freeMysql();

    printf("\nDigite la cantidad de estudiantes que admitirá el curso:\t");
    scanf("%d", &pCursoXPeriodo.cantidadEstudiantes);
    
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
    listarCursosXPeriodo();
    int id;
    printf("\nDigite el numero del curso por periodo que desea eliminar:\t");
    scanf("%d", &id);
    delInfoCursosXPeriodo(id);
    freeMysql();
    pausa();
    return;
}
///////////////////////////////////////////////////////////////////////////////////




///////Reservaciones////////////////////////////


void reservarAula(){
    system("clear");
    struct Reserva pReserva;
    Date fecha ={0};
    int fechaValida;
    printf("\nFecha de inicio (dd/mm/aaaa):\t");
    scanf("%d/%d/%d",&fecha.dd, &fecha.mm, &fecha.yyyy);

    fechaValida = isValidDate(&fecha);
    while(fechaValida!=1){
        while((getchar()!='\n'));
        printf("\nPor favor ingrese una fecha valida en el formato indicado!\n");
        printf("\nFecha de inicio (dd/mm/aaaa):\t");
        scanf("%d/%d/%d",&fecha.dd, &fecha.mm, &fecha.yyyy);
        fechaValida = isValidDate(&fecha);
    }
    Time horaInicio = {0};
    int horaValida;
    printf("\nHora de inicio (HH:MM):\t");
    scanf("%d:%d",&horaInicio.HH, &horaInicio.MM);
    horaValida = validarHora(&horaInicio);
    while(horaValida!=1){
        while((getchar()!='\n'));
        printf("\nPor favor ingrese una hora valida en el formato indicado!\n");
        printf("\nHora de inicio (HH:MM):\t");
        scanf("%d:%d",&horaInicio.HH, &horaInicio.MM);
        horaValida = validarHora(&horaInicio);
    }

    Time horaFin = {0};
    printf("\nHora de salida (HH:MM):\t");
    scanf("%d:%d",&horaFin.HH, &horaFin.MM);
    horaValida = validarHora(&horaFin);
    while(horaValida!=1 && validarHoraInicioFin(&horaInicio, &horaFin)!=1){
        while((getchar()!='\n'));
        printf("\nPor favor ingrese una hora valida en el formato indicado!\n");
        printf("\nHora de salida (HH:MM):\t");
        scanf("%d:%d",&horaFin.HH, &horaFin.MM);
        horaValida = validarHora(&horaFin);
    }
    while((getchar()!='\n'));
   

    sprintf(pReserva.fecha, "%d-%d-%d", fecha.yyyy, fecha.mm, fecha.dd);
    sprintf(pReserva.horaInicio, "%d:%d:00", horaInicio.HH, horaInicio.MM);
    sprintf(pReserva.horaFinal, "%d:%d:00", horaFin.HH, horaFin.MM);
    //año sale del struct, dato repetido pero solicitado

    printf("\nPeriodo (1 ó 2):\t");
    scanf("%d",&pReserva.periodo);

    
    int cantidadCursos = getInfoCursosXPeriodoByAnio(fecha.yyyy, pReserva.periodo);
    char* cursos[cantidadCursos];
    char* grupos[cantidadCursos];
    char* cantEstudiantes[cantidadCursos];
    if(cantidadCursos == 0){
        printf("\n\nAun no existen cursos registrados en el periodo indicado.\nRegistre un curso en intente de nuevo\n");
        freeMysql();
        return;
    }
    int i=0;
    printf("\n  Codigo Curso\tNombre Curso\tAño\tPeriodo\tGrupo\tProfesor\t\tCantidad de estudiantes\n");
    while ((row = mysql_fetch_row(res)) != NULL)
    {
        printf("%d.%s\t%s\t%s\t%s\t%s\t%s\t%s\n",i,row[0], row[1], row[2], row[3], row[4], row[5], row[6]);
        cursos[i] = row[0];
        grupos[i] = row[4];
        cantEstudiantes[i]= row[6];
        i++;
    }
    freeMysql();
    int numCurso;
    printf("\nDigite el numero de curso que quiere asociar:\t");
    scanf("%d", &numCurso);
    pReserva.codigoCurso=cursos[numCurso];
    long test;
    char *temp;
    pReserva.grupo = strtol(grupos[numCurso], &temp,10);
    char* cantidadEstudiantes=cantEstudiantes[numCurso];
    int cantidadAulas = getInfoAulas(&pReserva, cantidadEstudiantes);
    if(cantidadAulas ==0){
        printf("\nNo existen aulas disponibles para el curso y fecha indicados.\n");
        freeMysql();
        return;
    }
    printf("\nLas siguientes aulas se encuentran disponibles:\n\n\tAula\t\tCapacidad\n");
    char *aulas[cantidadAulas];
    i=0;
    while ((row = mysql_fetch_row(res)) != NULL)
    {
        printf("%d.\t%s\t%s\t\t\n",i,row[0], row[1]);
        aulas[i] = row[0];
        i++;
    }

    int numAula;
    printf("\nDigite el numero aula que quiere reservar:\t");
    scanf("%d", &numAula);
    pReserva.nombreAula=aulas[numAula];
    pReserva.anio = fecha.yyyy;
    freeMysql();

    insertReserva(&pReserva);
    printf("El numero de reservación es:\t");
    i=0;
    while ((row = mysql_fetch_row(res)) != NULL)
    {
        printf("%s",row[0]);
        i++;
    }
    freeMysql();
    pausa();
    return;
    
}


void cancelarReservacion(){
    system("clear");
    freeMysql();
    printf("Digite el codigo de la reservación que desea cancelar:\t");
    int codigo;
    scanf("%d", &codigo);
    
    if(getReserva(codigo) == 1){
        freeMysql();
        delReserva(codigo);
        printf("\n\nSu reservación ha sido cancelada\n");
        pausa();
    }else{
        printf("\nNo existe ninguna reserva con el codigo indicado\n");
        freeMysql();
        pausa();
        return;
    }
    freeMysql();
    return;
}



/********************************************
 * fuente:aticleworld.com/check-valid-date/
 * *****************************************/
int IsLeapYear(int year){
    return(((year % 4 == 0) && (year % 100 != 0)) || (year %400 == 0));
}

int isValidDate(Date *validDate){
    if(validDate->yyyy > MAX_YR || validDate->yyyy <MIN_YR) return 0;
    if(validDate->mm <1 || validDate->mm >12) return 0;
    if(validDate->dd <1 || validDate->dd > 31) return 0;

    if(validDate->mm ==2){
        if(IsLeapYear(validDate->yyyy)) return(validDate->dd <=29);
        else return (validDate->dd <= 28);
    }

    if(validDate->mm ==4 || validDate ->mm ==6 || validDate->mm ==9 || validDate->mm ==11)
        return(validDate->dd <=30);
    return 1;
}
/*********************************************************************************************/


int validarHora(Time *pHora){
    if(pHora->HH>24 || pHora->HH < 0) return 0;
    if(pHora->MM>59 || pHora->MM < 0) return 0;
    return 1;
}


int validarHoraInicioFin(Time *pInicio, Time *pFin){
    if(pInicio->HH>pFin->HH) return 0;
    if(pInicio->HH==pFin->HH && pInicio->MM>pFin->MM) return 0;
    return 1;
}

/****************************************************************************************************/



///////////////////////////////Estadisticas////////////////////////////////////////////////////

void menuEstadisticas(){
    system("clear");
    char opcion;
    char repetir = 1;
    do{
        
        printf("#####   Estadísticas  #####\n\n");
        printf("1.Top 3 aulas más reservadas. \n");
        printf("2.Top 3 profesores con más reservas. \n");
        printf("3.Cantidad de reservaciones por año-mes\n");
        printf("4.Volver al menú principal\n");
        printf("5.Salir\n");
        printf("#############################\n");
        printf("Seleccione una opcion del 1 al 5:\t");

        scanf(" %c", &opcion);
        switch (opcion)
        {
        case '1':
            topAulas();
            break;
        
        case '2':
            topProfesores();
            break;
        
        case '3':
            reservasMesAnio();
            break;
        
        case '4':
            repetir = 0;
            break;
    
        case '5':
            salir();
        
        default:
            break;
        }
    }while(repetir);
    return;
}


void topAulas(){
    system("clear");
    int cantidad = getTopAulas();
    printf("  Aula\tCantidad de reservaciones\n");
    int i=1;
    while ((row = mysql_fetch_row(res)) != NULL)
    {
        printf("%d.%s\t%s\n",i,row[0], row[1]);
        i++;
    }
    freeMysql();
    
    return;
}

void topProfesores(){
    system("clear");
    int cantidad = getTopProfesores();
    printf("  Profesor\tCantidad de reservaciones\n");
    int i=1;
    while ((row = mysql_fetch_row(res)) != NULL)
    {
        printf("%d.%s\t%s\n",i,row[0], row[1]);
        i++;
    }
    freeMysql();
    
    return;
}

void reservasMesAnio(){
    system("clear");
    int cantidad = getReservasMesAnio();
    printf("  Mes\tAño\tCantidad de reservaciones\n");
    int i=1;
    while ((row = mysql_fetch_row(res)) != NULL)
    {
        printf("%d.%s\t%s\t%s\n",i,row[0], row[1],row[2]);
        i++;
    }
    freeMysql();
    
    return;
}
/*******************************************************************************/



//////////////////////////////////OPCIONES GENERALES////////////////////////////////////

void opcionesGenerales(){
    system("clear");
    char opcion;
    char repetir = 1;
    do{
        
        printf("#####   Opciones Generales  #####\n\n");
        printf("1.Consultar reservas por dia. \n");
        printf("2.Consultar reservas por aula. \n");
        printf("3.Consultar reservas por curso.\n");
        printf("4.Volver al menú principal\n");
        printf("5.Salir\n");
        printf("#############################\n");
        printf("Seleccione una opcion del 1 al 5:\t");

        scanf(" %c", &opcion);
        switch (opcion)
        {
        case '1':
            consultaDia();
            break;
        
        case '2':
            consultaAula();
            break;
        
        case '3':
            consultaCurso();
            break;
        
        case '4':
            repetir = 0;
            break;
    
        case '5':
            salir();
        
        default:
            break;
        }
    }while(repetir);
    return;
}

void consultaDia(){
    system("clear");
    Date fecha ={0};
    int fechaValida;
    printf("\nFecha a consultar (dd/mm/aaaa):\t");
    scanf("%d/%d/%d",&fecha.dd, &fecha.mm, &fecha.yyyy);

    fechaValida = isValidDate(&fecha);
    while(fechaValida!=1){
        while((getchar()!='\n'));
        printf("\nPor favor ingrese una fecha valida en el formato indicado!\n");
        printf("\nFecha a consultar(dd/mm/aaaa):\t");
        scanf("%d/%d/%d",&fecha.dd, &fecha.mm, &fecha.yyyy);
        fechaValida = isValidDate(&fecha);
    }
    char pFecha[10];
    sprintf(pFecha, "%d-%d-%d", fecha.yyyy, fecha.mm, fecha.dd);
    int cantidad = getReservasByDia(pFecha);
    printf("  Aula\tCód reserva\tAño\tPeríodo\tCód curso\tGrupo\tHora inicio\tHora final\n");
    int i=1;
    while ((row = mysql_fetch_row(res)) != NULL)
    {
        if(row[1]==NULL){
            printf("%d.%s\tSin reservaciones\n",i, row[0]);
        }else{
            printf("%d.%s\t%s\t\t%s\t%s\t%s\t\t%s\t%s\t%s\n",i,row[0], row[1],row[2],row[3],row[4],row[5],row[6],row[7]);
        }
        
        i++;
    }
    freeMysql();
    return;
}

void consultaAula(){
    system("clear");
    char aula[4];
    printf("Nombre del aula a consultar:\t");
    scanf("%s", aula);
    int cantidad = getReservasByAula(aula);
    printf("  Cód reserva\tFecha\t\tInicio\t\tFin\t\tAula\tAño\tPeríodo\tCódigo Curso\n");
    int i=1;
    while ((row = mysql_fetch_row(res)) != NULL)
    {
        if(row[1]==NULL){
            printf("%d.%s\tSin reservaciones\n",i, row[0]);
        }else{
            printf("%d.%s\t\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n",i,row[0], row[1],row[2],row[3],row[4],row[5],row[6],row[7]);
        }
        
        i++;
    }
    freeMysql();
    return;
}


void consultaCurso(){
    system("clear");
    int anio;
    printf("\nAño del curso:");
    scanf("%d", &anio);

    int periodo;
    printf("\nPeriodo del curso:");
    scanf("%d", &periodo);

    char curso[6];
    printf("Codigo del curso a consultar:\t");
    scanf("%s", curso);

    int grupo;
    printf("\nNúmero de grupo:");
    scanf("%d", &grupo);
    int cantidad = getReservasByCurso(anio, periodo, curso, grupo);
    printf("  Cód reserva\tFecha\t\tInicio\t\tFin\t\tAula\n");
    int i=1;
    if(cantidad ==0){
        printf("\nEste curso no existe o no tiene reservaciones.\n");
    }
    while ((row = mysql_fetch_row(res)) != NULL)
    {
        if(row[1]==NULL){
            printf("%d.%s\tSin reservaciones\n",i, row[0]);
        }else{
            printf("%d.%s\t\t%s\t%s\t%s\t%s\n",i,row[0], row[1],row[2],row[3],row[4]);
        }
        
        i++;
    }
    freeMysql();
    return;
}
/*******************************************************************/
void pausa(){
    getchar();
    printf("\n\nPresione enter para continuar....");
    getchar();
    system("clear");
    return;
}
void salir(){
    exit(0);
}