#include "RWLock.h"
#include <cstdio>


#define CANT_THREADS 40
int variable_disputada;

RWLock rwlck;

void *escribir(void *p_minumero){
    int minumero = *((int *) p_minumero);
    rwlck.wlock();
    variable_disputada = minumero;
    printf("Estoy escribiendo! variable_disputada =  %d.\n", variable_disputada);
    rwlck.wunlock();
    
    return NULL;
}



void *leer(void *nada){

    rwlck.rlock();
    printf(">> variable_disputada = %d.\n", variable_disputada);
    rwlck.runlock();
    return NULL;
}


int main(int argc, char* argv[]) {

    /* Implementar */
    pthread_t thread[CANT_THREADS];
    int tid[CANT_THREADS];

    for (int i = 0; i < CANT_THREADS; i++)
        tid[i] = i;

    for (int i = 0; i < CANT_THREADS; i++){

        if(i != 10) pthread_create(&thread[i], NULL, leer , &tid[i]);
        else pthread_create(&thread[i], NULL, escribir, &tid[i]);
    }


    for (int i = 0; i < CANT_THREADS; i++)
        pthread_join(thread[i], NULL);
    


    return 0;
}


