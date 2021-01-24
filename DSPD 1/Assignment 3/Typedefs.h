//
//  Typedefs.h
//  DSPD ASS 3
//
//  Created by Official on 02/06/20.
//  Copyright © 2020 Official. All rights reserved.
//

#ifndef Typedefs_h
#define Typedefs_h





//Graphs

typedef struct t1{
    int destination;
    int weight;
    struct t1 *next;
} AdjListNode;

typedef struct t2{
    AdjListNode *head;
    int parent;
    int distance_from_source;
} AdjList;

typedef struct{
    int v;
    AdjList *array;
} Graph;



//Queue

typedef struct tag {
    int val;
    struct tag *next;
}Queue_Node;

typedef struct{
    Queue_Node *head,*tail;
} Queue;


//Topological
typedef struct topotag{
    int d;
    struct topotag *nxt;
} Topo_tag;

// MST
typedef struct edge {
    int source,destination,weight;
    struct edge *next;
}Edge;

typedef struct soE{
    Edge *head;
}Sorted_Edge;


typedef struct subset
{
    int parent;
    int rank;
}newSubset;

#endif /* Typedefs_h */
