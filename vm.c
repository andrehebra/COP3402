/*
Name: Andre Hebra

I did not work in a group, all work was done by myself.
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
	int arb = BP;	   // arb = activation record base
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

    // create array and integer to track the activation record
    int arTrack[500] = {0};
    arTrack[0] = ARRAY_SIZE - 1;
    int arTop = 0;

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
        // fetch the instruction and load into the struct
        ir.OP = pas[PC];
        ir.L = pas[PC + 1];
        ir.M = pas[PC + 2];
        
        // increment the program counter
        PC = PC + 3;
        
        // execute
        // use a switch case to differentiate between each opcode
        switch(ir.OP) {
            case 1:
                SP--;
                pas[SP] = ir.M;
                break;
            case 2:
                switch(ir.M){
                    case 0:
                        SP = BP + 1; 
                        BP = pas[SP - 2];
                        PC = pas[SP - 3];

                        arTop--;
                        break;
                    case 1: // add
                        pas[SP + 1] = pas[SP + 1] + pas[SP];
						SP = SP + 1;
                        break;
                    case 2: // sub
                        pas[SP + 1] = pas[SP + 1] - pas[SP];
						SP = SP + 1;
                        break;
                    case 3: // multiply
                        pas[SP+1] = pas[SP+1] * pas[SP];
                        SP = SP + 1;
                        break;
                    case 4: // divide
                        pas[SP+1] = pas[SP+1] / pas[SP];
                        SP = SP + 1;
                        break;
                    case 5: // eql
                        pas[SP+1] = pas[SP+1] == pas[SP];
                        SP = SP + 1;
                        break;
                    case 6: // neq
                        pas[SP+1] = pas[SP+1] != pas[SP];
                        SP = SP + 1;
                        break;
                    case 7: // lss
                        pas[SP+1] = pas[SP+1] < pas[SP];
                        SP = SP + 1;
                        break;
                    case 8: // leq
                        pas[SP+1] = pas[SP+1] <= pas[SP];
                        SP = SP + 1;
                        break;
                    case 9: // gtr
                        pas[SP+1] = pas[SP+1] > pas[SP];
                        SP = SP + 1;
                        break;
                    case 10: //geq
                        pas[SP+1] = pas[SP+1] >= pas[SP];
                        SP = SP + 1;
                        break;
                    case 11: // odd --> 1 for odd, 0 for even
                        pas[SP] = pas[SP] % 2;
                        break;
                }
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
                arTop++;
                arTrack[arTop] = BP;
                break;
            case 6:
                SP = SP - ir.M;
                break;
            case 7:
                PC = ir.M;
                break;
            case 8:
                if (pas[SP] == 0) {
                    PC = ir.M;
                    SP = SP + 1;
                }
                
                break;
            case 9:
                switch(ir.M) {
                    case 1:
                        printf("Output result is: %d\n", pas[SP]); 
                        SP = SP+1;
                        break;
                    case 2:
                        SP = SP-1;
                        printf("Please Enter an Integer: ");
                        scanf("%d", &pas[SP]);

                        break;
                    case 3:
                        eop = 0;
                        break;
                }
                break;
        }
        
        // print out the current state
        
        // print out the decoded opcode that is currently still in the IR struct
        printf("  ");
        switch(ir.OP) {
            case 1:
                printf("LIT");
                break;
            case 2:
                switch(ir.M) {
                    case 1:
                        printf("ADD");
                        break;
                    case 2:
                        printf("SUB");
                        break;
                    case 3:
                        printf("MUL");
                        break;
                    case 4:
                        printf("DIV");
                        break;
                    case 5:
                        printf("EQL");
                        break;
                    case 6:
                        printf("NEQ");
                        break;
                    case 7:
                        printf("LSS");
                        break;
                    case 8:
                        printf("LEQ");
                        break;
                    case 9:
                        printf("GTR");
                        break;
                    case 10:
                        printf("GEQ");
                        break;
                    case 11:
                        printf("ODD");
                        break;
                    case 0:
                        printf("RTN");
                        break;
                    
                }
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
                switch(ir.M) {
                    case 1:
                        printf("SOU");
                        break;
                    case 2:
                        printf("SIN");
                        break;
                    case 3:
                        printf("EOP");
                        break;   
                }
                break;
        }
        printf(" ");

        // print out the current values of L and M
        printf("%-2d%-8d", ir.L, ir.M);

        // print out the current values of PC, BP, and SP
        printf("%-8d%-8d%-8d", PC, BP, SP);

        // go through the stack and print each value
        for (int i = ARRAY_SIZE - 1; i >= SP; i--) {
            // check if the current element in the stack is the beginning of an activation record
            // if it is print "| " to the console
            for (int j = 0; j <= arTop; j++) {
                if (i == arTrack[j] && arTrack[j] != ARRAY_SIZE - 1) {
                    printf("| ");
                }
            }
            
            // print out the current value of the stack
            printf("%d ", pas[i]);
        }

        //print a new line, then move to next instruction
        printf("\n");
    }
  
}