//
//  Paths.c
//  DSPD ASS 3
//
//  Created by Official on 04/06/20.
//  Copyright © 2020 Official. All rights reserved.
//

#include "Paths.h"
#include "limits.h"
#include <stdlib.h>


void initialise_single_source(Graph *g,int source){
    for(int i=0;i<g->v;i++){
        g->array[i].distance_from_source= INT_MAX/100;
        g->array[i].parent=-1;
    }
    g->array[source].distance_from_source=0;
}

void Relax(Graph *g,int source,int destination,int weight){
    if(g->array[destination].distance_from_source > g->array[source].distance_from_source + weight){
        g->array[destination].distance_from_source = g->array[source].distance_from_source + weight;
        g->array[destination].parent = source;
    }
}

int Bellman_Ford(Graph *g,int source){
    initialise_single_source(g, source);
    for(int i=0;i<g->v-1;i++){
        for(int j=0;j<g->v;j++){
            AdjListNode *ptr = g->array[j].head;
            while(ptr!=NULL){
                Relax(g, j, ptr->destination, ptr->weight);
                ptr = ptr->next;
            }
        }
    }
    for(int i=0;i<g->v;i++){
        AdjListNode *ptr = g->array[i].head;
        while (ptr!=NULL) {
            if(g->array[ptr->destination].distance_from_source > g->array[i].distance_from_source + ptr->weight){
                return 0;
            }
            ptr = ptr->next;
        }
    }
    return 1;
}

void Shortest_path(Graph *g,int source){
    if(Bellman_Ford(g, source)==0){
        printf("The Graph Contains Negative Cycle\n\n");
    }
    printf("Shortest Distance from All vertex to source %d\n\n",source);
    for(int i=g->v-1;i>=0;i--){
        if(g->array[i].parent != -1){
            printf("The Path cost of %d from source %d is : %d\n",i,source,g->array[i].distance_from_source);
            if(g->array[i].distance_from_source>=0){
                int des = i;
                while(des!=source){
                    printf("%d <-- ",des);
                    des = g->array[des].parent;
                }
                printf(" %d \n",source);
            }
            else{
                printf("Negative Cycle therefore Infinite Path\n\n");
            }
        }
    }
}


void floydWarshall (int *graph[],int V)
{
    int dist[V][V], i, j, k;
  
    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            dist[i][j] = graph[i][j];
    for (k = 0; k < V; k++)
    {
        for (i = 0; i < V; i++)
        {
            for (j = 0; j < V; j++)
            {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
    for(i=0;i<V;i++){
        for(j=0;j<V;j++){
            graph[i][j] = dist[i][j];
        }
    }
    
}

void All_Pair_Shortest(Graph *g){
    int *graph[g->v];
    for(int i=0;i<g->v;i++){
        graph[i] = (int*)malloc(sizeof(int)*(g->v));
    }
    
    for(int i=0;i<g->v;i++){
        for(int j=0;j<g->v;j++){
            graph[i][j]=INT_MAX/100;
            if(i==j){
                graph[i][j]=0;
            }
            // Just To Be Safe INT_MAX/3 as Int_MAX + INTMAX = 0 in c or worse
        }
    }
    for(int i=0;i<g->v;i++){
        AdjListNode *ptr = g->array[i].head;
        while(ptr!=NULL){
            graph[i][ptr->destination] = ptr->weight;
            ptr = ptr->next;
        }
    }
    floydWarshall(graph, g->v);
    for(int i=0;i<g->v;i++){
        for(int j=0;j<g->v;j++){
            printf("Shortest Path b/w %d and %d is : %d \n",i,j,graph[i][j]);
        }
        printf("\n");
    }
}


void print_all_pair_shortestPath(Graph *g){
    for(int i=0;i<g->v;i++){
        Shortest_path(g, i);
    }
}


void AllPathUtil(Graph *g,int paths[],int index,int destination,int vertex){
    if(vertex == destination){
        for(int i=0;i<index;i++){
            printf("%d --> ",paths[i]);
        }
        printf("%d \n",vertex);
    }
    else{
        int found = 0;
        for(int i=0;i<index && !found;i++){
            if(paths[i]==vertex){
                found = 1;
            }
        }
        if(!found){
            paths[index] = vertex;
            AdjListNode *ptr = g->array[vertex].head;
            while(ptr!=NULL){
                AllPathUtil(g, paths, index+1, destination, ptr->destination);
                ptr = ptr->next;
            }
        }
    }
}

void AllPath(Graph *g,int source,int destination){
    int paths[g->v+1];
    paths[0]=source;
    printf("All Paths From %d to %d are : \n\n",source,destination);
    AdjListNode *ptr = g->array[source].head;
    while(ptr!=NULL){
        AllPathUtil(g, paths, 1, destination, ptr->destination);
        ptr = ptr->next;
    }
}

int detectCyclesUtil(Graph *g,int destination,int visited[]){
    if(visited[destination]){
        return 1;
    }
    else{
        AdjListNode *ptr=g->array[destination].head;
        visited[destination] = 1;
        while(ptr!=NULL){
            int ans = detectCyclesUtil(g, ptr->destination, visited);
            if(ans == 1){
                return ans;
            }
            ptr = ptr->next;
        }
        visited[destination]=0;
        return 0;
    }
}


int detectCycles(Graph *g){
    int visited[g->v];
    for(int i=0;i<g->v;i++){
        visited[i]=0;
    }
    for(int i=0;i<g->v;i++){
        int ans = detectCyclesUtil(g, i, visited);
        if(ans == 1){
            return 1;
        }
    }
    return 0;
}
