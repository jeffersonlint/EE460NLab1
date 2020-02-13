/*
	Name 1: Jefferson Lint
	Name 2: Michael O'Leary
	UTEID 1: jdl3858
	UTEID 2: mso547
*/

/* necessary #includes */
#include <stdio.h> /* standard input/output library */
#include <stdlib.h> /* Standard C Library */
#include <string.h> /* String operations library */
#include <ctype.h> /* Library for useful character operations */
#include <limits.h> /* Library for definitions of common variable type characteristics */

/* constants! */
#define MAX_LINE_LENGTH 255
#define MAX_LABEL_LEN 20
#define MAX_SYMBOLS 255
#define NUM_OF_OPCODES 31

/*use to build symbol table*/
typedef struct {
	int address;
	char label[MAX_LABEL_LEN + 1];
} TableEntry;
TableEntry symbolTable[MAX_SYMBOLS];

/*use to determine if valid Opcode*/
char* validOpcode[NUM_OF_OPCODES] = {"add", "and", "br", "brn", "brnz", "brnzp", "brz", "brzp", "brp", "brnp",
                        "halt", "jmp", "jsr", "jsrr", "ldb", "ldw", "lea", "nop", "not", "ret",
                        "lshf", "rshfl", "rshfa", "rti", "stb", "stw", "trap", "xor", ".fill", ".orig", ".end"};
char* trapRoutines[4] = {"in", "out", "getc", "puts"};


/*use in readAndParse as return values*/
enum
{
  DONE,
  OK,
  EMPTY_LINE
};

/* prototypes */
int readAndParse(FILE* pInFile, char* pLine, char** pLabel, char** pOpcode, char** pArg1, char** pArg2, char** pArg3, char** pArg4);
int isOpcode(char* op);

int main(int argc, char* argv[])
{
  /*--------------------------------------------------------OPEN FILES--------------------------------------------------------------*/
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

  /*--------------------------------------------------------FIRST PASS--------------------------------------------------------------*/
  char lLine[MAX_LINE_LENGTH + 1], *lLabel, *lOpcode, *lArg1, *lArg2, *lArg3, *lArg4;
  int lRet;
  int x=1;
  do{
    lRet = readAndParse( inFile, lLine, &lLabel, &lOpcode, &lArg1, &lArg2, &lArg3, &lArg4 );
    if(lRet != DONE && lRet != EMPTY_LINE)
    {
				
    }
  } while(lRet != DONE);

  /*-------------------------------------------------------SECOND PASS--------------------------------------------------------------*/
  rewind(inFile);
  int y=1;
  do{
    lRet = readAndParse( inFile, lLine, &lLabel, &lOpcode, &lArg1, &lArg2, &lArg3, &lArg4 );
    if(lRet != DONE && lRet != EMPTY_LINE)
    {
        //fprintf(outFile, "Second Pass, Line: %i;  OPCODE:  %s\n", y, lOpcode);
        //y++;
    }
  } while(lRet != DONE);
}

int readAndParse( FILE * pInfile, char * pLine, char ** pLabel, char** pOpcode, char ** pArg1, char ** pArg2, char ** pArg3, char ** pArg4)
{
  char *lRet, *lPtr;
  int i;
  if(!fgets(pLine, MAX_LINE_LENGTH, pInfile))
  {
    return( DONE );
  }
  for(i = 0; i < strlen( pLine ); i++)
  {
    pLine[i] = tolower(pLine[i]);
  }
  /* convert entire line to lowercase */
  *pLabel = *pOpcode = *pArg1 = *pArg2 = *pArg3 = *pArg4 = pLine + strlen(pLine);

  /* ignore the comments */
  lPtr = pLine;

  while(*lPtr != ';' && *lPtr != '\0' && *lPtr != '\n')
  {
    lPtr++;
  }
  *lPtr = '\0';
  if(!(lPtr = strtok(pLine, "\t\n ,")))
  {
    return( EMPTY_LINE );
  }
  if(isOpcode(lPtr) == -1 && lPtr[0] != '.') /* found a label */
  {
    *pLabel = lPtr;
    if(!(lPtr = strtok(NULL, "\t\n ,"))) return(OK);
  }

  *pOpcode = lPtr;
  if(!(lPtr = strtok(NULL, "\t\n ,"))) return(OK);

  *pArg1 = lPtr;
  if(!(lPtr = strtok(NULL, "\t\n ,"))) return(OK);

  *pArg2 = lPtr;
  if(!(lPtr = strtok(NULL, "\t\n ,"))) return(OK);

  *pArg3 = lPtr;
  if(!(lPtr = strtok(NULL, "\t\n ,"))) return(OK);

  *pArg4 = lPtr;
  return(OK);
}

int isOpcode(char* op)
{
	//printf("%s\n", op);
  for(int i=0; i<NUM_OF_OPCODES; i++)
  {
    if(strcmp(op, (validOpcode[i]))==0)
    {
      return 1;
    }
  }
  return -1;
}
