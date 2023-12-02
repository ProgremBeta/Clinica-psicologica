#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

#define LIMPIAR system("cls")
#define PRESIONAR printf("\n    Presiona ENTER para continuar"); getchar();
#define SALTARLINEA(N) {for(int i=0; i<N; i++) printf("\n");}

struct FechaNacimiento {
    int dia;
    int mes;
    int year;
};

struct HistorialPsicologico {
    char trastorno[50];
    char consulta[100];
    char antecedentesFamiliares[100];
    char descripcion[200];
};

struct Paciente {
    char nombre[30];
    char apellido[30];
    int edad;
    FechaNacimiento fecha;
    HistorialPsicologico historial;
};

void Inicio() {
    printf("    TRASTORNOS PSICOLOGICOS");
    SALTARLINEA(2);
    printf("    Son sintomas psicologicos o comportamientos que afectan y crean malestar emocional a una persona\n    y que pueden llegar a ser muy graves.");
    SALTARLINEA(1);
    PRESIONAR;
}

void Menu() {
	SALTARLINEA(1);
    printf("    CLINICA PSICOLOGICA");
    SALTARLINEA(2);
    printf("    1. Agregar nuevo paciente");
    SALTARLINEA(1);
    printf("    2. Mostrar paciente por nombre y apellido");
    SALTARLINEA(1);
    printf("    3. Mostrar todos los pacientes");
    SALTARLINEA(1);
    printf("    0. Salir");
    SALTARLINEA(2);
    printf("    Ingrese su opcion: ");
}

Paciente pedirDatosPaciente() {
    Paciente nuevoPaciente;

    printf("    Ingrese el nombre: ");
    scanf("%s", nuevoPaciente.nombre);
    printf("    Ingrese el apellido: ");
    scanf("%s", nuevoPaciente.apellido);
    printf("    Ingrese la edad: ");
    scanf("%d", &nuevoPaciente.edad);

    printf("    Ingresa fecha de nacimiento");
    SALTARLINEA(1);
    printf("    Dia: ");
    scanf("%d", &nuevoPaciente.fecha.dia);
    printf("    Mes: ");
    scanf("%d", &nuevoPaciente.fecha.mes);
    printf("    Año: ");
    scanf("%d", &nuevoPaciente.fecha.year);

    printf("    Ingresa motivo de consulta del paciente: ");
    scanf("%[^\n]", nuevoPaciente.historial.consulta);
    printf("    Ingresa antecedentes familiares: ");
    scanf(" %[^\n]", nuevoPaciente.historial.antecedentesFamiliares);
    printf("    Ingresa trastorno detectado: ");
    scanf(" %[^\n]", nuevoPaciente.historial.trastorno);
    printf("    Descripcion");
    SALTARLINEA(1);
    printf("    ");
    scanf(" %[^\n]", nuevoPaciente.historial.descripcion);

    return nuevoPaciente;
}

Paciente pedirDatosPacienteI() {
    Paciente nuevoPaciente;
    printf("    Ingrese el nombre: ");
    scanf("%s", nuevoPaciente.nombre);
    printf("    Ingrese el apellido: ");
    scanf("%s", nuevoPaciente.apellido);

    return nuevoPaciente;
}

void escribirEnArchivo(Paciente paciente) {
    char nombreArchivo[50];
    sprintf(nombreArchivo, "%s_%s.txt", paciente.nombre, paciente.apellido);

    FILE *archivo = fopen(nombreArchivo, "w");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    fprintf(archivo, "Nombre: %s %s\n", paciente.nombre, paciente.apellido);
    SALTARLINEA(1);
    fprintf(archivo, "Edad: %d", paciente.edad);
    SALTARLINEA(1);
    fprintf(archivo, "Fecha de nacimiento: %d-%d-%d\n", paciente.fecha.dia, paciente.fecha.mes, paciente.fecha.year);
    SALTARLINEA(1);
    fprintf(archivo, "Trastorno: %s\n", paciente.historial.trastorno);
    SALTARLINEA(1);
    fprintf(archivo, "Antecedentes Familiares: %s\n", paciente.historial.antecedentesFamiliares);
    SALTARLINEA(1);
    fprintf(archivo, "Motivo de Consulta: %s\n", paciente.historial.consulta);
    SALTARLINEA(1);
    fprintf(archivo, "Descripcion: %s\n", paciente.historial.descripcion);
    SALTARLINEA(1);

    fclose(archivo);

    // Registra el paciente en el archivo pacientes
    FILE *registro = fopen("pacientes.txt", "a");
    if (registro == NULL) {
        perror("Error al abrir el archivo de registro");
        exit(EXIT_FAILURE);
    }

    fprintf(registro, "%s %s %d", paciente.nombre, paciente.apellido,paciente.edad);

    fclose(registro);
}

void mostrarPacienteArchivo(Paciente *paciente) {
    char nombreArchivo[50];
    sprintf(nombreArchivo, "%s_%s.txt", paciente->nombre, paciente->apellido);

    FILE *archivo = fopen(nombreArchivo, "r");

    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    printf("\nDatos del paciente %s %s:", paciente->nombre, paciente->apellido);
    SALTARLINEA(1);

	int c;
    while ((c = fgetc(archivo)) != EOF) {
        putchar(c);
    }
    fclose(archivo);
}

void mostrarTodosLosPacientes() {
    Paciente paciente;

    FILE *archivo = fopen("pacientes.txt", "r");

    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }
    
    int cont=0;
    SALTARLINEA(1);
    printf("    Lista de pacientes");
    SALTARLINEA(1);
    printf("    ---------------------");
    SALTARLINEA(1);
	
    while (fscanf(archivo, "%s %s %d", paciente.nombre, paciente.apellido, &paciente.edad) == 3) {
    	printf("    %d",cont+1);
        printf("    %s %s %d ", paciente.nombre, paciente.apellido, paciente.edad);
        SALTARLINEA(1);
    	cont++;
	}
	
	printf("\n	Pacientes en total: %d",cont);
	SALTARLINEA(1);

    fclose(archivo);
}

int main() {
	
    Inicio();
    int opcion;
    Paciente nuevoPaciente;

    do {
        LIMPIAR;
        Menu();
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                nuevoPaciente = pedirDatosPaciente();
                escribirEnArchivo(nuevoPaciente);
                break;

            case 2:
            	LIMPIAR;
                nuevoPaciente = pedirDatosPacienteI();
                mostrarPacienteArchivo(&nuevoPaciente);
                PRESIONAR;
                break;

            case 3:
            	LIMPIAR;
                mostrarTodosLosPacientes();
                PRESIONAR;
                break;

            case 0:
                LIMPIAR;
                printf("    !!SALISTE DEL PROGRAMA!!");
                SALTARLINEA(1);
                break;

            default:
                printf("    Opcion no valida.");
                PRESIONAR;
        }
        
        getchar();

    } while (opcion != 0);

    return 0;
}

