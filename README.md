# Producer-Consumer Problem in C

This repository contains a C program that demonstrates the classic producer-consumer problem using shared memory and semaphores.

## Problem Description

The producer-consumer problem is a classic synchronization problem in computer science. It involves two types of processes, producers and consumers, that share a common, fixed-size buffer as a communication channel. Producers are responsible for adding data to the buffer, while consumers remove data from it. The problem's primary challenge is to ensure that producers and consumers can work concurrently without data corruption, race conditions, or deadlock.

## Implementation

The program is implemented in C and uses POSIX shared memory and semaphores for synchronization. It consists of the following components:

1. **shared_table.h**: A header file that defines the shared data structure and includes the necessary libraries.

2. **producer.h** and **producer.c**: Header and source files for the producer module. The producer function adds items to the shared buffer. Producer function inserts either 1 or 0 into the shared table.

3. **consumer.h** and **consumer.c**: Header and source files for the consumer module. The consumer function removes items from the shared buffer. Consumer function removes the produces binary integer from the shared table.

4. **main.c**: The main program that creates shared memory, initializes semaphores, and spawns producer and consumer processes. It manages synchronization and cleanup.

## Usage

1. Clone this repository to your local machine.

2. Compile the program using GCC:

   ```bash
   gcc -o producer_consumer main.c producer.c consumer.c -lrt
   ```

3. Run the executable:

   ```bash
   ./producer_consumer
   ```

## Dependencies

This program depends on the following libraries:

- POSIX Real-Time Library (`-lrt`) for shared memory and semaphore functions.

## Contributors

- [Garrett Stallsmith](https://github.com/gwstallsmith)
