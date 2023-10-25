#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>

#define N 4 
void multiply_matrices(int A[N][N], int B[N][N], int C[N][N], int row_start, int row_end) {
    for (int i = row_start; i < row_end; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    int A[N][N];
    int B[N][N];
    int C[N][N] = {0};
    

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    }

    int num_processes = N;
    pid_t pid;
    int pipefd[2];


    struct timeval start, end;
    gettimeofday(&start, NULL);

    for (int i = 0; i < num_processes; i++) {
        if (pipe(pipefd) == -1) {
            perror("pipe");
            exit(1);
        }

        pid = fork();

        if (pid == 0) {

            close(pipefd[0]); 
            int row_start = i * (N / num_processes);
            int row_end = (i == num_processes - 1) ? N : (i + 1) * (N / num_processes);
            multiply_matrices(A, B, C, row_start, row_end);

            write(pipefd[1], &C[row_start][0], (row_end - row_start) * N * sizeof(int));
            close(pipefd[1]);
            exit(0);
        } else {
            close(pipefd[1]); 
            int row_start = i * (N / num_processes);
            int row_end = (i == num_processes - 1) ? N : (i + 1) * (N / num_processes);

            read(pipefd[0], &C[row_start][0], (row_end - row_start) * N * sizeof(int));
            close(pipefd[0]);
        }
    }


    for (int i = 0; i < num_processes; i++) {
        wait(NULL);
    }


    gettimeofday(&end, NULL);
    double execution_time = (double)(end.tv_sec - start.tv_sec) + (double)(end.tv_usec - start.tv_usec) / 1000000.0;
    

    printf("Resultant Matrix C:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
    
    printf("Execution time: %f seconds\n", execution_time);

    return 0;
}
