/*
** EPITECH PROJECT, 2023
** B-CCP-400-NCE-4-1-panoramix-alexandre-kevin.de-freitas-martins
** File description:
** main
*/

#include "./include/trains.h"

void bridge_thread(void)
{
    int i = 0;
    while (i < NB_TRAINS) {
        pthread_mutex_lock(&bridge);
        pthread_mutex_lock(&trains[i]);
        pthread_mutex_unlock(&bridge);
        pthread_mutex_unlock(&trains[i]);
        i++;
    }
}

void train_thread(void)
{
    int i = 0;
    while (i < NB_TRAINS) {
        pthread_mutex_lock(&trains[i]);
        pthread_mutex_lock(&bridge);
        pthread_mutex_unlock(&bridge);
        pthread_mutex_unlock(&trains[i]);
        i++;
    }
}

int main(void)
{
    int i = 0;
    pthread_t trains[NB_TRAINS];
    pthread_t bridge;

    pthread_create(&bridge, NULL, &bridge_thread, NULL);
    while (i < NB_TRAINS) {
        pthread_create(&trains[i], NULL, &train_thread, NULL);
        i++;
    }
    i = 0;
    while (i < NB_TRAINS) {
        pthread_join(trains[i], NULL);
        i++;
    }
    pthread_join(bridge, NULL);
    return (0);
}
