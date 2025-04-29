
#include <stdio.h>

struct Process {
    int pid;
    int bt;
    int priority;
    int wt;
    int tat;
    int remaining_bt; 
};

void resetProcessData(struct Process proc[], struct Process backup[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i] = backup[i];
        proc[i].wt = 0;
        proc[i].tat = 0;
        proc[i].remaining_bt = proc[i].bt;
    }
}

void calculateAvgTimes(struct Process proc[], int n) {
    int total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += proc[i].wt;
        total_tat += proc[i].tat;
    }
    printf("\nAverage Waiting Time: %.2f", (float)total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)total_tat / n);
}

void printTable(struct Process proc[], int n) {
    printf("\nPID\tBT\tWT\tTAT\tPriority\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", proc[i].pid, proc[i].bt, proc[i].wt, proc[i].tat, proc[i].priority);
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
    printTable(proc, n);
    calculateAvgTimes(proc, n);
}

void sjf(struct Process proc[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (proc[j].bt > proc[j + 1].bt) {
                struct Process temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }

    proc[0].wt = 0;
    for (int i = 1; i < n; i++) {
        proc[i].wt = proc[i - 1].wt + proc[i - 1].bt;
    }
    for (int i = 0; i < n; i++) {
        proc[i].tat = proc[i].wt + proc[i].bt;
    }

    printTable(proc, n);
    calculateAvgTimes(proc, n);
}

void priorityScheduling(struct Process proc[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (proc[j].priority > proc[j + 1].priority) {
                struct Process temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }

    proc[0].wt = 0;
    for (int i = 1; i < n; i++) {
        proc[i].wt = proc[i - 1].wt + proc[i - 1].bt;
    }
    for (int i = 0; i < n; i++) {
        proc[i].tat = proc[i].wt + proc[i].bt;
    }

    printTable(proc, n);
    calculateAvgTimes(proc, n);
}

void roundRobin(struct Process proc[], int n, int quantum) {
    int time = 0, done;
    do {
        done = 1;
        for (int i = 0; i < n; i++) {
            if (proc[i].remaining_bt > 0) {
                done = 0;
                if (proc[i].remaining_bt > quantum) {
                    time += quantum;
                    proc[i].remaining_bt -= quantum;
                } else {
                    time += proc[i].remaining_bt;
                    proc[i].wt = time - proc[i].bt;
                    proc[i].remaining_bt = 0;
                    proc[i].tat = proc[i].wt + proc[i].bt;
                }
            }
        }
    } while (!done);

    printTable(proc, n);
    calculateAvgTimes(proc, n);
}

int main() {
    int n, choice, quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n], backup[n];

    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter Burst Time for Process %d: ", i + 1);
        scanf("%d", &proc[i].bt);
        printf("Enter Priority for Process %d (lower = higher priority): ", i + 1);
        scanf("%d", &proc[i].priority);
        proc[i].remaining_bt = proc[i].bt;
        proc[i].wt = 0;
        proc[i].tat = 0;
        backup[i] = proc[i]; 
    }

    do {
        printf("\n--- CPU Scheduling Menu ---\n");
        printf("1. First Come First Serve (FCFS)\n");
        printf("2. Shortest Job First (SJF)\n");
        printf("3. Round Robin\n");
        printf("4. Priority Scheduling\n");
        printf("5. Exit\n");
        printf("Enter your choice (1-5): ");
        scanf("%d", &choice);

        resetProcessData(proc, backup, n);

        switch (choice) {
            case 1:
                printf("\n--- FCFS Scheduling ---\n");
                fcfs(proc, n);
                break;

            case 2:
                printf("\n--- SJF Scheduling ---\n");
                sjf(proc, n);
                break;

            case 3:
                printf("Enter Time Quantum: ");
                scanf("%d", &quantum);
                printf("\n--- Round Robin Scheduling ---\n");
                roundRobin(proc, n, quantum);
                break;

            case 4:
                printf("\n--- Priority Scheduling ---\n");
                priorityScheduling(proc, n);
                break;

            case 5:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Please select again.\n");
        }

    } while (choice != 5);

    return 0;
}
