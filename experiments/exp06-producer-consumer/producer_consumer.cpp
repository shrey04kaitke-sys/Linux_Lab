#include <iostream>
#include <pthread.h>
#include <semaphore.h>   // sem_t, sem_init, sem_wait, sem_post
#include <unistd.h>      // sleep, usleep
using namespace std;

const int BUFFER_SIZE = 5;
const int ITEMS = 10;

int buffer[BUFFER_SIZE];
int in = 0;              // where the producer writes next
int out = 0;             // where the consumer reads next

sem_t empty_slots;       // counts free slots (starts at BUFFER_SIZE)
sem_t full_slots;        // counts filled slots (starts at 0)
sem_t mutex_sem;         // protects in and out (starts at 1)

void* producer(void* arg) {
    for (int i = 1; i <= ITEMS; i++) {
        sem_wait(&empty_slots);      // wait until there is a free slot
        sem_wait(&mutex_sem);
        buffer[in] = i;
        in = (in + 1) % BUFFER_SIZE;
        cout << "Producer produced: " << i << endl;
        sem_post(&mutex_sem);
        sem_post(&full_slots);       // one more filled slot
        sleep(1);
    }
    return nullptr;
}

void* consumer(void* arg) {
    for (int i = 1; i <= ITEMS; i++) {
        sem_wait(&full_slots);       // wait until there is an item
        sem_wait(&mutex_sem);
        int item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        cout << "Consumer consumed: " << item << endl;
        sem_post(&mutex_sem);
        sem_post(&empty_slots);      // one more free slot
        sleep(2);
    }
    return nullptr;
}

int main() {
    sem_init(&empty_slots, 0, BUFFER_SIZE);
    sem_init(&full_slots, 0, 0);
    sem_init(&mutex_sem, 0, 1);

    pthread_t producer_thread, consumer_thread;
    pthread_create(&producer_thread, nullptr, producer, nullptr);
    pthread_create(&consumer_thread, nullptr, consumer, nullptr);

    pthread_join(producer_thread, nullptr);
    pthread_join(consumer_thread, nullptr);

    sem_destroy(&empty_slots);
    sem_destroy(&full_slots);
    sem_destroy(&mutex_sem);
    return 0;
}
