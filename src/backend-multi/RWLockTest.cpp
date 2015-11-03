#include "RWLock.h"
#include <cstdio>
#include <stdio.h> 
#include <stdlib.h> 
#include <cstdlib>

using std::cout;

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

    if (argc != 2){
        cout << "Modo de uso: ./rwlocktest numeroDeTest" << std::endl;
        cout << "numeroDeTest 0 para test con muchos lectores y un escritor " << std::endl;
        cout << "numeroDeTest 1 para test con muchos escritores y un lector " << std::endl;
        cout << "numeroDeTest 2 para test con lectores y escritores alternados " << std::endl;
        return 0;
    }

    srand (time(NULL));
    int test = atoi(argv[1]);

    if (test == 0){

        // Test con muchos lectores y un escritor

    pthread_t thread[CANT_THREADS];
    int tid[CANT_THREADS];

    for (int i = 0; i < CANT_THREADS; i++)
        tid[i] = i;


    int random = rand() % CANT_THREADS; // entre 0 y CANT_THREADS
    
    for (int i = 0; i < CANT_THREADS; i++){
        if(i != random) pthread_create(&thread[i], NULL, leer , &tid[i]);
        else pthread_create(&thread[i], NULL, escribir, &tid[i]);
    }


    for (int i = 0; i < CANT_THREADS; i++)
        pthread_join(thread[i], NULL);


    }else if (test == 1){

    // Test con muchos escritores y un lector

    pthread_t thread[CANT_THREADS];
    int tid[CANT_THREADS];

    for (int i = 0; i < CANT_THREADS; i++)
        tid[i] = i;

    int random = rand() % CANT_THREADS ; // entre 0 y CANT_THREADS

    for (int i = 0; i < CANT_THREADS; i++){
        if(i == random) pthread_create(&thread[i], NULL, leer , &tid[i]);
        else pthread_create(&thread[i], NULL, escribir, &tid[i]);
    }


    for (int i = 0; i < CANT_THREADS; i++)
        pthread_join(thread[i], NULL);

    }else if (test == 2){

    // Test con lectores y escritores alternados pseudoaleatoriamente

    pthread_t thread[CANT_THREADS];
    int tid[CANT_THREADS];

    for (int i = 0; i < CANT_THREADS; i++)
        tid[i] = i;

    for (int i = 0; i < CANT_THREADS; i++){
        int random = rand() % 2 ; //moneda 0 o 1
        if(random % 2 == 0) pthread_create(&thread[i], NULL, leer , &tid[i]);
        else pthread_create(&thread[i], NULL, escribir, &tid[i]);
    }


    for (int i = 0; i < CANT_THREADS; i++)
        pthread_join(thread[i], NULL);

    }else{
        cout << "Modo de uso: ./rwlocktest numeroDeTest" << std::endl;
        cout << "numeroDeTest 0 para test con muchos lectores y un escritor " << std::endl;
        cout << "numeroDeTest 1 para test con muchos escritores y un lector " << std::endl;
        cout << "numeroDeTest 2 para test con lectores y escritores alternados " << std::endl;
    }

    return 0;
}


