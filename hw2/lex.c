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


    return 0;
}