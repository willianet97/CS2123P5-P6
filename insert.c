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
/************************** allocateEdgeNode ********************************
EdgeNode *allocateEdgeNode(Graph g, int iPreValue, int iSuccValue)
Purpose:
    Allocates a new edge node to insert in graph.
Parameters:
    I Graph g         the graph
    I int iPreValue   vertex of prereq to insert
    I int iSuccValue  vertex of successor to insert
Returns:
    A pointer to the new edge node.
Notes:
    n/a
**************************************************************************/
EdgeNode *allocateEdgeNode(Graph g, int iPreValue, int iSuccValue)
{
  // allocate memory for an edge node
  EdgeNode *pNew;
  
  pNew = (EdgeNode *) malloc(sizeof(EdgeNode));
  
  // check if memory is available
  if(pNew == NULL)
    ErrExit(ERR_ALGORITHM, "No available memory for edge node");
  
  // assign empty values
  pNew->pNextEdge = NULL;
  pNew->iPrereqVertex = iPreValue;
  pNew->iSuccVertex = iSuccValue;
   
  return pNew;
}

