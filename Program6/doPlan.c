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
      //if(plan->semesterM[iLevel])
          //plan->semesterM[iLevel + 1][0] = i;
    }
  }
  printPlan(graph, plan);
}
