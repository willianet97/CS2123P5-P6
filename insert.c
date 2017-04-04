void insertPrereq(Graph graph, int iPrereqVertex, int iCourseVertex)
{
  //local variable iPV to hold findCourse info
  //this might be redundant and unneccessary
  int iPV = findCourse(graph, graph->vertexM[iPrereqVertex].szCourseId);
  if (i < 0) //findcourse returns -1 if course not found
  {
    /*insert prereq into graph and set name as TBD*/
  }
  //set the course prereqlist vertex to the passed in prereq vertex
  graph->vertexM[iCourseVertex].prereqList->iPrereqVertex = iPV;
  //set the prereq successorlist vertex to the passed in course vertex
  graph->vertexM[iPV].successorList->iSuccVertex = iCourseVertex;
  /*need some way to increment list possibly because if we added another prereq to that
  course would it override the previous prereq we put in does pNextEdge need to be used?*/
  
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
   
   // check if memory is available
   if(g == NULL)
     ErrExit(ERR_ALGORITHM, "No available memory for graph");
  
   // mark the graph as empty
   g->iNumVertices = 0;
  
   // g->vertexM will be set in driver
  
   return g;
}
/************************** allocateEdgeNode ********************************
EdgeNode *allocateEdgeNode()
Purpose:
    Allocates a new edge node.
Parameters:
    n/a
Returns:
    A pointer to the new edge node.
Notes:
    n/a
**************************************************************************/
EdgeNode *allocateEdgeNode()
{
  // allocate memory for an edge node
  EdgeNode *pNew;
  
  pNew = (EdgeNode *) malloc(sizeof(EdgeNode));
  
  // check if memory is available
  if(pNew == NULL)
    ErrExit(ERR_ALGORITHM, "No available memory for edge node");
  
  // assign empty values
  pNew->pNextEdge = NULL;
  pNew->iPrereqVertex = -1;
  pNew->iSuccVertex = -1;
   
  return pNew;
}
