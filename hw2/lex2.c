/*
Author: Andre Hebra
Homework 2: Lexical Analyzer
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


//define the reserved words
char reserved[14][10] = {"const", "var", "procedure", "call", "begin", "end", "if", "fi", "then", "else", "while", "do", "read", "write"};

//define the special symbols
char special[13][1] = {"+", "-", "*", "/", "(", ")", "=", "," , ".", "<", ">", ";" , ":"};

typedef struct ident {
    char name[12];
    char value[6];
} ident;

typedef enum {
    skipsym = 1, identsym = 2, numbersym = 3, plussym = 4, minussym = 5,
    multsym = 6, slashsym = 7, fisym = 8, eqlsym = 9, neqsym = 10, lessym = 11, leqsym = 12, 
    gtrsym = 13, geqsym = 14, lparentsym = 15, rparentsym = 16, commasym = 17,
    semicolonsym = 18, periodsym = 19, becomessym = 20,
    beginsym = 21, endsym = 22, ifsym = 23, thensym = 24, whilesym = 25, dosym = 26,
    callsym = 27, constsym = 28, varsym = 29, procsym = 30, writesym = 31,
    readsym = 32, elsesym = 33
} token_type;

char* findSymbol(char* line) {
    if (line[0] == '=' || line[0] == '+' || line[0] == '-' || line[0] == '*' || line[0] == '/' || line[0] == '(' || line[0] == ')' || line[0] == ',' || line[0] == '.' || line[0] == '<'|| line[0] == '>' || line[0] == ';' || line[0] == ':') {
        
        //printf("%s", (char[2]) {line[0], '\0'});
        return (char[2]) {line[0], '\0'};
    }

    return "NEG";
}

char* getReserved(char* line, char* returnWord) {
    for (int i = 0; i < 14; i++) {
        int requiredCount = strlen(reserved[i]);
        int count = 0;
        for (int j = 0; j < requiredCount; j++) {
            if (line[i] == reserved[i]) {
                count++;
            }
        }

        if (count == requiredCount) {
            return reserved[i];
        }
    }

    return "NEG";
}

char* compareIdents(char* bigList, ident* wordList, int wordLength) {
    for (int i = 0; i < wordLength; i++) {
        int requiredCount = strlen(wordList[i].name);
        int count = 0;
        for (int j = 0; j < strlen(wordList[i].name); j++) {
            if (wordList[i].name[j] == bigList[j]) {
                count++;
            }
        }

        if (count == requiredCount) {
            return wordList[i].name;
        }

        count = 0;
    }

    return "NEG";
}

char* getDigits(char* word, char* returnWord) {
    int position = 0;
    while (word[position] == '0' ||word[position] == '1' ||word[position] == '2' ||word[position] == '3' ||word[position] == '4' ||word[position] == '5' ||word[position] == '6' ||word[position] == '7' ||word[position] == '8' ||word[position] == '9') {
        strcat(returnWord, (char[2]) {word[position], '\0'});
        position++;
    }

    return returnWord;
}

// removes whitespace, tabs, and new line characters from the string passed to it utilizing recursion
char* removeWhiteSpace(char* line) {
    int currentLineSize = strlen(line);
    for (int j = 0; j < currentLineSize; j++) {
        if (line[j] == ' ' || line[j] == '\t' || line[j] == '\n') {
            for (int k = j; k < currentLineSize; k++) {
                line[k] = line[k+1];
            }
            return removeWhiteSpace(line);
        }
    }

    return line;
}

char* removeWord(char* line, char* word) {
    /*int wordLength = strlen(word);
    int count = 0;
    for (int i = 0; i < strlen(line); i++) {
         for (int j = 0; j < wordLength; j++) {
            if (i+j < strlen(line) && line[i+j] == line[j]) {
                count++;
            }
         }

         if (count == wordLength) {
            for (int k = i; k < strlen(line); k++) {
                line[k] = line[k+wordLength];
            }
            
         }
         count = 0;
         return line;
    }*/
    
    for (int i = 0; i < strlen(line); i++) {
        line[i] = line[i + strlen(word)];
    }

    return line;
}

// find reserved word in the given string
char* findReserved(char* line) {
    int requiredCount = 0;
    int count = 0;

    for (int i = 0; i < 14; i++) {
        requiredCount = strlen(reserved[i]);
        count = 0;
        for (int j = 0; j < strlen(reserved[i]); j++) {
            if (reserved[i][j] == line[j]) {
                count++;
            }
        }

        if (count == requiredCount) {
            return reserved[i];
        }
    }

    return "NEG";    
}

