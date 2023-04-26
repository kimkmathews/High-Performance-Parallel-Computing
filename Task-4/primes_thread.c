#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_THREADS 2

int is_prime(int n){
    for (int i=2; i<=n/2; i++)
        if (n%i == 0)
            return 0;
    return 1;
}

struct thread_data {
    int start;
    int end;
    int count;
};

void* count_primes(void* arg) {
    struct thread_data* data = (struct thread_data*) arg;
    int count = 0;
    for (int i=data->start; i<=data->end; i++) {
        if (is_prime(i))
            count++;
    }
    data->count = count;
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s M\n", argv[0]);
        return 1;
    }

    int M = atoi(argv[1]);
    int range1_end = M / 2;
    int range2_start = range1_end + 1;

    struct thread_data thread_data_array[NUM_THREADS];
    pthread_t threads[NUM_THREADS];
    int rc;

    for (int i=0; i<NUM_THREADS; i++) {
        struct thread_data* data = &thread_data_array[i];
        if (i == 0) {
            data->start = 1;
            data->end = range1_end;
        } else {
            data->start = range2_start;
            data->end = M;
        }
        data->count = 0;
        rc = pthread_create(&threads[i], NULL, count_primes, (void*) data);
        if (rc) {
            printf("Error: return code from pthread_create() is %d\n", rc);
            return 1;
        }
    }

    int total_count = 0;
    for (int i=0; i<NUM_THREADS; i++) {
        rc = pthread_join(threads[i], NULL);
        if (rc) {
            printf("Error: return code from pthread_join() is %d\n", rc);
            return 1;
        }
        total_count += thread_data_array[i].count;
    }

    printf("There are %d prime numbers between 1 and %d\n", total_count, M);

    return 0;
}