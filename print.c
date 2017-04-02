void printAllInList(Graph graph)
{
  EdgeNode *p;
  int i;
  int i2;
  /*header*/
  printf("%s %s %s %s %s %s"
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
     for (p = graph->vertexM[i]->prereqList; p != NULL; p = p->pNextEdge)
     {
    i2 = graph->vertexM[i]->prereqList.iPrereqVertex;
    printf("%s"
           ,graph->vertexM[i].szCourseId);
     }
     for (p = graph->vertexM[i]->successorList; p != NULL; p = p->pNextEdge)
     {
    i2 = graph->vertexM[i]->prereqList.iSuccVertex;
    printf("%s"
           ,graph->vertexM[i].szCourseId);
  }
         
}
/*********************************/
/*******requires a findCourse call to pass in iVertex******
iVertex = findCourse(graph, szCourseId - what was grabbed from sscanf)*********/
void printOne(Graph graph, int iVertex)
{
  EdgeNode *p;
  int i;
  /*header*/
  printf("%s %s %s %s %s %s"
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
  for (p = graph->vertexM[iVertex]->prereqList; p != NULL; p = p->pNextEdge)
  {
    i = graph->vertexM[iVertex]->prereqList.iPrereqVertex;
    printf("%s"
           ,graph->vertexM[i].szCourseId);
  }
  for (p = graph->vertexM[iVertex]->successorList; p != NULL; p = p->pNextEdge)
  {
    i = graph->vertexM[iVertex]->prereqList.iSuccVertex;
    printf("%s"
           ,graph->vertexM[i].szCourseId);
  }
}
/*********************************/
void printSources(Graph graph)
{
  int i;
  /*header*/
  printf("%s %s"
         ,"Course"
         ,"Name");
  for (i = 0; i < graph->iNumVertices; i++)
  {
    if (graph->vertexM[i]->prereqList.iPrereqVertex == FALSE)
    {
      printf("%s %s"
            ,graph->vertexM[i].szCourseId
            ,graph->vertexM[i].szCourseName);
    }
}
/*********************************/
void printSinks(Graph graph)
{
  int i;
  /*header*/
  printf("%s %s"
         ,"Course"
         ,"Name");
  for (i = 0; i < graph->iNumVertices; i++)
  {
    if (graph->vertexM[i]->succesorList.iSuccVertex == FALSE)
    {
      printf("%s %s"
            ,graph->vertexM[i].szCourseId
            ,graph->vertexM[i].szCourseName);
    }
}

