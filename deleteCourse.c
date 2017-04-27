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
    int i;  //local variable to traverse for loop
    EdgeNode *e;    //local pointer variable used for traversal
    EdgeNode *e2;   //local pointer variable used for traversal
    EdgeNode *ePrev;    //local pointer variable used to hold previous node
    EdgeNode *ePrev2;   //local pointer variable used to hold previous node
    //traverse through all vertices
    for (i = 0; i < graph->iNumVertices; i++)
    {
        //initialize ePrev and ePrev2 to NULL
        ePrev = NULL;
        ePrev2 = NULL;
        //traverse through prereqs
        for (e = graph->vertexM[i].prereqList; e != NULL; e = e->pNextEdge)//the segfault is caused somewhere in here
        {
            if (e->iPrereqVertex == iVertex)
            {
                if (ePrev == NULL)//if it is at the head of the list
                {
                    //set the head of list to the next edge
                    graph->vertexM[i].prereqList = e->pNextEdge;
                    free(e);
                }
                else//if it is in the middle
                {
                    //set prev next edge to e's next edge
                    ePrev->pNextEdge = e->pNextEdge;
                    break;
                    
                }
            }
            //set ePrev to e
                ePrev = e;
        }
        //traverse through successors
         for (e2 = graph->vertexM[i].successorList; e2 != NULL; e2 = e2->pNextEdge)
         {
             //check for head of list
             if (e2->iSuccVertex == iVertex)
             {
                 //if head of list
                 if (ePrev2 == NULL)
                 {
                     //set head of list to be the next edge
                    graph->vertexM[i].successorList = e2->pNextEdge;
                    free(e);
                 }
                 else
                 {
                     //set ePrev2 next edge to e2's next edge
                    ePrev2->pNextEdge = e2->pNextEdge;
                }
             }
             //set ePrev2 to e2
             ePrev2 = e2;
        }
        //free e and e2
        free(e);
        free(e2);
    }
    //set the vertex to false
     graph->vertexM[iVertex].bExists = FALSE;
}
