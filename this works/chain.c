#define CRT SECURE NO WARNINGS 1
//include files
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "cs2123p5.h"
int maxChain(Graph graph, int iVertex)
{
  if(iVertex < 0)
    return 0;
  EdgeNode *e;// does this have to be malloced too? i'm suddenly forgetting the nitty gritty details.... no its a local pointer variable
  int iCount = 1;// counts itself too
  // traverse to the adjacent vertices
  //goes through successor lists
  for (e = graph->vertexM[iVertex].successorList; e != NULL; 
     e = e->pNextEdge)
  {
    //within successor lists it takes each path
    iCount = 1 + maxChain(graph, e->iSuccVertex);// this almost works
    //somehow this should be reset
    //but no quite like this because if it has more
    //than one successor it subracts too many
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
  pathM[iLevel] = iVertex;// this reads current vertex into pathM
  for (e = graph->vertexM[iVertex].successorList; e!= NULL;
       e = e->pNextEdge)
  {
    printLongChains(graph, graph->vertexM[iVertex].successorList->iSuccVertex, pathM, iLevel+1, iLongLength);
    // we want to be able to overwrite shorter paths 
    // without permanently increasing iLevel
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
}
