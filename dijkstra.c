#include <stdio.h>
#define MAX 10
#define INF 9999

int graph[MAX][MAX];
int dist[MAX];
int visited[MAX];
int parent[MAX];
int n;


int minDistance() {
    int min = INF, minIndex = -1;
    for (int i = 0; i < n; i++) {
        if (!visited[i] && dist[i] <= min) {
            min = dist[i];
            minIndex = i;
        }
    }
    return minIndex;
}

void printPath(int dest) {
    if (parent[dest] == -1) {
        printf("%d", dest);
        return;
    }
    printPath(parent[dest]);
    printf(" -> %d", dest);
}


void dijkstra(int source) {

    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }
    dist[source] = 0;

  
    for (int count = 0; count < n - 1; count++) {
        int u = minDistance();
        if (u == -1) break;
        visited[u] = 1;

        
        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] != INF && graph[u][v] != 0) {
                if (dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                    parent[v] = u;
                }
            }
        }
    }
}

int main() {
    int source;

    printf("=====================================================\n");
    printf("  Dijkstra's Shortest Path Algorithm\n");
    printf("  Computer Networks-II Lab | Mayank Bisht | 2361323\n");
    printf("=====================================================\n\n");

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix (use 0 for no direct edge):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
            if (graph[i][j] == 0 && i != j)
                graph[i][j] = INF;
        }
    }

    printf("Enter source vertex (0 to %d): ", n - 1);
    scanf("%d", &source);

    dijkstra(source);

    printf("\n-----------------------------------------------------\n");
    printf("Shortest distances from vertex %d:\n", source);
    printf("-----------------------------------------------------\n");
    printf("%-10s %-15s %s\n", "Vertex", "Distance", "Path");
    printf("-----------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("%-10d ", i);
        if (dist[i] == INF)
            printf("%-15s ", "UNREACHABLE");
        else
            printf("%-15d ", dist[i]);

        if (dist[i] == INF)
            printf("No path");
        else
            printPath(i);
        printf("\n");
    }
    printf("-----------------------------------------------------\n");

    return 0;
}

