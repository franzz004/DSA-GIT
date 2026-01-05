#include <stdio.h>
#include <stdlib.h>

#define INF 9999
#define MAX 5

typedef struct node {
    int vertex;
    int weight;
    struct node* next;
} Vertex;

typedef struct {
    int vertices;
    Vertex* v[MAX]; // fix here | my bad gang
} Adjacent;

typedef int MATRIX[MAX][MAX];

void initAdjacentList(Adjacent* J);
void createEdge(Adjacent* J, int src ,int dest, int weight);
int minDistance(int dist[], int visit[]);
void freeAdjList(Adjacent* J);
void displayList(Adjacent L);

void initMatrix(MATRIX G);
void convertAdjacent2Matrix(MATRIX G, Adjacent* J);
void displayMatrix(MATRIX G);
void dfs(MATRIX G, int start);
int main() {
    Adjacent list;
    initAdjacentList(&list);
    createEdge(&list, 0, 1, 15);
    createEdge(&list, 1, 2, 5);
    createEdge(&list, 2, 3, 20);
    createEdge(&list, 0, 4, 30);

    if (list.v[0] != NULL)
        printf("First neighbor of vertex 0: %d\n", list.v[0]->vertex);

    displayList(list);
    MATRIX mat;
    initMatrix(mat);
    convertAdjacent2Matrix(mat,&list);
    

    displayMatrix(mat);
    //printf("[%d][%d] %d", 0,1, mat[0][1]);
    dfs(mat, 0);
    freeAdjList(&list);
    return 0;
}

void initAdjacentList(Adjacent* J) {
    J->vertices = MAX;
    for (int x = 0; x < MAX; x++) {
        J->v[x] = NULL;
    }
}

void createEdge(Adjacent* J, int src, int dest, int weight) {
    Vertex* temp = (Vertex*)malloc(sizeof(Vertex));
    if (temp != NULL) {
        temp->vertex = dest;
        temp->weight = weight;
        temp->next = J->v[src];
        J->v[src] = temp;
    }
}

int minDistance(int dist[], int visit[]) {
    int min_dist = INF, mindex = -1;
    for (int x = 0; x < MAX; x++) {
        if (visit[x] == 0 && dist[x] <= min_dist) {
            min_dist = dist[x];
            mindex = x;
        }
    }
    return mindex;
}

void freeAdjList(Adjacent* J) {
    for (int x = 0; x < J->vertices; x++) {
        Vertex* v = J->v[x];
        while (v != NULL) {
            Vertex* t = v;
            v = v->next;
            free(t);
        }
    }
}

void displayList(Adjacent L) {
    for (int x = 0; x < L.vertices; x++) {
        printf("[%d]: ", x);
        Vertex* trav = L.v[x];
        if (trav == NULL) {
            printf("NULL\n");
        }
        while (trav != NULL) {
            printf("-> (v:%d, w:%d) ", trav->vertex, trav->weight);
            trav = trav->next;
        }
        printf("\n");
    }
}


void initMatrix(MATRIX G) {
    int x, y;
    for(x = 0; x < MAX;x++) {
        for(y = 0; y < MAX; y++){
            G[x][y] = INF;
       }
       G[x][x] = 0;
    }
}

void convertAdjacent2Matrix(MATRIX G, Adjacent* J) {
    int x;
    for(x = 0; x < J->vertices; x++) {
        Vertex* trav = J->v[x];
        while(trav != NULL) {
            if(G[x][trav->vertex] == INF) {
            G[x][trav->vertex] = trav->weight;
            }else {
                G[x][trav->vertex] = (trav->weight < G[x][trav->vertex])? trav->weight : G[x][trav->vertex];
            }
            trav = trav->next;
        }
        printf("\n");
    }
}

void displayMatrix(MATRIX G) {
    int x,y;
    printf("   ");
    for(x = 0; x < MAX; x++) {
        printf("%4d ",x);
    }
    printf("\n\n");
    for(x = 0; x < MAX; x++) {
        printf("%d ", x);
        for(y = 0; y < MAX; y++) {
            if(G[x][y] == INF) {
                printf("%5s","INF");
            }else {
                printf("%5d", G[x][y]);
            }
        }
        printf("\n");
    }
}

void dfs(MATRIX G, int start) {
    int visit[MAX] = {0};
    int stack[MAX];
    int top =-1;
    int x;
    printf("\nDFS\n");
    printf("%5s", "tail weight head\n");
    stack[++top] = start;
    
    while(top != -1) {
        int curr = stack[top--];
        if(!visit[curr]) {
            visit[curr] = 1;

            for(x = MAX-1; x >=0; x--) {
                if(G[curr][x] != INF && G[curr][x] != 0 && !visit[x]) {
                    printf("%d -> %d --> %d\n", curr, G[curr][x], x);
                    stack[++top] = x;
                }
            }
        }
    }
}
/*
void BFS_iterative(int start) {
    visited[start] = 1;
    enqueue(start);

    while (!isQueueEmpty()) {
        int v = dequeue();
        printf("%d ", v);

        Node* temp = adjList[v];
        while (temp != NULL) {
            if (!visited[temp->vertex]) {
                visited[temp->vertex] = 1;
                enqueue(temp->vertex);
            }
            temp = temp->next;
        }
    }
}*/