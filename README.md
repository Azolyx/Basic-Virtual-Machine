
# Basic Virtual Machine

This is a basic vitual machine that was made in C. It supports a few basic commands such as POP, PSH, ADD, etc (Expaned on later). It was made using the tutorial linked below however I have expaned on it to add new commands, features, and logic.

> [Basic virtual machine in c](https://felix.engineer/blogs/virtual-machine-in-c/)

## Syntax

### Commands

|Command|Full Name|Syntax                    |Example               |Description                                                                 |
|:-----:|:-------:|:------------------------:|:--------------------:|:--------------------------------------------------------------------------:|
|PSH    |Push     |PSH VALUE                 |PSH INT 5             |Pushes a value of a registry or a int to the stack.                         |
|POP    |Pop      |POP                       |POP                   |Pops the top value of the stack.                                            |
|ADD    |Add      |ADD                       |ADD                   |Adds the top 2 values of the stack.                                         |
|SUB    |Subtract |SUB                       |SUB                   |Subtracts the top 2 values of the stack.                                    |
|MUL    |Multiply |MUL                       |MUL                   |Multiplies the top 2 values of the stack.                                   |
|DIV    |Divide   |DIV                       |DIV                   |Divides the top 2 values of the stack.                                      |
|SET    |Set      |SET REGISTRY VALUE        |SET A INT 5           |Sets a registry to the value of a registry or a int.                        |
|INP    |Input    |INP REGISTRY              |INP A                 |Gets an input from the user and sets that value to a registry.              |
|PRT    |Print    |PRT REGISTRY              |PRT A                 |Prints the value of a stack.                                                |
|IFT    |If Then  |IFT VALUE COMPARISON VALUE|IFT A LESS_EQUAL INT 5|If the equasion is true then run all the code untell a BRK command comes up.|
|BRK    |Break    |BRK                       |BRK                   |Stops a If Then.                                                            |
|HLT    |Halt     |HLT                       |HLT                   |Stops the program *Required*.                                               |

### Registrys

|Registry|Description                                                                                                              |
|:------:|:-----------------------------------------------------------------------------------------------------------------------:|
|A       |Basic registry.                                                                                                          |
|B       |Basic registry.                                                                                                          |
|C       |Basic registry.                                                                                                          |
|D       |Basic registry.                                                                                                          |
|E       |Basic registry.                                                                                                          |
|F       |Basic registry.                                                                                                          |
|G       |Basic registry.                                                                                                          |
|H       |Basic registry.                                                                                                          |
|IP      |Used by the program to know what command to run next. Can be set to earlier value to rerun pieces of code and make loops.|
|STACK   |Has a value of the top value of the stack.                                                                               |
|INT     |When read by a command it will use the value of the next instruction.                                                    |

## Examples

### Print input from user

    INP A  
    PRT A  
    HTL  

### Add 2 inputs from the user

    INP A  
    PSH A  
    INP B  
    PSH B  
    ADD  
    PRT STACK  
    HTL  

### Finds the largest of 2 inputs from the user

    INP A  
    INP B  
    IFT A MORE_EQUAL B  
    PRT A  
    BRK  
    IFT A LESS B  
    PRT B  
    BRK  
    HTL  

### Basic Calculator

    INP A  
    INP B  
    PSH B  
    INP C  
    PSH C  

    IFT A EQUAL INT 1  
    ADD  
    PRT STACK  
    BRK  

    IFT A EQUAL INT 2  
    SUB  
    PRT STACK  
    BRK  

    IFT A EQUAL INT 3  
    MUL  
    PRT STACK  
    BRK  

    IFT A EQUAL INT 4  
    DIV  
    PRT STACK  
    BRK  

    HLT  
    
## Notes

When writing any code you need to put it into the `program[]` variable on line 12. It has to be formatted like a array with each command being a diffrent item in the array. An example using the ***Add 2 inputs from users*** example as shown above:

    const int program[] = {
        INP, A,  
        PSH, A,  
        INP, B,  
        PSH, B,  
        ADD,  
        PRT, STACK,  
        HTL  
    }
