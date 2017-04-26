#define CRT SECURE NO WARNINGS 1
//include files
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "cs2123p6.h"
/*************************** setLevel *****************************************
void setLevel(Graph graph, Plan plan, int iVertex, int iLevel)
Purpose:
    Sets the vertex's semester level based on where that course should be taken 
    earliest.  
Parameters:
    I Graph graph     graph with course info
    I Plan plan       plan for semester info
    I int iVertex     the index of the vertex to set level for
    I int iLevel      numeric level of the semester
Notes:
    Prior to setting this value and prior to calling setLevel, 
    you probably want to determine the distance from the source for this vertex.
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
    
    // error checking
    printf("Semester #%d | Vertex Index = %d | %s  %s\n", iLevel+1, iVertex
            , graph->vertexM[iVertex].szCourseId
            , graph->vertexM[iVertex].szCourseName);
}
