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
typedef struct TableEntry {
	int address;
	char label[MAX_LABEL_LEN+1];
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
int toNum(char* pStr);
char* binaryStringToHexString(char* bStr);

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
  int x=-1, tablePointer=0;
	int start=0;
  do{
    lRet = readAndParse( inFile, lLine, &lLabel, &lOpcode, &lArg1, &lArg2, &lArg3, &lArg4 );
    if(lRet != DONE && lRet != EMPTY_LINE)
    {
				//get original start point
				if(strcmp(lOpcode, ".orig")==0)
				{
					start = toNum("x3000");
				}
				//check to see if there's a lLabel
				if(strcmp(lLabel, "")!=0)
				{
					symbolTable[tablePointer].address = start+(x*2)-4;
					strcpy(symbolTable[tablePointer].label, lLabel);
					tablePointer++;
				}
				//fprintf(outFile, "%i:  %s\t%s\t%s\n", start+(x*2), lLabel, lOpcode, lArg1);

				//increment loop pointer
				x++;
    }
  } while(lRet != DONE);

  /*-------------------------------------------------------SECOND PASS--------------------------------------------------------------*/
  rewind(inFile);
  int y=-1;
  do{
    lRet = readAndParse( inFile, lLine, &lLabel, &lOpcode, &lArg1, &lArg2, &lArg3, &lArg4 );
    if(lRet != DONE && lRet != EMPTY_LINE)
    {
				char* bInstruction[16]; //string representation of an instruction in BINARY

				//we don't need to worry about this one! we already did what we need to do in the first pass
				if(strcmp(lOpcode, ".orig")==0){/**/}
				// "add", "and", "br", "brn", "brnz", "brnzp", "brz", "brzp", "brp", "brnp",
				// "halt", "jmp", "jsr", "jsrr", "ldb", "ldw", "lea", "nop", "not", "ret",
				// "lshf", "rshfl", "rshfa", "rti", "stb", "stw", "trap", "xor", ".fill", ".orig", ".end"
				else if(strcmp(lOpcode, "add")==0)
				{
					fprintf(outFile, "need to do this opcode!\n");
				}
				else if(strcmp(lOpcode, "and")==0)
				{
					char* binInstruction = "0101";
					
					fprintf(outFile, "need to do this opcode!\n");
				}
				else if(strcmp(lOpcode, "br")==0)
				{
					fprintf(outFile, "need to do this opcode!\n");
				}
				else if(strcmp(lOpcode, "brn")==0)
				{
					fprintf(outFile, "need to do this opcode!\n");
				}
				else if(strcmp(lOpcode, "brnz")==0)
				{
					fprintf(outFile, "need to do this opcode!\n");
				}
				else if(strcmp(lOpcode, "brnzp")==0)
				{
					fprintf(outFile, "need to do this opcode!\n");
				}
				else if(strcmp(lOpcode, "brz")==0)
				{
					fprintf(outFile, "need to do this opcode!\n");
				}
				else if(strcmp(lOpcode, "brzp")==0)
				{
					fprintf(outFile, "need to do this opcode!\n");
				}
				else if(strcmp(lOpcode, "brp")==0)
				{
					fprintf(outFile, "need to do this opcode!\n");
				}
				else if(strcmp(lOpcode, "brnp")==0)
				{
					fprintf(outFile, "need to do this opcode!\n");
				}
				else if(strcmp(lOpcode, "halt")==0)
				{
					fprintf(outFile, "need to do this opcode!\n");
				}
				else if(strcmp(lOpcode, "jmp")==0)
				{
					fprintf(outFile, "need to do this opcode!\n");
				}
				else if(strcmp(lOpcode, "jsr")==0)
				{
					fprintf(outFile, "need to do this opcode!\n");
				}
				else if(strcmp(lOpcode, "jsrr")==0)
				{
					fprintf(outFile, "need to do this opcode!\n");
				}
				else if(strcmp(lOpcode, "ldb")==0)
				{
					fprintf(outFile, "need to do this opcode!\n");
				}
				else if(strcmp(lOpcode, "ldw")==0)
				{
					fprintf(outFile, "need to do this opcode!\n");
				}
				else if(strcmp(lOpcode, "lea")==0)
				{
					fprintf(outFile, "need to do this opcode!\n");
				}
				else if(strcmp(lOpcode, "nop")==0)
				{
					fprintf(outFile, "need to do this opcode!\n");
				}
				else if(strcmp(lOpcode, "not")==0)
				{
					fprintf(outFile, "need to do this opcode!\n");
				}
				else if(strcmp(lOpcode, "ret")==0)
				{
					fprintf(outFile, "need to do this opcode!\n");
				}
				else if(strcmp(lOpcode, "lshf")==0)
				{
					fprintf(outFile, "need to do this opcode!\n");
				}
				else if(strcmp(lOpcode, "rshfl")==0)
				{
					fprintf(outFile, "need to do this opcode!\n");
				}
				else if(strcmp(lOpcode, "rshfa")==0)
				{
					fprintf(outFile, "need to do this opcode!\n");
				}
				else if(strcmp(lOpcode, "rti")==0)
				{
					fprintf(outFile, "need to do this opcode!\n");
				}
				else if(strcmp(lOpcode, "stb")==0)
				{
					fprintf(outFile, "need to do this opcode!\n");
				}
				else if(strcmp(lOpcode, "stw")==0)
				{
					fprintf(outFile, "need to do this opcode!\n");
				}
				else if(strcmp(lOpcode, "trap")==0)
				{
					fprintf(outFile, "need to do this opcode!\n");
				}
				else if(strcmp(lOpcode, "xor")==0)
				{
					fprintf(outFile, "need to do this opcode!\n");
				}
				else if(strcmp(lOpcode, ".fill")==0)
				{
					fprintf(outFile, "%s\n", lArg1);
				}
				else if(strcmp(lOpcode, ".end")==0)
				{
					break;
				}
				//invalid opcode
				else
				{
					printf("Invalid opcode encountered; assembly process terminated\n");
					exit(2);
				}

				//increment loop pointer
				y++;
    }
  } while(lRet != DONE);
}

  /*-------------------------------------------------------readAndParse--------------------------------------------------------------*/

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
	for(int i=0; pLine[i]!='\0'; i++)
	{
		while(pLine[i]==13)
		{
			int j=i;
			for(j=i; pLine[j]!='\0'; j++)
			{
				pLine[j] = pLine[j+1];
			}
			pLine[j]='\0';
		}
	}

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

  /*-------------------------------------------------------isOpcode--------------------------------------------------------------*/

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

  /*-------------------------------------------------------toNum--------------------------------------------------------------*/

