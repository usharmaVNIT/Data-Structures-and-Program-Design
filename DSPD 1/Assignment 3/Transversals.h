//
//  Transversals.h
//  DSPD ASS 3
//
//  Created by Official on 30/05/20.
//  Copyright © 2020 Official. All rights reserved.
//

#ifndef Transversals_h
#define Transversals_h

#include <stdio.h>
#include "Graph_definitions.h"
#include "Typedefs.h"


void BreadthFirstTransversal(Graph *g,int source);

void DFTUtil(Graph *g,int visited[],int source);

void DepthFirstTransversal(Graph *g);

Topo_tag* insert_at_start(Topo_tag *t,int d);

void Topological_Sort_Util(Graph *g);

Topo_tag* Topo_Util(Graph *g,int source,int visited[],Topo_tag *ta);

void Topological_Sort(Graph *g);

void BFT_for_Connected(Graph *g,int source);

void BreadthFirsSearch(Graph *g,int destination);

void DepthFirstSearch(Graph *g,int destination);


#endif /* Transversals_h */
