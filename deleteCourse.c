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
    EdgeNode *e;
    EdgeNode *e2;
    EdgeNode *eCurrent;
    EdgeNode *eCurrent2;
    EdgeNode *ePrev;
    EdgeNode *ePrev2;
    for (i = 0; i < graph->iNumVertices; i++)
    {
        ePrev = NULL;
        ePrev2 = NULL;
        for (e = graph->vertexM[i].prereqList; e != NULL; e = e->pNextEdge)//the segfault is caused somewhere in here
        {
            if (e->iPrereqVertex == iVertex)
            {
                if (ePrev == NULL)//if it is at the head of the list
                {
                    graph->vertexM[i].prereqList = e->pNextEdge;
                    free(e);
                }
                else//if it is in the middle
                {
                    ePrev->pNextEdge = e->pNextEdge;;//i think this is the issue because its trying to read something null
                    break;
                    
                }
            }
                ePrev = e;
        }
         for (e2 = graph->vertexM[i].successorList; e2 != NULL; e2 = e2->pNextEdge)//this works beautifully
         {
             if (e2->iSuccVertex == iVertex)
             {
                 if (ePrev2 == NULL)
                 {
                    graph->vertexM[i].successorList = e2->pNextEdge;
                    free(e);
                 }
                 else
                 {
                    eCurrent2 = e2->pNextEdge;
                    ePrev2->pNextEdge = eCurrent2;
                }
             }
             ePrev2 = e2;
        }
        free(e);
        free(e2);
    }
     graph->vertexM[iVertex].bExists = FALSE;
}
