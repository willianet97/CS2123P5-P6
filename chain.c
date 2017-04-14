#define CRT SECURE NO WARNINGS 1
//include files
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "cs2123p5.h"
int maxChain(Graph graph, int iVertex)
{
  EdgeNode *e;// does this have to be malloced too? i'm suddenly forgetting the nitty gritty details.... no its a local pointer variable
  int iCount = 0;
  int iFirst = 0;
  // traverse to the adjacent vertices
  //goes through successor lists
  for (e = graph->vertexM[iVertex].successorList; e != NULL; 
     e = e->pNextEdge)
  {
    //printf("\t%s %d\n", graph->vertexM[iVertex].szCourseId, iCount);
    //within successor lists it takes each path
    iCount = 1 + maxChain(graph, e->iSuccVertex);
    if(iCount > iFirst)
        iFirst = iCount;
    //printf("\t\t%s %d\n", graph->vertexM[e->iSuccVertex].szCourseId, iCount);
  }
    //printf("\t\t%s %d\n", graph->vertexM[iVertex].szCourseId, iCount);
  return iFirst;
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
  pathM[iLevel] = iVertex;// this reads current vertex into pathM
  for (e = graph->vertexM[iVertex].successorList; e!= NULL;
       e = e->pNextEdge)
  {
    printLongChains(graph, e->iSuccVertex, pathM, iLevel+1, iLongLength);
    // we want to be able to overwrite shorter paths 
    // without permanently increasing iLevel
  }
    if((iLevel+1) == iLongLength)
    {
      for(i = 0; i < iLevel; i++)
      {
        printf("%-8s", graph->vertexM[pathM[i]].szCourseId);
      }
      printf("%-8s\n", graph->vertexM[pathM[iLevel]].szCourseId);
    }
}
