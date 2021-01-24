//
//  Transversals.c
//  DSPD_Assignment3
//
//  Created by Official on 27/05/20.
//  Copyright © 2020 Official. All rights reserved.
//

#include "Graph_definitions.h"
#include <limits.h>
#include "queue.h"
#include "Transversals.h"
#include <stdlib.h>
#include "Paths.h"

void BreadthFirstTransversal(Graph *g,int source){
    int vertex = g->v;
    int visited[vertex];
    for(int i=0;i<vertex;i++){
        visited[i]=0;
        g->array[i].parent=-1;
        g->array[i].distance_from_source = INT_MAX;
    }
    Queue *q = malloc(sizeof(Queue));
    init_Queue(q);
    Enqueue(source, q);
    visited[source] = 1;
    g->array[source].distance_from_source = 0;
    while(isEmpty_Queue(q)==0){
        int v = Dequeue(q);
        printf("%d --> ",v);
        AdjListNode *ptr = g->array[v].head;
        while(ptr!=NULL){
            if(visited[ptr->destination]==0){
                visited[ptr->destination]=1;
                g->array[ptr->destination].parent = v;
                g->array[ptr->destination].distance_from_source = g->array[v].distance_from_source+1;
                Enqueue(ptr->destination, q);
            }
            ptr = ptr->next;
        }
    }
    printf("\n\n ** END OF BREADTH FIRST TRAVERSAL ** \n\n");
}

// Depth First Search

void DFTUtil(Graph *g,int visited[],int source){
    AdjListNode *ptr = g->array[source].head;
    visited[source] = 1;
    printf(" ( %d",source);
    while(ptr!=NULL){
        if(visited[ptr->destination] == 0){
            g->array[ptr->destination].parent=source;
            DFTUtil(g, visited, ptr->destination);
        }
        ptr = ptr->next;
    }
    visited[source] = 2;
    printf(" ) ");
}

void DepthFirstTransversal(Graph *g){
    int ver = g->v;
    int visited[ver];
    for(int i=0;i<ver;i++){
        visited[i]=0;
    }
    for(int i=0;i<ver;i++){
        if(visited[i]==0){
            DFTUtil(g,visited,i);
        }
    }
}



Topo_tag* insert_at_start(Topo_tag *t,int d){
    Topo_tag *ptr = (Topo_tag*)malloc(sizeof(Topo_tag));
    ptr->d = d;
    ptr->nxt=t;
    return ptr;
}

Topo_tag* Topo_Util(Graph *g,int source,int visited[],Topo_tag *ta){
    AdjListNode *ptr = g->array[source].head;
    visited[source] = 1;
    while(ptr!=NULL){
        if(visited[ptr->destination] == 0){
            g->array[ptr->destination].parent=source;
            ta = Topo_Util(g, ptr->destination, visited, ta);
        }
        ptr = ptr->next;
    }
    visited[source] = 2;
    ta = insert_at_start(ta, source);
    return ta;
}

void Topological_Sort_Util(Graph *g){
    Topo_tag *top_list = NULL;
    int ver = g->v;
    int visited[ver];
    for(int i=0;i<ver;i++){
        visited[i]=0;
    }
    for(int i=0;i<ver;i++){
        if(visited[i]==0){
            top_list = Topo_Util(g, i, visited, top_list);
        }
    }
    Topo_tag *ptr = top_list;
    while (ptr) {
        printf("%d, ",ptr->d);
        ptr = ptr->nxt;
    }
}

void Topological_Sort(Graph *g){
    if(detectCycles(g)==0){
        Topological_Sort_Util(g);
    }
    else{
        printf("\n\nGraph contains cycle hence Topological sorting Fails\n\n");
    }
}



void BFT_for_Connected(Graph *g,int source){
    int vertex = g->v;
    int visited[vertex];
    for(int i=0;i<vertex;i++){
        visited[i]=0;
        g->array[i].parent=-1;
        g->array[i].distance_from_source = INT_MAX;
    }
    Queue *q = malloc(sizeof(Queue));
    init_Queue(q);
    Enqueue(source, q);
    visited[source] = 1;
    g->array[source].distance_from_source = 0;
    while(isEmpty_Queue(q)==0){
        int v = Dequeue(q);
        AdjListNode *ptr = g->array[v].head;
        while(ptr!=NULL){
            if(visited[ptr->destination]==0){
                visited[ptr->destination]=1;
                g->array[ptr->destination].parent = v;
                g->array[ptr->destination].distance_from_source = g->array[v].distance_from_source+1;
                Enqueue(ptr->destination, q);
            }
            ptr = ptr->next;
        }
    }
}


void BreadthFirsSearch(Graph *g,int destination){
    
    for (int i=0; i<g->v; i++) {
        if(i!=destination){
            BFT_for_Connected(g, i);
            if(g->array[destination].distance_from_source!=INT_MAX){
                int j = destination;
                while(j!=i){
                    printf("%d <-- ",j);
                    j = g->array[j].parent;
                }
                printf("%d \n\n",j);
                return;
            }
        }
    }
    printf("No BFS Route For %d \n\n",destination);
}

int DFSUtil(Graph *g,int visited[],int source,int destination){
    if(source == destination){
        return 1;
    }
    else{
        int ans=0;
        AdjListNode *ptr = g->array[source].head;
        visited[source] = 1;
        while(ptr!=NULL){
            if(visited[ptr->destination] == 0){
                g->array[ptr->destination].parent=source;
                ans = DFSUtil(g, visited, ptr->destination,destination);
                if(ans==1){
                    return ans;
                }
            }
            ptr = ptr->next;
        }
        visited[source] = 2;
        
        return ans;
    }
}


void DepthFirstSearch(Graph *g,int destination){
    int visited[g->v];
    for(int i=0;i<g->v;i++){
        visited[i]=0;
    }
    for(int i=0;i<g->v;i++){
        if(i!=destination){
            if(DFSUtil(g, visited, i, destination)){
                int j = destination;
                while (j!=i) {
                    printf("%d <-- ",j);
                    j = g->array[j].parent;
                }
                printf("%d \n\n",j);
                return;
            }
            for(int l=0;l<g->v;l++){
                visited[l]=0;
            }
        }
    }
    printf("\nNo DFS Route for %d \n\n",destination);
}


