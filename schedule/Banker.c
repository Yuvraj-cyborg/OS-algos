#include <stdio.h>

int check_need(int m, int need[][m], int i, int work[]) {
    for (int j = 0; j < m; j++) {
        if (need[i][j] > work[j]) {
            return 0; 
        }
    }
    return 1; 
}

int safety(int n, int m, int allocation[][m], int need[][m], int available[]) {
    int work[m], finish[n], safeSeq[n], count = 0;

    for (int i = 0; i < m; i++)
        work[i] = available[i];

    for (int i = 0; i < n; i++)
        finish[i] = 0;

    while (count < n) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (!finish[i] && check_need(m, need, i, work)) {
                for (int j = 0; j < m; j++)
                    work[j] += allocation[i][j];
                safeSeq[count++] = i;
                finish[i] = 1;
                found = 1;
            }
        }
        if (!found) {
            printf("System is NOT in a safe state.\n");
            return 0;
        }
    }

    printf("\nSystem is in a SAFE state.\nSafe Sequence: ");
    for (int i = 0; i < n; i++)
        printf("P%d ", safeSeq[i]);
    printf("\n");
    return 1;
}

int main() {
    int n, m;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    int allocation[n][m], max[n][m], need[n][m], available[m];

    printf("\nEnter Allocation Matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("Process P%d: ", i);
        for (int j = 0; j < m; j++)
            scanf("%d", &allocation[i][j]);
    }

    printf("\nEnter Max Matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("Process P%d: ", i);
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);
    }

    printf("\nEnter Available Resources:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &available[i]);

    printf("\nNeed Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    safety(n, m, allocation, need, available);

    return 0;
}
