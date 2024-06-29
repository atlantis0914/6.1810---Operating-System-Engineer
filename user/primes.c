#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int prime(int * read_pipe)
{
    int pid, p;

    int write_pipe[2];
    //close(read_pipe[1]);

    if (read(read_pipe[0], &p, 1) == 0) {
        close(read_pipe[0]);
        exit(0);
    }

    printf("prime %d\n", p);


    pipe(write_pipe); 
    pid = fork();
    if (pid == 0) {
        close(read_pipe[0]);
        close(write_pipe[1]);
        prime(write_pipe);
    } else {
        int n;
        while (read(read_pipe[0], &n, 1)) {
            if (n % p) {
                write(write_pipe[1], &n, 1);
            }
        }
        close(read_pipe[0]);
        close(write_pipe[1]);
        wait(0);
    }
    exit(0);
}

int main(int argc, char *argv[])
{
    int pid;
    int write_pipe[2];

    pipe(write_pipe);
    pid = fork();
    if (pid == 0) {
        close(write_pipe[1]);
        prime(write_pipe);
    } else {
        close(write_pipe[0]);
        for (int i = 2; i < 36; i++) {
            write(write_pipe[1], &i, 1);
        }
        close(write_pipe[1]);
        wait(0);
    }
    exit(0);
}
