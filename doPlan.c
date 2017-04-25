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
  int iLev = 0;
  for(i = 0; i < MAX_VERTICES; i++)
  {
    if(plan->bIncludeM[i] == TRUE){
      setLevel(graph, plan, i, iLev);
      plan->semesterM[iLev][i]; // insert Vertex to Semester array in corresponding iLevel, which was returned by setLevel;
    }
  }
  printPlan(graph, plan);//this needs to be added to the print.c file
}
