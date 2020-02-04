/*
	Name 1: Jefferson Lint
	Name 2: Michael O'Leary
	UTEID 1: jdl3858
	UTEID 2: mso547
*/

#include <stdio.h> /* standard input/output library */
#include <stdlib.h> /* Standard C Library */
#include <string.h> /* String operations library */
#include <ctype.h> /* Library for useful character operations */
#include <limits.h> /* Library for definitions of common variable type characteristics */

#define MAX_LINE_LENGTH 255

/*prototypes*/
int readAndParse(FILE* pInFile, char* pLine, char** pLabel, char** pOpcode, char** pArg1, char** pArg2, char** pArg3, char** pArg4);
int isOpCode(char* op);

int main(int argc, char* argv[])
{
  //open up the files babyyyy
  FILE* inFile = NULL;
  FILE* outFile = NULL;
  if(argc<3)
  {
    printf("SCREAM\n");
    exit(5);
  }
  inFile = fopen(argv[1], "r");
  outFile = fopen(argv[2], "w");

  if (!inFile)
  {
    printf("Error: Cannot open file %s\n", argv[1]);
    exit(4);
  }
  if (!outFile)
  {
    printf("Error: Cannot open file %s\n", argv[2]);
    exit(4);
  }
  printf("Opening files!\n");

  fprintf(outFile, "0x4500\n");

}
