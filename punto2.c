#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct {
    int tareaID;
    char *desc;
    int duracion;
} typedef Tarea;

void mostrarTareas(Tarea *tareas[], int cantTareas);
void moverTareas(Tarea *tareas[], Tarea *tareasRealizadas[], int cantTareas);
void mostrarTareasRealizadas(Tarea *tareas[], int cantTareas);
void buscarTareaPorId(Tarea *tareas[], Tarea *tareasRealizadas[], int cantTareas);
void buscarTareaPorPalabra(Tarea *tareas[], Tarea *tareasRealizadas[], int cantTareas);

int main() {
    int numTareas;
    printf("Igrese el numero de tareas: ");
    scanf("%d", &numTareas);
    srand(time(NULL));
    Tarea **tareas = (Tarea **)malloc(numTareas * sizeof(Tarea *));
    Tarea **tareasRealizadas = (Tarea **)malloc(numTareas * sizeof(Tarea *));

    for (int i = 0; i < numTareas; i++) {
        tareas[i] = NULL;
        tareasRealizadas[i] = NULL;
    }

    for (int i = 0; i < numTareas; i++) {
        tareas[i] = (Tarea *)malloc(sizeof(Tarea));
        printf("Ingrese los datos de la tarea %d\n", i + 1);
        tareas[i]->tareaID = i + 1;
        tareas[i]->desc = (char *)malloc(50 * sizeof(char));
        printf("Ingrese la desc: ");
        fflush(stdin);
        gets(tareas[i]->desc);
        tareas[i]->duracion = rand() % 91 + 10;
    }
    moverTareas(tareas,tareasRealizadas, numTareas);
    mostrarTareasRealizadas(tareasRealizadas, numTareas);
    // mostrarTareas(tareas, numTareas);
    buscarTareaPorId(tareas, tareasRealizadas, numTareas);
    buscarTareaPorPalabra(tareas, tareasRealizadas, numTareas);

    for (int i = 0; i < numTareas; i++) {
        free(tareas[i]->desc);
        free(tareas[i]);
        free(tareasRealizadas[i]);
    }
    
    free(tareas);
    free(tareasRealizadas);
    
    return 0;
}

void mostrarTareas(Tarea *tareas[], int cantTareas) {
    printf("\nDatos de las tareas\n");
    for (int i = 0; i < cantTareas; i++)
    {
        if (tareas[i] != NULL){
            printf("ID de la tarea: %d\n", tareas[i]->tareaID);
            printf("Descripcion: ");
            puts(tareas[i]->desc);
            printf("Duracion: %d\n", tareas[i]->duracion);
        }
    }
}

void moverTareas(Tarea *tareas[], Tarea *tareasRealizadas[], int cantTareas) {
    printf("Datos de las tareas\n");
    for (int i = 0; i < cantTareas; i++)
    {
        int realizada;

        printf("ID de la tarea: %d\n", tareas[i]->tareaID);
        printf("Descripcion: ");
        puts(tareas[i]->desc);
        printf("Duracion: %d\n", tareas[i]->duracion);
        printf("Se realizo? 1-si, 0-no: ");
        scanf("%d", &realizada);
        if (realizada) {
            tareasRealizadas[i] = tareas[i];
            tareas[i] = NULL;
        }
    }
}

void mostrarTareasRealizadas(Tarea *tareas[], int cantTareas) {
    printf("\nDatos de las tareas realizadas\n");
    for (int i = 0; i < cantTareas; i++)
    {
        if (tareas[i] != NULL){
            printf("ID de la tarea: %d\n", tareas[i]->tareaID);
            printf("Descripcion: ");
            puts(tareas[i]->desc);
            printf("Duracion: %d\n", tareas[i]->duracion);
        }
    }
}

void buscarTareaPorPalabra(Tarea *tareas[], Tarea *tareasRealizadas[], int cantTareas) {
    char palabra[20];
    printf("Ingrese palabra clave: ");
    fflush(stdin);
    gets(palabra);
    for (int i = 0; i < cantTareas; i++) {
        if (tareas[i]!=NULL && (strstr(tareas[i]->desc, palabra) != NULL)) {
            printf("PENDIENTE\n");
            printf("ID de la tarea: %d\n", tareas[i]->tareaID);
            printf("Descripcion: ");
            puts(tareas[i]->desc);
            printf("Duracion: %d\n", tareas[i]->duracion);
            break;
        } else if (tareasRealizadas[i]!=NULL && (strstr(tareasRealizadas[i]->desc, palabra) != NULL)) {
            printf("REALIZADA\n");
            printf("ID de la tarea: %d\n", tareasRealizadas[i]->tareaID);
            printf("Descripcion: ");
            puts(tareasRealizadas[i]->desc);
            printf("Duracion: %d\n", tareasRealizadas[i]->duracion);
            break;
        }
    }
}

void buscarTareaPorId(Tarea *tareas[], Tarea *tareasRealizadas[], int cantTareas) {
    int id;
    printf("\nIngrese el id: ");
    scanf("%d", &id);
    for (int i = 0; i < cantTareas; i++) {
        if (tareas[i]!=NULL && tareas[i]->tareaID == id) {
            printf("PENDIENTE\n");
            printf("ID de la tarea: %d\n", tareas[i]->tareaID);
            printf("Descripcion: ");
            puts(tareas[i]->desc);
            printf("Duracion: %d\n", tareas[i]->duracion);
            break;
        } else if (tareasRealizadas[i]!=NULL && tareasRealizadas[i]->tareaID == id) {
            printf("REALIZADA\n");
            printf("ID de la tarea: %d\n", tareasRealizadas[i]->tareaID);
            printf("Descripcion: ");
            puts(tareasRealizadas[i]->desc);
            printf("Duracion: %d\n", tareasRealizadas[i]->duracion);
            break;
        }
    }
}