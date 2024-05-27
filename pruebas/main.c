// #include <stdio.h>
// #include <pthread.h>

// int mails = 0;
// pthread_mutex_t mutex;

// void    *routine(){
//     pthread_mutex_lock(&mutex);
//     for (int i = 0; i < 10000000; i++){
//         mails++;
//     }
//     pthread_mutex_unlock(&mutex);
// }

// int main(int argc, char *argv[]) {
//     pthread_t p1, p2;
//     pthread_mutex_init(&mutex, NULL);
//     pthread_create(&p1, NULL, &routine, NULL);
//     pthread_create(&p2, NULL, &routine, NULL);
//     pthread_join(p1, NULL);
//     pthread_join(p2, NULL);
//     pthread_mutex_destroy(&mutex);
//     printf("Number of mails: %d\n", mails);
//     return (0);
// }

#include <pthread.h>
#include <stdio.h>
#include <unistd.h> // for sleep

// This function will be executed by the detached thread
void* print_in_background(void* arg)
{
    printf("This is printed from the thread.\n");
    sleep(5);
    return NULL;
}

int main() {
    pthread_t thread_id;

    // Create a new thread
    if (pthread_create(&thread_id, NULL, print_in_background, NULL) != 0)
    {
        perror("Failed to create thread");
        return 1;
    }

    // 🚨 toggle these 2 🚨
   pthread_detach(thread_id);
     //pthread_join(thread_id, NULL);

    // Continue with the main thread's work
    printf("This is printed from the main thread.\n");
    usleep(100000);

    return 0;
}