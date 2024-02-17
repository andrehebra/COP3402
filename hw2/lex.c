/*
Author: Andre Hebra
Homework 2: Lexical Analyzer
*/
#include <stdio.h>
#include <string.h>


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
    int wordLength = strlen(word);
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
    }

    return line;
}

// find reserved word in the given string
char* findReserved(char* line) {
    int lineLength = strlen(line);

    for (int i = 0; i < lineLength; i++) {
        switch(line[i]) {
            case 'c':
                if (line[i+1] == 'o' && line[i+2] == 'n' && line[i+3] == 's' && line[i+4] == 't') {
                    return "const";
                }
                break;
            case 'v':
                if (line[i+1] == 'a' && line[i+2] == 'r') {
                    return "var";
                }
                break;
            case 'b':
                if (line[i+1] == 'e' && line[i+2] == 'g' && line[i+3] == 'i' && line[i+4] == 'n') {
                    return "begin";
                }
                break;
            case ':':
                if (line[i+1] == '=') {
                    return ":=";
                }
                break;
            case 'e':
                if (line[i+1] == 'n' && line[i+2] == 'd') {
                    return "end";
                }
                break;
        }
    }

    return "NEG";    
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

    
    
    

    for (int i = 0; i < lineCount; i++) {
        char reservedWord[20];

        strcpy(reservedWord, findReserved(lineByLine[i]));
        
        // var
        if (strcmp(reservedWord, "var") == 0) {
            int printSemi = 0;
            strcpy(lineByLine[i], removeWord(lineByLine[i], reservedWord));
            printf("\n%-10s 29", reservedWord);
            strcpy(tokenList[tokenPosition], "29");
            tokenPosition++;
            for (int j = 0; j < strlen(lineByLine[i]); j++) {
                if (lineByLine[i][j] == ';') {
                    printSemi = 1;
                } else if (lineByLine[i][j] == ',') {
                    strcpy(tokenList[tokenPosition], "2");
                    tokenPosition++;
                    strcpy(tokenList[tokenPosition], identList[identPosition].name);
                    tokenPosition++;
                    strcpy(tokenList[tokenPosition], "17");
                    tokenPosition++;

                    printf("\n%-10s 2", identList[identPosition].name);
                    printf("\n%-10s 17", ",");

                    identPosition++;
                } else {
                    strcat(identList[identPosition].name, (char[2]) { lineByLine[i][j], '\0' });
                }
            }

            strcpy(tokenList[tokenPosition], "2");
            tokenPosition++;
            strcpy(tokenList[tokenPosition], identList[identPosition].name);
            tokenPosition++;

            printf("\n%-10s 2", identList[identPosition].name);

            identPosition++;

            if (printSemi == 1) {
                printf("\n%-10s 18", ";");
                strcat(tokenList[tokenPosition], "18");
                tokenPosition++;
            }
        }
        
        //begin
        if (strcmp(reservedWord, "begin") == 0) {
            printf("\n%-10s 21", reservedWord);
            strcpy(tokenList[tokenPosition++],"21");
        }

        // := 
        if (strcmp(reservedWord, ":=") == 0) {
            while (strlen(lineByLine[i]) > 0) {
                char wordToRemove[200];
                strcpy(wordToRemove, compareIdents(lineByLine[i], identList, identPosition));
                if (strcmp(wordToRemove, "NEG") != 0) {
                    removeWord(lineByLine[i], wordToRemove);
                    printf("\n%-10s 2", wordToRemove);
                    strcpy(tokenList[tokenPosition++], "2");
                    strcpy(tokenList[tokenPosition++], wordToRemove);
                } else {
                    if (lineByLine[i][0] == ':' && lineByLine[i][1] == '=') {
                        removeWord(lineByLine[i], ":=");
                        strcpy(tokenList[tokenPosition++], "20");
                        printf("\n%-10s 20", ":=");
                    } else if (lineByLine[i][0] == '+') {
                        removeWord(lineByLine[i], (char[2]) { '+', '\0' });
                        strcpy(tokenList[tokenPosition++], "4");
                        printf("\n%-10s 4", "+\0");
                    } else if (lineByLine[i][0] == ';') {
                        removeWord(lineByLine[i], (char[2]) { ';', '\0' });
                        strcpy(tokenList[tokenPosition++], "18");
                        printf("\n%-10s 18", ";\0");
                    } else if (lineByLine[i][0] == '0' ||lineByLine[i][0] == '1' ||lineByLine[i][0] == '2' ||lineByLine[i][0] == '3' ||lineByLine[i][0] == '4' ||lineByLine[i][0] == '5' ||lineByLine[i][0] == '6' ||lineByLine[i][0] == '7' ||lineByLine[i][0] == '8' ||lineByLine[i][0] == '9') {
                        char digits[100];
                        digits[0] = '\0';
                        strcpy(digits, getDigits(lineByLine[i], digits));
                        removeWord(lineByLine[i], digits);
                        printf("\n%-10s 3", digits);
                        strcpy(tokenList[tokenPosition++], "3");
                        strcpy(tokenList[tokenPosition++], digits);
                    }
                }
            }
        }

        if (strcmp(reservedWord, "end") == 0) {
            int endofprogram = 0;
            while (strlen(lineByLine[i]) > 0 || endofprogram != 1) {
                if (lineByLine[i][0] == '.') {
                    removeWord(lineByLine[i], ".\0");
                    strcpy(tokenList[tokenPosition++], "19");
                    printf("\n%-10s 19", ".\0");
                    endofprogram = 1;
                } else if (lineByLine[i][0] == 'e' && lineByLine[i][1] == 'n' && lineByLine[i][2] == 'd') {
                    removeWord(lineByLine[i], "end");
                    strcpy(tokenList[tokenPosition++], "22");
                    printf("\n%-10s 22", ";\0");
                }
            }
        }
        //printf("%s", reservedWord);
    }

    /*
    //print out the source program
    printf("Source Program:\n");
    for (int i = 0; i < lineCount; i++) {
        printf("%s\n", lineByLine[i]);
    }
    */

    printf("\n\nToken List:\n");
    for (int i = 0; i < tokenPosition; i++) {
        printf("%s ", tokenList[i]);
    }

    return 0;
}