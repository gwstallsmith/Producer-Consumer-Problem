#include "producer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <semaphore.h>


void producer(SharedTable *sTable) {
    int item = 0; 

    while(1) {
        item = rand() % 2;     // Produce a data item (Just 1 or 0)

        sem_wait(sTable->empty);        // Wait for an empty index in table
        sem_wait(sTable->mutex);        // Wait until critical section is open

        sTable->table[sTable->in] = item;               // Add data to shared table
        sTable->in = (sTable->in + 1) % BUFFER_SIZE;    // Increment input index

        printf("Producer: %d\n", item);     // Display item

        sem_post(sTable->mutex);        // Unlock critical section
        sem_post(sTable->full);         // Produce until buffer full

        sleep(rand() % 2);      // Sleep for < 2 seconds so I can view what is happening
    }
}



