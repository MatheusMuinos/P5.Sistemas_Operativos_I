#include <stdio.h>
int g = 10;
int arr_global[5];

int main() {
    int local = 5;
    int arr_local[10][10][10];
    printf("main: %p\n", main);
    printf("global: %p\n", &g);
    printf("array global: %p\n", arr_global);
    printf("local: %p\n", &local);
    printf("array local: %p\n", arr_local);
    scanf("%d", &local); // pausa
}

void f1(int x){ int y = x + 1; printf("f1 param: %p local: %p\n", &x, &y); }
void f2(int x){ int y = x + 2; printf("f2 param: %p local: %p\n", &x, &y); }

int main() {
    f1(10);
    f2(20);
    scanf("%*d");
}


int main() {
    int *p = malloc(100 * sizeof(int));
    printf("malloc: %p\n", p);
    scanf("%*d");
    free(p);
    scanf("%*d");
}


#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        void *p = malloc(100);
        printf("Hijo malloc: %p\n", p);
        execl("./otro", "otro", NULL);
    } else {
        scanf("%*d");
    }
}

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int global = 3;

void* hilo(void* arg){
    int param = *(int*)arg;
    int local = global * param;
    int *m = malloc(10);
    printf("Hilo param: %p local: %p malloc: %p global: %p\n",
           &param, &local, m, &global);
    return NULL;
}

int main(){
    int local = 5;
    pthread_t t1, t2;
    pthread_create(&t1, NULL, hilo, &local);
    pthread_create(&t2, NULL, hilo, &local);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    scanf("%*d");
}
