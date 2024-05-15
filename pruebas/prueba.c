# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

// the initial balance is 0
int balance = 0;
pthread_mutex_t lock;

// write the new balance (after as simulated 1/4 second delay)
void write_balance(int new_balance)
{
  usleep(250000);
  balance = new_balance;
}

// returns the balance (after a simulated 1/4 seond delay)
int read_balance()
{
  usleep(250000);
  return balance;
}

// carry out a deposit
void* deposit(void *amount)
{
  pthread_mutex_lock(&lock);
  // retrieve the bank balance
  int account_balance = read_balance();

  // make the update locally
  account_balance += *((int *) amount);

  // write the new bank balance
  write_balance(account_balance);
  pthread_mutex_unlock(&lock);

  return NULL;
}
u_int64_t   get_time(void)
{
    struct timeval  tv;
    gettimeofday(&tv, NULL);
    // convert tv_sec & tv_usec to millisecond
    return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}

int main()
{
  // output the balance before the deposits
  int before = read_balance();
  printf("Before: %d\n", before);

  // we'll create two threads to conduct a deposit using the deposit function
  pthread_t thread1;
  pthread_t thread2;

  // the deposit amounts... the correct total afterwards should be 500
  int deposit1 = 300;
  int deposit2 = 200;
    if (pthread_mutex_init(&lock, NULL) != 0) { 
        printf("\n mutex init has failed\n"); 
        return 1; 
    }

  // create threads to run the deposit function with these deposit amounts
  pthread_create(&thread1, NULL, deposit, (void*) &deposit1);
  pthread_create(&thread2, NULL, deposit, (void*) &deposit2);

  // join the threads
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  // output the balance after the deposits
  int after = read_balance();
  printf("After: %d\n", after);
  pthread_mutex_destroy(&lock);

  printf("%ld\n", get_time());

  return 0;
}