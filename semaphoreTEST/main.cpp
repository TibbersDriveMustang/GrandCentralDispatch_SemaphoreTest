//
//  main.cpp
//  semaphoreTEST
//  Using Grand Central Dispatch,dispatch semaphore library
//  Created by Hongyi Guo on 10/2/15.
//  Copyright © 2015 Hongyi Guo. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>
#include <dispatch/dispatch.h>


#define MAX_MSG_LEN  256

sem_t sem1;
sem_t sem2;
dispatch_semaphore_t semaphore;
int coin=0;

void *thrdFun1(void *arg);
void *thrdFun2(void *arg);
void toggleCase(char *buf, int cnt);

int main()
{
    semaphore = dispatch_semaphore_create(1);
//    printf("semaphore value %ld\n",semaphore);
    pthread_t thrd1;
    char argmsg1[] = "Thread1: Waiting\n";
    int thNum;
    int res;
    
    //res = sem_init(&sem1, 1,0);
    //printf("res=%d\n",res);
    //  res = sem_init(&sem2, 0,0);
    
    pthread_create(&thrd1, NULL, thrdFun1, argmsg1);
    //dispatch_semaphore_signal(semaphore);
    while(1)
    {
        if (coin==0)
        {
//            dispatch_semaphore_signal(semaphore);
//            printf("semaphore value %ld\n",semaphore);
//            dispatch_semaphore_wait(semaphore, DISPATCH_TIME_FOREVER);
              printf("no coin: please enter coin\n");
//            printf("semaphore value %ld\n",semaphore);
            dispatch_semaphore_wait(semaphore, DISPATCH_TIME_FOREVER);
            scanf("%d",&coin);
            dispatch_semaphore_signal(semaphore);
            sleep(1);
        }
        else if(coin > 0){
            sleep(1);
        }
        else if(coin < 0)
        {
            dispatch_release(semaphore);
            sleep(1);
            break;
        }
    }
    printf("Program terminating...\n");
    return 0;
}

void *thrdFun1(void *arg)
{
    while(1)
    {
        dispatch_semaphore_wait(semaphore, DISPATCH_TIME_FOREVER);
        printf("I'm %s\n",(char *)arg);
        if(coin > 0){
            printf("%d Delivered...\n",coin);
            coin=0;
        }
        dispatch_semaphore_signal(semaphore);
        sleep(1);
    }
}