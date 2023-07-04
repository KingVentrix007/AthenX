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
    printf("\nEAX: %x", eax);
    //printf("d\nd");
    printf("\nEBX: %x|", ebx);
    printf("\nECX: %x|   ", ecx);
    printf("\nEDX: %x|", edx);
    //printf("\n%s",__FILE__);

}



void PANIC_T(char* msg)
{
    for (size_t y = 0; y <= 80; y++)
    {
        for (size_t x = 0; x <= 25; x++)
        {
            int offset = 2 * (x * 80 + y);
            unsigned char *vidmem = (unsigned char *) VIDEO_ADDRESS;
            vidmem[offset] = ' ';
            vidmem[offset + 1] = 1;
        }
        //delay(1);
        
    }
    printf(msg);
    printf("LINE(%d), FILE(%s),",__LINE__,__FILE__);
    for(;;);
    


}