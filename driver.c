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
  char szName;
  char szCommand;
  char szInputBuffer[100];
  Graph graph = malloc(sizeof(GraphImp));
  while(fgets(szInputBuffer, 100, stdin) != NULL)
  {
   getToken(&szInputBuffer, szCommand, 50);
    if(strcmp(szCommand, “COURSE”))
    {
       iScanfCnt = sscanf(szInputBuffer, %s %s,
          , graph->vertexM.szCourseId
          , graph->vertexM.szCourseName);
      graph->vertexM->prereqList.iPrereqVertex = FALSE;
      strcpy(graph->vertexM.szCourseId, szName);
    }
    if(strcmp(szCommand, “PREREQ”))
    {
       findCourse(graph, szName);
       iScanfCnt = sscanf(szInputBuffer, %s,
       graph->vertexM.szCourseId);
       
    }   
   if(strcmp(szCommand, “PRTONE”))
    {
       sscanf()
    }
if(strcmp(szCommand, “PRTALL”))
    {
      
    }
if(strcmp(szCommand, “PRTSUCC”))
    {
       sscanf()
    }
if(strcmp(szCommand, “MAXCHAIN”))
    {
       sscanf()
    }
if(strcmp(szCommand, “PRTLONGS”))
    {
       sscanf()
    }
if(strcmp(szCommand, “PRTSINKS”))
    {
       sscanf()
    }
if(strcmp(szCommand, “PRTSOURCES”))
    {
       sscanf()
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
