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
    //iLev is going to be returned through parameter list so it is passed an address
    //to an integer
    //this function does not traverse. All it does is assign a specific semester
    //to a course
    EdgeNode *e;
    iLev = 0;
    for(e = graph->vertexM[iVertex].prereqList; e != NULL;
       e = e->pNextEdge)
    {
        if(!(findPrereq(plan, iLev, iVertex)))
            iLev++;
    }
}
/*************************** findPrereq ***********************************
**************************************************************************/
int findPrereq(Plan plan, int iLev, int iPrereqVertex)
{
    int i;
    for(i = 0; i < 5; i++)
    {
        if(iPrereqVertex == plan->semesterM[iLev][i])
            return TRUE;
    }
    return FALSE;
}
