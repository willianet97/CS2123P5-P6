int maxChainLength(Graph graph, int iVertex)
{
  //still working on the basics of this one
  EdgeNode *e;
  int iCount = 0;
  int iFirst =0;
  // traverse to the adjacent vertices
  //goes through successor lists
  for (e = graph->vertexM[iVertex].successorList; e != NULL; 
     e = e->pNextEdge)
  {
    //within successor lists it takes each path
    iCount += countG(graph, e->iVertex);
    if(iCount >= iFirst)
      iFirst = iCount;
    //somehow this should be reset
    iCount--;
    //but no quite like this because if it has more
    //than one successor it subracts too many
  }
  return iFirst;
}

}
/***********************************************************/
/*maxchain is always called before this function
use return of maxchain as iLongLength*/

/*function needs a lot of work just some rudimentary basics jotted down may even be wrong so far*/
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
