#include <stdio.h>
#include <pthread.h>

void* the_thread_func(void* arg) {
  /* Do something here? */
  double* data = (double*) arg;
  printf("thread() starting doing some work.\n");
  long int i;
  double sum;
  for(i = 0; i < 1000000000; i++)
    sum += 1e-7;
  
  printf("Data from thread: %f, %f, %f\n", data[0], data[1], data[2]);

  printf("Result of work in thread(): sum = %f\n", sum);
  return NULL;
}



int main() {
  printf("This is the main() function starting.\n");

  double data_for_thread[3];
  data_for_thread[0] = 5.7;
  data_for_thread[1] = 9.2;
  data_for_thread[2] = 1.6;

  double data_for_thread2[3];
  data_for_thread2[0] = 7.5;
  data_for_thread2[1] = 2.9;
  data_for_thread2[2] = 6.1;

  /* Start thread. */
  pthread_t thread;
  pthread_t thread2;

  printf("the main() function now calling pthread_create() for thread 1.\n");
  pthread_create(&thread, NULL, the_thread_func, data_for_thread);

  printf("the main() function now calling pthread_create() for thread 2.\n");
  pthread_create(&thread2, NULL, the_thread_func, data_for_thread2);


  printf("This is the main() function after pthread_create()\n");

  /* Do something here? */
  printf("main() starting doing some work.\n");
  long int i;
  double sum;
  for(i = 0; i < 50000000; i++)
    sum += 1e-7;
  printf("Result of work in main(): sum = %f\n", sum);
  /* Wait for thread to finish. */
  printf("the main() function now calling pthread_join() for thread 1.\n");
  pthread_join(thread, NULL);

  printf("the main() function now calling pthread_join() for thread 2.\n");
  pthread_join(thread, NULL);

  return 0;
}
