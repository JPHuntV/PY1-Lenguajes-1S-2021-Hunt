#ifndef structs
#define structs

struct Aula{
    char nombre[4];
    int capacidad;
};

struct Profesor
{
    int cedula;
    char nombre[50];
};

struct Curso
{
    char codigoCurso[6];
    char codigoCarrera[2];
    char nombre[50];
};

struct CursoXPeriodo
{
    char *codigoCurso;
    int anio;
    int periodo;
    int grupo;
    char *cedProfesor;
    int cantidadEstudiantes;
};

struct Reserva
{
    char codigoReserva[6];
    char fecha[10];
    char horaInicio[5];
    char horaFinal[5];
    char nombreAula[4];
    int anio[4];
    int periodo[1];
    char codigoCurso[6];
    int grupo;
};



#endif