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
    return 0;
}


























#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
    int rc = fork();
    if (rc < 0) { // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // child: redirect standard output to a file
	close(STDOUT_FILENO); 
	open("./p4.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
	// now exec "wc"...
        char *myargs[3];
        myargs[0] = strdup("wc");   // program: "wc" (word count)
        myargs[1] = strdup("p4.c"); // argument: file to count
        myargs[2] = NULL;           // marks end of array
        execvp(myargs[0], myargs);  // runs word count
    } else { // parent goes down this path (original process)
        int wc = wait(NULL);
	assert(wc >= 0);
    }
    return 0;
}
