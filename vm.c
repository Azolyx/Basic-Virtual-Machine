#include <stdio.h>
#include <stdbool.h>
/* **************************************************************************************************** */

/*
Program code will go here in the program array.
Included is a simple program which will print the highest of 2 inputs.
To create code make sure each command is seperated with a comma.
As long as they are all seperated spacing, tabbing, etc does not matter.
*/

const int program[] = {
    INP, A,
    INP, B,
    IFT, A, MORE_EQUAL, B,
    PRT, A,
    BRK,
    IFT, A, LESS_EQUAL, B,
    PRT, B,
    BRK,
    HLT
};

/* **************************************************************************************************** */

typedef enum {
    A, B, C, D, E, F, G, H,
    IP,
    INT, STR,
    SP, STACK,
    NUM_OF_REGISTERS
} Registers;

typedef enum {
    LESS, LESS_EQUAL, EQUAL, MORE_EQUAL, MORE
} Comparisons;

typedef enum {
    PSH, POP,
    ADD, SUB, MUL, DIV,
    SET, INP, PRT,
    IFT, BRK,
    HLT
} InstructionSet;

int stack[256];
int registers[NUM_OF_REGISTERS];

bool running = true;

int fetch() {
    return program[registers[IP]];
}

char* getRegistery(int r) {
    switch (r) {
        case A: {
            return "A";
        }
        case B: {
            return "B";
        }
        case C: {
            return "C";
        }
        case D: {
            return "D";
        }
        case E: {
            return "E";
        }
        case F: {
            return "F";
        }
        case G: {
            return "G";
        }
        case H: {
            return "H";
        }
        case IP: {
            return "IP";
        }
    }
    return "null";
}

void eval(int instr) {
    switch (instr) {
        case PSH: {
            int a = program[++registers[IP]];
            if (a == INT) stack[++registers[SP]] = program[++registers[IP]];
            else stack[++registers[SP]] = registers[a];
            break;
        }
        case POP: {
            registers[SP]--;
            break;
        }
        case ADD: {
            int a = stack[registers[SP]--];
            int b = stack[registers[SP]--];
            int result = b + a;
            registers[SP]++;
            stack[registers[SP]] = result;
            break;
        }
        case SUB: {
            int a = stack[registers[SP]--];
            int b = stack[registers[SP]--];
            int result = b - a;
            registers[SP]++;
            stack[registers[SP]] = result;
            break;
        }
        case MUL: {
            int a = stack[registers[SP]--];
            int b = stack[registers[SP]--];
            int result = b * a;
            registers[SP]++;
            stack[registers[SP]] = result;
            break;
        }
        case DIV: {
            int a = stack[registers[SP]--];
            int b = stack[registers[SP]--];
            int result = b / a;
            registers[SP]++;
            stack[registers[SP]] = result;
            break;
        }
        case SET: {
            int a = program[++registers[IP]];
            int b = program[++registers[IP]];
            switch (a) {
                case INT: {
                    printf("ERROR: INT is not a valid registry\n");
                    running = false;
                    break;
                }
                case STR: {
                    printf("ERROR: STR is not a valid registry\n");
                    running = false;
                    break;
                }
                case NUM_OF_REGISTERS: {
                    printf("ERROR: NUM_OF_REGISTERS is not a valid registry\n");
                    running = false;
                    break;
                }
                case SP: {
                    printf("ERROR: Cannot edit SP\n");
                    running = false;
                    break;
                }
                case STACK: {
                    printf("ERROR: Cannot edit STACK\n");
                    running = false;
                    break;
                }
                default: {
                    if (b == INT) registers[a] = program[++registers[IP]];
                    else registers[a] = registers[b];
                    break;
                }
            }
            break;
        }
        case INP: {
            int input = 0;
            int a = program[++registers[IP]];
            printf("Input %s: ", getRegistery(a));
            scanf("%d", &input);
            registers[a] = input;
            break;
        }
        case PRT: {
            printf("%d\n", registers[program[++registers[IP]]]);
            break;
        }
        case IFT: {
            int a = program[++registers[IP]];
            if (a == INT) {
                a = program[++registers[IP]];
            }
            else {
                a = registers[a];
            }
            int b = program[++registers[IP]];
            int c = program[++registers[IP]];
            if (c == INT) {
                c = program[++registers[IP]];
            }
            else {
                c = registers[c];
            }
            
            switch(b) {
                case LESS:
                    if (a < c) {
                        while (fetch() != BRK) {
                            if (registers[SP] > -1) registers[STACK] = stack[registers[SP]];
                            eval(fetch());
                            registers[IP]++;
                        }
                    } else {
                        while (fetch() != BRK) {
                            registers[IP]++;
                        }
                    }
                    break;
                case LESS_EQUAL:
                    if (a <= c) {
                        while (fetch() != BRK) {
                            if (registers[SP] > -1) registers[STACK] = stack[registers[SP]];
                            eval(fetch());
                            registers[IP]++;
                        }
                    } else {
                        while (fetch() != BRK) {
                            registers[IP]++;
                        }
                    }
                    break;
                case EQUAL:
                    if (a == c) {
                        while (fetch() != BRK) {
                            if (registers[SP] > -1) registers[STACK] = stack[registers[SP]];
                            eval(fetch());
                            registers[IP]++;
                        }
                    } else {
                        while (fetch() != BRK) {
                            registers[IP]++;
                        }
                    }
                    break;
                case MORE_EQUAL:
                    // For some reoson having >= makes it not work but having > and == seperate works
                    if (a > c || a == c) {
                        while (fetch() != BRK) {
                            if (registers[SP] > -1) registers[STACK] = stack[registers[SP]];
                            eval(fetch());
                            registers[IP]++;
                        }
                    } else {
                        while (fetch() != BRK) {
                            registers[IP]++;
                        }
                    }
                    break;
                case MORE:
                    if (a > c) {
                        while (fetch() != BRK) {
                            if (registers[SP] > -1) registers[STACK] = stack[registers[SP]];
                            eval(fetch());
                            registers[IP]++;
                        }
                    } else {
                        while (fetch() != BRK) {
                            registers[IP]++;
                        }
                    }
                    break;
            }

            break;
        }
        case BRK: {
            break;
        }
        case HLT: {
            running = false;
            break;
        }
    }
}

int main() {
    registers[IP] = 0;
    registers[SP] = -1;
    while (running) {
        if (registers[SP] > -1) registers[STACK] = stack[registers[SP]];
        eval(fetch());
        registers[IP]++;
    }
    return 0;
}