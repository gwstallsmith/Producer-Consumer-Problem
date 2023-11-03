#include "consumer.h"

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


void consumer(SharedTable *sTable) {
    int item = 0;

    while(1) {
        sem_wait(sTable->full);         // Wait for a full index in table
        sem_wait(sTable->mutex);        // Wait until critical section is open

        item = sTable->table[sTable->out];              // Remove item from shared table
        sTable->out = (sTable->out + 1) % BUFFER_SIZE;  // Increment output index

        printf("Consumer: %d\n", item);     // Display item

        sem_post(sTable->mutex);        // Unlock critical section
        sem_post(sTable->empty);        // Consume until buffer empty
        
        sleep(rand() % 2);      // Sleep for <= 2 seconds so I can view what is happening
    }
}