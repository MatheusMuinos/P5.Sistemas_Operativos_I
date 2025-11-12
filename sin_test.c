#include <stdio.h>
#include <math.h>
#include <unistd.h>

int main(void){
    double v = sin(1.0);
    printf("sin(1.0) = %f\n", v);
    while (1) sleep(1);
    return 0;
}

/*
# COMANDOS DE COMPILAÇÃO
# Compilação dinâmica (padrão)
gcc -o sin_dyn sin_test.c -lm
# Enlazar libm estaticamente (só libm)
gcc -o sin_m_static sin_test.c -Wl,-Bstatic -lm -Wl,-Bdynamic
# Enlazado totalmente estático (pode falhar em algumas distros)
gcc -o sin_static sin_test.c -static -lm

# EXECUÇAO E OBTER PIDS
./sin_dyn   & pid_dyn=$!
./sin_m_static & pid_m_static=$!
# ./sin_static & pid_static=$!   # se gerou

# COMANDOS DE INSPEÇÃO
# 1) Dependências do binário
ldd ./sin_dyn
ldd ./sin_m_static
ldd ./sin_static

# 2) Ver se o executável tem intérprete dinâmico (INTERP)
readelf -l ./sin_dyn | grep INTERP -A1
readelf -l ./sin_m_static | grep INTERP -A1

# 3) Tamanho comparativo dos binários
ls -lh sin_dyn sin_m_static sin_static

# 4) Mapas de memória do processo em execução
pmap $pid_dyn
pmap $pid_m_static

# ou via /proc (mais detalhado)
cat /proc/$pid_dyn/maps | grep -E 'libm|ld-linux|libc'
cat /proc/$pid_m_static/maps | grep -E 'libm|ld-linux|libc'

*/