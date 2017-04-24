#define CRT SECURE NO WARNINGS 1
//include files
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "cs2123p6.h"

/******************* deleteCourse **********************
void deleteCourse(Graph graph, int iVertex)
Purpose:
    This will delete a course. Additional notes below.
Parameters:
    I/O Graph graph    graph with info on courses
    I int iVertex      the index of the course vertex
Notes:
This course will not be associated with any successors, 
meaning any successors will no longer have it as a prereq.
.....................................................
This course will not be associated with any prereqs, 
meaning no prereqs will have this course as a successor.
.....................................................
Frees all edge nodes which reference this vertex.
.....................................................
The course is marked deleted in the vertex array. 
.....................................................
EXTRA CREDIT: it is also removed from an overflow chain 
if it is in the overflow area.
********************************************************/
void deleteCourse(Graph graph, int iVertex)
{
    int i;
    int iCount;
    EdgeNode *e;
    EdgeNode *eCurrent;
    EdgeNode *ePrev;
    for (i = 0; i < graph->iNumVertices; i++)
    {
        iCount = 0;
        for (e = graph->vertexM[i].prereqList; e != NULL; e = e->pNextEdge)
        {
            if (e->iPrereqVertex == iVertex && iCount == 0)
            {
                e->pNextEdge = eCurrent;
                graph->vertexM[i].prereqList = eCurrent;
                free(e);
            }
            else if (e->iPrereqVertex == iVertex && iCount > 0)
            {
                ePrev->pNextEdge = e->pNextEdge;
                free(e);
            }
            ePrev = e;
            iCount++;
         }
         for (e = graph->vertexM[i].successorList; e != NULL; e = e->pNextEdge)
         {
             if (e->iSuccVertex == iVertex && iCount == 0)
             {
                e->pNextEdge = eCurrent;
                graph->vertexM[i].successorList = eCurrent;
                free(e);
             }
             else if (e->iSuccVertex == iVertex && iCount > 0)
             {
                ePrev->pNextEdge = e->pNextEdge;
                free(e);
             }
             ePrev = e;
             iCount++;
         }
     }
     graph->vertexM[iVertex].bExists = FALSE;
}
               
  







}
