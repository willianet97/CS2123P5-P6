#define CRT SECURE NO WARNINGS 1
//include files
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "cs2123p5.h"
/********************** maxChain **************************
int maxChain(Graph graph, int iVertex)
Purpose:
    Finds the longest chain possible from iVertex course and
    returns it.
Parameters:
    I Graph graph     the graph with info
    I int iVertex     the index of the course
Returns:
    Returns the number of courses in the longest chain possible 
    from iVertex course.
Notes:
    This is a recursive function.
**********************************************************/
int maxChain(Graph graph, int iVertex)
{
  EdgeNode *e;
  int iCount = 0;
  int iFirst = 0;
  // traverse to the adjacent vertices
  //goes through successor lists
  for (e = graph->vertexM[iVertex].successorList; e != NULL; 
     e = e->pNextEdge)
  {
    //within successor lists it takes each path
    iCount = 1 + maxChain(graph, e->iSuccVertex);
    if(iCount > iFirst)
        iFirst = iCount;
  }
  return iFirst;
}
/******************** printLongChains ***************************
void printLongChains(Graph graph, int iVertex, int pathM[],
               int iLevel, int iLongLength)
Purpose:
    Uses the value from maxChain to print out the longest chains 
    starting with the course id.
Parameters:
    I Graph graph      the graph with info
    I int iVertex      the index of the course
    I int pathM[]      
    I int iLevel       
    I int iLongLength  the value from maxChain that is used to 
                       determine which paths to print (longest)
Notes:
    This is a recursive function.
****************************************************************/
void printLongChains(Graph graph, int iVertex, int pathM[], 
               int iLevel, int iLongLength)
{
  if(iVertex < 0) 
    return;

  EdgeNode *e;
  int i;
  pathM[iLevel] = iVertex; // this reads current vertex into pathM
  for (e = graph->vertexM[iVertex].successorList; e!= NULL;
       e = e->pNextEdge)
  {
    printLongChains(graph, e->iSuccVertex, pathM, iLevel+1, iLongLength);
  }
    if((iLevel+1) == iLongLength)
    {
      for(i = 0; i < iLevel; i++)
      {
        // prints course ids
        printf("%-8s", graph->vertexM[pathM[i]].szCourseId);
      }
      // prints final id with a line feed
      printf("%-8s\n", graph->vertexM[pathM[iLevel]].szCourseId);
    }
}
