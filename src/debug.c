#include "../include/debug.h"
#include "../include/io.h"
#include "../include/string.h"
#include "../include/tty.h"
#include "../include/vga.h"

void reg()
{
    int eax, ebx, ecx, edx;

    // Inline assembly to move register values to variables
    asm volatile(
        "movl %%eax, %0\n\t"
        "movl %%ebx, %1\n\t"
        "movl %%ecx, %2\n\t"
        "movl %%edx, %3\n\t"
        : "=r" (eax), "=r" (ebx), "=r" (ecx), "=r" (edx)
        :
        :);

    // Printing register values
    printf("Register values:");
    
    //printf("\n");
    printf("\nEAX: %d", eax);
    //printf("d\nd");
    printf("\nEBX: %d|", ebx);
    printf("\nECX: %d|   ", ecx);
    printf("\nEDX: %d|", edx);
    printf("\nHere");

}