#include <stdio.h>
#include <stdlib.h>


struct graphEdge {
        int src, dest, weight;
};

typedef struct graphEdge Edge;


void swapEdge (Edge* a, Edge* b);
void qsortEdge (Edge* edges, int startIndex, int endIndex);
void kruskalMST (Edge* edges, int numEdges, int numVertices);
int findSrc (int*a, int src, int numVertices);
void groupEdges (int* a, int r1, int r2);

int main(){
        for (size_t g = 0; g < 1e7; g++) {
                int numVertices = 7;
                int numEdges = 10;

                Edge edges [] = { { 1, 2, 10 }, { 1, 3, 12 }, { 1, 4, 17 }, { 2, 5, 15 }, { 3, 7, 31 }, { 3, 6, 6 }, { 4, 5, 5 }, { 4, 7, 25 }, { 6, 7, 8 }, { 5, 7, 21 } };

                // for (int i = 0; i < numEdges; i++) {
                //         printf("%d -- %d : %d\n", edges [i].src, edges [i].dest, edges [i].weight);
                // }
                // printf("--------------------------------\n");

                kruskalMST(edges, numEdges, numVertices);
        }

        return 0;
}


void kruskalMST(Edge* edges, int numEdges, int numVertices){
        qsortEdge(edges, 0, numEdges - 1);

        // for (int i = 0; i < numEdges; i++) {
        //         printf("%d -- %d : %d\n", edges [i].src, edges [i].dest, edges [i].weight);
        // }
        // printf("--------------------------------\n");

        int*a = (int*)malloc(numVertices * sizeof(int));
        for (int i = 0; i < numVertices; i++)
                a [i] = i + 1;


        int countEdges = 0, i = 0;

        while (countEdges < numVertices - 1) {
                int src = findSrc(a, edges [i].src, numVertices);
                int dest = findSrc(a, edges [i].dest, numVertices);
                // printf("Src: %d Dest: %d\n", src, dest);
                if (src != dest) {
                        groupEdges(a, src - 1, dest - 1);
                        // printf("%d -- %d : %d\n", edges [i].src, edges [i].dest, edges [i].weight);
                        countEdges++;
                }
                i++;
        }
        free(a);
}




void qsortEdge(Edge* edges, int startIndex, int endIndex) {
        int currentIndex = startIndex;
        int pivotIndex = startIndex;

        if (startIndex >= endIndex) return;

        for (int i = startIndex + 1; i <= endIndex; i++)
                if (edges [i].weight < edges [pivotIndex].weight)
                        swapEdge(edges + i, edges + (++currentIndex));
        swapEdge(edges + pivotIndex, edges + currentIndex);

        qsortEdge(edges, startIndex, currentIndex - 1);
        qsortEdge(edges, currentIndex + 1, endIndex);
}
void swapEdge(Edge* a, Edge* b) {
        Edge temp = *a;

        *a = *b;
        *b = temp;
}

int findSrc(int*a, int src, int numVertices){
        if (a [src - 1] == src)
                return src;
        findSrc(a, a [src - 1], numVertices);
}

void groupEdges(int* a, int r1, int r2){
        a [r2] = r1 + 1;
}
