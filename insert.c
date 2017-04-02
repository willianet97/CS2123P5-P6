void insertPrereq(Graph graph, int iPrereqVertex, int iCourseVertex)
{
  
}
/************************** newGraph ********************************
Graph newGraph()
Purpose:
    Creates a new graph.
Parameters:
    n/a
Returns:
    The new graph.
Notes:
    n/a
**************************************************************************/
Graph newGraph()
{
   // allocate memory for graph
   Graph g = malloc(sizeof(GraphImp));
   
   // mark the graph as empty
   g->iNumVertices = 0;
  
   // g->vertexM will be set in driver
  
   return g;
}
