#include <iostream>
#include <pthread.h>
#include <semaphore.h>   // sem_t, sem_init, sem_wait, sem_post
#include <unistd.h>      // usleep
using namespace std;

sem_t mutex_sem;         // protects readCount
sem_t wrt;               // gives a writer exclusive access
int readCount = 0;       // how many readers are reading right now
int sharedData = 0;      // the shared resource

void* reader(void* arg) {
    int id = *(int*)arg;
    for (int round = 0; round < 2; round++) {
        sem_wait(&mutex_sem);
        readCount++;
        if (readCount == 1) sem_wait(&wrt);   // first reader blocks writers
        sem_post(&mutex_sem);

        cout << "Reader " << id << " reads value " << sharedData << endl;
        usleep(500000);                       // reading takes a while

        sem_wait(&mutex_sem);
        readCount--;
        if (readCount == 0) sem_post(&wrt);   // last reader lets writers in
        sem_post(&mutex_sem);

        usleep(300000);
    }
    return nullptr;
}

void* writer(void* arg) {
    int id = *(int*)arg;
    for (int round = 0; round < 2; round++) {
        sem_wait(&wrt);                       // wait for exclusive access
        sharedData += 10;
        cout << "Writer " << id << " writes value " << sharedData << endl;
        usleep(700000);                       // writing takes a while
        sem_post(&wrt);                       // release access
        usleep(400000);
    }
    return nullptr;
}

int main() {
    sem_init(&mutex_sem, 0, 1);
    sem_init(&wrt, 0, 1);

    pthread_t readers[3], writers[2];
    int rid[3] = {1, 2, 3};
    int wid[2] = {1, 2};

    for (int i = 0; i < 2; i++)
        pthread_create(&writers[i], nullptr, writer, &wid[i]);
    for (int i = 0; i < 3; i++)
        pthread_create(&readers[i], nullptr, reader, &rid[i]);

    for (int i = 0; i < 2; i++) pthread_join(writers[i], nullptr);
    for (int i = 0; i < 3; i++) pthread_join(readers[i], nullptr);

    sem_destroy(&mutex_sem);
    sem_destroy(&wrt);
    cout << "Final value: " << sharedData << endl;
    return 0;
}
