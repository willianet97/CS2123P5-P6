#define CRT SECURE NO WARNINGS 1
//include files
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "cs2123p5.h"

/***************************** causesCycle ********************************
int causesCycle(Graph graph, int iPrereqVertex, int iVertex)
Purpose:
    Checks to see if an insertion causes a cycle and returns a boolean
    accordingly.
Parameters:
    I Graph graph         the graph containing info on the vertices
    I int iPrereqVertex   the index of the prereq vertex
    I int iVertex         the index of the current vertex
Returns:
    Returns TRUE if the insertion of an edge containing the course and its
    prereq would cause a cycle.
    Otherwise, returns FALSE.
Notes:
    This is used by the PREREQ command to check if whether the insertion of
    a prereq would cause a cycle prior to actually inserting that prereq.
***************************************************************************/
int causesCycle(Graph graph, int iPrereqVertex, int iVertex)
{
  if(iVertex == iPrereqVertex)
     return TRUE;
  EdgeNode *e; // EdgeNode for traversal
  for (e = graph->vertexM[iVertex].successorList; e != NULL; e = e->pNextEdge)
  { 
      if(causesCycle(graph, iPrereqVertex,  e->iSuccVertex)) // e->iPrereqVertex is not correct but for now it prevents segfaults
         return TRUE;
  }
  
  return FALSE;
}   

/***************************** insertPrereq ********************************
int insertPrereq(Graph graph, int iPrereqVertex, int iCourseVertex)
Purpose:
    Inserts the Edgenodwith the PreReqVertex and iSuccVertex to the lists of Nodes of each course. 
Parameters:
    I Graph graph         the graph containing info on the vertices
    I int iPrereqVertex   the index of the prereq vertex
    I int iCourseVertex   the index of the course
Notes:
    This is used by the PREREQ command.
***************************************************************************/

void insertPrereq(Graph graph, int iPrereqVertex, int iCourseVertex)
{
    EdgeNode *eNew = allocateEdgeNode();    //new node to be inserted
    EdgeNode *eNew2 = allocateEdgeNode();
    EdgeNode *eCurrent;     //pointer to the current head of the list
    
    eNew->iPrereqVertex = iPrereqVertex;
    eNew->iSuccVertex = iCourseVertex;
    eNew2->iPrereqVertex = iPrereqVertex;
    eNew2->iSuccVertex = iCourseVertex;
    
    //set the courseVertex prereqlist vertex to the ones passed
    if (graph->vertexM[iCourseVertex].prereqList == NULL)// check if prereqList list already had Edges
    {
        graph->vertexM[iCourseVertex].prereqList = eNew;
        eNew->pNextEdge = NULL;
    }
    else
    {
        //set eCurrent to head of list
        eCurrent = graph->vertexM[iCourseVertex].prereqList;
        //set eNew next edge to the current head
        eNew->pNextEdge = eCurrent;
        //make eNew the current head
        graph->vertexM[iCourseVertex].prereqList = eNew;
        //set eCurrents next edge to NULL
    }
    //set the prereqVertex successorlist vertex to the ones passed
    if (graph->vertexM[iPrereqVertex].successorList == NULL) // check if successor list already had Edges
    {
        graph->vertexM[iPrereqVertex].successorList = eNew2;
        eNew2->pNextEdge = NULL;
    }
    else
    {
        //set eCurrent to point to head of list
        eCurrent = graph->vertexM[iPrereqVertex].successorList;
        //set eNew next edge to current head
        eNew2->pNextEdge = eCurrent;
        //make eNew the new head
        graph->vertexM[iPrereqVertex].successorList = eNew2;
        //set eCurrent next edge to NULL
    }
}
/************************** newGraph ********************************
Graph newGraph()
Purpose:
    Creates a new graph.
Parameters:
    n/a
Returns:
    The new graph.
Notes:
    n/a
**************************************************************************/
Graph newGraph()
{
   // allocate memory for graph
   Graph g = (Graph)malloc(sizeof(GraphImp));
   
   // check if memory is available
   if(g == NULL)
     ErrExit(ERR_ALGORITHM, "No available memory for graph");
  
   // mark the graph as empty
   g->iNumVertices = 0;
  
   // initialize the values of the vertex array to -1
   memset(g->vertexM, -1, MAX_VERTICES);
  
   return g;
}
/************************** allocateEdgeNode ********************************
EdgeNode *allocateEdgeNode(int iPrereqVertex, int iSuccVertex)
Purpose:
    Allocates a new edge node.
Parameters:
    n/a
Returns:
    A pointer to the new edge node.
Notes:
    n/a
**************************************************************************/
EdgeNode * allocateEdgeNode()
{
  // allocate memory for an edge node
  EdgeNode *eNew;
  
  eNew = (EdgeNode *) malloc(sizeof(EdgeNode));
  
  // check if memory is available
  if(eNew == NULL)
    ErrExit(ERR_ALGORITHM, "No available memory for edge node");
  
  // make this node's next edge NULL
  eNew->pNextEdge = NULL;
  
  // assign empty values
  eNew->iPrereqVertex = -1;
  eNew->iSuccVertex = -1;
   
  return eNew;
}
