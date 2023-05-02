#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct Tarea {
    int TareaID;
    char *Descripcion;
    int Duracion;
} typedef Tarea;

struct Nodo {
    Tarea T;
    struct Nodo *Siguiente;
} typedef Nodo;

Tarea crearTarea(int id);
Nodo *crearNodo(Tarea tarea);
void agregarNodoAlFinal(Nodo **Start, Nodo *NNodo);
void mostrarLista(Nodo *Start);
void controlarTareas(Nodo **Start, Nodo **StartRealizadas);
void moverTarea(Nodo **Start, Nodo **StartRealizadas, int id);
Nodo *eliminarNodo(Nodo **Start, int id);
Nodo *buscarTareaPorId(Nodo *Start, Nodo *StartRealizadas, int id);
Nodo *buscarTareaPorPalabra(Nodo *Start, Nodo *StartRealizadas, char *palabra);

int cantTareas = 0;

int main() {
    int sigue, opcion, idBuscado;
    char *palabra = (char *)malloc(sizeof(char) * 50);

    Nodo *TareasPendientes = NULL;
    Nodo *TareasRealizadas = NULL;

    srand(time(NULL));

    do {
        printf("\n _____________ MENU _____________ \n");
        printf("|                                |\n");
        printf("|  1 - Cargar Tarea              |\n");
        printf("|  2 - Mostrar Tareas            |\n");
        printf("|  3 - Controlar Tareas          |\n");
        printf("|  4 - Buscar tarea por ID       |\n");
        printf("|  5 - Buscar tarea por palabra  |\n");
        printf("|  6 - Salir                     |\n");
        printf("|________________________________|\n");

        scanf("%d", &opcion);

        switch (opcion) {
        case 1:
            sigue = 1;
            for(int i = 1; sigue; i++) {
                Tarea tarea;
                tarea = crearTarea(cantTareas++);

                Nodo *NNodo = crearNodo(tarea);
                agregarNodoAlFinal(&TareasPendientes, NNodo);

                printf("Desea ingresar otra tarea? (1->si, 0->no): ");
                scanf("%d", &sigue);
            }
            break;
        case 2:
            printf("\n========== Tareas Pendientes ==========\n");
            mostrarLista(TareasPendientes);
            printf("\n========== Tareas Realizadas ==========\n");
            mostrarLista(TareasRealizadas);
            break;
        case 3:
            printf("\n********** Control de Tareas ***********\n");
            controlarTareas(&TareasPendientes, &TareasRealizadas);
            break;
        case 4:
            printf("Ingrese el id: ");
            scanf("%d", &idBuscado);
            Nodo *buscado = buscarTareaPorId(TareasPendientes,  TareasRealizadas, idBuscado);
            if (buscado) {
                printf("ID: %d\n", buscado->T.TareaID);
                printf("Descpripcion: %s\n", buscado->T.Descripcion);
                printf("Duracion: %d\n", buscado->T.Duracion);
            }
            break;
        case 5:
            printf("Ingrese la palabra clave: ");
            fflush(stdin);
            gets(palabra);
            Nodo *buscadoPalabra = buscarTareaPorPalabra(TareasPendientes,     TareasRealizadas, palabra);
            if (buscadoPalabra) {
                printf("ID: %d\n", buscadoPalabra->T.TareaID);
                printf("Descpripcion: %s\n", buscadoPalabra->T.Descripcion);
                printf("Duracion: %d\n", buscadoPalabra->T.Duracion);
            }
            break;
        }
    } while (opcion >= 1 && opcion <= 5);
}

Nodo *crearNodo(Tarea tarea) {
    Nodo *NNodo = (Nodo *)malloc(sizeof(Nodo));
    NNodo->T.TareaID = tarea.TareaID;
    NNodo->T.Descripcion = (char *)malloc((strlen(tarea.Descripcion)+1) * sizeof(char));
    strcpy(NNodo->T.Descripcion, tarea.Descripcion);
    NNodo->T.Duracion = tarea.Duracion;
    NNodo->Siguiente = NULL;

    return NNodo;
}

