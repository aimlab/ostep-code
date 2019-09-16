#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
    printf("hello world (pid:%d)\n", (int) getpid());
    pid_t pid;
    pid = fork();
    if (pid < 0)
        printf("error occurred!\n");
    else if (pid == 0) {
        printf("I'm a child (pid:%d) of (pid:%d)\n", 
                (int) getpid(), (int) getppid());
        sleep(60);
        printf("I'm a orphan (pid:%d), adopted by (pid:%d)\n", 
                (int) getpid(), (int) getppid());
        exit(0); //(1)
    } else {
        sleep(20);
        printf("The father (pid:%d) says goodbye to the child (pid:%d)\n", 
                (int) getpid(), pid);
    }
}
