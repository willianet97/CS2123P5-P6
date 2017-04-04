void printAllInList(Graph graph)
{
  EdgeNode *p;      //pointer variable used for traversing adjacency list
  int iCount = 0;   //local variable used for printing ...
  int i;            //local variable used for traversing vertices
  int iVertex = 0;  //local variable used to hold vertex number
  /*header*/
  printf("%s %s %s %s %s %s\n"
         ,"Vx"
         ,"TE"
         ,"Course"
         ,"Name"
         ,"Prereqs"
         ,"Successors");
  //for loop used to traverse all vertices
  for (i = 0; i < graph->iNumVertices; i++)
  {
    //prints the vertex, te, course id, course name
    printf("%d %d %s %s"
         ,i
         ,0 //te
         ,graph->vertexM[i].szCourseId
         ,graph->vertexM[i].szCourseName);
    //for loop used to traverse the prereqs of the specified vertex
    //may need tweaking or reworking
     for (p = graph->vertexM[i].prereqList; p != NULL; p = p->pNextEdge)
     {
       //iVertex used to hold the vertex number of the prereq
       iVertex = graph->vertexM[i].prereqList->iPrereqVertex;
       //prints the prereq
       printf("%s"
              ,graph->vertexM[iVertex].szCourseId);
       //iterate iCount to see if ... is needed to be printed
       iCount++;
     }
    //conditional checking to see how many prereqs were printed
    //if less than 4 prints the appropriate number of ...
     if (iCount < 4)
     {
        for (i = iCount; i <= 4; i++)
        {
          printf("...");
        }
     }
    //for loop to traverse successors
    //may need tweaking or reworking
     for (p = graph->vertexM[i].successorList; p != NULL; p = p->pNextEdge)
     {
       iVertex = graph->vertexM[i].prereqList->iSuccVertex;
       printf("%s\n"
              ,graph->vertexM[iVertex].szCourseId);
     }
  }      
}
/*********************************/
/*******requires a findCourse call to pass in iVertex******
iVertex = findCourse(graph, szCourseId - what was grabbed from sscanf)*********/
void printOne(Graph graph, int iVertex)
{
  EdgeNode *p;  //local pointer variable used to traverse adjacency list
  int iCount = 0; //local variable used for printing ...
  int i = 0;  //local variable used to hold vertex number
  /*header*/
  printf("%s %s %s %s %s %s\n"
         ,"Vx"
         ,"TE"
         ,"Course"
         ,"Name"
         ,"Prereqs"
         ,"Successors");
  //prints the vertex, te, courseId, courseName
  printf("%d %d %s %s"
         ,iVertex
         ,0 //te
         ,graph->vertexM[iVertex].szCourseId
         ,graph->vertexM[iVertex].szCourseName);
  //used to traverse prereqs
  //may need tweaking or reworking
  for (p = graph->vertexM[iVertex].prereqList; p != NULL; p = p->pNextEdge)
  {
    //stores the vertex of the prereq to be printed
    i = graph->vertexM[iVertex].prereqList->iPrereqVertex;
    printf("%s"
           ,graph->vertexM[i].szCourseId);
    //increment iCount for each prereq
    iCount++
  }
  //if iCount < 4 print appropriate number of ...
  if (iCount < 4)
  {
    for (i = iCount; i <= 4; i++)
    {
      printf("...");
    }
  }
  //used to traverse succesor list
  //may need tweaks or rework
  for (p = graph->vertexM[iVertex].successorList; p != NULL; p = p->pNextEdge)
  {
    //stores vertex of successsor
    i = graph->vertexM[iVertex].prereqList->iSuccVertex;
    printf("%s\n"
           ,graph->vertexM[i].szCourseId);
  }
}
/*********************************/
void printSources(Graph graph)
{
  int i;  //local variable used to traverse all vertices
  /*header*/
  printf("%s %s\n"
         ,"Course"
         ,"Name");
  //for loop to traverse all vertices
  for (i = 0; i < graph->iNumVertices; i++)
  {
    //conditional if the vertex has no prereq print that vertex
    if (graph->vertexM[i].prereqList->iPrereqVertex == -1)
    {
      printf("%s %s\n"
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
  printf("%s %s\n"
         ,"Course"
         ,"Name");
  //for loop to traverse all vertices
  for (i = 0; i < graph->iNumVertices; i++)
  {
    //if the vertex has no successor print that vertex
    if (graph->vertexM[i].successorList->iSuccVertex == -1)
    {
      printf("%s %s\n"
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
  int iVertexSucc = 0;  //local variable used to hold successor vertex number
  EdgeNode *p;  //local pointer variable used to traverse adjacency list
  //for loop used to traverse successor list of specified vertex
  for (p = graph->vertexM[iVertex].successorList; p != NULL;
    p = p->pNextEdge)
  {
    //prints appropriate number of indentations
    for (i = 0; i < iIndent; i++)
    {
      printf("  ");
    }
    //assigns iVertexSucc to the successor vertex of the specified original vertex and prints
    iVertexSucc = graph->vertexM[iVertex].successorList->iSuccVertex;
    printf("%s %s"
           ,graph->vertexM[iVertexSucc].szCourseId
           ,graph->vertexM[iVertexSucc].szCourseName);
    //recursive call for printTraversals passing the graph the new vertex and the increased indent
    //p->iSuccVertex may not be right
    printTraversal(graph, p->iSuccVertex,iIndent+1);
  }
}

