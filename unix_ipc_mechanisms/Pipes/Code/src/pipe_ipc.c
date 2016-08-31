/* Author: Gopi Krishna Marella.
 * Date : 08/26/2016.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/* A child process is created and waits for input from the parent process.replaced with a python script to run.
 * Parent process takes an input string from the stdin and sends it to child process using pipe.
 */
int main()
{
    int pipe_fds[2];
    char buff[1024];
    int buff_bytes;
    pid_t pid;

    if (pipe(pipe_fds) == -1) {
        perror("Pipe command");
        exit(-1);
    }

    pid = fork();
    if (pid == -1) {
        perror("Fork failed");
        exit(-1);
    }

    if (pid == 0) {
        /* Child process */
        /* Wait for some message from the parent */
        while(1) {
            buff_bytes = read(pipe_fds[0], buff, sizeof(buff));
            if (buff_bytes == -1) {
                /* Something happened */
                exit(-1);
            }
            printf(">> Ahem! Echo: %s\n", buff);
        }
    } else {
        /* Parent process */
        printf(">> ");
        while(fgets(buff, sizeof(buff), stdin)) {
            if (-1 == write(pipe_fds[1], buff, sizeof(buff))) {
                break;
            }
            sleep(1);
            printf(">> ");
        }
        /* Wait for the child to exit */
        wait(NULL);
    }

    return 0;
}
