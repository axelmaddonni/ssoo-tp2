#include "RWLock.h"

/* IMPORTANTE: Se brinda una implementación básica del Read-Write Locks
que hace uso de la implementación provista por pthreads. Está dada para
que puedan utilizarla durante la adaptación del backend de mono a multi
jugador de modo de poder concentrarse en la resolución de un problema
a la vez. Una vez que su adaptación esté andando DEBEN hacer su propia
implementación de Read-Write Locks utilizando únicamente Variables de
Condición. */

RWLock :: RWLock() {
    pthread_mutex_init(&m, NULL);
    pthread_cond_init(&molinete, NULL);
    lectores = 0;  
    mol = true;
}

void RWLock :: rlock() {
    pthread_mutex_lock(&m);

    while(!mol)
        pthread_cond_wait(&molinete, &m);

    lectores++;
    pthread_mutex_unlock(&m);
}

void RWLock :: wlock() {
    pthread_mutex_lock(&m);
    
    while (!mol)
        pthread_cond_wait(&molinete, &m);
    mol = false;
 
    while (lectores > 0)
        pthread_cond_wait(&molinete, &m);
    pthread_mutex_unlock(&m);
}

void RWLock :: runlock() {
    pthread_mutex_lock(&m);
    lectores--;
    pthread_cond_broadcast(&molinete);
    pthread_mutex_unlock(&m);
}

void RWLock :: wunlock() {
    pthread_mutex_lock(&m);
    mol = true;
    pthread_cond_broadcast(&molinete);
    pthread_mutex_unlock(&m);
}
