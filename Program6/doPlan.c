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
  int iLevel = 0;
  for(i = 0; i < MAX_VERTICES; i++)
  {
    if(plan->bIncludeM[i] == TRUE){
      setLevel(graph, plan, i, 0);
      // need to work on this
      iLevel = graph->vertexM[iVertex].iSemesterLevel;
      while (plan->semesterM[iLevel][5] != -1){ // if iLev is full increment it.
        iLevel = graph->vertexM[iVertex].iSemesterLevel + 1;      
      }
        for(i = 0; i < 5; i++) // loof for a space in semester array for the current course
        {
            if(plan->semesterM[iLevel][i] == -1) //found it
                plan->semesterM[iLevel][i] = iVertex;
        }
    }
  }
  //printPlan(graph, plan);//this needs to be added to the print.c file
}
