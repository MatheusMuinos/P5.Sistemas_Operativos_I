#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>
#include <pthread.h>

#define MAX 100

//Variables del apartado 1
int globa1;
double global2;
float global3;
char global_array[MAX];
//Variable del apartado 6
int var_global=3;

int main(){
    int opcion;
    // Mostrar menú para que el usuario seleccione el apartado a ejecutar
    printf("Selecciona el apartado a ejecutar (1-6):\n");
    printf("1. Apartado 1: Variables globales, locales y array 3D\n");
    printf("2. Apartado 2: Funciones f1 y f2\n");
    printf("3. Apartado 3: Uso de malloc y free\n");
    printf("4. Apartado 4: Proceso hijo con malloc y execv\n");
    printf("5. Apartado 5: Librería matemática estática vs dinámica\n");
    printf("6. Apartado 6: Hilos y variables locales\n");
    printf("Elige una opción: ");
    
    scanf("%d", &opcion);

    
    switch(opcion){

        // Apartado 1
        case 1:{
            int local1;
            double local2;
            float local3;
            int local_array[10][10][10];

            printf("Dirección de la variable global globa1: %p\n", (void*)&globa1);
            printf("Dirección de la variable global global2: %p\n", (void*)&global2);
            printf("Dirección de la variable global global3: %p\n", (void*)&global3);
            printf("Dirección de la variable global global_array: %p\n", (void*)&global_array);

        
            printf("Dirección de la variable local1: %p\n", (void*)&local1);
            printf("Dirección de la variable local2: %p\n", (void*)&local2);
            printf("Dirección de la variable local3: %p\n", (void*)&local3);

        
            printf("Dirección del array 3D local_array: %p\n", (void*)&local_array);
        
        
            printf("Dirección de la función main: %p\n", (void*)&main);

            printf("Dirección del primer elemento de local_array[0][0][0]: %p\n", (void*)&local_array[0][0][0]);
            printf("Dirección del segundo elemento local_array[0][0][1]: %p\n", (void*)&local_array[0][0][1]);
            printf("Dirección del tercer elemento local_array[0][1][0]: %p\n", (void*)&local_array[0][1][0]);

            return 0;
        }
        // Apartado 2
        case 2:{
            void f1 (int n){
        
                int x = n + 1;
                printf ("parametro de f1 n: %p variable local para f1 x: %p\n", &n, &x);    
            } 
            void f2 (int n) {
                int y = n + 2;
                printf ("parametro de f2 n: %p variable local para f2 y: %p\n", &n, &y);
            }
            return 0;
        }

        // Apartado 3
        case 3:{
            int *p = malloc(100 * sizeof(int));
            printf("alocacion de memoria: %p\n", p);
            scanf("%*d"); // mantener el proceso activo para mirar la memoria
            free(p);
            scanf("%*d");

            return 0;
        }
        // Apartado 4
        case 4:{
            pid_t hijo;
            hijo=fork();
            if(hijo<0){
                perror("Error en fork");
                fflush(stdout);
                exit(EXIT_FAILURE);
            }
            if (hijo==0){
                int *numero=(int*)malloc(sizeof(int));
                execlp("./programa","programa", NULL);
            }
            return 0;    
        }
        
        // Apartado 5:
        case 5: {
            double v = sin(1.0);
            printf("sin(1) = %f\n", v);
            while(1) sleep(1);
            return 0;
            // mirar el sin_test.c
        }

        // Apartado 6:
        case 6:{

            void *funcion_hilo(void* arg){
                int param = *(int*)arg;
                int var_local_hilo = var_global * param;
                int *m = malloc(10);
                printf("Hilo param: %p local: %p malloc: %p global: %p\n", &param, &var_local_hilo, m, &var_global);
                free(m);
                return NULL;
            }

            int var_local=5;
            pthread_t hilo1, hilo2;
            if(pthread_create(&hilo1, NULL, funcion_hilo, &var_local) != 0){
                perror("Error al crear el hilo 1");
                exit(EXIT_FAILURE);
            }
            if(pthread_create(&hilo2, NULL, funcion_hilo, &var_local) != 0){
                perror("Error al crear el hilo 2");
                exit(EXIT_FAILURE);
            }
            pthread_join(hilo1, NULL);
            pthread_join(hilo2, NULL);
            scanf("%*d");
            
        }
























    }
}