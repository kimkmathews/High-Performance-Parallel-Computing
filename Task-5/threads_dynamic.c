#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* thread_func(void* arg) {
    int thread_index = *(int*) arg;
    printf("Thread %d\n", thread_index);
    long int i;
    long int n = 1000000000*(thread_index+1);
    double sum;
    for(i = 0; i < n; i++)
      sum += 1e-7;
    printf("Result of work in thread %d: sum = %7.20f\n", thread_index, sum);

    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s N\n", argv[0]);
        return 1;
    }
    int N = atoi(argv[1]);

    pthread_t threads[N];
    int thread_indices[N];
    for (int i = 0; i < N; i++) {
        thread_indices[i] = i;
        pthread_create(&threads[i], NULL, thread_func, &thread_indices[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
