/*

Name: Andre Hebra

*/

#include <stdio.h>

// define the struct that holds the instruciton record: OP, L, M
typedef struct IR {
  int OP;
  int L;
  int M;
} IR;

int main(int argc, char* argv[]) {

  // set end of program (eop) flag to 1
  // when set to zero, indicates the end of the program
  int eop = 1;
  
  // initialize an instruction register (ir)
  IR ir;
  ir.OP = 0;
  ir.L = 0;
  ir.M = 0;

  // set maximum value for array
  int ARRAY_SIZE = 500;
  
  // initialize pas array and set all values to zero
  int pas[ARRAY_SIZE];
  for (int i = 0; i < ARRAY_SIZE; i++) {
    pas[i] = 0;
  }
  
  // read in OP, L, and M into the pas array
  FILE* inputFile = fopen(argv[1], "r");
  int num;
  int count = 0;
  fscanf(inputFile, "%d", &num);
  pas[count++] = num;
  while (!feof (inputFile)) {  
      fscanf (inputFile, "%d", &num); 
      pas[count++] = num;     
  }
  fclose (inputFile); 

  // initialize BP, SP, and PC  
  int BP = 499;     // base pointer
  int SP = BP + 1;  // stack pointer
  int PC = 0;       // program counter
  int IR;           // instruction register
  
  // print the initial values of PC, BP, SP
  printf("                PC      BP      SP      stack\n");
  printf("Initial values: %-8d%-8d%-8d\n", PC, BP, SP);
  
  // run program until end of program (eop) flag is set to 0
  while (eop != 0) {
    // set IR values to those in the current PC (program counter)
    ir.OP = pas[PC];
    ir.L = pas[PC + 1];
    ir.M = pas[PC + 2];
    
    // increment the program counter
    PC = PC + 3;
    
    // execute
    switch(ir.OP) {
        case 7:
            PC = ir.M;
            break;
        case 9:
            switch(ir.M) {
                case 3:
                    eop = 0;
                    break;
            }
            break;
    }
    
    // print out the current state
    printf("  ");
    switch(ir.OP) {
        case 7:
            printf("JMP");
            break;
        case 9: 
            printf("SYS");
            break;
    }
    printf(" ");

    printf("%-2d%-8d", ir.L, ir.M);
    printf("%-8d%-8d%-8d\n", PC, BP, SP);
  }
  
}