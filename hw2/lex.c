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

int skipsym = 1, identsym = 2, numbersym = 3, plussym = 4, minussym = 5, multsym = 6, slashsym = 7, fisym = 8, eqlsym = 9, neqsym = 10, lessym = 11, leqsym = 12, gtrsym = 13, geqsym = 14, lparentsym = 15, rparentsym = 16, commasym = 17, semicolonsym = 18, periodsym = 19, becomessym = 20, beginsym = 21, endsym = 22, ifsym = 23, thensym = 24, whilesym = 25, dosym = 26, callsym = 27, constsym = 28, varsym = 29, procsym = 30, writesym = 31, readsym = 32, elsesym = 33;

// removes whitespace, tabs, and new line characters from the string passed to it utilizing recursion
char* removeWhiteSpace(char* line) {
    int currentLineSize = strlen(line);
    for (int j = 0; j < currentLineSize; j++) {
        if (line[j] == ' ' || line[j] == '\t' || line[j] == '\n') {
            for (int k = j; k < currentLineSize; k++) {
                line[k] = line[k+1];
            }
        }
    }

    for (int i = 0; i < currentLineSize; i++) {
        if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n') return removeWhiteSpace(line);
    }

    return line;
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




    printf("\n\nLexeme Table:\n\nlexeme token type\n");

    // remove comments
    // this works by noting the beginning position of the comment and then replaces each character between slashes with witespace. This allows for the progam to remove it later
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

    printf("Source Program:\n");
    for (int i = 0; i < lineCount; i++) {
        printf("%s", lineByLine[i]);
    }


    return 0;
}