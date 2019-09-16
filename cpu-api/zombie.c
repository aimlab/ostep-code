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
        printf("Hi father! I'm a ZOMBIE (pid:%d)\n", (int) getpid());
        exit(0); //(1)
    } else {
        sleep(60);
        wait(NULL); //(2)
        printf("The father (pid:%d) collects the information of the 
                ZOMBIE child (pid:%d)\n", (int) getpid(), pid);
    }
    return 0;
}
