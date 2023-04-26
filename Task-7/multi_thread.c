#include <stdio.h>
#include <pthread.h>

void* thread_function(void* arg) {
    int id = *(int*) arg;
    printf("Thread %d started\n", id);

    if (id < 4) {
        int child_id1 = id * 2 + 1;
        int child_id2 = id * 2 + 2;
        pthread_t child_thread1, child_thread2;

        printf("Thread %d creating child threads %d and %d\n", id, child_id1, child_id2);

        pthread_create(&child_thread1, NULL, thread_function, &child_id1);
        pthread_create(&child_thread2, NULL, thread_function, &child_id2);

        pthread_join(child_thread1, NULL);
        pthread_join(child_thread2, NULL);

        printf("Thread %d finished\n", id);
    } 
    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;
    int id1 = 1, id2 = 2;

    printf("Main thread started\n");

    pthread_create(&thread1, NULL, thread_function, &id1);
    pthread_create(&thread2, NULL, thread_function, &id2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Main thread finished\n");

    return 0;
}
