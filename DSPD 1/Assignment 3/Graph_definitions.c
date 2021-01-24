//
//  Graph_definitions.c
//  DSPD ASS 3
//
//  Created by Official on 30/05/20.
//  Copyright © 2020 Official. All rights reserved.
//

#include "Graph_definitions.h"
#include <stdio.h>
#include<stdlib.h>
#include "Transversals.h"
#include "limits.h"

Graph *createGraph(int v){
    Graph *g = (Graph*)malloc(sizeof(Graph));
    g->v = v;
    g->array = (AdjList*)malloc(sizeof(AdjList)*v);
    for(int i=0;i<v;i++){
        g->array[i].head=NULL;
    }
    return g;
}

void addNode(Graph *g){
    g->v = g->v+1;
    AdjList *newList = (AdjList*)malloc(sizeof(AdjList)*(g->v));
    for(int i = 0;i<g->v-1;i++){
        newList[i].head = g->array[i].head;
        newList[i].distance_from_source = g->array->distance_from_source;
        newList[i].parent = g->array[i].parent;
    }
    newList[g->v-1].head = NULL;
    AdjList *ptr = g->array;
    g->array = newList;
    free(ptr);

}


AdjListNode* addEdgeUtil(int destination,int weight){
    AdjListNode *node = (AdjListNode*)malloc(sizeof(AdjListNode));
    node->destination = destination;
    node->weight = weight;
    node->next = NULL;
    return node;
}

void addEdge(Graph *g,int source,int destination,int weight){
    if(source>g->v || destination > g->v){
        printf("Out of Bounds\n");
    }
    else{
        if(g->array[source].head == NULL){
            g->array[source].head = addEdgeUtil(destination,weight);
        }
        else{
            AdjListNode *ptr = g->array[source].head;
            AdjListNode *prev = NULL;
            while(ptr!=NULL){
                prev = ptr;
                ptr = ptr->next;
            }
            prev->next=addEdgeUtil(destination,weight);
        }
    }
}


void addDirectionalEdge(Graph *g,int source,int destination,int weight){
    addEdge(g, source, destination, weight);
}

void addUndirectionalEdge(Graph *g,int v1,int v2,int weight){
    addEdge(g, v1, v2, weight);
    addEdge(g, v2, v1, weight);
}

AdjList* delEdgeUtil(AdjList *list,int source,int destination){
    AdjListNode *ptr = list[source].head;
    AdjListNode *prev = NULL;
    int found =0;
    while(ptr!=NULL && !found){
        if(ptr->destination == destination){
            printf("found %d",ptr->destination);
            found = 1;
        }
        else{
            prev = ptr;
            ptr = ptr->next;
        }
    }
    if(ptr == NULL){
        printf("No Such Node exist That is connected to source\n");
    }
    else if (prev == NULL){
        printf(" and deleted\n");
        list[source].head = ptr->next;
        free(ptr);
    }
    else{
        prev->next = ptr->next;
        free(ptr);
        printf(" and deleted\n");
    }
    ptr = list[source].head;
    return list;
}

void del_Edge(Graph *g,int source,int destination){
    g->array=delEdgeUtil(g->array, source, destination);
}

void print_Graph(Graph *g){
    for(int i=0;i<g->v;i++){
        AdjListNode *ptr = g->array[i].head;
        printf("Source is %d",i);
        while(ptr != NULL){
            printf(" ==> %d",ptr->destination);
            ptr = ptr->next;
        }
        printf("\n");
    }
}

AdjList* delEdgeUtil2(AdjList *list,int source,int destination){
    int found =1;
    while(found){
        found = 0;
        AdjListNode *ptr = list[source].head;
        AdjListNode *prev = NULL;
        while(ptr!=NULL && !found){
            if(ptr->destination == destination){
                found = 1;
            }
            else{
                prev = ptr;
                ptr = ptr->next;
            }
        }
        if(ptr == NULL){
        }
        else if (prev == NULL){
            list[source].head = ptr->next;
            free(ptr);
        }
        else{
            prev->next = ptr->next;
            free(ptr);
        }
        ptr = list[source].head;
        
    }
    return list;
}

void delEdgeForNode(Graph *g,int source,int destination){
    g->array = delEdgeUtil2(g->array, source, destination);
}

int isConnected(Graph *g){
    for (int i=0; i<g->v; i++) {
        BFT_for_Connected(g, i);
        for(int j = 0;j<g->v;j++){
            if(g->array[j].distance_from_source == INT_MAX){
                printf("The Graph Is Not Connected As Their is No Path b/w %d and %d \n",i,j);
                return 0;
            }
        }
    }
    printf("The Graph Is Connected and path b/w all pairs exists\n\n");
    return 1;
}

Graph* deleteNode(Graph *g,int vertex){
    for(int i=0;i<g->v;i++){
        delEdgeForNode(g, i, vertex);
    }
    
    for(int i=0;i<g->v;i++){
        AdjListNode *ptr = g->array[i].head;
        while(ptr!=NULL){
            if(ptr->destination>vertex){
                ptr->destination = ptr->destination-1;
            }
            ptr = ptr->next;
        }
    }
    AdjListNode *ptr = g->array[vertex].head;
    AdjListNode *prev = NULL;
    while(ptr!=NULL){
        prev = ptr;
        ptr = ptr->next;
        free(prev);
    }
    Graph *tmpg = createGraph(g->v-1);
    for(int i=0;i<vertex;i++){
        tmpg->array[i].head=g->array[i].head;
    }
    for(int i=vertex;i<g->v-1;i++){
        tmpg->array[i].head = g->array[i+1].head;
    }
    free(g);
    print_Graph(tmpg);
    return tmpg;
}

int isEmptyGraph(Graph *g){
    for(int i=0;i<g->v;i++){
        if(g->array[i].head!=NULL){
            return 0;
        }
    }
    return 1;
}
