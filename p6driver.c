/*********************************************************************************************
p6Driver.c by Travis Woods, Brian Rusnak, William Nester Tamayo, Kyle Astl
Purpose:
    Use a double adjacency list graph to represent courses and their prerequisites
Command Parameters:
    make p6
    p6 < p6Input.txt
Input:
    COURSE szCourseId szName
    This is a course to insert. If the course already exists simply replace its szName.
    
    PREREQ    szPrereqCourseId
    This is a prerequisite course for the most recent COURSE.  
    If this course doesn't already exist, insert it and set its szName to "TBD".  
    If the insertion of the PREREQ would cause a cycle, show a message and don't insert it.

    PRTONE    szCourseId
    Print the vertex subscript, max dist from source (for now use 0), course ID,
    course name, prereqs (max of 4), and successors. If the course doesn't exist, 
    show a warning.

    PRTALL
    Print all of the courses as is done for PRTONE.
    
    PRTSUCC   szCourseId
    Print all the successors of the specified course in a depth first manner with indentation.  
    For each course, print the course ID and course name.  Also include the specified course 
    ID in output. If the course doesn't exist, show a warning.
    
    PRTSOURCES
    Print each of the courses (ID and name) of courses that are sources (i.e., have no prereq)

    PRTSINKS
    Print each of the courses (ID and name) of courses that are sinks (i.e., no other courses 
    have them as prereqs).
    
    MAXCHAIN   szCourseId
    Prints the count of the number of successors in the longest chain that begins with the 
    specified vertex. If the course doesn't exist, show a warning.
    
    PRTLONGS  szCourseID
    Prints each chain that is the longest chain of courses and prerequisites beginning at the 
    specified course.  There may be many of these.  The chains are ones having a length equal 
    to the length of this course's max chain.
    
    PLAN szCourseId
    This course is included in the set of courses we want to show in a semester by 
    semester plan. If the course doesn't exist, show a warning.
    
    DOPLAN
    This produces and prints the semester by semester plan.
     
    DELETE    szCourseId
    Deletes the course, updates the edge lists appropriately, and frees the edge nodes.   
    As a result of this command:
     1. This course will not be associated with any successors. 
        This also means that any successors will no longer have it as a prerequisite.
     2. This course will not be associated with any prereqs.
        This also means that no prereqs will have this course as a successor.
    
    PRTHASH
    Prints the graph in a special format to show the hash table.  
    This uses printHash, which was provided by Larry.
    
    *Comment
    Print the comment (as should be done with the other input commands) and ignore it.
Returns:
    0 - normal
    900 - inalid command line argument
    903 - error in algorithm
Notes:
   Some variables are initialized under the respective strcmp if statement.
*********************************************************************************************/
#define CRT SECURE NO WARNINGS 1
//include files
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "cs2123p6.h"