int isNumber(char* line) {
    char first = line[0];
    if (first == '0' || first == '1' || first == '2' || first == '3' || first == '4' || first == '5' || first == '6' || first == '7' || first == '8' || first == '9') {
        return 1;
    }

    return 0;
}

void getNumber(char* line, char* returnNumber) {
    int i = 0;
    while (line[i] == '0' || line[i] == '1' || line[i] == '2' || line[i] == '3' || line[i] == '4' || line[i] == '5' || line[i] == '6' || line[i] == '7' || line[i] == '8' || line[i] == '9') {
        strcat(returnNumber, (char[2]) {line[i], '\0'});
        i++;
    }

    if (strlen(returnNumber) > 5) {
        printf("\n\n ERROR: NUMBER TOO LONG\n\n");
    }

    return;
}

void getVar(char* line, char* returnString) {
    
    char currentLine[500];
    strcpy(currentLine, line);

    if (isalpha(currentLine[0]) == 0) {
        return;
    }
    if (strcmp(findSymbol(currentLine), "NEG") != 0) {
        return;
    }
    if (strcmp(findReserved(currentLine), "NEG") != 0) {
        return;
    }
    if (isNumber(currentLine) == 1) {
        return;
    }

    strcat(returnString, (char[2]) {currentLine[0], '\0'});
    for (int i = 0; i < 499; i++) {
        currentLine[i] = currentLine[i+1];
    }

    getVar(currentLine, returnString);

    return;

    
}

