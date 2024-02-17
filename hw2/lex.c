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

typedef enum {
    skipsym = 1, identsym = 2, numbersym = 3, plussym = 4, minussym = 5,
    multsym = 6, slashsym = 7, fisym = 8, eqlsym = 9, neqsym = 10, lessym = 11, leqsym = 12, 
    gtrsym = 13, geqsym = 14, lparentsym = 15, rparentsym = 16, commasym = 17,
    semicolonsym = 18, periodsym = 19, becomessym = 20,
    beginsym = 21, endsym = 22, ifsym = 23, thensym = 24, whilesym = 25, dosym = 26,
    callsym = 27, constsym = 28, varsym = 29, procsym = 30, writesym = 31,
    readsym = 32, elsesym = 33
} token_type;

// removes whitespace, tabs, and new line characters from the string passed to it utilizing recursion
char* removeWhiteSpace(char* line) {
    int currentLineSize = strlen(line);
    for (int j = 0; j < currentLineSize; j++) {
        if (line[j] == ' ' || line[j] == '\t' || line[j] == '\n' || line[j] == ';') {
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

        if (strcmp(reservedWord, "var") == 0) {
            strcpy(lineByLine[i], removeWord(lineByLine[i], reservedWord));
            printf("%-10s 29", reservedWord);
            strcpy(tokenList[tokenPosition], "29");
            tokenPosition++;
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