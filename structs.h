#ifndef structs
#define structs

struct Aula{
    char *nombre;
    char *capacidad;
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
    char *codigoReserva;
    char fecha[10];
    char horaInicio[8];
    char horaFinal[8];
    char *nombreAula;
    int anio;
    int periodo;
    char *codigoCurso;
    int grupo;
};



#endif