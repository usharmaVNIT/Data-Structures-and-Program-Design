//
//  main.c
//  dspdass3
//
//  Created by Official on 29/05/20.
//  Copyright © 2020 Official. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//************************************************************************************************************

typedef struct t1{
    int destination;
    int weight;
    struct t1 *next;
    int parent;
} AdjListNode;

typedef struct t2{
    AdjListNode *head;
    int distance_from_parent;
} AdjList;

typedef struct{
    int v;
    AdjList *array;
} Graph;

Graph *createGraph(int v){
    Graph *g = (Graph*)malloc(sizeof(Graph));
    g->v = v;
    g->array = (AdjList*)malloc(sizeof(AdjList)*v);
    for(int i=0;i<v;i++){
        g->array[i].head=NULL;
    }
    return g;
}

AdjListNode* addNodeUtil(int destination,int weight){
    AdjListNode *node = (AdjListNode*)malloc(sizeof(AdjListNode));
    node->destination = destination;
    node->weight = weight;
    node->next = NULL;
    return node;
}

void add_Node(Graph *g,int source,int destination,int weight){
    if(source>g->v || destination > g->v){
        printf("Out of Bounds\n");
    }
    else{
        if(g->array[source].head == NULL){
            g->array[source].head = addNodeUtil(destination,weight);
        }
        else{
            AdjListNode *ptr = g->array[source].head;
            AdjListNode *prev = NULL;
            while(ptr!=NULL){
                prev = ptr;
                ptr = ptr->next;
            }
            prev->next=addNodeUtil(destination,weight);
        }
    }
}

AdjList* delNodeUtil(AdjList *list,int source,int destination,int *v){
    AdjListNode *ptr = list[source].head;
    AdjListNode *prev = NULL;
    int found =0;
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
        printf("No Such Node exist That is connected to source\n");
    }
    else if (prev == NULL){
        free(ptr);
        list[source].head = NULL;
        *v = *v -1;
    }
    else{
        prev->next = ptr->next;
        free(ptr);
        *v = *v -1;
    }
    return list;
}

void del_Node(Graph *g,int source,int destination){
    g->array=delNodeUtil(g->array, source, destination,&(g->v));
}

void print_Graph(Graph *g){
    for(int i=0;i<g->v;i++){
        AdjListNode *ptr = g->array[i].head;
        printf("Source is %d",i);
        while(ptr != NULL){
            printf("==> %d",ptr->destination);
            ptr = ptr->next;
        }
        printf("\n");
    }
}

//************************************************************************************************************

typedef struct tag {
    int val;
    struct tag *next;
}Queue_Node;

typedef struct{
    Queue_Node *head,*tail;
} Queue;

void init_Queue(Queue *q){
    q->head = NULL;
    q->tail = NULL;
}

int isEmpty_Queue(Queue *q){
    return q->tail == NULL;
}

void Enqueue(int s,Queue *q){
    Queue_Node *ptr = (Queue_Node*)malloc(sizeof(Queue_Node));
    ptr->val = s;
    ptr->next=NULL;
    if(isEmpty_Queue(q)==1){
        q->tail = q->head = ptr;
    }
    else{
        q->tail->next = ptr;
        q->tail = ptr;
    }
}

int Dequeue(Queue *q){
    int ans=-1;
    if(isEmpty_Queue(q)==0){
        ans = q->head->val;
        Queue_Node *ptr = q->head;
        q->head = q->head->next;
        if(q->head == NULL){
            q->tail = NULL;
        }
        free(ptr);
    }
    return ans;
}

//************************************************************************************************************



//************************************************************************************************************

void BreadthFirstSearch(Graph *g,int source){
    int vertex = g->v;
    int visited[vertex];
    for(int i=0;i<vertex;i++){
        visited[i]=0;
        AdjListNode *ptr = g->array[i].head;
        while(ptr !=NULL){
            ptr->parent=-1;
            ptr = ptr->next;
        }
        g->array[i].distance_from_parent = INT_MAX;
    }
    Queue *q = malloc(sizeof(Queue));
    init_Queue(q);
    Enqueue(source, q);
    visited[source] = 1;
    g->array[source].distance_from_parent = 0;
    while(isEmpty_Queue(q)==0){
        int v = Dequeue(q);
        printf("%d --> ",v);
        AdjListNode *ptr = g->array[v].head;
        while(ptr!=NULL){
            if(visited[ptr->destination]==0){
                visited[ptr->destination]=1;
                ptr->parent = v;
                g->array[ptr->destination].distance_from_parent = g->array[v].distance_from_parent+1;
                Enqueue(ptr->destination, q);
            }
            ptr = ptr->next;
        }
    }
}

// Depth First Search

void DFSUtil(Graph *g,int visited[],int source){
    AdjListNode *ptr = g->array[source].head;
    visited[source] = 1;
    while(ptr!=NULL){
        if(visited[ptr->destination] == 0){
            printf("( %d ",ptr->destination);
            ptr->parent = source;
            DFSUtil(g, visited, ptr->destination);
            printf(" ) ");
        }
        ptr = ptr->next;
    }
    visited[source] = 2;
}

void DepthFirstSearch(Graph *g){
    int ver = g->v;
    int visited[ver];
    for(int i=0;i<ver;i++){
        visited[i]=0;
    }
    for(int i=0;i<ver;i++){
        if(visited[i]==0){
            printf("( %d ",i);
        }
        DFSUtil(g,visited,i);
    }
    printf(" ) ");
}

//************************************************************************************************************

int main(void) {
    Graph *g;
    g = createGraph(6);
    add_Node(g, 0, 1, 0);
    add_Node(g, 0, 2, 0);
    add_Node(g, 0, 3, 0);
    add_Node(g, 0, 4, 0);
    add_Node(g, 1, 2, 0);
    add_Node(g, 1, 4, 0);
    add_Node(g, 1, 5, 0);
    add_Node(g, 2, 3, 0);
    add_Node(g, 2, 1, 0);
    add_Node(g, 2, 2, 0);
    add_Node(g, 3, 4, 0);
    add_Node(g, 4, 5, 0);
    add_Node(g, 5, 1, 0);
    add_Node(g, 5, 4, 0);
    add_Node(g, 5, 3, 0);
    add_Node(g, 5, 5, 0);
    print_Graph(g);
    BreadthFirstSearch(g, 0);
    printf("\n\n\n");
    printf("Distance From 0 of 5 is %d\n",g->array[5].distance_from_parent);
    DepthFirstSearch(g);
    printf("\n\n\n");
    
    
    return 0;
}




//************************************************************************************************************




//************************************************************************************************************




//************************************************************************************************************




//************************************************************************************************************




//************************************************************************************************************
