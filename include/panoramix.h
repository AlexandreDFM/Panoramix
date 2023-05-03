/*
** EPITECH PROJECT, 2023
** B-CCP-400-NCE-4-1-panoramix-alexandre-kevin.de-freitas-martins
** File description:
** panoramix
*/

#ifndef PANORAMIX_H_
    #define PANORAMIX_H_

    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>
    #include <stdbool.h>
    #include <pthread.h>
    #include <semaphore.h>

typedef struct values_s {
    int id;
    int pot_size;
    int nb_fights;
    int nb_refills;
    int nb_villagers;
    sem_t *sem_druid;
    sem_t *sem_villagers;
    pthread_mutex_t mutex;
    pthread_barrier_t barrier;
} values_t;


#endif /* !PANORAMIX_H_ */
