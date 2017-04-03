int maxChainLength(Graph graph, int iVertex)
{
  //still working on the basics of this one
    EdgeNode *e;
    int iCount = 0;
    // traverse to the adjacent vertices
    for (e = g->vertexM[iVertex].successorList; e != NULL; 
         e = e->pNextEdge)
    {
        iCount += countG(g, e->iVertex);
    }
    return iCount;
}

}
/***********************************************************/
void printLongChains(Graph graph, int iVertex, int pathM[], int iLevel, int iLongLength)
{
}
