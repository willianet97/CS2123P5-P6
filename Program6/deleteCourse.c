/******************* deleteCourse **********************
void deleteCourse(Graph graph, int iVertex)
Purpose:
    This will delete a course. Additional notes below.
Parameters:
    I/O Graph graph    graph with info on courses
    I int iVertex      the index of the course vertex
Notes:
This course will not be associated with any successors, 
meaning any successors will no longer have it as a prereq.
.....................................................
This course will not be associated with any prereqs, 
meaning no prereqs will have this course as a successor.
.....................................................
Frees all edge nodes which reference this vertex.
.....................................................
The course is marked deleted in the vertex array. 
.....................................................
EXTRA CREDIT: it is also removed from an overflow chain 
if it is in the overflow area.
********************************************************/
void deleteCourse(Graph graph, int iVertex)
{
  







}
