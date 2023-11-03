#ifndef SHARED_TABLE_H
#define SHARED_TABLE_H

#include <semaphore.h>

#define BUFFER_SIZE 2           // Table size of 2

// Shared table of data
typedef struct {
    int table[BUFFER_SIZE];     // Shared table
    int in;                     // Producer insert index
    int out;                    // Consumer remove index

    // Semaphores (signals)
    sem_t *mutex;                   // Mutex to protect critical sections 
    sem_t *empty;                   // Tracks empty indexes
    sem_t *full;                    // Tracks filled indexes

} SharedTable;

#endif