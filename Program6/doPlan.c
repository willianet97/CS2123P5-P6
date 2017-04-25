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
      setLevel(graph, plan, i, &iLev);
      // need to work on this
      while (plan->semesterM[iLev][5] != -1){ // if iLev is full increment it.
        iLev++;      
      }
        for(i = 0; i < 5; i++) // loof for a space in semester array for the current course
        {
            if(plan->semesterM[iLev][i] == -1) //found it
                plan->semesterM[iLev][i] = iVertex;
        }
     iLev = 0; // set iLev to 0 to pass it to setLev as 0
    }
  }
  //printPlan(graph, plan);//this needs to be added to the print.c file
}
