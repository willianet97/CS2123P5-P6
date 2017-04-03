void printAllInList(Graph graph)
{
  EdgeNode *p;
  int iCount = 0;
  int i;
  int iVertex = 0;
  /*header*/
  printf("%s %s %s %s %s %s\n"
         ,"Vx"
         ,"TE"
         ,"Course"
         ,"Name"
         ,"Prereqs"
         ,"Successors");
  for (i = 0; i < graph->iNumVertices; i++)
  {
    printf("%d %d %s %s"
         ,i
         ,0 //te
         ,graph->vertexM[i].szCourseId
         ,graph->vertexM[i].szCourseName);
     for (p = graph->vertexM[i].prereqList; p != NULL; p = p->pNextEdge)
     {
       iVertex = graph->vertexM[i].prereqList.iPrereqVertex;
       printf("%s"
              ,graph->vertexM[iVertex].szCourseId);
       iCount++;
     }
     if (iCount < 4)
     {
        for (i = iCount; i <= 4; i++)
        {
          printf("...");
        }
     }
     for (p = graph->vertexM[i].successorList; p != NULL; p = p->pNextEdge)
     {
       iVertex = graph->vertexM[i].prereqList.iSuccVertex;
       printf("%s\n"
              ,graph->vertexM[iVertex].szCourseId);
  }
         
}
/*********************************/
/*******requires a findCourse call to pass in iVertex******
iVertex = findCourse(graph, szCourseId - what was grabbed from sscanf)*********/
void printOne(Graph graph, int iVertex)
{
  EdgeNode *p;
  int iCount = 0;
  int i = 0;
  /*header*/
  printf("%s %s %s %s %s %s\n"
         ,"Vx"
         ,"TE"
         ,"Course"
         ,"Name"
         ,"Prereqs"
         ,"Successors");
  printf("%d %d %s %s"
         ,iVertex
         ,0 //te
         ,graph->vertexM[iVertex].szCourseId
         ,graph->vertexM[iVertex].szCourseName);
  for (p = graph->vertexM[iVertex].prereqList; p != NULL; p = p->pNextEdge)
  {
    i = graph->vertexM[iVertex].prereqList.iPrereqVertex;
    printf("%s"
           ,graph->vertexM[i].szCourseId);
    iCount++
  }
  if (iCount < 4)
  {
    for (i = iCount; i <= 4; i++)
    {
      printf("...");
    }
  }
  for (p = graph->vertexM[iVertex].successorList; p != NULL; p = p->pNextEdge)
  {
    i = graph->vertexM[iVertex].prereqList.iSuccVertex;
    printf("%s\n"
           ,graph->vertexM[i].szCourseId);
  }
}
/*********************************/
void printSources(Graph graph)
{
  int i;
  /*header*/
  printf("%s %s\n"
         ,"Course"
         ,"Name");
  for (i = 0; i < graph->iNumVertices; i++)
  {
    if (graph->vertexM[i].prereqList.iPrereqVertex == FALSE)
    {
      printf("%s %s\n"
            ,graph->vertexM[i].szCourseId
            ,graph->vertexM[i].szCourseName);
    }
}
/*********************************/
void printSinks(Graph graph)
{
  int i;
  /*header*/
  printf("%s %s\n"
         ,"Course"
         ,"Name");
  for (i = 0; i < graph->iNumVertices; i++)
  {
    if (graph->vertexM[i].succesorList.iSuccVertex == FALSE)
    {
      printf("%s %s\n"
            ,graph->vertexM[i].szCourseId
            ,graph->vertexM[i].szCourseName);
    }
}
void printTraversal(Graph graph, int iVertex, int iIndent)
{
  int i;
  int iVertexSucc = 0;
  EdgeNode *p;
  for (p = graph->vertexM[iVertex].succesorList; p != NULL;
    p = p->pNextEdge)
  {
    for (i = 0; i < iIndent; i++)
    {
      printf("  ");
    }
    iVertexSucc = graph->vertexM[iVertex].succesorList.iSuccVertex;
    printf("%s %s"
           ,graph->vertexM[iVertexSucc].szCourseId
           ,graph->vertexM[iVertexSucc].szCourseName);
    printTraversal(graph, p->iVertex,iIndent+1)
  }
}

