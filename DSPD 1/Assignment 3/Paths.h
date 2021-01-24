//
//  Paths.h
//  DSPD ASS 3
//
//  Created by Official on 04/06/20.
//  Copyright © 2020 Official. All rights reserved.
//

#ifndef Paths_h
#define Paths_h

#include <stdio.h>
#include "Graph_definitions.h"

void initialise_single_source(Graph *g,int source);

void Relax(Graph *g,int source,int destination,int weight);

int Bellman_Ford(Graph *g,int source);

void Shortest_path(Graph *g,int source);

void floydWarshall (int *graph[],int V);

void All_Pair_Shortest(Graph *g);

void print_all_pair_shortestPath(Graph *g);

void AllPathUtil(Graph *g,int paths[],int index,int source,int vertex);

void AllPath(Graph *g,int source,int destination);

int detectCyclesUtil(Graph *g,int destination,int visited[]);

int detectCycles(Graph *g);

Graph* deleteNode(Graph *g,int vertex);

#endif /* Paths_h */
