#include <stdio.h>
#define MAX 10
#define INF 999

int cost[MAX][MAX];  
int dist[MAX][MAX];  
int via[MAX][MAX];    
int n;                


void initialize() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = cost[i][j];
            if (cost[i][j] != INF && i != j)
                via[i][j] = j;   
            else
                via[i][j] = -1;
        }
        dist[i][i] = 0;
        via[i][i] = i;
    }
}


void distanceVectorRouting() {
    int updated = 1;
    int iterations = 0;

    while (updated) {
        updated = 0;
        iterations++;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
              
                for (int k = 0; k < n; k++) {
                    if (cost[i][k] != INF && dist[k][j] != INF) {
                        if (dist[i][j] > cost[i][k] + dist[k][j]) {
                            dist[i][j] = cost[i][k] + dist[k][j];
                            via[i][j] = k;
                            updated = 1;
                        }
                    }
                }
            }
        }
    }
    printf("  Converged in %d iteration(s)\n\n", iterations);
}


void printRoutingTable(int node) {
    printf("\n  Routing Table for Node %d:\n", node);
    printf("  +-------------+----------+----------+\n");
    printf("  | Destination | Distance | Next Hop |\n");
    printf("  +-------------+----------+----------+\n");

    for (int j = 0; j < n; j++) {
        printf("  |      %d      |", j);
        if (dist[node][j] == INF)
            printf("   INF    |");
        else
            printf("    %-5d |", dist[node][j]);

        if (via[node][j] == -1 || dist[node][j] == INF)
            printf("    --    |\n");
        else if (via[node][j] == j)
            printf("  Direct  |\n");
        else
            printf("    %-5d |", via[node][j]), printf("  |\n");
    }
    printf("  +-------------+----------+----------+\n");
}


void printDistanceMatrix() {
    printf("\n  Shortest Distance Matrix:\n  ");
    for (int j = 0; j < n; j++) printf("  %3d", j);
    printf("\n  ");
    for (int j = 0; j < n; j++) printf("-----");
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("  ");
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF)
                printf("  INF");
            else
                printf("  %3d", dist[i][j]);
        }
        printf("\n");
    }
}

int main() {
    printf("=====================================================\n");
    printf("  Distance Vector Routing Algorithm\n");
    printf("  Computer Networks-II Lab | Mayank Bisht | 2361323\n");
    printf("=====================================================\n\n");

    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    printf("Enter the cost matrix (%d is infinity for no link):\n", INF);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
        }
    }

    initialize();

    printf("\nRunning Distance Vector Routing Algorithm...\n");
    distanceVectorRouting();

    printDistanceMatrix();

    printf("\n-----------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printRoutingTable(i);
    }

    printf("\nResult: DVR Algorithm converged successfully.\n");
    printf("=====================================================\n");
    return 0;
}

