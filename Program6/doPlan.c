#define CRT SECURE NO WARNINGS 1
//include files
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "cs2123p6.h"
/**************************** doPlan *************************************

*************************************************************************/
void doPlan(Graph graph, Plan plan)
{
  //within the set level function it just returns the level that course
  //goes based on
  //read bIncludes
  int i;
  int j;
  int iLevel = 0;
  int isFullM[5];
  for(i = 0; i < MAX_VERTICES; i++)
  {
    if(plan->bIncludeM[i] == TRUE)
    {
      setLevel(graph, plan, i, 0);
      // need to work on this
      iLevel = graph->vertexM[i].iSemesterLevel;
      if(isFullM[iLevel] == TRUE) // if iLev is full increment it.
      {
        iLevel++;
      }
      for(j = 0; j < 5; j++) // look for a space in semester array for the current course
      {
            if(plan->semesterM[iLevel][j] == -1) //found it
            {
               plan->semesterM[iLevel][j] = i;
               break;
            }
            if(j == 4 && plan->semesterM[iLevel][j] != -1)
                isFullM[iLevel] = TRUE;
      }
      if(isFullM[iLevel] == TRUE)
      {
          for(j = 0; j < 5; j++)
          {
              if(plan->semesterM[iLevel + 1][j] == -1)
              {
                 plan->semesterM[iLevel + 1][j] = i;
                 break;
              }
          }
      }
    }
  }
  printPlan(graph, plan);
}
/**************************** DistSource **************************************

******************************************************************************/
int DistSource(Graph graph, int iVertex)
{
    EdgeNode *e;
    int iCount = 0;
    int iFirst = 0;
    // traverse to the adjacent vertices
    //goes through successor lists
    for (e = graph->vertexM[iVertex].prereqList; e != NULL; 
        e = e->pNextEdge)
    {
        //within successor lists it takes each path
        iCount = 1 + DistSource(graph, e->iPrereqVertex);
        if(iCount > iFirst)
            iFirst = iCount;
    }
    return iFirst;
}
