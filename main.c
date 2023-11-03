#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/ipc.h>       
#include <fcntl.h>          

#include <semaphore.h>

#include "shared_table.h"
#include "producer.h"
#include "consumer.h"


int main() {

    int sharedMemId = shmget(IPC_PRIVATE, sizeof(SharedTable), IPC_CREAT | 0666);

    // Intialize Shared Table
    SharedTable *sTable = (SharedTable*)shmat(sharedMemId, NULL, 0);
    // Initialize table indexes to 0
    sTable->in = 0;     
    sTable->out = 0;

    // Initialize Semaphores
    sem_unlink("/mutex");
    sem_unlink("/empty");
    sem_unlink("/full");

    // Mutex initialized to 1 to protect mutual exclusion
    sTable->mutex = sem_open("/mutex", O_CREAT, 0666, 1);
    // Empty intialized to table size
    sTable->empty = sem_open("/empty", O_CREAT, 0666, BUFFER_SIZE);
    // Full initialized to 0
    sTable->full = sem_open("/full", O_CREAT, 0666, 0);

    // Create producer and consumer processes
    pid_t producer_pid, consumer_pid;

    producer_pid = fork();          // Create a child process for the producer


    // Producer consumer problem in action
    if (producer_pid == 0) {
        producer(sTable);           // In the child process, call the producer function
    } else {
        consumer_pid = fork();      // In the parent process, create a child process for the consumer
        if (consumer_pid == 0) {
            consumer(sTable);       // In the child process, call the consumer function
        }
    }



    // Wait for the child processes to finish
    waitpid(producer_pid, NULL, 0); // Wait for the producer process to complete
    waitpid(consumer_pid, NULL, 0); // Wait for the consumer process to complete

    // Clean up resources
    shmdt(sTable);                          // Detach from the shared memory
    shmctl(sharedMemId, IPC_RMID, NULL);    // Remove the shared memory segment
    sem_unlink("/mutex");                   // Unlink the "mutex" semaphore
    sem_unlink("/empty");                   // Unlink the "empty" semaphore
    sem_unlink("/full");                    // Unlink the "full" semaphore


    return 0;
}
