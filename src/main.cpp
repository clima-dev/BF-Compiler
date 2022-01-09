#include <iostream>                                     // outputting data to screen
#include <stdio.h>                                      // switch statement
#include <errno.h>                                        // handling errors with fopen

#define SOURCE_SIZE 10000                               // source code len limit (x chars)
#define MEMORY_SIZE 30000                               // "infinite tape" const

int memory[MEMORY_SIZE];                                // available program memory
char source[SOURCE_SIZE];                               // bf source code
char* src = source;                                     // instruction pointer
int* mem = memory;                                      // memory pointer
int loop = 0;                                           // nested loops counter

void bf_execute()
{
    while(*src)
    {
        switch(*src)
        {
            case '>': *mem++;  break;                   // increment memory pointer
            case '<': *mem--;  break;                   // decrement memory pointer 
            case '+': ++*mem;  break;                   // increments memory reference 
            case '-': --*mem;  break;                   // decrements memory reference 
            case '.': putc(*mem, stdout); break;        // output char to screen 
            case ',': *mem = getc(stdin); break;        // get char from keyboard 
                
            case '[':                                   // loop start 

                if(!*mem)                               // if cell at data pointer is zero 
                {
                    loop = 1;                           // loop variable holds a number of '[]' 
                    while(loop)                         // do until find matching ']' 
                    {
                        *src++;                         // increment instruction pointer 

                        if(*src == '[') loop++;         // inc loop on '[' instruction 
                        if(*src == ']') loop--;         // dec loop on ']' instruction 
                    }
                }

                break;

            case ']':                                   // loop end 

                loop = 1;                               // loop variable holds a number of '[]' 
                while(loop)                             // do until find matching '[' 
                {
                    *src--;                             // decrement instruction pointer 
                   
                    if(*src == '[') loop--;             // dec loop on '[' instruction 
                    if(*src == ']') loop++;             // inc loop on ']' instruction 
                }

                *src--;                                 // decrement instruction pointer 
                break;
        }
        
        *src++;                                         // increment instruction pointer 
    }
}

int main(int argc, char* argv[])
{
    if(argc == 1)                                       // if there's no arguments passed (file path), output error.
    {
        std::cout << "ERROR: No arguments passed. \n compilation terminated." << std::endl;
        return 0;
    }

    FILE *file = fopen(argv[1], "r");                   // open filestream

    if(errno)                                           // output error if file doesn't exist
    {
        std::cout << "File " << argv[1] << "does not exist!" << std::endl;    
        return 0;
    }

    fread(source, 1, SOURCE_SIZE, file);                // read source code from file
    fclose(file);                                       // close filestream
    bf_execute();                                       // execute brainfuck program

    return 0;
}