int toNum(char* pStr)
{
  char* t_ptr;
  char* orig_pStr;
  int t_length, k;
  int lNum, lNeg = 0;
  long int lNumLong;

  orig_pStr = pStr;
  if(*pStr == '#')                                /* decimal */
  {
    pStr++;
    if(*pStr == '-')                                /* dec is negative */
    {
      lNeg = 1;
      pStr++;
    }
    t_ptr = pStr;
    t_length = strlen(t_ptr);
    for(k=0;k < t_length;k++)
    {
      if (!isdigit(*t_ptr))
      {
         printf("Error: invalid decimal operand, %s\n",orig_pStr);
         exit(4);
      }
      t_ptr++;
    }
    lNum = atoi(pStr);
    if(lNeg)
      lNum = -lNum;

    return lNum;
  }
  else if(*pStr == 'x')        /* hex     */
  {
    pStr++;
    if(*pStr == '-')                                /* hex is negative */
    {
      lNeg = 1;
      pStr++;
    }
    t_ptr = pStr;
    t_length = strlen(t_ptr);
    for(k=0;k < t_length;k++)
    {
      if (!isxdigit(*t_ptr))
      {
				 //printf("%s\n", t_ptr);
         printf("Error: invalid hex operand, %s\n",orig_pStr);
         exit(4);
      }
      t_ptr++;
    }
    lNumLong = strtol(pStr, NULL, 16);    /* convert hex string into integer */
    lNum = (lNumLong > INT_MAX)? INT_MAX : lNumLong;
    if(lNeg)
      lNum = -lNum;
    return lNum;
  }
  else
  {
        printf("Error: invalid operand, %s\n", orig_pStr);
        exit(4);  /* This has been changed from error code 3 to error code 4, see clarification 12 */
  }
}

  /*------------------------------------------------binaryStringToHexString----------------------------------------------------*/

char* binaryStringToHexString(char* bStr)
{
	char* hexString;
	hexString[0] = 'x';
	int pt = 0;
	int hpt = 1;
	for(int i=0; i<4; i++)
	{
			if(bStr[pt]==0)
			{
				if(bStr[pt+1]==0)
				{
					if(bStr[pt+2]==0)
					{
						if(bStr[pt+3]==0)
						{
							hexString[hpt]='0'; //0000
						}
						else
						{
							hexString[hpt]='1'; //0001
						}
					}
					else
					{
						if(bStr[pt+3]==0)
						{
							hexString[hpt]='2'; //0010
						}
						else
						{
							hexString[hpt]='3'; //0011
						}
					}
				}
				else
				{
					if(bStr[pt+2]==0)
					{
						if(bStr[pt+3]==0)
						{
							hexString[hpt]='4'; //0100
						}
						else
						{
							hexString[hpt]='5'; //0101
						}
					}
					else
					{
						if(bStr[pt+3]==0)
						{
							hexString[hpt]='6'; //0110
						}
						else
						{
							hexString[hpt]='7'; //0111
						}
					}
				}
			}
			else
			{
				if(bStr[pt+1]==0)
				{
					if(bStr[pt+2]==0)
					{
						if(bStr[pt+3]==0)
						{
							hexString[hpt]='8'; //1000
						}
						else
						{
							hexString[hpt]='9'; //1001
						}
					}
					else
					{
						if(bStr[pt+3]==0)
						{
							hexString[hpt]='A'; //1010
						}
						else
						{
							hexString[hpt]='B'; //1011
						}
					}
				}
				else
				{
					if(bStr[pt+2]==0)
					{
						if(bStr[pt+3]==0)
						{
							hexString[hpt]='C'; //1100
						}
						else
						{
							hexString[hpt]='D'; //1101
						}
					}
					else
					{
						if(bStr[pt+3]==0)
						{
							hexString[hpt]='E'; //1110
						}
						else
						{
							hexString[hpt]='F'; //1111
						}
					}
				}
			}

			pt+=4;
			hpt++;
	}

	return "";
}
