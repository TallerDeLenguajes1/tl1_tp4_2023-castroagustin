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
void controlarTareas(Nodo **Start, Nodo **StartRealizadas, Nodo **StartProceso);
void moverTarea(Nodo **Start, Nodo **StartRealizadas, int id);
Nodo *eliminarNodo(Nodo **Start, int id);
Nodo *buscarTareaPorId(Nodo *Start, Nodo *StartRealizadas, Nodo *StartProceso, int id, int *listaPertence);
Nodo *buscarTareaPorPalabra(Nodo *Start, Nodo *StartRealizadas, Nodo *StartProceso, char *palabra);
void mostrarDatos(Nodo *Start);
void mostrarTodasTareas(Nodo *Start, Nodo *StartRealizadas, Nodo *StartProceso);

int cantTareas = 0;

int main() {
    int sigue, opcion, idBuscado, listaPertence;
    char *palabra = (char *)malloc(sizeof(char) * 50);

    Nodo *TareasPendientes = NULL;
    Nodo *TareasRealizadas = NULL;
    Nodo *TareasEnProceso = NULL;

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
            mostrarTodasTareas(TareasPendientes, TareasRealizadas, TareasEnProceso);
            break;
        case 3:
            printf("\n********** Control de Tareas ***********\n");
            controlarTareas(&TareasPendientes, &TareasRealizadas, &TareasEnProceso);
            mostrarTodasTareas(TareasPendientes, TareasRealizadas, TareasEnProceso);
            break;
        case 4:
            printf("Ingrese el id: ");
            scanf("%d", &idBuscado);
            Nodo *buscado = buscarTareaPorId(TareasPendientes,  TareasRealizadas, TareasEnProceso, idBuscado, &listaPertence);
            if (buscado) {
                printf("ID: %d\n", buscado->T.TareaID);
                printf("Descpripcion: %s\n", buscado->T.Descripcion);
                printf("Duracion: %d\n", buscado->T.Duracion);

                switch (listaPertence) {
                case 1: printf("Tarea Pendiente!\n");
                    break;
                case 2: printf("Tarea En Proceso!\n");
                    break;
                case 3: printf("Tarea Realizada!\n");
                    break;
                }
            }
            break;
        case 5:
            printf("Ingrese la palabra clave: ");
            fflush(stdin);
            gets(palabra);
            Nodo *buscadoPalabra = buscarTareaPorPalabra(TareasPendientes, TareasRealizadas, TareasEnProceso, palabra);
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

void controlarTareas(Nodo **Start, Nodo **StartRealizadas, Nodo **StartProceso) {
    int id, realizada, sigue = 1;

    while (sigue) {
        printf("\n========== Tareas Pendientes ==========\n");
        mostrarLista(*Start);
        printf("\n========== Tareas En Proceso ==========\n");
        mostrarLista(*StartProceso);
        printf("\n========== Tareas Realizadas ==========\n");
        mostrarLista(*StartRealizadas);
        printf("ID de la tarea a seleccionar: ");
        scanf("%d", &id);

        //buscar por id y controlar a que lista pertenece
        int listaPerteneciente;
        buscarTareaPorId(*Start, *StartRealizadas, *StartProceso, id, &listaPerteneciente);
        if (listaPerteneciente) {
            int op, op2;
            printf("Que desea hacer con esta tarea?\n1-Mover a otra lista\n2-Eliminar\n3-Nada\n");
            scanf("%d", &op);

            switch (listaPerteneciente) {
                case 1:
                    if (op == 1) {
                        printf("1-Mover a 'En Proceso'\n2-Mover a 'Realizada'\n");
                        scanf("%d", &op2);
                        if (op2 == 1) {
                            moverTarea(Start, StartProceso, id);
                        } else if (op2 == 2) {
                            moverTarea(Start, StartRealizadas, id);
                        }
                    } else if (op == 2) {
                        eliminarNodo(Start, id);
                    }
                    break;
                case 2:
                    if (op == 1) {
                        printf("1-Mover a 'Pendiente'\n2-Mover a 'Realizada'\n");
                        scanf("%d", &op2);
                        if (op2 == 1) {
                            moverTarea(StartProceso, Start, id);
                        } else if (op2 == 2) {
                            moverTarea(StartProceso, StartRealizadas, id);
                        }
                    } else if (op == 2) {
                        eliminarNodo(StartProceso, id);
                    }
                    break;
                case 3:
                    if (op == 1) {
                        printf("1-Mover a 'Pendiente'\n2-Mover a 'En Proceso'\n");
                        scanf("%d", &op2);
                        if (op2 == 1) {
                            moverTarea(StartRealizadas, Start, id);
                        } else if (op2 == 2) {
                            moverTarea(StartRealizadas, StartProceso, id);
                        }
                    } else if (op == 2) {
                        eliminarNodo(StartRealizadas, id);
                    }
                    break;
                default:
                    break;
            }
        } else {
            printf("No se encontro la tarea...");
        }
        printf("Desea controlar otra tarea? 1-si, 0-no: ");
        scanf("%d", &sigue);
    }
}

void moverTarea(Nodo **Start, Nodo **StartRealizadas, int id) {
    Nodo *Aux = eliminarNodo(Start, id);
    agregarNodoAlFinal(StartRealizadas, Aux);
}

Nodo *buscarTareaPorId(Nodo *Start, Nodo *StartRealizadas, Nodo *StartProceso, int id, int *listaPertence) {
    Nodo *AuxPendientes = Start;
    Nodo *AuxRealizadas = StartRealizadas;
    Nodo *AuxProceso = StartProceso;

    while (AuxPendientes) {
        if (AuxPendientes->T.TareaID == id) {
            *listaPertence = 1;
            return AuxPendientes;
        }
        AuxPendientes = AuxPendientes->Siguiente;
    }
    while (AuxProceso) {
        if (AuxProceso->T.TareaID == id) {
            *listaPertence = 2;
            return AuxProceso;
        }
        AuxProceso = AuxProceso->Siguiente;
    }
    while (AuxRealizadas) {
        if (AuxRealizadas->T.TareaID == id) {
            *listaPertence = 3;
            return AuxRealizadas;
        }
        AuxRealizadas = AuxRealizadas->Siguiente;
    }
    
    printf("No existe una tarea con ID: %d", id);
    return NULL;
}

Nodo *buscarTareaPorPalabra(Nodo *Start, Nodo *StartRealizadas, Nodo *StartProceso, char *palabra) {
    Nodo *AuxP = Start;
    Nodo *AuxEP = StartProceso;
    Nodo *AuxR = StartRealizadas;
    while (AuxP) {
        if (strstr(AuxP->T.Descripcion, palabra)) {
            printf("Tarea encontrada (PENDIENTE)\n");
            return AuxP;
        }
        AuxP = AuxP->Siguiente;
    }
    while (AuxEP) {
        if (strstr(AuxEP->T.Descripcion, palabra)) {
            printf("Tarea encontrada (EN PROCESO)\n");
            return AuxEP;
        }
        AuxR = AuxR->Siguiente;
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

void mostrarDatos(Nodo *Start) {
    Nodo *Aux = Start;
    int cant = 0, tiempo = 0;

    while(Aux) {
        cant++;
        tiempo += Aux->T.Duracion;
        Aux = Aux->Siguiente;
    }
    printf("Cantidad de tareas de la lista: %d\n", cant);
    printf("Tiempo total de tareas: %d\n", tiempo);
}

void mostrarTodasTareas(Nodo *Start, Nodo *StartRealizadas, Nodo *StartProceso) {
    printf("\n========== Tareas Pendientes ==========\n");
    mostrarLista(Start);
    mostrarDatos(Start);
    printf("\n========== Tareas En Proceso ==========\n");
    mostrarLista(StartProceso);
    mostrarDatos(StartProceso);
    printf("\n========== Tareas Realizadas ==========\n");
    mostrarLista(StartRealizadas);
    mostrarDatos(StartRealizadas);
}