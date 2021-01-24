//
//  MST.h
//  DSPD ASS 3
//
//  Created by Official on 07/06/20.
//  Copyright © 2020 Official. All rights reserved.
//

#ifndef MST_h
#define MST_h

#include <stdio.h>
#include "Graph_definitions.h"
#include "Typedefs.h"

void Init_Edge(Edge *e);

void init_sorted_edge(Sorted_Edge *e);

Edge* insertAtLastEdge(Edge me,Edge *list);

Sorted_Edge* sortGraph(Graph *g);

int find(struct subset subsets[], int i);

void Union(struct subset subsets[], int x, int y);

int nos_Edges(Graph *g);

Edge *popEdge(Sorted_Edge *se);

void KruskalMST(Graph* graph);

void MinimumSpanningTree(Graph *g);

#endif /* MST_h */
