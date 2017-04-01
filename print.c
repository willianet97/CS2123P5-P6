void printAllInList(Graph graph)
{
  int i;
  for (i = 0; i < graph->iNumVertices; i++)
  {
    printf("%d %d %s %s %s %s"
         ,i
         ,0 //te
         ,graph->vertexM[i].szCourseId
         ,graph->vertexM[i].szCourseName
         
}
/*********************************/
/*******requires a findCourse call to pass in iVertex******
iVertex = findCourse(graph, szCourseId - what was grabbed from sscanf)*********/
void printOne(Graph graph, int iVertex)
{
  EdgeNode *p;
  int i;
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
  for (i = 0; i < graph->iNumVertices; i++)
  {
    if (graph->vertexM[i]->prereqList.iPrereqVertex == FALSE)
    {
      printf()
    }
}
/*********************************/
void printSinks(Graph graph)
{
  int i;
  for (i = 0; i < graph->iNumVertices; i++)
  {
    if (graph->vertexM[i]->succesorList.iSuccVertex == FALSE)
    {
      printf()
    }
}

