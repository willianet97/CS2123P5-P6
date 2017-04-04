int maxChain(Graph graph, int iVertex)
{
  if(iVertex <= 0)
    return 0;
  EdgeNode *e;// does this have to be malloced too? i'm suddenly forgetting the nitty gritty details.... no its a local pointer variable
  int iCount = 0;
  int iFirst = 0;
  // traverse to the adjacent vertices
  //goes through successor lists
  for (e = graph->vertexM[iVertex].successorList; e != NULL; 
     e = e->pNextEdge)
  {
    //within successor lists it takes each path
    iCount += maxChain(graph, e->iSuccVertex);
    if(iCount >= iFirst)
      iFirst = iCount;
    //somehow this should be reset
    iCount--;
    //but no quite like this because if it has more
    //than one successor it subracts too many
  }
  return iFirst;
}
/***********************************************************/
/*maxchain is always called before this function
use return of maxchain as iLongLength*/
/*function needs a lot of work just some rudimentary basics jotted down may even be wrong so far*/
void printLongChains(Graph graph, int iVertex, int pathM[], int iLevel, int iLongLength)
{
  if(iVertex <= 0)
    return;
  EdgeNode *e;
  pathM[iLevel] = iVertex;// this reads current vertex into pathM
  for (e = graph->vertexM[iVertex].successorList; e!= NULL;
       e = e->pNextEdge)
  {
    printLongChains(graph, graph->vertexM[iVertex].successorList.iSuccVertex, pathM[iLevel+1], iLongLength);
    // we want to be able to overwrite shorter paths 
    // without permanently increasing iLevel
    if(iLevel == iLongLength)
    {
      printf("\tLongest chains beginning with %s\n", graph->vertexM[pathM[0]].szCourseId); // this will always be 0
    }
  }
}
