#define CRT SECURE NO WARNINGS 1
//include files
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "cs2123p5.h"
void main()
{
  int iScanfCnt = 0;
  char szName[];
  char szCommand[];
  char szInputBuffer[100];
  char szPrintname[];
  char szPrereq[];
  int iPrereq;
  int iCourse; // dummy variable
  int iPrintThis; // dummy variable that is only different for avoiding confusion
  int iVertexCnt = 0; //this is incremented after each iteration to store the array subscript
  Graph graph = malloc(sizeof(GraphImp));
  while(fgets(szInputBuffer, 100, stdin) != NULL)
  {
    //the first argument here doesn't work so i dont know 
    //how to use getToken and sscanf at the same time
    getToken(&szInputBuffer, szCommand, 50);
    
    //this if saves the current course in case a prereq
    //comes after it in the input so it can search for it
    //and add it to the graph with the right prereqs and successors
    if(strcmp(szCommand, "COURSE") == 0)
    {
      iScanfCnt = sscanf(szInputBuffer, "%s %s"
         , graph->vertexM[iVertexCnt].szCourseId
         , graph->vertexM[iVertexCnt].szCourseName);
      if(iScanfCnt < 2)
        printf("Course input invalid\n");
      graph->vertexM[iVertexCnt]->prereqList.iPrereqVertex = FALSE;
      strcpy(graph->vertexM[iVertexCnt].szCourseId, szName);
    }
    
    //prereq should already exist otherwise this will cause an error
    if(strcmp(szCommand, "PREREQ") == 0)
    {
      iScanfCnt = sscanf(szInputBuffer, "%s"
         , szPrereq);
      if(iScanfCnt < 1)
        printf("Prereq input invalid\n");
      //takes prereq and course subscripts and inserts them
      insertPrereq(graph, findCourse(graph, szPrereq), findCourse(graph, szName));
    }
    
    if(strcmp(szCommand, "PRTONE") == 0)
    {
      iScanfCnt = sscanf(szInputBuffer, "%s",
          , szPrintname);
      if(iScanfCnt < 1)
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
      iScanfCnt = sscanf(szInputBuffer, "%s",
          , szPrintname);
      if(iScanfCnt < 1)
        printf("Print successor input invalid\n");
      //calls print successor
      //pretty sure this is for successor
      printTraversal(graph, findCourse(graph, szPrintname), 1);
    }
    
    if(strcmp(szCommand, "MAXCHAIN") == 0)
    {
      iScanfCnt = sscanf(szInputBuffer, "%s",
          , szPrintname);
      if(iScanfCnt < 1)
        printf("Max Chain input invalid\n");
      //calls max chain
      maxChain(graph, findCourse(graph, szPrintname));
    }
    
    if(strcmp(szCommand, "PRTLONGS") == 0)
    {
      iScanfCnt = sscanf(szInputBuffer, "%s",
          , szPrintname);
      if(iScanfCnt < 1)
        printf("Print long input invalid");
      //calls print longs
      printLongChains(graph, findCourse(graph, szPrintname), int pathM[], int iLevel, int iLongLength);
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
      char szComments;
      iScanfCnt = sscanf(szInputBuffer, "%s", szComments);
    }
    graph->iNumVertices++;
    iVertexCnt++;
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
  return NULL;
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
