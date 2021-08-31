#ifndef server
#define server

#include <mysql/mysql.h>





MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;
char *sqlServer = "localhost";
char *user = "root";
char *password = "JpHv0410";
char *database = "gestionDeAulas";




void insertAula(struct Aula *pAula);
void insertProfesor(struct Profesor *pProfesor);
int getInfoProfesores();
void delProfesores();


int getInfoCursos();

void insertCursoXPeriodo(struct CursoXPeriodo *pCursoXPeriodo);
int getInfoCursosXPeriodo();
int getInfoCursosXPeriodoByAnio(int anio, int periodo);
void delInfoCursosXPeriodo(int id);


int getInfoAulas(struct Reserva *pReserva, char* cantidadEstudiantes);
void insertReserva(struct Reserva *pReserva);
int getReserva(int codigo);
void delReserva();
void freeMysql();

//estableces conexion
int conectarServidor(){
    conn = mysql_init(NULL);
    if(!mysql_real_connect(conn, sqlServer, user, password, database, 0, NULL, 0)){
        fprintf(stderr, "%s\n", mysql_error(conn));
    }else{
        printf("\nconexion establecida \n");
    }
}


void insertAula(struct Aula *pAula){

    printf("Nombre:%s\tcedula:%s", pAula->nombre, pAula->capacidad);

    char query[2000];
    sprintf(query, "call insertAula('%s',%s)",pAula->nombre, pAula->capacidad);
    printf("\nQuery:\t%s\n",query);
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }else{
        printf("\nEl aula se ha insertado correctamente!\n");
        res = mysql_use_result(conn);
    }
    return;
}


int getInfoCursos(){
    char *query = "call getInfoCursos()";
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    res = mysql_store_result(conn);
    
    
    return (int)mysql_num_rows(res);
}

void insertProfesor(struct Profesor *pProfesor){

    printf("cedula:%d\tnombre:%s", pProfesor->cedula, pProfesor->nombre);

    char query[2000];
    //printf("\n\nQuery:\t");
    sprintf(query, "call insertProfesor(%d,'%s')",pProfesor->cedula, pProfesor->nombre);
    printf("\nQuery:\t%s\n",query);
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }else{
        printf("\nEl valor se ha insertado correctamente!\n");
        res = mysql_use_result(conn);
    }
    return;
}


int getInfoProfesores(){
    char *query = "call getInfoProfesores()";
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    res = mysql_store_result(conn);
    return (int)mysql_num_rows(res);;
}

void delProfesores(){
    char *query = "call delProfesores()";
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }else{
        printf("\n\nSe han eliminado todos los registros de profesores exitosamente\n\n");
    }
    return;
}
////////////////////////////////////////


///////CursosxPeriodo///////////////////////


void insertCursoXPeriodo(struct CursoXPeriodo *pCursoXPeriodo){
    printf("\n\ninsertCursoXPeriodo().......\n");
    char query[2000];
    sprintf(query, "call insertCursoXPeriodo('%s',%d,%d,%d,%s,%d)",
            pCursoXPeriodo->codigoCurso, pCursoXPeriodo->anio, pCursoXPeriodo->periodo,
            pCursoXPeriodo->grupo,pCursoXPeriodo->cedProfesor, pCursoXPeriodo->cantidadEstudiantes);

    printf("\nQuery:\t%s\n",query);
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }else{
        printf("\nEl valor se ha insertado correctamente!\n");
        res = mysql_use_result(conn);
    }
    return;
}

int getInfoCursosXPeriodo(){
    char *query = "call getInfoCursosXPeriodo()";
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    res = mysql_store_result(conn);
    return (int)mysql_num_rows(res);;
}

int getInfoCursosXPeriodoByAnio(int anio, int periodo){
    //char *query = "call getInfoCursosXPeriodo()";
    char query[200];
    sprintf(query, "call getInfoCursosXPeriodoByAnio(%d, %d)",anio, periodo);
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    res = mysql_store_result(conn);
    return (int)mysql_num_rows(res);
}

void delInfoCursosXPeriodo(int id){
    char query[2000];
    sprintf(query, "call delInfoCursosXPeriodoById(%d)",id);
    printf("\nQuery:\t%s\n",query);
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }else{
        printf("\n\nSe ha eliminado el curso por periodo exitosamente\n\n");
    }
    return;
}

///////////////////////////////////////////////////////////////

int getInfoAulas(struct Reserva *pReserva, char* cantidadEstudiantes){
    char query[2000];
    sprintf(query, "call getAulasAforo('%s','%s','%s',%s)",pReserva->fecha, pReserva->horaInicio,
                            pReserva->horaFinal, cantidadEstudiantes);
    printf("\nQuery:\t%s\n",query);
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    res = mysql_store_result(conn);
    return (int)mysql_num_rows(res);
}
/*insertReserva` (in pFecha date, in pHorainicio Time, in pHoraFin Time, in pNombreAula varchar(4),
					in pAnio int, in pPeriodo int, in pCodigoCurso varchar(6), in pGrupo int)
*/

void insertReserva(struct Reserva *pReserva){
    printf("\n\ninsertReserva().......\n");
    char query[2000];
    sprintf(query, "call insertReserva('%s','%s','%s', '%s', %d, %d, '%s', %d)",
            pReserva->fecha, pReserva->horaInicio, pReserva->horaFinal, pReserva->nombreAula,
            pReserva->anio, pReserva->periodo, pReserva->codigoCurso, pReserva->grupo);

    printf("\nQuery:\t%s\n",query);
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }else{
        printf("\nEl aula se ha reservado correctamente!\n");
        res = mysql_use_result(conn);
    }
    return;
}





int getReserva(int id){
    char query[2000];
    sprintf(query, "call getReserva(%d)",id);
    printf("\nQuery:\t%s\n",query);
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }else{
        res = mysql_store_result(conn);
    }
    return (int)mysql_num_rows(res);;
}


void delReserva(int id){
    char query[2000];
    sprintf(query, "call deleteReserva(%d)",id);
    printf("\nQuery:\t%s\n",query);
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }else{
        res = mysql_store_result(conn);
    }
    return ;
}

/////////////////////
void freeMysql(){
    printf("\n\nfreeMysql().....\n\n");
    do
    {
        if(res = mysql_store_result(conn)){
            mysql_free_result(res);
        }
    } while (mysql_more_results(conn)&&mysql_next_result(conn));
    
    return;
}
#endif