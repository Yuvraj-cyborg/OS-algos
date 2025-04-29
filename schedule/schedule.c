#include <stdio.h>

struct Process {
    int pid;
    int bt;
    int wt;
    int tat;
};

void calcAvg(struct Process proc[], int n) {
    float total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += proc[i].wt;
        total_tat += proc[i].tat;
    }
    printf("Average Waiting Time: %f\n", total_wt / n);
    printf("Average Turnaround Time: %f\n",total_tat / n);
}

void print(struct Process proc[], int n) {
    printf("\nPID\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\n", proc[i].pid, proc[i].bt, proc[i].wt, proc[i].tat);
    }
}

void fcfs(struct Process proc[], int n) {
    proc[0].wt = 0;
    for (int i = 1; i < n; i++) {
        proc[i].wt = proc[i - 1].wt + proc[i - 1].bt;
    }
    for (int i = 0; i < n; i++) {
        proc[i].tat = proc[i].wt + proc[i].bt;
    }
    print(proc, n);
    calcAvg(proc, n);
}

int main() {
    int n;
    struct Process proc[10];

    printf("Enter the number of processes (<= 10 cuz mukti mam said): ");
    scanf("%d", &n);


    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter Burst Time for Process %d: ", i + 1);
        scanf("%d", &proc[i].bt);
    }

    printf("FCFS here :- ");
    fcfs(proc, n);

    return 0;
}
