int maxChainLength(Graph graph, int iVertex)
{
  //still working on the basics of this one
    EdgeNode *e;
    int iCount = 0;
    // traverse to the adjacent vertices
    for (e = graph->vertexM[iVertex].successorList; e != NULL; 
         e = e->pNextEdge)
    {
        iCount += countG(graph, e->iVertex);
    }
    return iCount;
}

}
/***********************************************************/
/*maxchain is always called before this function
use return of maxchain as iLongLength*/
void printLongChains(Graph graph, int iVertex, int pathM[], int iLevel, int iLongLength)
{
  EdgeNode *e;
  for (e = graph->vertexM[iVertex].successorList; e!= NULL;
       e = e->pNextEdge)
  {
    iLevel++;
    printLongChains(graph, iVertex, pathM[iLevel], iLongLength);
  }
}
