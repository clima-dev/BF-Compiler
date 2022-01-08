#include <iostream>                                     // outputting data to screen
#include <stdio.h>                                      // switch statement

#define SOURCE_SIZE 10000                               // source code len limit (x chars)
#define MEMORY_SIZE 30000                               // "infinite tape" const

int memory[MEMORY_SIZE];                                // available program memory
char source[SOURCE_SIZE] = "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.";               // bf source code
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

int main()
{
    bf_execute();

    return 0;
}