Nodo *eliminarNodo(Nodo **Start, int id) {
    Nodo *Aux = *Start;
    Nodo *AuxAnterior;
    while (Aux && Aux->T.TareaID != id) {
        AuxAnterior = Aux;
        Aux = Aux->Siguiente;
    }
    if (Aux) {
        if (*Start == Aux) {
            *Start = Aux->Siguiente;
        } else {
            AuxAnterior->Siguiente = Aux->Siguiente;
        }
    }
    Aux->Siguiente = NULL;
    return Aux;
}

Tarea crearTarea(int id) {
    Tarea T;

    T.TareaID = id;
    char buff[100];
    printf("Ingrese los datos de la tarea %d: \n", id);
    printf("Descripcion de la tarea: ");
    fflush(stdin);
    gets(buff);
    T.Descripcion = (char *)malloc(strlen(buff) * sizeof(char));
    strcpy(T.Descripcion, buff);
    T.Duracion = rand() % 91 + 10;

    return T;
}

void agregarNodoAlFinal(Nodo **Start, Nodo *NNodo) {
    Nodo *Aux = *Start;
    if (*Start == NULL) {
        *Start = NNodo;
    } else {
        while (Aux->Siguiente) {
            Aux = Aux->Siguiente;
        }
        Aux->Siguiente = NNodo;
    }
}

void mostrarLista(Nodo *Start) {
    Nodo *Aux = Start;
    if (!Aux) {
        printf("Lista vacia\n");
    }
    while(Aux) {
        printf("ID: %d\n", Aux->T.TareaID);
        printf("Descpripcion: %s\n", Aux->T.Descripcion);
        printf("Duracion: %d\n", Aux->T.Duracion);
        Aux = Aux->Siguiente;
    }
}

void controlarTareas(Nodo **Start, Nodo **StartRealizadas) {
    int id, realizada, sigue = 1;

    Nodo *AuxPendientes = *Start;
    Nodo *AuxRealizadas = *StartRealizadas;

    while (sigue) {
        printf("\n========== Tareas Pendientes ==========\n");
        mostrarLista(AuxPendientes);
        printf("ID de la tarea a controlar: ");
        scanf("%d", &id);
        printf("Se realizo? 1-si, 0-no: ");
        scanf("%d", &realizada);
        if (realizada) {
            moverTarea(Start, StartRealizadas, id);
        }
        printf("Desea controlar otra tarea? 1-si, 0-no: ");
        scanf("%d", &sigue);
    }
}

void moverTarea(Nodo **Start, Nodo **StartRealizadas, int id) {
    Nodo *Aux = eliminarNodo(Start, id);
    agregarNodoAlFinal(StartRealizadas, Aux);
}

Nodo *buscarTareaPorId(Nodo *Start, Nodo *StartRealizadas, int id) {
    Nodo *AuxPendientes = Start;
    Nodo *AuxRealizadas = StartRealizadas;
    while (AuxPendientes) {
        if (AuxPendientes->T.TareaID == id) {
            printf("Tarea encontrada (PENDIENTE)\n");
            return AuxPendientes;
        }
        AuxPendientes = AuxPendientes->Siguiente;
    }
    while (AuxRealizadas) {
        if (AuxRealizadas->T.TareaID == id) {
            printf("Tarea encontrada (REALIZADA)\n");
            return AuxRealizadas;
        }
        AuxRealizadas = AuxRealizadas->Siguiente;
    }
    printf("No existe una tarea con ID: %d", id);
    return NULL;
}

Nodo *buscarTareaPorPalabra(Nodo *Start, Nodo *StartRealizadas, char *palabra) {
    Nodo *AuxP = Start;
    Nodo *AuxR = StartRealizadas;
    while (AuxP) {
        if (strstr(AuxP->T.Descripcion, palabra)) {
            printf("Tarea encontrada (PENDIENTE)\n");
            return AuxP;
        }
        AuxP = AuxP->Siguiente;
    }
    while (AuxR) {
        if (strstr(AuxR->T.Descripcion, palabra)) {
            printf("Tarea encontrada (REALIZADA)\n");
            return AuxR;
        }
        AuxR = AuxR->Siguiente;
    }
    printf("No se encontro ninguna tarea con esa palabra\n");
    return NULL;
}