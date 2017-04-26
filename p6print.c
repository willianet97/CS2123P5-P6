#define CRT SECURE NO WARNINGS 1
//include files
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "cs2123p6.h"
/************************ printAllInList **************************
void printAllInList(Graph graph)
Purpose:
    Prints all the vertices of the graph with prereqs and successors
Parameters:
    I Graph graph   the graph with info
Notes:
    n/a
*****************************************************************/
void printAllInList(Graph graph)
{
  EdgeNode *e;      //pointer variable used for traversing adjacency list
  int iCount;   //local variable used for printing ...
  int iCount2;  //local variable used for printing -
  int i;    //local variable used for traversing vertices
  int j;    //local variable used for iCount conditional

  /*header*/
  printf("All Vertices In a List\n");
  printf("%-2s %-2s %-7s %-20s  %-8s\t\t\t        %-22s\n"
         ,"Vx"
         ,"TE"
         ,"Course"
         ,"Name"
         ,"Prereqs"
         ,"Successors");
  //for loop used to traverse all vertices
  for (i = 0; i < graph->iNumVertices; i++)
  {
    iCount = 0; //initialize
    iCount2 = 0; //initialize
    //prints the vertex, te, course id, course name
    if (graph->vertexM[i].bExists == FALSE)
    {
        continue;
    }
    else
    {
    printf("%2d %2d %-7s %-22s"
         ,i+1
         ,0 //te
         ,graph->vertexM[i].szCourseId
         ,graph->vertexM[i].szCourseName);
    //for loop used to traverse the prereqs of the specified vertex
     for (e = graph->vertexM[i].prereqList; e != NULL; e = e->pNextEdge)
     {
       //prints the prereq
       printf("%-7s\t"
              ,graph->vertexM[e->iPrereqVertex].szCourseId);
       //iterate iCount to see if ... is needed to be printed
       iCount++;
     }
    //if the count of prereqs is 0 prints a - and iterates the count
    if (iCount == 0)
    {
      printf("%-7s\t", "-");
      iCount++;
    }
    //conditional checking to see how many prereqs were printed
    //if less than 4 prints the appropriate number of ...
     if (iCount < 4)
     {
        for (j = iCount; j < 4; j++)
        {
          printf("%-7s\t", "...");
        }
     }
    //for loop to traverse successors
    //may need tweaking or reworking
     for (e = graph->vertexM[i].successorList; e != NULL; e = e->pNextEdge)
     {
       printf("%s\t"
              ,graph->vertexM[e->iSuccVertex].szCourseId);
       iCount2++;
     }
    //if count of successors is 0 prints a -
    if (iCount2 == 0)
      printf("-");
    printf("\n");
  }
  }
}
/*************************** printOne ********************************
void printOne(Graph graph, int iVertex)
Purpose:
    Prints one of the specified vertices with prereqs and successors
Parameters:
    I Graph graph   the graph with info
    I int iVertex   vertex number being passed in to be printed
Notes:
    n/a
********************************************************************/
void printOne(Graph graph, int iVertex)
{
  EdgeNode *e;  //local pointer variable used to traverse adjacency list
  int iCount = 0; //local variable used for printing ...
  int iCount2 = 0; //local variable used for printing -
  int i; //local variable used for iCount 
  /*header*/
  printf("%-2s %-2s %-7s %-21s %-8s\t\t\t        %-20s\n"
         ,"Vx"
         ,"TE"
         ,"Course"
         ,"Name"
         ,"Prereqs"
         ,"Successors");
  //prints the vertex, te, courseId, courseName
  printf("%2d %2d %-6s  %-22s"
         ,iVertex+1
         ,0 //te
         ,graph->vertexM[iVertex].szCourseId
         ,graph->vertexM[iVertex].szCourseName);
  //used to traverse prereqs
  for (e = graph->vertexM[iVertex].prereqList; e != NULL; e = e->pNextEdge)
  {
    //prints prereqs
    printf("%-7s\t"
           ,graph->vertexM[e->iPrereqVertex].szCourseId);
    //increment iCount for each prereq
    iCount++;
  }
  //if there are no prereqs prints a - and iterates count
  if (iCount == 0)
  {
    printf("%-7s\t", "-");
    iCount++;
   }
  //if iCount < 4 print appropriate number of ...
  if (iCount < 4)
  {
    for (i = iCount; i < 4; i++)
    {
      printf("%-7s\t", "...");
    }
  }
  //used to traverse succesor list
  for (e = graph->vertexM[iVertex].successorList; e != NULL; e = e->pNextEdge)
  {
    //prints successors
    printf("%s\t"
           ,graph->vertexM[e->iSuccVertex].szCourseId);
    iCount2++;
  }
  //if no successors prints a -
  if (iCount2 == 0)
  {
    printf("-");
  }
  printf("\n");
}
/**************** printSources **********************************
void printSources(Graph graph)
Purpose:
    Prints all vertices that have no prereqs
Parameters:
    I Graph graph  the graph structure
Notes:
    n/a
**************************************************************/
void printSources(Graph graph)
{
  int i;  //local variable used to traverse all vertices
  /*header*/
  printf("\n");
  printf("%-7s %-20s\n"
         ,"Course"
         ,"Name");
  //for loop to traverse all vertices
  for (i = 0; i < graph->iNumVertices; i++)
  {
    //conditional if the vertex has no prereq print that vertex
    if (graph->vertexM[i].prereqList == NULL && graph->vertexM[i].bExists == TRUE)
    {
      printf("%-7s %-20s\n"
            ,graph->vertexM[i].szCourseId
            ,graph->vertexM[i].szCourseName);
    }
  }
}
/******************* printSinks *******************************
void printSinks(Graph graph)
Purpose:
  Prints all the vertices that have no successors
Parameters:
  I Graph graph   the graph structure
Notes:
  n/a
************************************************************/
void printSinks(Graph graph)
{
  int i;  //local variable used to traverse all vertices
  /*header*/
  printf("\n");
  printf("%-7s %-20s\n"
         ,"Course"
         ,"Name");
  //for loop to traverse all vertices
  for (i = 0; i < graph->iNumVertices; i++)
  {
    //if the vertex has no successor print that vertex
    if (graph->vertexM[i].successorList == NULL && graph->vertexM[i].bExists == TRUE)
    {
      printf("%-7s %-20s\n"
            ,graph->vertexM[i].szCourseId
            ,graph->vertexM[i].szCourseName);
    }
  }
}
/***************** printTraversal *******************************
void printTraversal(Graph graph, int iVertex, int iIndent)
Purpose:
  Prints the successors of the vertex passed in
Parameters:
  I Graph graph   the graph structure
  I int iVertex   the specified vertex to be used
  I int iIndent   the number of indentations
Notes:
  This function is recursive
***************************************************************/
void printTraversal(Graph graph, int iVertex, int iIndent)
{
  int i;  //local varible used for indentations
  EdgeNode *e;  //local pointer variable used to traverse adjacency list
  //for loop used to traverse successor list of specified vertex
  for (e = graph->vertexM[iVertex].successorList; e != NULL;
    e = e->pNextEdge)
  {
    //prints appropriate number of indentations
    for (i = 0; i < iIndent; i++)
    {
      printf("  ");
    }
    //prints the vertex course id and name
    printf("%-6s %-20s\n"
           ,graph->vertexM[e->iSuccVertex].szCourseId
           ,graph->vertexM[e->iSuccVertex].szCourseName);
    //recursive call for printTraversals passing the graph the new vertex and the increased indent
    printTraversal(graph, e->iSuccVertex,iIndent+1);
  }
}
/********************** printPlan ***************************
void printPlan(Graph graph, Plan plan)
Purpose:
    Prints out the current semester by semester plan.
Parameters:
    I Graph graph     graph with course info
    I Plan plan       plan with semester info
Notes:
    n/a
************************************************************/
void printPlan(Graph graph, Plan plan)
{
    int i;
    int j;
    
    // header
    printf("Semester Plan\n");
    
    // print semester plan
    for (i = 0; i < 5; i++)
    {
        j = 0;
        
        // print semester number
        printf("%s #%d\n"
               ,"Semester"
               ,i+1);
        
        // print semester course info
        while(plan->semesterM[i][j] != -1)
        {
            printf("       %s %s\n"
                   ,graph->vertexM[plan->semesterM[i][j]].szCourseId
                   ,graph->vertexM[plan->semesterM[i][j]].szCourseName);
            j++;
        }
    }
}