int main(int argc, char *argv[])
{
  int iScanfCnt = 0;
  //for error checking;
  int iCourseIndex;
  //strings
  char szName[50];
  char szCourse[50];
  char szCommand[50];
  char szInputBuffer[100];
  char szPrereq[50];
  char szDummy[50];//this takes course and will exist for each sscanf
  char szPrintname[50];
  char szTBD[50]; // keeps track of the TBD ID
  int bCycle;// boolean for causescycle
  int iVertexCnt = 0; /* this is incremented after each iteration 
                         to store the array subscript */
  Graph graph = newGraph();
    
  Plan plan = newPlan();
    
  //memset all of bIncludeM to FALSE
  
  while(fgets(szInputBuffer, 100, stdin) != NULL)
  {
    //the first argument here doesn't work so i dont know 
    //how to use getToken and sscanf at the same time
    getToken(szInputBuffer, szCommand, 50);
    
    //this if saves the current course in case a prereq
    //comes after it in the input so it can search for it
    //and add it to the graph with the right prereqs and successors
    if(strcmp(szCommand, "COURSE") == 0)
    {
      iScanfCnt = sscanf(szInputBuffer, "%s %s %[^\n]"
         , szDummy
         , graph->vertexM[iVertexCnt].szCourseId
         , graph->vertexM[iVertexCnt].szCourseName);

      if(iScanfCnt < 3)
        printf("Course input invalid\n");

      // check if TBD and change name if so
      if(strcmp(graph->vertexM[iVertexCnt].szCourseId, szTBD) == 0)
          strcpy(graph->vertexM[findCourse(graph, szTBD)].szCourseName, graph->vertexM[iVertexCnt].szCourseName);
      
      strcpy(szName, graph->vertexM[iVertexCnt].szCourseId);
      strcpy(szCourse, graph->vertexM[iVertexCnt].szCourseName);

      if(findCourse(graph, graph->vertexM[iVertexCnt].szCourseId) < 0)// if the course already exists it doesn't create an entire new one
      {
        insertCourse(graph, iVertexCnt); 
        iVertexCnt++;
        graph->iNumVertices++;
      }
      printf(">> %s %s %s\n"
         , szCommand
         , szName
         , szCourse);
    }
    
    //prereq should already exist otherwise this will cause an error
    else if(strcmp(szCommand, "PREREQ") == 0)
    {
      iScanfCnt = sscanf(szInputBuffer, "%s %s"
         , szDummy
         , szPrereq);
      if(iScanfCnt < 2)
        printf("Prereq input invalid\n");
        //local variable iPV to hold findCourse info
      int iPrereqIndex = findCourse(graph, szPrereq);
      // if PreReqCourse is not in the vertex, then insert it with TBD szCourseName and its id
      if (iPrereqIndex == -1) //findcourse returns -1 if course not found because NULL won't work unless we figure that out
      
      {
        // create Vertex for new PreReqCourse which wasnt in the Graph before
        strcpy(graph->vertexM[iVertexCnt].szCourseId, szPrereq);
        strcpy(graph->vertexM[iVertexCnt].szCourseName, "TBD");
        // allocate edgeNodes for new course
        insertCourse(graph, iVertexCnt);
        // store value of szCourseId for TBD course
        strcpy(szTBD, szPrereq);
        iVertexCnt++;
        graph->iNumVertices++;
      }
      //takes prereq and course subscripts and inserts them
      bCycle = causesCycle(graph, findCourse(graph, szPrereq), findCourse(graph, szName));
      if (bCycle == TRUE)
        printf("\tPrereq insertion causes cycle\n");
      else
        insertPrereq(graph, findCourse(graph, szPrereq), findCourse(graph, szName));
        printf(">> %s %s\n"
            , szCommand
            , szPrereq);
    }
    
    else if(strcmp(szCommand, "PRTONE") == 0)
    {
      iScanfCnt = sscanf(szInputBuffer, "%s %s"
         , szDummy
         , szPrintname);
      if(iScanfCnt < 2)
        printf("Printone input invalid\n");
      //calls printone function
      printf(">> %s %s\n"
         , szCommand
         , szPrintname);

      if(graph->vertexM[findCourse(graph, szPrintname)].bExists == TRUE)
          printOne(graph, findCourse(graph, szPrintname));
      else
          printf("This course has been deleted");
     }
    
    //just calls print function, no scanf required
    else if(strcmp(szCommand, "PRTALL") == 0)
    {
      printf(">> %s\n", szCommand);
      printAllInList(graph);
    }
    
    else if(strcmp(szCommand, "PRTSUCC") == 0)
    {
      iScanfCnt = sscanf(szInputBuffer, "%s %s"
         , szDummy
         , szPrintname);
      if(iScanfCnt < 2)
        printf("Print successor input invalid\n");
      //calls print successor
      //pretty sure this is for successor
      iCourseIndex = findCourse(graph, szPrintname);
      printf(">> %s %s\n"
         , szCommand
         , szPrintname);
      //if course doesn't exist
      if(iCourseIndex == -1)
        printf("Warning: This course doesn't exist!\n");
      else
      {
        printf("%-6s %-20s\n"
            ,graph->vertexM[iCourseIndex].szCourseId
            ,graph->vertexM[iCourseIndex].szCourseName);
        if(graph->vertexM[iCourseIndex].bExists == TRUE)
            printTraversal(graph, iCourseIndex, 1);
        else
            printf("This course has been deleted");
      }
    }
    
    else if(strcmp(szCommand, "MAXCHAIN") == 0)
    {
      iScanfCnt = sscanf(szInputBuffer, "%s %s"
         , szDummy
         , szPrintname);
      if(iScanfCnt < 2)
        printf("Max Chain input invalid\n");
      //calls max chain
      //if course doesn't exist
      iCourseIndex = findCourse(graph, szPrintname);
      printf(">> %s %s\n"
        , szDummy
        , szPrintname);
      if(iCourseIndex == -1)
          printf("Warning: This course doesn't exist!\n");
      else
      {
        printf("\tMaximum chain for %s contains %d courses\n"
           , graph->vertexM[iCourseIndex].szCourseId
           , maxChain(graph, iCourseIndex) + 1);
      }
    }
    
    else if(strcmp(szCommand, "PRTLONGS") == 0)
    {
      iScanfCnt = sscanf(szInputBuffer, "%s %s"
         , szDummy
         , szPrintname);
      if(iScanfCnt < 2)
        printf("Print long input invalid");
      //calls print longs
      printf(">> %s %s\n"
         , szCommand
         , szPrintname);
      iCourseIndex = findCourse(graph, szPrintname); 
      if(iCourseIndex == -1)
          printf("Warning: This course doesn't exist!\n");
      else
      {
        int pathM[MAX_VERTICES];
        printf("\tLongest chains beginning with %s\n", graph->vertexM[iCourseIndex].szCourseId); // this will always be 0
        memset(pathM, -1, MAX_VERTICES * sizeof(int));
        printLongChains(graph, iCourseIndex, pathM
                      , 0, maxChain(graph, iCourseIndex) + 1);
      }
    }
    
    //just calls print function, no scanf required
    else if(strcmp(szCommand, "PRTSINKS") == 0)
    {
      printf(">> %s", szCommand);
      printSinks(graph);
    }
    
    //just calls print function, no scanf required
    else if(strcmp(szCommand, "PRTSOURCES") == 0)
    {
      printf(">> %s\n", szCommand);
      printSources( graph);
    }
    
    else if(strcmp(szCommand, "PLAN") == 0)
    {
        iScanfCnt = sscanf(szInputBuffer, "%s %s"
         , szDummy
         , szPrintname);
        printf(">> %s %s\n", szCommand, szPrintname);
        plan->bIncludeM[findCourse(graph, szPrintname)];
        //function
    }
      
    else if(strcmp(szCommand, "DOPLAN") == 0)
    {
        printf(">> %s\n", szCommand);
        doPlan(graph, plan);
        //function
    }
      
    else if(strcmp(szCommand, "DELETE") == 0)
    {
        iScanfCnt = sscanf(szInputBuffer, "%s %s"
         , szDummy
         , szPrintname);
        printf(">> %s\n", szCommand);
        deleteCourse(graph, findCourse(graph, szPrintname));
    }
    // shows comments marked with asterisks in output
    else if(strcmp(szCommand, "*") == 0)
    {
      char szComments[50];
      iScanfCnt = sscanf(szInputBuffer, "%[^\n]", szComments);
      if(iScanfCnt != 1)
        printf("Bad comments input");

      printf(">> %s\n", szComments);
    }
  }
}
/********************** findCourse ***************************
int findCourse(Graph graph, char szCourseId[])
Purpose:
    Find and return the index of the desired course ID.
Parameters:
    I Graph graph         the graph with all information
    I char szCourseId[]   the ID of the course we wish to find
Returns:
    The index of the desired course ID.
    Returns -1 if not found.
Notes:
    n/a
**************************************************************/
int findCourse(Graph graph, char szCourseId[])
{
  int i;
  for (i = 0; i < graph->iNumVertices; i++)
  {
    if (strcmp(szCourseId, graph->vertexM[i].szCourseId) == 0)
    {
      return i;
    }
  }

  return -1;
}
/******************** getToken **************************************
char * getToken (char *pszInputTxt, char szToken[], int iTokenSize)
Purpose:
    Examines the input text to return the next token.  It also
    returns the position in the text after that token.  This function
    does not skip over white space, but it assumes the input uses 
    spaces to separate tokens.
Parameters:
    I   char *pszInputTxt       input buffer to be parsed
    O   char szToken[]          Returned token.
    I   int iTokenSize          The size of the token variable.  
                                This is used to prevent overwriting memory. 
                                The size should be the memory size minus 1 (for
                                the zero byte).
Returns:
    Functionally:
         Pointer to the next character following the delimiter after the token.
         NULL - no token found.
         szToken parm - the returned token.  If not found, it will be an
         empty string.
Notes:
   If the token is larger than iTokenSize, we return a truncated value.
   If a token isn't found, szToken is set to an empty string
   This function does not skip over white space occurring prior to the token.
************************************************************************/
char * getToken(char *pszInputTxt, char szToken[], int iTokenSize)
{
    int iDelimPos;                      // found position of delim
    int iCopy;                          // number of characters to copy
    char szDelims[20] = " \n\r";        // delimiters
    szToken[0] = '\0';

    // check for NULL pointer 
    if (pszInputTxt == NULL)
        ErrExit(ERR_ALGORITHM
        , "getToken passed a NULL pointer");

    // Check for no token if at zero byte
    if (*pszInputTxt == '\0')
        return NULL;

    // get the position of the first delim
    iDelimPos = strcspn(pszInputTxt, szDelims);

    // if the delim position is at the first character, return no token.
    if (iDelimPos == 0)
        return NULL;

    // see if we have more characters than target token, if so, trunc
    if (iDelimPos > iTokenSize)
        iCopy = iTokenSize;             // truncated size
    else
        iCopy = iDelimPos;

    // copy the token into the target token variable
    memcpy(szToken, pszInputTxt, iCopy);
    szToken[iCopy] = '\0';              // null terminate

    // advance the position
    pszInputTxt += iDelimPos;
    if (*pszInputTxt == '\0')
        return pszInputTxt;
    else
        return pszInputTxt + 1;
}
/*************** insertCourse ****************
void insertCourse(Graph graph, int iVertex)
Purpose:
    Set the prereqList and successorList of
    the vertex to NULL
Parameters:
    I Graph graph      the graph with info
    I int iVertex      the index of the vertex
Notes:
    n/a
********************************************/
void insertCourse(Graph graph, int iVertex)
{
  graph->vertexM[iVertex].prereqList = NULL;
  graph->vertexM[iVertex].successorList = NULL;
  graph->vertexM[iVertex].bExists = TRUE;
}
/*********************** ErrExit **************************************
void ErrExit(int iexitRC, char szFmt[], ... )
Purpose:
    Prints an error message defined by the printf-like szFmt and the
    corresponding arguments to that function.  The number of 
    arguments after szFmt varies dependent on the format codes in
    szFmt.  
    It also exits the program with the specified exit return code.
Parameters:
     I   int iexitRC    Exit return code for the program
     I   char szFmt[]   This contains the message to be printed
                        and format codes (just like printf) for 
                        values that we want to print.
     I   ...            A variable-number of additional arguments
                        which correspond to what is needed
                        by the format codes in szFmt. 
Returns:
    Returns a program exit return code:  the value of iexitRC.
Notes:
    Prints "ERROR: " followed by the formatted error message specified 
    in szFmt. 
    Prints the file path and file name of the program having the error.
    This is the file that contains this routine.
    Requires including <stdarg.h>
***********************************************************************/
void ErrExit(int iexitRC, char szFmt[], ... )
{
    va_list args;               // This is the standard C variable argument list type
    va_start(args, szFmt);      // This tells the compiler where the variable arguments
                                // begins.  They begin after szFmt.
    printf("ERROR: ");
    vprintf(szFmt, args);       // vprintf receives a printf format string and  a
                                // va_list argument
    va_end(args);               // let the C environment know we are finished with the
                                // va_list argument
    printf("\n\tEncountered in file %s\n", __FILE__);  // this 2nd arg is filled in by
                                // the pre-compiler
    exit(iexitRC);
}
