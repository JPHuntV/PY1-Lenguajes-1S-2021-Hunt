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


void getInformacionDeCursos();


void insertProfesor(struct Profesor *pProfesor);
void getInfoProfesores();
void delProfesores();

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

void getInformacionDeCursos(){
    char *query = "call getInfoCursos()";
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    res = mysql_use_result(conn);
    return;
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


void getInfoProfesores(){
    char *query = "call getInfoProfesores()";
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    res = mysql_use_result(conn);
    return;
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