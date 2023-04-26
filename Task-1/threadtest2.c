#include <stdio.h>
#include <pthread.h>

void* the_thread_func(void* arg) {
  
  /* Do something here? */
  printf("thread() starting doing some work.\n");
  long int i;
  double sum;
  for(i = 0; i < 1000000000; i++)
    sum += 1e-7;
  printf("Result of work in thread(): sum = %f\n", sum);
  
  return NULL;
}

void* the_thread_func_2(void* arg) {
  
  /* Do something here? */
  printf("thread_2() starting doing some work.\n");
  long int i;
  double sum;
  for(i = 0; i < 2000000000; i++)
    sum += 1e-7;
  printf("Result of work in thread_2(): sum = %f\n", sum);
  
  return NULL;
}

int main() {
  printf("This is the main() function starting.\n");

  /* Start thread. */
  pthread_t thread;
  printf("the main() function now calling pthread_create().\n");
  pthread_create(&thread, NULL, the_thread_func, NULL);

  pthread_t thread_2;
  printf("the main() function now calling pthread_create().\n");
  pthread_create(&thread_2, NULL, the_thread_func_2, NULL);

  printf("This is the main() function after pthread_create()\n");

  /* Do something here? */
  printf("main() starting doing some work.\n");
  long int i;
  double sum;
  for(i = 0; i < 10000000; i++)
    sum += 1e-7;
  printf("Result of work in main(): sum = %f\n", sum);
  /* Wait for thread to finish. */
  printf("the main() function now calling pthread_join() for thread1.\n");
  pthread_join(thread, NULL);

  printf("the main() function now calling pthread_join() for thread2.\n");
  pthread_join(thread_2, NULL);

  return 0;
}
