//
//  MST.c
//  DSPD ASS 3
//
//  Created by Official on 07/06/20.
//  Copyright © 2020 Official. All rights reserved.
//

#include "MST.h"
#include <stdio.h>
#include <limits.h>
#include<stdlib.h>
#include "Typedefs.h"


void Init_Edge(Edge *e){
    e->destination = e->source = e->weight = -1;
    e->next = NULL;
}

void init_sorted_edge(Sorted_Edge *e){
    e->head=NULL;
}

Edge* insertAtLastEdge(Edge me,Edge *list){
    Edge *a = (Edge*)malloc(sizeof(Edge));
    a->destination=me.destination;
    a->source=me.source;
    a->weight=me.weight;
    a->next=NULL;
    Edge *ptr = list;
    Edge *prev = NULL;
    while(ptr!=NULL){
        prev = ptr;
        ptr = ptr->next;
    }
    if(prev == NULL){
        list = a;
    }
    else{
        prev->next = a;
    }
    return list;
}


Sorted_Edge* sortGraph(Graph *g){
    Edge minEdge;
    Sorted_Edge *se = (Sorted_Edge*)malloc(sizeof(Sorted_Edge));
    init_sorted_edge(se);
    Init_Edge(&minEdge);
    while(!isEmptyGraph(g)){
        minEdge.weight=INT_MAX;
        for(int i=0;i<g->v;i++){
            AdjListNode *ptr = g->array[i].head;
            while(ptr!=NULL){
                if(ptr->weight<minEdge.weight){
                    minEdge.weight=ptr->weight;
                    minEdge.source = i;
                    minEdge.destination = ptr->destination;
                }
                ptr = ptr->next;
            }
        }
        se->head = insertAtLastEdge(minEdge, se->head);
        del_Edge(g, minEdge.source, minEdge.destination);
    }
    return se;
}

int find(struct subset subsets[], int i)
{

    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
  
    return subsets[i].parent;
}

void Union(struct subset subsets[], int x, int y)
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
  
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    
    else
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

int nos_Edges(Graph *g){
    int e=0;
    for(int i=0;i<g->v;i++){
        AdjListNode *ptr = g->array[i].head;
        while (ptr!=NULL) {
            e++;
            ptr = ptr->next;
        }
    }
    return e;
}

Edge *popEdge(Sorted_Edge *se){
    Edge *ptr = se->head;
    se->head = ptr->next;
    return ptr;
}

void KruskalMST(Graph* graph)
{
    int V = graph->v;
    Edge result[V];
    int e = 0;  // An index variable, used for result[]
    int i = 0;  // An index variable, used for sorted edges
    int E = nos_Edges(graph);
  
    // Step 1:  Sort all the edges in non-decreasing
    // order of their weight. If we are not allowed to
    // change the given graph, we can create a copy of
    // array of edges
    Sorted_Edge *se;
    se = sortGraph(graph);
  
    newSubset *ss = (newSubset*)malloc(V*sizeof(newSubset));
  
    // Create V subsets with single elements
    for (int v = 0; v < V; ++v)
    {
        ss[v].parent = v;
        ss[v].rank = 0;
    }
  
    // Number of edges to be taken is equal to V-1
    while (e < V - 1 && i < E)
    {
        // Step 2: Pick the smallest edge. And increment
        // the index for next iteration
        Edge *next_edge = popEdge(se);
  
        int x = find(ss, next_edge->source);
        int y = find(ss, next_edge->destination);
  
        // If including this edge does't cause cycle,
        // include it in result and increment the index
        // of result for next edge
        if (x != y)
        {
            result[e].destination=next_edge->destination;
            result[e].source=next_edge->source;
            result[e].weight=next_edge->weight;
            e++;
            Union(ss, x, y);
        }
        // Else discard the next_edge
    }
  
    // print the contents of result[] to display the
    // built MST
    printf("Following are the edges in the constructed MST\n");
    for (i = 0; i < e; ++i)
        printf("%d -- %d == %d\n", result[i].source, result[i].destination,
                                                 result[i].weight);
    return;
}


void MinimumSpanningTree(Graph *g){
    if(isConnected(g)){
        KruskalMST(g);
    }
    
}
