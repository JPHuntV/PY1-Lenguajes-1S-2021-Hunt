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


int getTopAulas();
int getTopProfesores();
int getReservasMesAnio();

int getReservasByDia(char *pFecha);
int getReservasByAula(char *pAula);
int getReservasByCurso(int anio, int periodo, char *pCurso, int grupo);
void freeMysql();

//establecer conexion
int conectarServidor(){
    printf("Estableciendo conexión con el servidor...");
    conn = mysql_init(NULL);
    if(!mysql_real_connect(conn, sqlServer, user, password, database, 0, NULL, 0)){
        fprintf(stderr, "%s\n", mysql_error(conn));
    }else{
        printf("\nconexion establecida \n");
    }
}


void insertAula(struct Aula *pAula){
    char query[2000];
    sprintf(query, "call insertAula('%s',%s)",pAula->nombre, pAula->capacidad);
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n\n", mysql_error(conn));
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
    char query[2000];
    sprintf(query, "call insertProfesor(%d,'%s')",pProfesor->cedula, pProfesor->nombre);
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
    char query[2000];
    sprintf(query, "call insertCursoXPeriodo('%s',%d,%d,%d,%s,%d)",
            pCursoXPeriodo->codigoCurso, pCursoXPeriodo->anio, pCursoXPeriodo->periodo,
            pCursoXPeriodo->grupo,pCursoXPeriodo->cedProfesor, pCursoXPeriodo->cantidadEstudiantes);

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
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    res = mysql_store_result(conn);
    return (int)mysql_num_rows(res);
}


void insertReserva(struct Reserva *pReserva){
    char query[2000];
    sprintf(query, "call insertReserva('%s','%s','%s', '%s', %d, %d, '%s', %d)",
            pReserva->fecha, pReserva->horaInicio, pReserva->horaFinal, pReserva->nombreAula,
            pReserva->anio, pReserva->periodo, pReserva->codigoCurso, pReserva->grupo);

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
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }else{
        res = mysql_store_result(conn);
    }
    return ;
}
/**********************************************************/
int getTopAulas(){
    char *query = "call topAulas();";
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }else{
        res = mysql_store_result(conn);
    }
    return (int)mysql_num_rows(res);;
}

int getTopProfesores(){
    char *query = "call topProfesores();";
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }else{
        res = mysql_store_result(conn);
    }
    return (int)mysql_num_rows(res);;
}

int getReservasMesAnio(){
    char *query = "call reservasMesAnio();";
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }else{
        res = mysql_store_result(conn);
    }
    return (int)mysql_num_rows(res);;
}
/*************************************************************/
int getReservasByDia(char *pFecha){
    char query[2000];
    sprintf(query, "call getReservasByDia('%s')",pFecha);
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }else{
        res = mysql_store_result(conn);
    }
    return (int)mysql_num_rows(res);;
}

int getReservasByAula(char *pAula){
    char query[2000];
    sprintf(query, "call getReservasByAula('%s')",pAula);
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }else{
        res = mysql_store_result(conn);
    }
    return (int)mysql_num_rows(res);;
}

int getReservasByCurso(int anio, int periodo, char *pCurso, int grupo){
    char query[2000];
    sprintf(query, "call getReservasByCurso(%d,%d,'%s',%d)",anio, periodo, pCurso, grupo);
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }else{
        res = mysql_store_result(conn);
    }
    return (int)mysql_num_rows(res);;
}
/////////////////////
void freeMysql(){
    do
    {
        if(res = mysql_store_result(conn)){
            mysql_free_result(res);
        }
    } while (mysql_more_results(conn)&&mysql_next_result(conn));
    
    return;
}
#endif