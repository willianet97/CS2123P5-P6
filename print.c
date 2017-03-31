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
         ,
}
/*********************************/
/*******requires a findCourse call to pass in iVertex******
iVertex = findCourse(graph, szCourseId - what was grabbed from sscanf)*********/
void printOne(Graph graph, int iVertex)
{
  printf("%d %d %s %s %s %s"
         ,iVertex
         ,0 //te
         ,graph->vertexM[iVertex].szCourseId
         ,graph->vertexM[iVertex].szCourseName
         ,graph->vertexM[iVertex]
}
/*********************************/
void printSources(Graph graph)
{
  int i;
  for (i = 0; i < graph->iNumVertices; i++)
  {
    if (vertexM[i]
}
/*********************************/
void printSinks(Graph graph)
{
  int i;
  for (i = 0; i < graph->iNumVertices; i++)
  {
}

