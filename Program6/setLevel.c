#define CRT SECURE NO WARNINGS 1
//include files
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "cs2123p6.h"
/*************************** setLevel *****************************************
******************************************************************************/
void setLevel(Graph graph, Plan plan, int iVertex, int iLev)
{
    //this function does not traverse. All it does is assign a specific semester
    //to a course
    EdgeNode *e;
    // int iPrereqLev = 0;
    for(e = graph->vertexM[iVertex].prereqList; e != NULL;
       e = e->pNextEdge)
    {
        if((!findPrereq(plan, iLev, e->iPrereqVertex)))
            iLevel = vertexM[e->iPrereqVertex].iSemesterLevel + 1; 
        
      //iPrereqLev = graph->vertexM[e->iPrereqVertex].iSemesterLevel;
      //if(iPrereqLev >= iLevel) 
      //   iLevel = iPrereqLev + 1; 
    }
    graph->vertexM[iVertex].iSemesterLevel = iLev;
    printf("Semester level is %d and vertex index is %d", iLev, iVertex);
}
/*************************** findPrereq ***********************************
**************************************************************************/
int findPrereq(Plan plan, int iLev, int iPrereqVertex)
{
    int i;
    for(i = 0; i < 5; i++)
    {
        //searchs the semester plan for the iPrereqVertex of the current edgenode
        //this compares to see if the course has already been put into a previous semester
        //if it has been then it returns true
        //if it hasn't been then it returns false
        if(iPrereqVertex == plan->semesterM[iLev][i])
            return TRUE;
    }
    return FALSE;
}
