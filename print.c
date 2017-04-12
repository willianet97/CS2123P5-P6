#define CRT SECURE NO WARNINGS 1
//include files
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "cs2123p5.h"

void printAllInList(Graph graph)
{
  EdgeNode *e;      //pointer variable used for traversing adjacency list
  int iCount = 0;   //local variable used for printing ...
  int i;            //local variable used for traversing vertices
  int j;
   /*header*/
  printf("%-2s %-2s %-6s %-20s %-8s\t\t\t %-15s\n"
         ,"Vx"
         ,"TE"
         ,"Course"
         ,"Name"
         ,"Prereqs"
         ,"Successors");
  //for loop used to traverse all vertices
  for (i = 0; i < graph->iNumVertices; i++) 
  {
    //in the terminal the segfault always kicks in here for some reason but I don't see any errors
    //unless its passed a null graph which it isn't and it works fine in ddd
    //prints the vertex, te, course id, course name
    printf("%2d %2d %-6s %-20s"
         ,i+1
         ,0 //te
         ,graph->vertexM[i].szCourseId
         ,graph->vertexM[i].szCourseName);
    //for loop used to traverse the prereqs of the specified vertex
    //may need tweaking or reworking
     for (e = graph->vertexM[i].prereqList; e != NULL; e = e->pNextEdge)
     {
       //prints the prereq
       printf("%s\t"
              ,graph->vertexM[e->iPrereqVertex].szCourseId);
       //iterate iCount to see if ... is needed to be printed
       iCount++;
     }
    //conditional checking to see how many prereqs were printed
    //if less than 4 prints the appropriate number of ...
     if (iCount < 4)
     {
        for (j = iCount; j < 4; j++)
        {
          printf("...\t");
        }
     }
    //for loop to traverse successors
    //may need tweaking or reworking
     for (e = graph->vertexM[i].successorList; e != NULL; e = e->pNextEdge)
     {
       printf("%s"
              ,graph->vertexM[e->iSuccVertex].szCourseId);
     }
    printf("\n");
  }      
}
/*********************************/
/*******requires a findCourse call to pass in iVertex******
iVertex = findCourse(graph, szCourseId - what was grabbed from sscanf)*********/
void printOne(Graph graph, int iVertex)
{
  EdgeNode *e;  //local pointer variable used to traverse adjacency list
  int iCount = 0; //local variable used for printing ...
  int i;
  /*header*/
  printf("%-2s %-2s %-6s %-20s %-8s\t\t\t %-15s\n"
         ,"Vx"
         ,"TE"
         ,"Course"
         ,"Name"
         ,"Prereqs"
         ,"Successors");
  //prints the vertex, te, courseId, courseName
  printf("%2d %2d %-6s %-20s"
         ,iVertex+1
         ,0 //te
         ,graph->vertexM[iVertex].szCourseId
         ,graph->vertexM[iVertex].szCourseName);
  //used to traverse prereqs
  //may need tweaking or reworking
  for (e = graph->vertexM[iVertex].prereqList; e != NULL; e = e->pNextEdge)
  {
    printf("%s\t"
           ,graph->vertexM[e->iPrereqVertex].szCourseId);
    //increment iCount for each prereq
    iCount++;
  }
  //if iCount < 4 print appropriate number of ...
  if (iCount < 4)
  {
    for (i = iCount; i < 4; i++)
    {
      printf("...\t");
    }
  }
  //used to traverse succesor list
  //may need tweaks or rework
  for (e = graph->vertexM[iVertex].successorList; e != NULL; e = e->pNextEdge)
  {
    printf("%s\t"
           ,graph->vertexM[e->iSuccVertex].szCourseId);
  }
  printf("\n");
}
/*********************************/
void printSources(Graph graph)
{
  int i;  //local variable used to traverse all vertices
  /*header*/
  printf("%-6s %-20s\n"
         ,"Course"
         ,"Name");
  //for loop to traverse all vertices
  for (i = 0; i < graph->iNumVertices; i++)
  {
    //conditional if the vertex has no prereq print that vertex
    if (graph->vertexM[i].prereqList == NULL)
    {
      printf("%-6s %-20s\n"
            ,graph->vertexM[i].szCourseId
            ,graph->vertexM[i].szCourseName);
    }
  }
}
/*********************************/
void printSinks(Graph graph)
{
  int i;  //local variable used to traverse all vertices
  /*header*/
  printf("%-6s %-20s\n"
         ,"Course"
         ,"Name");
  //for loop to traverse all vertices
  for (i = 0; i < graph->iNumVertices; i++)
  {
    //if the vertex has no successor print that vertex
    if (graph->vertexM[i].successorList == NULL)
    {
      printf("%-6s %-20s\n"
            ,graph->vertexM[i].szCourseId
            ,graph->vertexM[i].szCourseName);
    }
  }
}
/********************************************************************/
/*this function is an extreme work in progress this is just a basic approach
may need serious reworking*/
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
    printf("%-6s %-20s\n"
           ,graph->vertexM[e->iSuccVertex].szCourseId
           ,graph->vertexM[e->iSuccVertex].szCourseName);
    //recursive call for printTraversals passing the graph the new vertex and the increased indent
    //p->iSuccVertex may not be right
    printTraversal(graph, e->iSuccVertex,iIndent+1);
  }
}

