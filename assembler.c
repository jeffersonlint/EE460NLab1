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
int regToInt(char* arg);

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
				//we don't need to worry about this one! we already did what we need to do in the first pass
				if(strcmp(lOpcode, ".orig")==0){/**/}
				// OPCODES THAT STILL NEED TO BE WRITTEN
				// "br", "brn", "brnz", "brnzp", "brz", "brzp", "brp", "brnp",
				// "jsr", "lea"
  /*-------------------------------------------------------ADD--------------------------------------------------------------*/
				else if(strcmp(lOpcode, "add")==0)
				{
					char binInstruction[16] = "0001\0";
					switch(regToInt(lArg1))
					{
						case(0): strncat(binInstruction, "000\0", 4); break;
						case(1): strncat(binInstruction, "001\0", 4); break;
						case(2): strncat(binInstruction, "010\0", 4); break;
						case(3): strncat(binInstruction, "011\0", 4); break;
						case(4): strncat(binInstruction, "100\0", 4); break;
						case(5): strncat(binInstruction, "101\0", 4); break;
						case(6): strncat(binInstruction, "110\0", 4); break;
						case(7): strncat(binInstruction, "111\0", 4); break;
						case(-1): printf("invalid register operand detected; assembly process halted\n"); exit(4);
					}
					switch(regToInt(lArg2))
					{
						case(0): strncat(binInstruction, "000\0", 4); break;
						case(1): strncat(binInstruction, "001\0", 4); break;
						case(2): strncat(binInstruction, "010\0", 4); break;
						case(3): strncat(binInstruction, "011\0", 4); break;
						case(4): strncat(binInstruction, "100\0", 4); break;
						case(5): strncat(binInstruction, "101\0", 4); break;
						case(6): strncat(binInstruction, "110\0", 4); break;
						case(7): strncat(binInstruction, "111\0", 4); break;
						case(-1): printf("invalid register operand detected; assembly process halted\n"); exit(4);
					}
					//immediate mode
					if(lArg3[0]=='x' || lArg3[0]=='#')
					{
						int imm5 = toNum(lArg3);
						if(imm5>15 || imm5<-16) {printf("invalid constant detected, assembly process halted"); exit(3);}
						strcat(binInstruction, "1");
						for(int i=0; i<5; i++)
						{
							int imm5shift = imm5>>(4-i);
							if(imm5shift&1==1) {strcat(binInstruction, "1");}
							else  {strcat(binInstruction, "0");}
						}
					}
					//register mode
					else
					{
						strcat(binInstruction, "000");

						switch(regToInt(lArg3))
						{
							case(0): strncat(binInstruction, "000\0", 4); break;
							case(1): strncat(binInstruction, "001\0", 4); break;
							case(2): strncat(binInstruction, "010\0", 4); break;
							case(3): strncat(binInstruction, "011\0", 4); break;
							case(4): strncat(binInstruction, "100\0", 4); break;
							case(5): strncat(binInstruction, "101\0", 4); break;
							case(6): strncat(binInstruction, "110\0", 4); break;
							case(7): strncat(binInstruction, "111\0", 4); break;
							case(-1): printf("invalid register operand detected; assembly process halted\n"); exit(4);
						}

					}
					char* hexInstruction = binaryStringToHexString(binInstruction);
					fprintf(outFile, "%s\n", hexInstruction);
				}
