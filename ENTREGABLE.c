#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>
#include <pthread.h>

#define MAX 100

// Variables del apartado 1
int global1;
double global2;
float global3;
char global_array[MAX];

// Variable del apartado 6
int var_global = 3;

void f1(int n) {
    int x = n + 1;
    printf("parametro de f1 n: %p \nvariable local para f1 x: %p\n", &n, &x);    
}

void f2(int n) {
    int y = n + 2;
    printf("parametro de f2 n: %p \nvariable local para f2 y: %p\n", &n, &y);
}

void* funcion_hilo(void* arg) {
    int param = *(int*)arg;
    int var_local_hilo = var_global * param;
    int *m = malloc(10);
    printf("Hilo param: %p \tlocal: \t%p malloc: \t%p global: %p\n", &param, &var_local_hilo, m, &var_global);
    free(m);
    return NULL;
}

int main() {
    int opcion;

    // Mostrar menú para que el usuario seleccione el apartado a ejecutar
    printf("PID del proceso principal: %d\n", getpid());
    printf("Selecciona el apartado a ejecutar (1-6):\n");
    printf("1. Apartado 1: Variables globales, locales y array 3D\n");
    printf("2. Apartado 2: Funciones f1 y f2\n");
    printf("3. Apartado 3: Uso de malloc y free\n");
    printf("4. Apartado 4: Proceso hijo con malloc y execv\n");
    printf("5. Apartado 5: Librería matemática estática vs dinámica\n");
    printf("6. Apartado 6: Hilos y variables locales\n");
    printf("Elige una opción: ");
    
    scanf("%d", &opcion);

    switch(opcion) {

        // Apartado 1
        case 1: {
            int local1;
            double local2;
            float local3;
            int local_array[10][10][10];
            
            printf("Dirección de la variable global globa1: %p\n", (void*)&global1);
            printf("Dirección de la variable global global2: %p\n", (void*)&global2);
            printf("Dirección de la variable global global3: %p\n", (void*)&global3);
            printf("Dirección de la variable global global_array: %p\n", (void*)&global_array);
            scanf("%d",&global1);
            getchar();

            printf("Dirección de la variable local1: %p\n", (void*)&local1);
            printf("Dirección de la variable local2: %p\n", (void*)&local2);
            printf("Dirección de la variable local3: %p\n", (void*)&local3);

            printf("Dirección del array 3D local_array: %p\n", (void*)&local_array);

            printf("Dirección de la función main: %p\n", (void*)&main);
            scanf("%d",&local1);
            getchar();

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    for (int k = 0; k < 3; k++) {
                        // Imprimir la dirección de cada elemento del array 3D
                        printf("Direccion del elemento del array 3D [%d][%d][%d]: %p\n", i, j, k, (void*)&local_array[i][j][k]);
                    }
                }
                scanf("%f",&local3);
                getchar();
            }
            return 0;
        }
        // Apartado 2
        case 2: {
            f1(10);
            f2(20);
            // limpa o buffer do ENTER do scanf
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            getchar();
            return 0;
        }

        // Apartado 3
        case 3: {

            // 1) Primer malloc: tamaño pequeño
            size_t nbytes1 = 100 * sizeof(int);
            int *p = malloc(nbytes1);

            printf("Primer malloc de %zu bytes. Direccion p = %p\n", nbytes1, (void *)p);
            printf("Mirar el cat /proc/PID/maps y despues pulsa ENTER para mirar el mapa de memoria DESPUES del primer malloc...\n");
            // limpa o buffer do ENTER do scanf
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            getchar(); // agora sim espera o ENTER
            // PAUSA 1: mirar /proc/PID/maps o pmap -x PID

            // 2) Liberar el bloque
            free(p);
            printf("free(p) ejecutado.\n");
            printf("Mirar el cat /proc/PID/maps y despues pulsa ENTER para mirar el mapa de memoria DESPUES del free(p)...\n");
            getchar();  // PAUSA 2: mirar otra vez el mapa de memoria

            // 3) Segundo malloc: tamaño distinto (mas grande)
            size_t nbytes2 = 1000 * sizeof(int);
            int *q = malloc(nbytes2);
            if (q == NULL) {
                perror("Error en malloc (segundo bloque)");
                return 1;
            }

            printf("Segundo malloc de %zu bytes. Direccion q = %p\n", nbytes2, (void *)q);
            printf("Mirar el cat /proc/PID/maps y despues pulsa ENTER para mirar el mapa de memoria DESPUES del segundo malloc...\n");
            getchar();  // PAUSA 3: mirar el mapa por tercera vez

            // 4) Liberar el segundo bloque
            free(q);
            printf("free(q) ejecutado. Fin del case 3.\n");

            return 0;
        }

        // Apartado 4
        case 4: {
            pid_t hijo;
            hijo = fork();

            if (hijo < 0) {
                perror("Error en fork");
                fflush(stdout);
                exit(EXIT_FAILURE);
            }
            if (hijo == 0) {
                printf("PID del proceso hijo: %d\n", getpid());
                printf("Hijo: Pausa antes de malloc\n");
                getchar(); 
                int *numero = (int*)malloc(sizeof(int));
                printf("Hijo: Pausa después de malloc\n");
                getchar();
                execlp("./programa", "programa", NULL);
                perror("Error en execlp");
                exit(EXIT_FAILURE);
            }
            printf("Padre: Pausa antes de la ejecución de malloc en el hijo\n");
            getchar();
            wait(NULL);
            return 0;
        }

        // Apartado 5:
        case 5: {
            double v = sin(1.0);
            printf("sin(1) = %f\n", v);
            while(1) sleep(1);
            return 0;
        }

        // Apartado 6:
        case 6: {
            int var_local = 5;
            pthread_t hilo1, hilo2;
            if (pthread_create(&hilo1, NULL, funcion_hilo, &var_local) != 0) {
                perror("Error al crear el hilo 1");
                exit(EXIT_FAILURE);
            }
            if (pthread_create(&hilo2, NULL, funcion_hilo, &var_local) != 0) {
                perror("Error al crear el hilo 2");
                exit(EXIT_FAILURE);
            }
            pthread_join(hilo1, NULL);
            pthread_join(hilo2, NULL);
            printf("La variable global tiene la direccion:%p\n",(void*)&var_global);
            printf("La variable local del hilo principal es:%p",(void*)&var_local);

            scanf("%*d");
            return 0;
        }
    }

    return 0;
}
