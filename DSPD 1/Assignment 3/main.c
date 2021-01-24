//
//  main.c
//  DSPD ASS 3
//
//  Created by Official on 30/05/20.
//  Copyright © 2020 Official. All rights reserved.
//

#include <stdio.h>
#include "Graph_definitions.h"
#include "Transversals.h"
#include "Paths.h"
#include "MST.h"

int main(void) {
    printf("\n\n ************************************************************************************************\n\n");
    Graph *g;
    printf(" \n Creating Graph G1  :- \n");
    g = createGraph(6);
    
    addUndirectionalEdge(g, 0, 1, 0);
    addUndirectionalEdge(g, 1, 2, 0);
    addUndirectionalEdge(g, 2, 3, 0);
    addUndirectionalEdge(g, 3, 4, 0);
    addUndirectionalEdge(g, 4, 5, 0);
    print_Graph(g);
    //*********************************************************************************
    Graph *g2 = createGraph(6);
    printf(" \n Creating Graph G2  :- \n ");
    addDirectionalEdge(g2, 0, 1, 1);
    addDirectionalEdge(g2, 1, 2, 2);
    addDirectionalEdge(g2, 2, 3, 3);
    addDirectionalEdge(g2, 3, 4, 4);
    addDirectionalEdge(g2, 4, 5, 5);
    addDirectionalEdge(g2, 0, 5, 3);
    print_Graph(g2);
    //*********************************************************************************
    Graph *g3 = createGraph(6);
    printf(" \n Creating Graph G3  :- \n ");
    addDirectionalEdge(g3, 0, 1, 1);
    addDirectionalEdge(g3, 1, 2, 2);
    addDirectionalEdge(g3, 2, 3, 3);
    addDirectionalEdge(g3, 3, 4, 4);
    addDirectionalEdge(g3, 4, 5, 5);
    addDirectionalEdge(g3, 0, 5, 3);
    addDirectionalEdge(g3, 5, 0, 3);
    print_Graph(g3);
    
    //*********************************************************************************
    Graph *g4 = createGraph(6);
    printf(" \n Creating Graph G4  :- \n ");
    addDirectionalEdge(g4, 1, 2, 0);
    addDirectionalEdge(g4, 1, 4, 0);
    addDirectionalEdge(g4, 1, 3, 0);
    addDirectionalEdge(g4, 2, 3, 0);
    addDirectionalEdge(g4, 4, 3, 0);
    addDirectionalEdge(g4, 4, 5, 0);
    addDirectionalEdge(g4, 5, 3, 0);
    addDirectionalEdge(g4, 4, 2, 0);
    addDirectionalEdge(g4, 2, 5, 0);
    addDirectionalEdge(g4, 5, 4, 0);
    addDirectionalEdge(g4, 2, 4, 0);
    print_Graph(g4);
    
    
    //*********************************************************************************
    Graph *g5 = createGraph(6);
    printf(" \n Creating Graph G5  :- \n ");
    addDirectionalEdge(g5, 1, 2, 0);
    addDirectionalEdge(g5, 2, 3, 0);
    addDirectionalEdge(g5, 1, 3, 0);
    addDirectionalEdge(g5, 1, 4, 0);
    addDirectionalEdge(g5, 2, 5, 0);
    addDirectionalEdge(g5, 4, 3, 0);
    addDirectionalEdge(g5, 4, 5, 0);
    addDirectionalEdge(g5, 4, 2, 0);
    addDirectionalEdge(g5, 4, 2, 0);
    addDirectionalEdge(g5, 4, 2, 0);
    addDirectionalEdge(g5, 5, 3, 0);
    addDirectionalEdge(g5, 5, 4, 0);
    print_Graph(g5);
    
    
    //*********************************************************************************
    printf("\n\n ************************************************************************************************\n\n");
    
    
    printf("\n**** BREADTH FIRST TRANSVERSAL ON G1 (with source vertex 0)****\n\n");
    BreadthFirstTransversal(g, 0);
    printf("\n**** DEPTH FIRST TRAVERSAL NO G1 ****\n\n");
    DepthFirstTransversal(g);
    printf("\n**** Topological Sort On G1 ****\n\n");
    Topological_Sort(g);
    //*********************************************************************************
    printf("\n**** BREADTH FIRST TRANSVERSAL ON G2 (with source vertex 0)****\n\n");
    BreadthFirstTransversal(g2, 0);
    printf("\n**** DEPTH FIRST TRAVERSAL NO G2 ****\n\n");
    DepthFirstTransversal(g2);
    printf("\n**** Topological Sort On G2 ****\n\n");
    Topological_Sort(g2);
    
    //*********************************************************************************
    printf("\n**** BREADTH FIRST TRANSVERSAL ON G3 (with source vertex 1)****\n\n");
    BreadthFirstTransversal(g3, 1);
    printf("\n**** DEPTH FIRST TRAVERSAL NO G3 ****\n\n");
    DepthFirstTransversal(g3);
    printf("\n**** Topological Sort On G3 ****\n\n");
    Topological_Sort(g3);
    
    //*********************************************************************************
    printf("\n**** BREADTH FIRST TRANSVERSAL ON G4 (with source vertex 1)****\n\n");
    BreadthFirstTransversal(g4, 1);
    printf("\n**** DEPTH FIRST TRAVERSAL NO G4 ****\n\n");
    DepthFirstTransversal(g4);
    printf("\n**** Topological Sort On G4 ****\n\n");
    Topological_Sort(g4);
    
    //*********************************************************************************
    printf("\n**** BREADTH FIRST TRANSVERSAL ON G5 (with source vertex 1)****\n\n");
    BreadthFirstTransversal(g5, 1);
    printf("\n**** DEPTH FIRST TRAVERSAL NO G5 ****\n\n");
    DepthFirstTransversal(g5);
    printf("\n**** Topological Sort On G5 ****\n\n");
    Topological_Sort(g5);
    
    //*********************************************************************************
    
    printf("\n\n ************************************************************************************************\n\n");
    
    
    printf("\n** Checking wheather Graph 1 is connected or not **\n\n");
    isConnected(g);
    printf("\n** Checking wheather Graph 2 is connected or not **\n\n");
    isConnected(g2);
    printf("\n** Checking wheather Graph 3 is connected or not **\n\n");
    isConnected(g3);
    printf("\n** Checking wheather Graph 4 is connected or not **\n\n");
    isConnected(g4);
    printf("\n** Checking wheather Graph 5 is connected or not **\n\n");
    isConnected(g5);
    
    //*********************************************************************************
    
    printf("\n\n ************************************************************************************************\n\n");
    
    
    printf("\n** Shortest Path From Vertex 0 to all other vertices in Graph G1 **\n");
    Shortest_path(g, 0);
    printf("\n** Shortest Path From Vertex 0 to all other vertices in Graph G2 **\n");
    Shortest_path(g2, 0);
    printf("\n** Shortest Path From Vertex 0 to all other vertices in Graph G3 **\n");
    Shortest_path(g3, 0);
    printf("\n** Shortest Path From Vertex 0 to all other vertices in Graph G4 **\n");
    Shortest_path(g4, 0);
    printf("\n** Shortest Path From Vertex 0 to all other vertices in Graph G5 **\n");
    Shortest_path(g5, 0);
    //*********************************************************************************
    
    printf("\n\n ************************************************************************************************\n\n");
    
    printf("\n** Shortest Path b/w all vertices of Graph G1 **\n");
    All_Pair_Shortest(g);
    print_all_pair_shortestPath(g);
    printf("\n** Shortest Path b/w all vertices of Graph G2 **\n");
    All_Pair_Shortest(g2);
    print_all_pair_shortestPath(g2);
    printf("\n** Shortest Path b/w all vertices of Graph G3 **\n");
    All_Pair_Shortest(g3);
    print_all_pair_shortestPath(g3);
    printf("\n** Shortest Path b/w all vertices of Graph G4 **\n");
    All_Pair_Shortest(g4);
    print_all_pair_shortestPath(g4);
    printf("\n** Shortest Path b/w all vertices of Graph G5 **\n");
    All_Pair_Shortest(g5);
    print_all_pair_shortestPath(g5);
    
    //*********************************************************************************
    
    printf("\n\n ************************************************************************************************\n\n");
    
    printf("\n*** Searching A value via BFS in Graph G1 with destination 4 ***\n");
    BreadthFirsSearch(g, 4);
    printf("\n*** Searching A value via DFS in Graph G1 with destination 2 ***\n");
    DepthFirstSearch(g, 2);
    printf("\n*** Searching A value via BFS in Graph G2 with destination 5 ***\n");
    BreadthFirsSearch(g2, 5);
    printf("\n*** Searching A value via DFS in Graph G2 with destination 5 ***\n");
    DepthFirstSearch(g2, 5);
    printf("\n*** Searching A value via BFS in Graph G3 with destination 2 ***\n");
    BreadthFirsSearch(g3, 2);
    printf("\n*** Searching A value via DFS in Graph G3 with destination 2 ***\n");
    DepthFirstSearch(g3, 2);
    printf("\n*** Searching A value via BFS in Graph G4 with destination 4 ***\n");
    BreadthFirsSearch(g4, 4);
    printf("\n*** Searching A value via DFS in Graph G4 with destination 4 ***\n");
    DepthFirstSearch(g4, 4);
    printf("\n*** Searching A value via BFS in Graph G5 with destination 4 ***\n");
    BreadthFirsSearch(g5, 4);
    printf("\n*** Searching A value via DFS in Graph G5 with destination 2 ***\n");
    DepthFirstSearch(g5, 2);
    
    //*********************************************************************************
    
    printf("\n\n ************************************************************************************************\n\n");
    
    printf("\n*** Detecting a cycle on graph G1 ***\n");
    if(detectCycles(g)){
        printf("Yes\n");
    }
    else{
        printf("No\n");
    }
    print_Graph(g);
    
    printf("\n*** Detecting a cycle on graph G2 ***\n");
    if(detectCycles(g2)){
        printf("Yes\n");
    }
    else{
        printf("No\n");
    }
    print_Graph(g2);
    
    printf("\n*** Detecting a cycle on graph G3 ***\n");
    if(detectCycles(g3)){
        printf("Yes\n");
    }
    else{
        printf("No\n");
    }
    print_Graph(g3);
    
    printf("\n*** Detecting a cycle on graph G4 ***\n");
    if(detectCycles(g4)){
        printf("Yes\n");
    }
    else{
        printf("No\n");
    }
    print_Graph(g4);
    
    printf("\n*** Detecting a cycle on graph G5 ***\n");
    if(detectCycles(g5)){
        printf("Yes\n");
    }
    else{
        printf("No\n");
    }
    print_Graph(g5);
        
    //*********************************************************************************
    
    printf("\n\n ************************************************************************************************\n\n");
    
    Graph *g1f;
    g1f = createGraph(6);
    
    addUndirectionalEdge(g1f, 0, 1, 0);
    addUndirectionalEdge(g1f, 1, 2, 0);
    addUndirectionalEdge(g1f, 2, 3, 0);
    addUndirectionalEdge(g1f, 3, 4, 0);
    addUndirectionalEdge(g1f, 4, 5, 0);
    Graph *g2f = createGraph(6);
    addDirectionalEdge(g2f, 0, 1, 1);
    addDirectionalEdge(g2f, 1, 2, 2);
    addDirectionalEdge(g2f, 2, 3, 3);
    addDirectionalEdge(g2f, 3, 4, 4);
    addDirectionalEdge(g2f, 4, 5, 5);
    addDirectionalEdge(g2f, 0, 5, 3);
    Graph *g3f = createGraph(6);
    addDirectionalEdge(g3f, 0, 1, 1);
    addDirectionalEdge(g3f, 1, 2, 2);
    addDirectionalEdge(g3f, 2, 3, 3);
    addDirectionalEdge(g3f, 3, 4, 4);
    addDirectionalEdge(g3f, 4, 5, 5);
    addDirectionalEdge(g3f, 0, 5, 3);
    addDirectionalEdge(g3f, 5, 0, 3);
    printf("\n **** Minimum Spanning Tree Of Graph G1 *****\n");
    MinimumSpanningTree(g1f);
    printf("\n **** Minimum Spanning Tree Of Graph G3 *****\n");
    MinimumSpanningTree(g3f);
    printf("\n **** Minimum Spanning Tree Of Graph G2 *****\n");
    MinimumSpanningTree(g2f);
    
    //*********************************************************************************
    
    printf("\n\n ************************************************************************************************\n\n");
    
    printf("\n*** All possibke Paths b/w vertex 1 and 4 in Graph G1 *** \n\n");
    AllPath(g, 1, 4);
    printf("\n*** All possibke Paths b/w vertex 2 and 4 in Graph G2 *** \n\n");
    AllPath(g2, 2, 4);
    printf("\n*** All possibke Paths b/w vertex 5 and 1 in Graph G3 *** \n\n");
    AllPath(g3, 5, 1);
    printf("\n*** All possibke Paths b/w vertex 1 and 5 in Graph G4 *** \n\n");
    AllPath(g4, 1, 3);
    printf("\n*** All possibke Paths b/w vertex 2 and 5 in Graph G5 *** \n\n");
    AllPath(g5, 2, 5);
    
    //*********************************************************************************
    
    printf("\n\n ************************************************************************************************\n\n");
    
    printf("\n ***Now to delete the node (it contains delete edge inside) ***\n\n\n");
    printf("It will delete all edges corresponding to that node\n");
    printf("We will delete node 2 from Graph G5\n");
    printf("Before Deleting :- \n");
    print_Graph(g5);
    printf("After Deleting :- \n");
    g5 = deleteNode(g5, 2);
    printf("After deleting nodes like 3 becomes 2 i.e n becomes n-1 from 3 onwards\n");
    printf("\nNow Adding A Node in G5\n\n");
    addNode(g5);
    print_Graph(g5);
    printf("Adding Edge B/w 5 and 1\n\n");
    addDirectionalEdge(g5, 5, 1, 0);
    print_Graph(g5);
    
    return 0;
}