/*-------------------------------------------------------AND--------------------------------------------------------------*/
				else if(strcmp(lOpcode, "and")==0)
				{
					char binInstruction[16] = "0101\0";
					switch(regToInt(lArg1))
					{
						case(0): strncat(binInstruction, "000\0", 4); break;
						case(1): strncat(binInstruction, "001\0", 4); break;
						case(2): strncat(binInstruction, "010\0", 4); break;
						case(3): strncat(binInstruction, "011\0", 4); break;
						case(4): strncat(binInstruction, "100\0", 4); break;
						case(5): strncat(binInstruction, "101\0", 4); break;
						case(6): strncat(binInstruction, "110\0", 4); break;
						case(7): strncat(binInstruction, "111\0", 4); break;
						case(-1): printf("invalid register operand detected; assembly process halted\n"); exit(4);
					}
					switch(regToInt(lArg2))
					{
						case(0): strncat(binInstruction, "000\0", 4); break;
						case(1): strncat(binInstruction, "001\0", 4); break;
						case(2): strncat(binInstruction, "010\0", 4); break;
						case(3): strncat(binInstruction, "011\0", 4); break;
						case(4): strncat(binInstruction, "100\0", 4); break;
						case(5): strncat(binInstruction, "101\0", 4); break;
						case(6): strncat(binInstruction, "110\0", 4); break;
						case(7): strncat(binInstruction, "111\0", 4); break;
						case(-1): printf("invalid register operand detected; assembly process halted\n"); exit(4);
					}
					//immediate mode
					if(lArg3[0]=='x' || lArg3[0]=='#')
					{
						int imm5 = toNum(lArg3);
						if(imm5>15 || imm5<-16) {printf("invalid constant detected, assembly process halted"); exit(3);}
						strcat(binInstruction, "1");
						for(int i=0; i<5; i++)
						{
							int imm5shift = imm5>>(4-i);
							if(imm5shift&1==1) {strcat(binInstruction, "1");}
							else  {strcat(binInstruction, "0");}
						}
					}
					//register mode
					else
					{
						strcat(binInstruction, "000");

						switch(regToInt(lArg3))
						{
							case(0): strncat(binInstruction, "000\0", 4); break;
							case(1): strncat(binInstruction, "001\0", 4); break;
							case(2): strncat(binInstruction, "010\0", 4); break;
							case(3): strncat(binInstruction, "011\0", 4); break;
							case(4): strncat(binInstruction, "100\0", 4); break;
							case(5): strncat(binInstruction, "101\0", 4); break;
							case(6): strncat(binInstruction, "110\0", 4); break;
							case(7): strncat(binInstruction, "111\0", 4); break;
							case(-1): printf("invalid register operand detected; assembly process halted\n"); exit(4);
						}

					}
					char* hexInstruction = binaryStringToHexString(binInstruction);
					fprintf(outFile, "%s\n", hexInstruction);
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
	/*------------------------------------------------HALT----------------------------------------------------*/
				else if(strcmp(lOpcode, "halt")==0)
				{
					fprintf(outFile, "xF025\n");
				}
	/*------------------------------------------------JMP----------------------------------------------------*/
				else if(strcmp(lOpcode, "jmp")==0)
				{
					char binInstruction[16] = "1100000\0";
					switch(regToInt(lArg1))
					{
						case(0): strncat(binInstruction, "000\0", 4); break;
						case(1): strncat(binInstruction, "001\0", 4); break;
						case(2): strncat(binInstruction, "010\0", 4); break;
						case(3): strncat(binInstruction, "011\0", 4); break;
						case(4): strncat(binInstruction, "100\0", 4); break;
						case(5): strncat(binInstruction, "101\0", 4); break;
						case(6): strncat(binInstruction, "110\0", 4); break;
						case(7): strncat(binInstruction, "111\0", 4); break;
						case(-1): printf("invalid register operand detected; assembly process halted\n"); exit(4);
					}
					strcat(binInstruction, "000000");
					char* hexInstruction = binaryStringToHexString(binInstruction);
					fprintf(outFile, "%s\n", hexInstruction);
				}
				else if(strcmp(lOpcode, "jsr")==0)
				{
					fprintf(outFile, "need to do this opcode!\n");
				}
	/*------------------------------------------------JSRR----------------------------------------------------*/
				else if(strcmp(lOpcode, "jsrr")==0)
				{
					char binInstruction[16] = "0100000\0";
					switch(regToInt(lArg1))
					{
						case(0): strncat(binInstruction, "000\0", 4); break;
						case(1): strncat(binInstruction, "001\0", 4); break;
						case(2): strncat(binInstruction, "010\0", 4); break;
						case(3): strncat(binInstruction, "011\0", 4); break;
						case(4): strncat(binInstruction, "100\0", 4); break;
						case(5): strncat(binInstruction, "101\0", 4); break;
						case(6): strncat(binInstruction, "110\0", 4); break;
						case(7): strncat(binInstruction, "111\0", 4); break;
						case(-1): printf("invalid register operand detected; assembly process halted\n"); exit(4);
					}
					strcat(binInstruction, "000000");
					char* hexInstruction = binaryStringToHexString(binInstruction);
					fprintf(outFile, "%s\n", hexInstruction);
				}
	/*------------------------------------------------LDB----------------------------------------------------*/
				else if(strcmp(lOpcode, "ldb")==0)
				{
					char binInstruction[16] = "0010\0";

					switch(regToInt(lArg1)){
						case(0): strncat(binInstruction, "000\0", 4); break;
						case(1): strncat(binInstruction, "001\0", 4); break;
						case(2): strncat(binInstruction, "010\0", 4); break;
						case(3): strncat(binInstruction, "011\0", 4); break;
						case(4): strncat(binInstruction, "100\0", 4); break;
						case(5): strncat(binInstruction, "101\0", 4); break;
						case(6): strncat(binInstruction, "110\0", 4); break;
						case(7): strncat(binInstruction, "111\0", 4); break;
						case(-1): printf("invalid register operand detected\n"); exit(4);
					}
					switch(regToInt(lArg2)){
						case(0): strncat(binInstruction, "000\0", 4); break;
						case(1): strncat(binInstruction, "001\0", 4); break;
						case(2): strncat(binInstruction, "010\0", 4); break;
						case(3): strncat(binInstruction, "011\0", 4); break;
						case(4): strncat(binInstruction, "100\0", 4); break;
						case(5): strncat(binInstruction, "101\0", 4); break;
						case(6): strncat(binInstruction, "110\0", 4); break;
						case(7): strncat(binInstruction, "111\0", 4); break;
						case(-1): printf("invalid register operand detected\n"); exit(4);
					}

					//Get offset
					//Immediate
					if(lArg3[0] == 'x' || lArg3[0] == '#'){
						int offset6 = toNum(lArg3);
						if(offset6 > 31 || offset6 < -32){
							printf("Invalid constant detected\n");
							exit(3);
						}
						for(int i = 0; i < 6; i++){				//Copy offset
							int shift = offset6>>(5-i);
							if(shift&1 == 1) strcat(binInstruction, "1");
							else strcat(binInstruction, "0");
						}
					}

					char* hexInstruction = binaryStringToHexString(binInstruction);
					fprintf(outFile, "%s\n", hexInstruction);
				}
	/*------------------------------------------------LDW----------------------------------------------------*/
				else if(strcmp(lOpcode, "ldw")==0)
				{
					char binInstruction[16] = "0110\0";

					switch(regToInt(lArg1)){
						case(0): strncat(binInstruction, "000\0", 4); break;
						case(1): strncat(binInstruction, "001\0", 4); break;
						case(2): strncat(binInstruction, "010\0", 4); break;
						case(3): strncat(binInstruction, "011\0", 4); break;
						case(4): strncat(binInstruction, "100\0", 4); break;
						case(5): strncat(binInstruction, "101\0", 4); break;
						case(6): strncat(binInstruction, "110\0", 4); break;
						case(7): strncat(binInstruction, "111\0", 4); break;
						case(-1): printf("invalid register operand detected\n"); exit(4);
					}
					switch(regToInt(lArg2)){
						case(0): strncat(binInstruction, "000\0", 4); break;
						case(1): strncat(binInstruction, "001\0", 4); break;
						case(2): strncat(binInstruction, "010\0", 4); break;
						case(3): strncat(binInstruction, "011\0", 4); break;
						case(4): strncat(binInstruction, "100\0", 4); break;
						case(5): strncat(binInstruction, "101\0", 4); break;
						case(6): strncat(binInstruction, "110\0", 4); break;
						case(7): strncat(binInstruction, "111\0", 4); break;
						case(-1): printf("invalid register operand detected\n"); exit(4);
					}
					//Get offset
					//Immediate
					if(lArg3[0] == 'x' || lArg3[0] == '#'){
						int offset6 = toNum(lArg3);
						if(offset6 > 31 || offset6 < -32){
							printf("Invalid constant detected\n");
							exit(3);
						}
						for(int i = 0; i < 6; i++){				//Copy offset
							int shift = offset6>>(5-i);
							if(shift&1 == 1) strcat(binInstruction, "1");
							else strcat(binInstruction, "0");
						}
					}

					char* hexInstruction = binaryStringToHexString(binInstruction);
					fprintf(outFile, "%s\n", hexInstruction);
				}
				else if(strcmp(lOpcode, "lea")==0)
				{
					fprintf(outFile, "need to do this opcode!\n");
				}
	/*------------------------------------------------NOP----------------------------------------------------*/
				else if(strcmp(lOpcode, "nop")==0)
				{
					fprintf(outFile, "x0000\n");
				}
	/*------------------------------------------------NOT----------------------------------------------------*/
				else if(strcmp(lOpcode, "not")==0)
				{
					char binInstruction[16] = "1001\0";

					switch(regToInt(lArg1)){
						case(0): strncat(binInstruction, "000\0", 4); break;
						case(1): strncat(binInstruction, "001\0", 4); break;
						case(2): strncat(binInstruction, "010\0", 4); break;
						case(3): strncat(binInstruction, "011\0", 4); break;
						case(4): strncat(binInstruction, "100\0", 4); break;
						case(5): strncat(binInstruction, "101\0", 4); break;
						case(6): strncat(binInstruction, "110\0", 4); break;
						case(7): strncat(binInstruction, "111\0", 4); break;
						case(-1): printf("invalid register operand detected\n"); exit(4);
					}
					switch(regToInt(lArg2)){
						case(0): strncat(binInstruction, "000\0", 4); break;
						case(1): strncat(binInstruction, "001\0", 4); break;
						case(2): strncat(binInstruction, "010\0", 4); break;
						case(3): strncat(binInstruction, "011\0", 4); break;
						case(4): strncat(binInstruction, "100\0", 4); break;
						case(5): strncat(binInstruction, "101\0", 4); break;
						case(6): strncat(binInstruction, "110\0", 4); break;
						case(7): strncat(binInstruction, "111\0", 4); break;
						case(-1): printf("invalid register operand detected\n"); exit(4);
					}
					strcat(binInstruction, "111111");
					char* hexInstruction = binaryStringToHexString(binInstruction);
					fprintf(outFile, "%s\n", hexInstruction);
				}
	/*------------------------------------------------RET----------------------------------------------------*/
				else if(strcmp(lOpcode, "ret")==0)
				{
					fprintf(outFile, "xC1C0\n");
				}
	/*------------------------------------------------LSHF----------------------------------------------------*/
				else if(strcmp(lOpcode, "lshf")==0)
				{
					char binInstruction[16] = "1101\0";
					switch(regToInt(lArg1)){
						case(0): strncat(binInstruction, "000\0", 4); break;
						case(1): strncat(binInstruction, "001\0", 4); break;
						case(2): strncat(binInstruction, "010\0", 4); break;
						case(3): strncat(binInstruction, "011\0", 4); break;
						case(4): strncat(binInstruction, "100\0", 4); break;
						case(5): strncat(binInstruction, "101\0", 4); break;
						case(6): strncat(binInstruction, "110\0", 4); break;
						case(7): strncat(binInstruction, "111\0", 4); break;
						case(-1): printf("invalid register operand detected\n"); exit(4);
					}
					switch(regToInt(lArg2)){
						case(0): strncat(binInstruction, "000\0", 4); break;
						case(1): strncat(binInstruction, "001\0", 4); break;
						case(2): strncat(binInstruction, "010\0", 4); break;
						case(3): strncat(binInstruction, "011\0", 4); break;
						case(4): strncat(binInstruction, "100\0", 4); break;
						case(5): strncat(binInstruction, "101\0", 4); break;
						case(6): strncat(binInstruction, "110\0", 4); break;
						case(7): strncat(binInstruction, "111\0", 4); break;
						case(-1): printf("invalid register operand detected\n"); exit(4);
					}
					if(lArg3[0]=='x' || lArg3[0]=='#')
					{
						int imm4 = toNum(lArg3);
						if(imm4>15 || imm4<0) {printf("invalid constant detected, assembly process halted"); exit(3);}
						strcat(binInstruction, "00");
						for(int i=0; i<4; i++)
						{
							int imm4shift = imm4>>(3-i);
							if(imm4shift&1==1) {strcat(binInstruction, "1");}
							else  {strcat(binInstruction, "0");}
						}
					}
					char* hexInstruction = binaryStringToHexString(binInstruction);
					fprintf(outFile, "%s\n", hexInstruction);
				}
	/*------------------------------------------------RSHFL----------------------------------------------------*/
				else if(strcmp(lOpcode, "rshfl")==0)
				{
					char binInstruction[16] = "1101\0";
					switch(regToInt(lArg1)){
						case(0): strncat(binInstruction, "000\0", 4); break;
						case(1): strncat(binInstruction, "001\0", 4); break;
						case(2): strncat(binInstruction, "010\0", 4); break;
						case(3): strncat(binInstruction, "011\0", 4); break;
						case(4): strncat(binInstruction, "100\0", 4); break;
						case(5): strncat(binInstruction, "101\0", 4); break;
						case(6): strncat(binInstruction, "110\0", 4); break;
						case(7): strncat(binInstruction, "111\0", 4); break;
						case(-1): printf("invalid register operand detected\n"); exit(4);
					}
					switch(regToInt(lArg2)){
						case(0): strncat(binInstruction, "000\0", 4); break;
						case(1): strncat(binInstruction, "001\0", 4); break;
						case(2): strncat(binInstruction, "010\0", 4); break;
						case(3): strncat(binInstruction, "011\0", 4); break;
						case(4): strncat(binInstruction, "100\0", 4); break;
						case(5): strncat(binInstruction, "101\0", 4); break;
						case(6): strncat(binInstruction, "110\0", 4); break;
						case(7): strncat(binInstruction, "111\0", 4); break;
						case(-1): printf("invalid register operand detected\n"); exit(4);
					}
					if(lArg3[0]=='x' || lArg3[0]=='#')
					{
						int imm4 = toNum(lArg3);
						if(imm4>15 || imm4<0) {printf("invalid constant detected, assembly process halted"); exit(3);}
						strcat(binInstruction, "01");
						for(int i=0; i<4; i++)
						{
							int imm4shift = imm4>>(3-i);
							if(imm4shift&1==1) {strcat(binInstruction, "1");}
							else  {strcat(binInstruction, "0");}
						}
					}
					char* hexInstruction = binaryStringToHexString(binInstruction);
					fprintf(outFile, "%s\n", hexInstruction);
				}
	/*------------------------------------------------RSHFA----------------------------------------------------*/
				else if(strcmp(lOpcode, "rshfa")==0)
				{
					char binInstruction[16] = "1101\0";
					switch(regToInt(lArg1)){
						case(0): strncat(binInstruction, "000\0", 4); break;
						case(1): strncat(binInstruction, "001\0", 4); break;
						case(2): strncat(binInstruction, "010\0", 4); break;
						case(3): strncat(binInstruction, "011\0", 4); break;
						case(4): strncat(binInstruction, "100\0", 4); break;
						case(5): strncat(binInstruction, "101\0", 4); break;
						case(6): strncat(binInstruction, "110\0", 4); break;
						case(7): strncat(binInstruction, "111\0", 4); break;
						case(-1): printf("invalid register operand detected\n"); exit(4);
					}
					switch(regToInt(lArg2)){
						case(0): strncat(binInstruction, "000\0", 4); break;
						case(1): strncat(binInstruction, "001\0", 4); break;
						case(2): strncat(binInstruction, "010\0", 4); break;
						case(3): strncat(binInstruction, "011\0", 4); break;
						case(4): strncat(binInstruction, "100\0", 4); break;
						case(5): strncat(binInstruction, "101\0", 4); break;
						case(6): strncat(binInstruction, "110\0", 4); break;
						case(7): strncat(binInstruction, "111\0", 4); break;
						case(-1): printf("invalid register operand detected\n"); exit(4);
					}
					if(lArg3[0]=='x' || lArg3[0]=='#')
					{
						int imm4 = toNum(lArg3);
						if(imm4>15 || imm4<0) {printf("invalid constant detected, assembly process halted"); exit(3);}
						strcat(binInstruction, "11");
						for(int i=0; i<4; i++)
						{
							int imm4shift = imm4>>(3-i);
							if(imm4shift&1==1) {strcat(binInstruction, "1");}
							else  {strcat(binInstruction, "0");}
						}
					}
					char* hexInstruction = binaryStringToHexString(binInstruction);
					fprintf(outFile, "%s\n", hexInstruction);
					}
	/*------------------------------------------------RTI----------------------------------------------------*/
				else if(strcmp(lOpcode, "rti")==0)
				{
					fprintf(outFile, "x8000\n");
				}
	/*------------------------------------------------STB----------------------------------------------------*/

				else if(strcmp(lOpcode, "stb")==0)
				{
					char binInstruction[16] = "0011\0";
					switch(regToInt(lArg1)){
						case(0): strncat(binInstruction, "000\0", 4); break;
						case(1): strncat(binInstruction, "001\0", 4); break;
						case(2): strncat(binInstruction, "010\0", 4); break;
						case(3): strncat(binInstruction, "011\0", 4); break;
						case(4): strncat(binInstruction, "100\0", 4); break;
						case(5): strncat(binInstruction, "101\0", 4); break;
						case(6): strncat(binInstruction, "110\0", 4); break;
						case(7): strncat(binInstruction, "111\0", 4); break;
						case(-1): printf("invalid register operand detected\n"); exit(4);
					}
					switch(regToInt(lArg2)){
						case(0): strncat(binInstruction, "000\0", 4); break;
						case(1): strncat(binInstruction, "001\0", 4); break;
						case(2): strncat(binInstruction, "010\0", 4); break;
						case(3): strncat(binInstruction, "011\0", 4); break;
						case(4): strncat(binInstruction, "100\0", 4); break;
						case(5): strncat(binInstruction, "101\0", 4); break;
						case(6): strncat(binInstruction, "110\0", 4); break;
						case(7): strncat(binInstruction, "111\0", 4); break;
						case(-1): printf("invalid register operand detected\n"); exit(4);
					}
					//Get offset
					//Immediate
					if(lArg3[0] == 'x' || lArg3[0] == '#'){
						int offset6 = toNum(lArg3);
						if(offset6 > 31 || offset6 < -32){
							printf("Invalid constant detected\n");
							exit(3);
						}
						for(int i = 0; i < 6; i++){				//Copy offset
							int shift = offset6>>(5-i);
							if(shift&1 == 1) strcat(binInstruction, "1");
							else strcat(binInstruction, "0");
						}
					}
					char* hexInstruction = binaryStringToHexString(binInstruction);
					fprintf(outFile, "%s\n", hexInstruction);
				}
	/*------------------------------------------------STW----------------------------------------------------*/
				else if(strcmp(lOpcode, "stw")==0)
				{
					char binInstruction[16] = "0111\0";
					switch(regToInt(lArg1)){
						case(0): strncat(binInstruction, "000\0", 4); break;
						case(1): strncat(binInstruction, "001\0", 4); break;
						case(2): strncat(binInstruction, "010\0", 4); break;
						case(3): strncat(binInstruction, "011\0", 4); break;
						case(4): strncat(binInstruction, "100\0", 4); break;
						case(5): strncat(binInstruction, "101\0", 4); break;
						case(6): strncat(binInstruction, "110\0", 4); break;
						case(7): strncat(binInstruction, "111\0", 4); break;
						case(-1): printf("invalid register operand detected\n"); exit(4);
					}
					switch(regToInt(lArg2)){
						case(0): strncat(binInstruction, "000\0", 4); break;
						case(1): strncat(binInstruction, "001\0", 4); break;
						case(2): strncat(binInstruction, "010\0", 4); break;
						case(3): strncat(binInstruction, "011\0", 4); break;
						case(4): strncat(binInstruction, "100\0", 4); break;
						case(5): strncat(binInstruction, "101\0", 4); break;
						case(6): strncat(binInstruction, "110\0", 4); break;
						case(7): strncat(binInstruction, "111\0", 4); break;
						case(-1): printf("invalid register operand detected\n"); exit(4);
					}
					//Get offset
					//Immediate
					if(lArg3[0] == 'x' || lArg3[0] == '#'){
						int offset6 = toNum(lArg3);
						if(offset6 > 31 || offset6 < -32){
							printf("Invalid constant detected\n");
							exit(3);
						}
						for(int i = 0; i < 6; i++){				//Copy offset
							int shift = offset6>>(5-i);
							if(shift&1 == 1) strcat(binInstruction, "1");
							else strcat(binInstruction, "0");
						}
					}
					char* hexInstruction = binaryStringToHexString(binInstruction);
					fprintf(outFile, "%s\n", hexInstruction);
				}
	/*------------------------------------------------TRAP----------------------------------------------------*/
				else if(strcmp(lOpcode, "trap")==0)
				{
					char binInstruction[16] = "11110000\0";
					if(lArg1[0]=='x')
					{
						int vector = toNum(lArg1);
						for(int i=0; i<8; i++)
						{
							int vectorShift = vector>>(7-i);
							if(vectorShift&1==1) strcat(binInstruction, "1");
							else strcat(binInstruction, "0");
						}
					}
					else
					{
						printf("Invalid constant; needs to be hex");
						exit(3);
					}

					char* hexInstruction = binaryStringToHexString(binInstruction);
					fprintf(outFile, "%s\n", hexInstruction);
				}
	/*------------------------------------------------XOR----------------------------------------------------*/
				else if(strcmp(lOpcode, "xor")==0)
				{
					char binInstruction[16] = "1001\0";
					switch(regToInt(lArg1))
					{
						case(0): strncat(binInstruction, "000\0", 4); break;
						case(1): strncat(binInstruction, "001\0", 4); break;
						case(2): strncat(binInstruction, "010\0", 4); break;
						case(3): strncat(binInstruction, "011\0", 4); break;
						case(4): strncat(binInstruction, "100\0", 4); break;
						case(5): strncat(binInstruction, "101\0", 4); break;
						case(6): strncat(binInstruction, "110\0", 4); break;
						case(7): strncat(binInstruction, "111\0", 4); break;
						case(-1): printf("invalid register operand detected; assembly process halted\n"); exit(4);
					}
					switch(regToInt(lArg2))
					{
						case(0): strncat(binInstruction, "000\0", 4); break;
						case(1): strncat(binInstruction, "001\0", 4); break;
						case(2): strncat(binInstruction, "010\0", 4); break;
						case(3): strncat(binInstruction, "011\0", 4); break;
						case(4): strncat(binInstruction, "100\0", 4); break;
						case(5): strncat(binInstruction, "101\0", 4); break;
						case(6): strncat(binInstruction, "110\0", 4); break;
						case(7): strncat(binInstruction, "111\0", 4); break;
						case(-1): printf("invalid register operand detected; assembly process halted\n"); exit(4);
					}
					//immediate mode
					if(lArg3[0]=='x' || lArg3[0]=='#')
					{
						int imm5 = toNum(lArg3);
						if(imm5>15 || imm5<-16) {printf("invalid constant detected, assembly process halted"); exit(3);}
						strcat(binInstruction, "1");
						for(int i=0; i<5; i++)
						{
							int imm5shift = imm5>>(4-i);
							if(imm5shift&1==1) {strcat(binInstruction, "1");}
							else  {strcat(binInstruction, "0");}
						}
					}
					//register mode
					else
					{
						strcat(binInstruction, "000");

						switch(regToInt(lArg3))
						{
							case(0): strncat(binInstruction, "000\0", 4); break;
							case(1): strncat(binInstruction, "001\0", 4); break;
							case(2): strncat(binInstruction, "010\0", 4); break;
							case(3): strncat(binInstruction, "011\0", 4); break;
							case(4): strncat(binInstruction, "100\0", 4); break;
							case(5): strncat(binInstruction, "101\0", 4); break;
							case(6): strncat(binInstruction, "110\0", 4); break;
							case(7): strncat(binInstruction, "111\0", 4); break;
							case(-1): printf("invalid register operand detected; assembly process halted\n"); exit(4);
						}

					}
					char* hexInstruction = binaryStringToHexString(binInstruction);
					fprintf(outFile, "%s\n", hexInstruction);
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
	char hexString[5] = "x\0";
	int pt = 0;
	int hpt = 1;
	for(int i=0; i<4; i++)
	{
			if(bStr[pt]=='0')
			{
				if(bStr[pt+1]=='0')
				{
					if(bStr[pt+2]=='0')
					{
						if(bStr[pt+3]=='0')
						{
							strncat(hexString, "0\0", 2); //0000
						}
						else
						{
							strncat(hexString, "1\0", 2); //0001
						}
					}
					else
					{
						if(bStr[pt+3]=='0')
						{
							strncat(hexString, "2\0", 2); //0010
						}
						else
						{
							strncat(hexString, "3\0", 2); //0011
						}
					}
				}
				else
				{
					if(bStr[pt+2]=='0')
					{
						if(bStr[pt+3]=='0')
						{
							strncat(hexString, "4\0", 2); //0100
						}
						else
						{
							strncat(hexString, "5\0", 2); //0101
						}
					}
					else
					{
						if(bStr[pt+3]=='0')
						{
							strncat(hexString, "6\0", 2); //0110
						}
						else
						{
							strncat(hexString, "7\0", 2); //0111
						}
					}
				}
			}
			else
			{
				if(bStr[pt+1]=='0')
				{
					if(bStr[pt+2]=='0')
					{
						if(bStr[pt+3]=='0')
						{
							strncat(hexString, "8\0", 2); //1000
						}
						else
						{
							strncat(hexString, "9\0", 2); //1001
						}
					}
					else
					{
						if(bStr[pt+3]=='0')
						{
							strncat(hexString, "A\0", 2); //1010
						}
						else
						{
							strncat(hexString, "B\0", 2); //1011
						}
					}
				}
				else
				{
					if(bStr[pt+2]=='0')
					{
						if(bStr[pt+3]=='0')
						{
							strncat(hexString, "C\0", 2); //1100
						}
						else
						{
							strncat(hexString, "D\0", 2); //1101
						}
					}
					else
					{
						if(bStr[pt+3]=='0')
						{
							strncat(hexString, "E\0", 2); //1110
						}
						else
						{
							strncat(hexString, "F\0", 2); //1111
						}
					}
				}
			}
			pt+=4;
			hpt++;
	}
	char* hexPt = hexString;
	return hexPt;
}

  /*------------------------------------------------binaryStringToHexString----------------------------------------------------*/

int regToInt(char* arg)
{
	if(strcmp(arg, "r0")==0) return 0;
	else if(strcmp(arg, "r1")==0) return 1;
	else if(strcmp(arg, "r2")==0) return 2;
	else if(strcmp(arg, "r3")==0) return 3;
	else if(strcmp(arg, "r4")==0) return 4;
	else if(strcmp(arg, "r5")==0) return 5;
	else if(strcmp(arg, "r6")==0) return 6;
	else if(strcmp(arg, "r7")==0) return 7;
	else return -1;
}
