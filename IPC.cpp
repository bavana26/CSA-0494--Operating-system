#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_SIZE 1024

int main() {
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }


    char *shm_addr = (char *)shmat(shmid, NULL, 0);
    if (shm_addr == (char *)(-1)) {
        perror("shmat");
        exit(1);
    }

    printf("Enter a message: ");
    fgets(shm_addr, SHM_SIZE, stdin);
    shmdt(shm_addr);
    shm_addr = (char *)shmat(shmid, NULL, 0);


    printf("Received message: %s", shm_addr);
    shmdt(shm_addr);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
    }
