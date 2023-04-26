#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

const long int N1 = 400000000;
const long int N2 = 400000000;

static double get_wall_seconds() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
  return seconds;
}

void* the_thread_func(void* arg) {
  long int i;
  long int sum = 0;
  for(i = 0; i < N2; i++)
    sum += 7;
  /* OK, now we have computed sum. Now copy the result to the location given by arg. */
  long int * resultPtr;
  resultPtr = (long int *)arg;
  *resultPtr = sum;
  return NULL;
}

int main() {
  printf("This is the main() function starting.\n");

  long int thread_result_value = 0;

  /* Start thread. */
  pthread_t thread;
  printf("the main() function now calling pthread_create().\n");

  double time1 = get_wall_seconds();
  pthread_create(&thread, NULL, the_thread_func, &thread_result_value);
  double time2 = get_wall_seconds();
  printf("Time for N2 = %li in thread took %7.7f wall seconds.\n", N2, time2-time1);  

  printf("This is the main() function after pthread_create()\n");
  
  double time3= get_wall_seconds();
  long int i;
  long int sum = 0;
  for(i = 0; i < N1; i++)
    sum += 7;
  double time4 = get_wall_seconds();
  printf("Time for N1 = %li in thread took %7.7f wall seconds.\n", N1, time4-time3);  
  
  /* Wait for thread to finish. */
  printf("the main() function now calling pthread_join().\n");
  pthread_join(thread, NULL);

  printf("sum computed by main() : %ld\n", sum);
  printf("sum computed by thread : %ld\n", thread_result_value);
  long int totalSum = sum + thread_result_value;
  printf("totalSum : %ld\n", totalSum);

  return 0;
}
