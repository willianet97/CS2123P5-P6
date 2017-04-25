#define CRT SECURE NO WARNINGS 1
//include files
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "cs2123p6.h"
/*************************** setLevel *****************************************
******************************************************************************/
void setLevel(Graph graph, Plan plan, int iVertex, int iLevel)
{
    //this function does not traverse. All it does is assign a specific semester
    //to a course
    EdgeNode *e;
    int iPrereqLev = 0;
    for(e = graph->vertexM[iVertex].prereqList; e != NULL;
       e = e->pNextEdge)
    {
        
      iPrereqLev = graph->vertexM[e->iPrereqVertex].iSemesterLevel;
      if(iPrereqLev >= iLevel) 
         iLevel = iPrereqLev + 1; 
    }
    graph->vertexM[iVertex].iSemesterLevel = iLevel;
    printf("Semester level is %d and vertex index is %d\n", iLevel, iVertex);
}
