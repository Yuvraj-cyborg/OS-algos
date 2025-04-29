#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main() {
    int pipefd[2];

    if (pipe(pipefd) == -1) {
        printf("error in getting pipes lol..");
        exit(1);
    }

    printf("Read descriptor: %d\n", pipefd[0]);
    printf("Write descriptor: %d\n", pipefd[1]);

    return 0;
}