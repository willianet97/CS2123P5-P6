/***************************** causesCycle ********************************
int causesCycle(Graph graph, int iPrereqVertex, int iVertex)
Purpose:
    Checks to see if an insertion causes a cycle and returns a boolean
    accordingly.
Parameters:
    I Graph graph         the graph containing info on the vertices
    I int iPrereqVertex   the index of the prereq vertex
    I int iVertex         the index of the current vertex
Returns:
    Returns TRUE if the insertion of an edge containing the course and its
    prereq would cause a cycle.
    Otherwise, returns FALSE.
Notes:
    This is used by the PREREQ command to check if whether the insertion of
    a prereq would cause a cycle prior to actually inserting that prereq.
***************************************************************************/
int causesCycle(Graph graph, int iPrereqVertex, int iVertex)
{
  EdgeNode *e; // EdgeNode for traversal
  int iSV;     // variable that will hold SuccVertex
  for (e = graph->vertexM[iVertex].successorList; e != NULL; e = e->pNextEdge)
  {
     if (iPrereqVertex == e->iSuccVertex) // check if successors of iVertex reach iPrereqVertex
                                          // is this the only case that we have to check to see if ther eis a cycle?
       return TRUE;
  }
  
  return FALSE;
}   
/***************************** insertPrereq ********************************
int insertPrereq(Graph graph, int iPrereqVertex, int iCourseVertex)
Purpose:
    Inserts the Edgenodwith the PreReqVertex and iSuccVertex to the lists of Nodes of each course. 
Parameters:
    I Graph graph         the graph containing info on the vertices
    I int iPrereqVertex   the index of the prereq vertex
    I int iCourseVertex   the index of the course
Notes:
    This is used by the PREREQ command.
***************************************************************************/

void insertPrereq(Graph graph, int iPrereqVertex, int iCourseVertex)
{
    EdgeNode *eNew = allocateEdgeNode();
    eNew->iPrereqVertex = iPrereqVertex;
    eNew->iSuccVertex = iCourseVertex;
    //set the courseVertex prereqlist vertex to the ones passed
    if (graph->vertexM[iCourseVertex].prereqList->iPrereqVertex == -1)// check if prereqList list already had Edges
    {
        graph->vertexM[iCourseVertex].prereqList = eNew;
        eNew->pNextEdge = NULL;
    }
    else
    {
        graph->vertexM[iCourseVertex].prereqList->pNextEdge = eNew;
        eNew->pNextEdge = NULL
    }
    //set the prereqVertex successorlist vertex to the ones passed
    if (graph->vertexM[iPrereqVertex].successorList->iSuccVertex == -1) // check if successor list already had Edges
    {
        graph->vertexM[iPrereqVertex].successorList = eNew;
        eNew->pNextEdge = NULL;
    }
    else
    {
        graph->vertexM[iPrereqVertex].successorList->pNextEdge = eNew;
        eNew->pNextEdge = NULL;
    }
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
