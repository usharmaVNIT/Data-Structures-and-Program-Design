//
//  Graph_definitions.h
//  DSPD ASS 3
//
//  Created by Official on 30/05/20.
//  Copyright © 2020 Official. All rights reserved.
//

#ifndef Graph_definitions_h
#define Graph_definitions_h

#include <stdio.h>
#include "Typedefs.h"

Graph *createGraph(int v);

AdjListNode* addNodeUtil(int destination,int weight);

void addNode(Graph *g);

void addEdge(Graph *g,int source,int destination,int weight);

void addDirectionalEdge(Graph *g,int source,int destination,int weight);

void addUndirectionalEdge(Graph *g,int v1,int v2,int weight);

AdjList* delEdgeUtil(AdjList *list,int source,int destination);

void del_Edge(Graph *g,int source,int destination);

void print_Graph(Graph *g);

int isConnected(Graph *g);

AdjList* delEdgeUtil2(AdjList *list,int source,int destination);

int isEmptyGraph(Graph *g);


#endif /* Graph_definitions_h */