int main(int argc, char *argv[]) {
    //read in file line by line
    char lineByLine[500][200];
    int lineCount = 0;

    char line[5000];
    FILE* fp = fopen(argv[1], "r");
    while (fgets(line, sizeof(line), fp)) {
        strcpy(lineByLine[lineCount], line);
        lineCount++;
    }

    fclose(fp);

    //print out the source program
    printf("Source Program:\n");
    for (int i = 0; i < lineCount; i++) {
        printf("%s", lineByLine[i]);
    }

    //create a token list to be printed later
    char tokenList[1000][200];
    int tokenPosition = 0;

    //create a list of variables
    ident identList[1000];
    int identPosition = 0;


    printf("\n\nLexeme Table:\n\nlexeme token type\n");

    // remove comments
    // this works by noting the beginning position of the comment and then replaces each character between slashes with witespace. This allows for the progam to remove it later when the removewhitespace function is called on the line
    for (int i = 0; i < lineCount; i++) {
        int currentLineSize = strlen(lineByLine[i]);
        int commentFlag = 0;
        int commentStartPosition;
        int commentEndPosition;
        for (int j = 0; j < currentLineSize; j++) {
            if (commentFlag == 0 && lineByLine[i][j] == '/') {
                if (j + 1 < currentLineSize && lineByLine[i][j+1] == '*') {
                    commentStartPosition = j;
                    commentFlag = 1;
                }
            }

            if (commentFlag == 1 && lineByLine[i][j] == '*') {
                if (j + 1 < currentLineSize && lineByLine[i][j+1] == '/') {
                    commentEndPosition = j+1;
                }
            }
        }

        if (commentFlag == 1) {
            for (int k = commentStartPosition; k <= commentEndPosition; k++) {
                lineByLine[i][k] = ' ';
            }
        }

    }
    
    

    // remove whitespace and unwanted characters
    for (int i = 0; i < lineCount; i++) {
        strcpy(lineByLine[i], removeWhiteSpace(lineByLine[i]));
    }
    
    
    
    
    
    char varString[500];
    char numberString[500];
    char currentWord[20];

    for (int i = 0; i < lineCount; i++) {
        

        while (strlen(lineByLine[i]) > 1) {
        
          
            
            
            //printf("\ncurrent line:%s", lineByLine[i]);
            
            int caught = 0;

            //printf("%s", lineByLine[i]);
            // check for special symbols
            for (int i = 0; i < 20; i++) {
              currentWord[i] = '\0';
            }
            strcpy(currentWord, findSymbol(lineByLine[i]));
            // remove special symols if found and add them to the token list and print it
            if (strcmp(currentWord, "NEG") != 0) {
                caught = 1;

                switch(currentWord[0]) {
                    case '+':
                        removeWord(lineByLine[i], (char[2]) { '+', '\0' });
                        strcpy(tokenList[tokenPosition++], "4");
                        printf("\n%-10s 4", "+\0");
                        break;
                    case ',':
                        removeWord(lineByLine[i], (char[2]) { ',', '\0' });
                        strcpy(tokenList[tokenPosition++], "17");
                        printf("\n%-10s 17", ",\0");
                        break;
                    case '.':
                        removeWord(lineByLine[i], (char[2]) { '.', '\0' });
                        strcpy(tokenList[tokenPosition++], "19");
                        printf("\n%-10s 19", ".\0");
                        break;
                    case '-':
                        removeWord(lineByLine[i], (char[2]) { '-', '\0' });
                        strcpy(tokenList[tokenPosition++], "5");
                        printf("\n%-10s 5", "-\0");
                        break;
                    case '*':
                        removeWord(lineByLine[i], (char[2]) { '*', '\0' });
                        strcpy(tokenList[tokenPosition++], "6");
                        printf("\n%-10s 6", "*\0");
                        break;
                    case '/':
                        removeWord(lineByLine[i], (char[2]) { '/', '\0' });
                        strcpy(tokenList[tokenPosition++], "7");
                        printf("\n%-10s 7", "/\0");
                        break;
                    case '(':
                        removeWord(lineByLine[i], (char[2]) { '(', '\0' });
                        strcpy(tokenList[tokenPosition++], "15");
                        printf("\n%-10s 15", "(\0");
                        break;
                    case ')':
                        removeWord(lineByLine[i], (char[2]) { ')', '\0' });
                        strcpy(tokenList[tokenPosition++], "16");
                        printf("\n%-10s 16", ")\0");
                        break;
                    case '=':
                        removeWord(lineByLine[i], (char[2]) { '=', '\0' });
                        strcpy(tokenList[tokenPosition++], "9");
                        printf("\n%-10s 9", "=\0");
                        break;
                    case '<':
                        if (lineByLine[i][1] == '>') {
                            removeWord(lineByLine[i], (char[3]) { '<', '>', '\0' });
                            strcpy(tokenList[tokenPosition++], "10");
                            printf("\n%-10s 10", "<>\0");
                        } else if (lineByLine[i][1] == '=') {
                            removeWord(lineByLine[i], (char[3]) { '<', '=', '\0' });
                            strcpy(tokenList[tokenPosition++], "12");
                            printf("\n%-10s 12", "<=\0");
                        } else {
                            removeWord(lineByLine[i], (char[2]) { '<', '\0' });
                            strcpy(tokenList[tokenPosition++], "11");
                            printf("\n%-10s 11", "<\0");  
                        }
                        
                        break;
                    case ':':
                        if (lineByLine[i][1] == '=') {
                            removeWord(lineByLine[i], (char[3]) { ':', '=', '\0' });
                            strcpy(tokenList[tokenPosition++], "20");
                            printf("\n%-10s 20", ":=\0");
                        } else if (lineByLine[i][1] == ':' && lineByLine[i][2] == '=') {
                            removeWord(lineByLine[i], (char[4]) { ':', '=', '=', '\0' });
                            strcpy(tokenList[tokenPosition++], "12");
                            printf("\n%-10s 12", ":==\0");
                        } else {
                            removeWord(lineByLine[i], (char[2]) { ':', '\0' });
                            strcpy(tokenList[tokenPosition++], "11");
                            printf("\n%-10s 11", "<\0");  
                        }
                        
                        break;
                    case '>':
                        if (lineByLine[i][1] == '=') {
                            removeWord(lineByLine[i], (char[3]) { '<', '=', '\0' });
                            strcpy(tokenList[tokenPosition++], "14");
                            printf("\n%-10s 14", ">=\0");
                        } else {
                            removeWord(lineByLine[i], (char[2]) { '>', '\0' });
                            strcpy(tokenList[tokenPosition++], "13");
                            printf("\n%-10s 13", ">\0");
                        }
                        
                        break;
                    case ';':
                        removeWord(lineByLine[i], (char[2]) { ';', '\0' });
                        strcpy(tokenList[tokenPosition++], "18");
                        printf("\n%-10s 18", ";\0");
                        break;
                    default:
                        break;
                }
            }

            strcpy(currentWord, findReserved(lineByLine[i]));
            if (strcmp(currentWord, "NEG") != 0 && caught == 0) {
                caught = 1;

                if (strcmp(currentWord, "const") == 0) {
                    removeWord(lineByLine[i], "const");
                    strcpy(tokenList[tokenPosition++], "28");
                    printf("\n%-10s 28", "const\0");
                } else if (strcmp(currentWord, "var") == 0) {
                    removeWord(lineByLine[i], "var");
                    strcpy(tokenList[tokenPosition++], "29");
                    printf("\n%-10s 29", "var\0");
                }else if (strcmp(currentWord, "procedure") == 0) {
                    removeWord(lineByLine[i], "procedure");
                    strcpy(tokenList[tokenPosition++], "30");
                    printf("\n%-10s 30", "procedure\0");
                }else if (strcmp(currentWord, "call") == 0) {
                    removeWord(lineByLine[i], "call");
                    strcpy(tokenList[tokenPosition++], "27");
                    printf("\n%-10s 27", "call\0");
                }else if (strcmp(currentWord, "begin") == 0) {
                    removeWord(lineByLine[i], "begin");
                    strcpy(tokenList[tokenPosition++], "21");
                    printf("\n%-10s 21", "begin\0");
                }else if (strcmp(currentWord, "end") == 0) {
                    removeWord(lineByLine[i], "end");
                    strcpy(tokenList[tokenPosition++], "22");
                    printf("\n%-10s 22", "end\0");
                }else if (strcmp(currentWord, "if") == 0) {
                    removeWord(lineByLine[i], "if");
                    strcpy(tokenList[tokenPosition++], "23");
                    printf("\n%-10s 23", "if\0");
                }else if (strcmp(currentWord, "fi") == 0) {
                    removeWord(lineByLine[i], "fi");
                    strcpy(tokenList[tokenPosition++], "8");
                    printf("\n%-10s 8", "fi\0");
                }else if (strcmp(currentWord, "then") == 0) {
                    removeWord(lineByLine[i], "then");
                    strcpy(tokenList[tokenPosition++], "24");
                    printf("\n%-10s 24", "then\0");
                }else if (strcmp(currentWord, "else") == 0) {
                    removeWord(lineByLine[i], "else");
                    strcpy(tokenList[tokenPosition++], "33");
                    printf("\n%-10s 33", "else\0");
                }else if (strcmp(currentWord, "while") == 0) {
                    removeWord(lineByLine[i], "while");
                    strcpy(tokenList[tokenPosition++], "25");
                    printf("\n%-10s 25", "while\0");
                }else if (strcmp(currentWord, "do") == 0) {
                    removeWord(lineByLine[i], "do");
                    strcpy(tokenList[tokenPosition++], "26");
                    printf("\n%-10s 26", "do\0");
                }else if (strcmp(currentWord, "read") == 0) {
                    removeWord(lineByLine[i], "read");
                    strcpy(tokenList[tokenPosition++], "32");
                    printf("\n%-10s 32", "read\0");
                }else if (strcmp(currentWord, "write") == 0) {
                    removeWord(lineByLine[i], "write");
                    strcpy(tokenList[tokenPosition++], "31");
                    printf("\n%-10s 31", "write\0");
                }
            }
        
            if (caught == 0) {
                int isNum = isNumber(lineByLine[i]);
                if (isNum == 1) {
                    caught = 1;
                    
                    getNumber(lineByLine[i], numberString);

                    removeWord(lineByLine[i], numberString);
                    strcpy(tokenList[tokenPosition++], "3");
                    strcpy(tokenList[tokenPosition++], numberString);
                    printf("\n%-10s 3", numberString);
                    
                    for (int i = 0; i < 500; i++) {
                      numberString[i] = '\0';
                    }
                } 
            }

            if (caught == 0) {
                for (int i = 0; i < 500; i++) {
                  varString[i] = '\0';
                }
                
                getVar(lineByLine[i], varString);
                
                if (strlen(varString) > 0) {
                
                  caught = 1;
                  removeWord(lineByLine[i], varString);
                  strcpy(tokenList[tokenPosition++], "2");
                  strcpy(tokenList[tokenPosition++], varString);
                  printf("\n%-10s 2", varString);
                  
                  if (strlen(varString) > 11) {
                    printf("\n\n ERROR: IDENTIFIER MORE THAN 11 CHARACTERS\n\n");
                  }
                  
                  
                }

                
                
                
                
            }
            
            if (caught == 0) {
              printf("\n\n ERROR: INVALID CHARACTER: %c", lineByLine[i][0]);
              removeWord(lineByLine[i], (char[2]) {lineByLine[i][0], '\0'});
            }
        }
        
        //printf("%s", reservedWord);
    }

    
    
    

    printf("\n\nToken List:\n");
    for (int i = 0; i < tokenPosition; i++) {
        printf("%s ", tokenList[i]);
    }
    
    printf("\n");

    return 0;
}