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

// set maximum value for array
int ARRAY_SIZE = 500;

// initialize pas array and set all values to zero
int pas[500] = {0};

int base(int BP,int L)
{
	int arb = BP;	// arb = activation record base
	while ( L > 0)     //find base L levels down
	{
		arb = pas[arb];
		L--;
	}
	return arb;
}

int main(int argc, char* argv[]) {

    // set end of program (eop) flag to 1
    // when set to zero, indicates the end of the program
    int eop = 1;
    
    // initialize an instruction register (ir)
    IR ir;
    ir.OP = 0;
    ir.L = 0;
    ir.M = 0;

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
    int BP = ARRAY_SIZE - 1;      // base pointer
    int SP = BP + 1;              // stack pointer
    int PC = 0;                   // program counter
    int IR;                       // instruction register
    
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
            case 1:
                SP--;
                pas[SP] = ir.M;
                break;
            case 2:
                SP = BP + 1; 
                BP = pas[SP - 2];
                PC = pas[SP - 3];
                break;
            case 3:
                SP = SP - 1;    
                pas[SP] = pas[base(BP, ir.L) - ir.M];

                break;
            case 4:
                pas[base(BP, ir.L) - ir.M] = pas[SP];
                SP = SP + 1;

                break;
            case 5:
                pas[SP - 1] = base(BP, ir.L);
                pas[SP - 2] = BP;
                pas[SP - 3] = PC; 
                BP = SP - 1;
                PC = ir.M;

                break;
            case 6:
                SP = SP - ir.M;
                break;
            case 7:
                PC = ir.M;
                break;
            case 8:
                
                
                break;
            case 9:
                switch(ir.M) {
                    case 1:
                        break;
                    case 2:
                        break;
                    case 3:
                        eop = 0;
                        break;
                }
                break;
        }
        
        // print out the current state
        printf("  ");
        switch(ir.OP) {
            case 1:
                printf("LIT");
                break;
            case 2:
                printf("RTN");
                break;
            case 3:
                printf("LOD");
                break;
            case 4:
                printf("STO");
                break;
            case 5:
                printf("CAL");
                break;
            case 6:
                printf("INC");
                break;
            case 7:
                printf("JMP");
                break;
            case 8:
                printf("JPC");
                break;
            case 9: 
                printf("SYS");
                break;
        }
        printf(" ");

        printf("%-2d%-8d", ir.L, ir.M);
        printf("%-8d%-8d%-8d", PC, BP, SP);

        for (int i = BP; i >= SP; i--) {
            printf("%2d", pas[i]);
        }
        printf("\n");
    }
  
}