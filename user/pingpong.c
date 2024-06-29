#include "kernel/types.h"
#include "user/user.h"

int
main()
{
    int fd1[2]; // parent write, child read
    int fd2[2]; // child write, parent read
    int pid;

    int input_byte[1] = {3};

    if (pipe(fd1) == -1) {
        fprintf(2, "Create pipe fail");
        exit(1);
    }

    if (pipe(fd2) == -1) {
        fprintf(2, "Create pipe fail");
        exit(1);
    }

    pid = fork();
    if (pid == 0) {
        int read_byte[1];

        close(fd1[1]);
        read(fd1[0], read_byte, 1);
        if (read_byte[0] == 3) {
            printf("%d: received ping\n", getpid());
        }
        write(fd2[1], read_byte, 1);
        close(fd2[1]);
        exit(0);
    } else {
        int read_byte[1];

        close(fd1[0]);
        write(fd1[1], input_byte, 1);
        close(fd1[1]);

        wait(0);
        close(fd2[1]);
        read(fd2[0], read_byte, 1);
        if (read_byte[0] == 3) {
            printf("%d: received pong\n", getpid());
        }
        close(fd2[0]);
        exit(0);
    }
}