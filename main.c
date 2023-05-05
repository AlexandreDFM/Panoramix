/*
** EPITECH PROJECT, 2023
** B-CCP-400-NCE-4-1-panoramix-alexandre-kevin.de-freitas-martins
** File description:
** main
*/

#include "./include/panoramix.h"

void help(void)
{
    printf("USAGE: ./panoramix <nb_villagers> <pot_size> <nb_fights>"
    " <nb_refills>\n");
}

void *druid_fct(void *values)
{
    values_t *v = (values_t *)values;
    int pot_size = v->pot_size;
    printf("Druid: I'm ready... but sleepy...\n");
    pthread_barrier_wait(&v->barrier);
    while (v->nb_refills > 0) {
        sem_wait(v->sem_druid);
        if (v->pot_size < 0) {
            v->pot_size = pot_size, v->nb_refills--;
            printf("Druid: Ah! Yes, yes, I'm awake! Working on it! Beware I"
            " can only make %d more refills after this one.\n", v->nb_refills);
            sem_post(v->sem_villagers);
        }
    }
    sem_post(v->sem_villagers);
    printf("Druid: I'm out of viscum. I'm going back to... zZz\n");
    pthread_barrier_wait(&v->barrier);
    pthread_exit(NULL);
}

void *villager_fct(void *values)
{
    values_t *v = (values_t *) values;
    int id = v->id, nb_fights = v->nb_fights; v->id = id + 1;
    printf("Villager %d: Going into battle!\n", id);
    pthread_barrier_wait(&v->barrier);
    while (nb_fights > 0) {
        pthread_mutex_lock(&v->mutex);
        printf("Villager %d: I need a drink... I see %d servings left.\n",
        id, v->pot_size); v->pot_size -= 1;
        if (v->pot_size < 0) {
            printf("Villager %d: Hey Pano wake up! We need more potion.\n",
            id); sem_post(v->sem_druid); sem_wait(v->sem_villagers);
        }
        pthread_mutex_unlock(&v->mutex);
        nb_fights -= 1; printf("Villager %d: Take that roman scum!"
        " Only %d left.\n", id, nb_fights);
    }
    pthread_barrier_wait(&v->barrier);
    printf("Villager %d: I'm going to sleep now.\n", id); pthread_exit(NULL);
}

void panoramix(values_t *values)
{
    pthread_t druid, villagers[values->nb_villagers];
    values->sem_villagers = malloc(sizeof(sem_t));
    values->sem_druid = malloc(sizeof(sem_t));
    values->mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
    sem_init(values->sem_druid, 0, 0);
    sem_init(values->sem_villagers, 0, 0);
    pthread_barrier_init(&values->barrier, NULL, values->nb_villagers + 1);
    pthread_mutex_init(&values->mutex, NULL);
    pthread_create(&druid, NULL, &druid_fct, values);
    for (int i = 0; i < values->nb_villagers; i++) {
        pthread_create(&villagers[i], NULL, &villager_fct, values);
    }
    pthread_join(druid, NULL);
    for (int i = 0; i < values->nb_villagers; i++) {
        pthread_join(villagers[i], NULL);
    }
    pthread_mutex_destroy(&values->mutex);
    free(values);
}

int main(int argc, char **argv)
{
    if (argc == 2 && strcmp(argv[1], "-h") == 0) {
        help(); return 0;
    }
    if (argc != 5) {
        printf("Invalid number of arguments.\n"); return 84;
    }
    for (int i = 1; i < 5; i++) {
        if (atoi(argv[i]) <= 0) {
            printf("Invalid arguments.\n"); return 84;
        }
    }
    int nb_villagers = atoi(argv[1]), pot_size = atoi(argv[2]);
    int nb_fights = atoi(argv[3]), nb_refills = atoi(argv[4]);
    values_t *values = malloc(sizeof(values_t));
    values->pot_size = pot_size; values->nb_fights = nb_fights;
    values->nb_refills = nb_refills; values->nb_villagers = nb_villagers;
    panoramix(values);
    return 0;
}
