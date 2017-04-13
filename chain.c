#define CRT SECURE NO WARNINGS 1
//include files
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "cs2123p5.h"
int maxChain(Graph graph, int iVertex)
{
  EdgeNode *e;
  int iCount = 1;
  // traverse to the adjacent vertices
  //goes through successor lists
  for (e = graph->vertexM[iVertex].successorList; e != NULL; 
     e = e->pNextEdge)
  {
    //within successor lists it takes each path
    iCount = 1 + maxChain(graph, e->iSuccVertex);//this almost works except for cs1713 and further courses
  }
  return iCount;
}
/***********************************************************/
/*maxchain is always called before this function
use return of maxchain as iLongLength*/
/*function needs a lot of work just some rudimentary basics jotted down may even be wrong so far*/
void printLongChains(Graph graph, int iVertex, int pathM[], int iLevel, int iLongLength)
{
  if(iVertex < 0) // this condition isn't correct
    return;
  EdgeNode *e;
  int i;
  pathM[iLevel] = iVertex;// this doesn't update for another long chain for some reason, inside the forloop causes segfault
  for (e = graph->vertexM[iVertex].successorList; e!= NULL;
       e = e->pNextEdge)
  {
    printLongChains(graph, graph->vertexM[iVertex].successorList->iSuccVertex, pathM, iLevel+1, iLongLength);
    // we want to be able to overwrite shorter paths 
  }
  if((iLevel+1) == iLongLength)
  {
    printf("\tLongest chains beginning with %s\n", graph->vertexM[pathM[0]].szCourseId); // this will always be 0
    for(i = 0; i < iLevel; i++)
    {
      printf("%-8s", graph->vertexM[pathM[i]].szCourseId);
    }
    printf("%-8s\n", graph->vertexM[pathM[iLevel]].szCourseId);
  }
}
