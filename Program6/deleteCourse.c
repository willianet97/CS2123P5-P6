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
    EdgeNode *ePrev = NULL;
    EdgeNode *ePrev2 = NULL;
    for (i = 0; i < graph->iNumVertices; i++)
    {
        for (e = graph->vertexM[i].prereqList; e != NULL; e = e->pNextEdge)//the segfault is caused somewhere in here
        {
            if (e->iPrereqVertex == iVertex)
            {
                if (ePrev == NULL)//if it is at the head of the list
                {
                    graph->vertexM[i].prereqList = e->pNextEdge;
                }
                else//if it is in the middle
                {
                    ePrev->pNextEdge = e->pNextEdge;//i think this is the issue because its trying to read something null
                }
                free(e);
            }
            else
                ePrev = e;
         }
         for (e = graph->vertexM[i].successorList; e != NULL; e = e->pNextEdge)//this works beautifully
         {
             if (e->iSuccVertex == iVertex)
             {
                 if (ePrev2 == NULL)
                 {
                    graph->vertexM[i].successorList = e->pNextEdge;
                 }
                 else
                 {
                    ePrev2->pNextEdge = e->pNextEdge;
                 }
                 free(e);
             }
             else
                ePrev2 = e;
        }
    }
     graph->vertexM[iVertex].bExists = FALSE;
}
