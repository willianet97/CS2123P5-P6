#define CRT SECURE NO WARNINGS 1
//include files
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "cs2123p5.h"

int main(int argc, char *argv[])
{
  int iScanfCnt = 0;
  char szName[50];
  char szCommand[50];
  char szInputBuffer[100];
  char szPrereq[50];
  char szDummy[50];//this takes course and will exist for each sscanf
  char szPrintname[50];
  int bCycle;
  int iVertexCnt = 0; //this is incremented after each iteration to store the array subscript
  Graph graph = newGraph();
  
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
      iScanfCnt = sscanf(szInputBuffer, "%s %s %s"
         , szDummy
         , graph->vertexM[iVertexCnt].szCourseId
         , graph->vertexM[iVertexCnt].szCourseName);
      if(iScanfCnt < 3)
        printf("Course input invalid\n");
      strcpy(graph->vertexM[iVertexCnt].szCourseId, szName);
      if(findCourse(graph, iVertexCnt) < 0)// if the course already exists it doesn't create an entire new one
      {
        insertCourse(graph, iVertexCnt); 
        graph->vertexM[iVertexCnt].prereqList->iPrereqVertex = -1;
        iVertexCnt++;
        graph->iNumVertices++;
      }
      //we'll add in the exception that the prereq inserted a course to overwrite the tbd later
    }
    
    //prereq should already exist otherwise this will cause an error
    if(strcmp(szCommand, "PREREQ") == 0)
    {
      iScanfCnt = sscanf(szInputBuffer, "%s %s"
         , szDummy
         , szPrereq);
      if(iScanfCnt < 2)
        printf("Prereq input invalid\n");
        //local variable iPV to hold findCourse info
      int iPV = findCourse(graph, szPrereq);
      // if PreReqCourse is not in the vertex, then insert it with TBD szCourseName and its id
      if (iPV < 0) //findcourse returns -1 if course not found because NULL won't work unless we figure that out
      {
        // create Vertex for new PreReqCourse which wasnt in the Graph before
        strcpy(szPrereq ,graph->vertexM[iVertexCnt].szCourseId);
        strcpy("TBD" ,graph->vertexM[iVertexCnt].szCourseName);
        // allocate edgeNodes for new course
        insertCourse(graph, iVertexCnt);
        graph->vertexM[iVertexCnt].prereqList->iPrereqVertex = -1;
        iVertexCnt++;
        graph->iNumVertices++
      }
      //takes prereq and course subscripts and inserts them
      bCycle = causesCycle(graph, iPV, findCourse(graph, szName));
      if (bCycle == 0)
        printf("Prereq insertion causes cycle\n");
      else
        insertPrereq(graph, iPV, findCourse(graph, szName));
    }
    
    if(strcmp(szCommand, "PRTONE") == 0)
    {
      iScanfCnt = sscanf(szInputBuffer, "%s %s"
         , szDummy
         , szPrintname);
      if(iScanfCnt < 2)
        printf("Printone input invalid\n");
      //calls printone function
      printOne(graph, findCourse(graph, szPrintname));  
    }
    
    //just calls print function, no scanf required
    if(strcmp(szCommand, "PRTALL") == 0)
    {
      printAllInList(graph);
    }
    
    if(strcmp(szCommand, "PRTSUCC") == 0)
    {
      iScanfCnt = sscanf(szInputBuffer, "%s %s"
         , szDummy
         , szPrintname);
      if(iScanfCnt < 2)
        printf("Print successor input invalid\n");
      //calls print successor
      //pretty sure this is for successor
      printTraversal(graph, findCourse(graph, szPrintname), 1);
    }
    
    if(strcmp(szCommand, "MAXCHAIN") == 0)
    {
      iScanfCnt = sscanf(szInputBuffer, "%s %s"
         , szDummy
         , szPrintname);
      if(iScanfCnt < 2)
        printf("Max Chain input invalid\n");
      //calls max chain
      maxChain(graph, findCourse(graph, szPrintname));
    }
    
    if(strcmp(szCommand, "PRTLONGS") == 0)
    {
      iScanfCnt = sscanf(szInputBuffer, "%s %s"
         , szDummy
         , szPrintname);
      if(iScanfCnt < 2)
        printf("Print long input invalid");
      //calls print longs
      int pathM[MAX_VERTICES];
      printLongChains(graph, findCourse(graph, szPrintname), pathM
                      , 0, maxChain(graph, findCourse(graph, szPrintname)));
    }
    
    //just calls print function, no scanf required
    if(strcmp(szCommand, "PRTSINKS") == 0)
    {
      printSinks(graph);
    }
    
    //just calls print function, no scanf required
    if(strcmp(szCommand, "PRTSOURCES") == 0)
    {
      printSources( graph);
    }
    
    if(strcmp(szCommand, "*"))
    {
      char szComments[50];
      iScanfCnt = sscanf(szInputBuffer, "%s['\n]", szComments);
    }
  }
}
/************************************************/
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
  /*we want this to be NULL not 0 if 0 that means it would be the vertexM[0] we want to use a 
  conditional for if (!= NULL) or if (== NULL)*/
  return -1;
}
/*************************************************/
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
/**********************************/
void insertCourse(Graph graph, int iVertex)
{
  EdgeNode *e = allocateEdgeNode();
  graph->vertexM[i].prereqList = e;
  EdgeNode *p = allocateEdgeNode();
  graph->vertexM[i].successorList = p;
}
/***************************************/
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
void exitUsage(int iArg, char *pszMessage, char *pszDiagnosticInfo)
{
     switch (iArg)
     {
       case USAGE_ERR:
          fprintf(stderr, "Error: %s %s\n"
          , pszMessage
          , pszDiagnosticInfo);
         break;
       case USAGE_ONLY:
         break;
       default:
         fprintf(stderr, "Error: bad argument #%d.  %s %s\n"
                  , iArg
                  , pszMessage
                  , pszDiagnosticInfo);
     }
           // print the usage information for any type of command line error
  fprintf(stderr, "p2 -c courseFileName -q queryFileName\n");
  if (iArg == USAGE_ONLY)
    exit(USAGE_ONLY);
  else
    exit(ERR_COMMAND_LINE);
}
// we don't need command switches in this program. We just give it input only
