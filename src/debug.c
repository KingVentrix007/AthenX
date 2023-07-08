#include "../include/debug.h"
#include "../include/io.h"
#include "../include/string.h"
#include "../include/tty.h"
#include "../include/vga.h"
// struct registers
// {
//     int eax, ebx, ecx, edx,esi,edi,esp,ebp;
// }registers_save;
struct registers registers_save;
void reg()
{
    int eax, ebx, ecx, edx,esi,edi,esp,ebp;

    // Inline assembly to move register values to variables
    asm volatile(
        "movl %%eax, %0\n\t"
        "movl %%ebx, %1\n\t"
        "movl %%ecx, %2\n\t"
        "movl %%edx, %3\n\t"
        
        : "=r" (eax), "=r" (ebx), "=r" (ecx), "=r" (edx)
        :
        :);
    asm volatile(
        "movl %%esi, %0\n\t"
        "movl %%edi, %1\n\t"
        "movl %%esp, %2\n\t"
        "movl %%ebp, %3\n\t"

        : "=r" (esi), "=r" (edi), "=r" (esp), "=r" (ebp)
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
    printf("\nESI: %x|", esi);
    printf("\nEDI: %x|",edi);

    printf("\nStack Pointer: %x",esp);
    printf("\nStack Base Pointer %x",ebp);
    //printf("\n%s",__FILE__);

}

void cmp_reg(struct registers reg_old)
{
    int eax, ebx, ecx, edx,esi,edi,esp,ebp;

    // Inline assembly to move register values to variables
    asm volatile(
        "movl %%eax, %0\n\t"
        "movl %%ebx, %1\n\t"
        "movl %%ecx, %2\n\t"
        "movl %%edx, %3\n\t"
        
        : "=r" (eax), "=r" (ebx), "=r" (ecx), "=r" (edx)
        :
        :);
    asm volatile(
        "movl %%esi, %0\n\t"
        "movl %%edi, %1\n\t"
        "movl %%esp, %2\n\t"
        "movl %%ebp, %3\n\t"

        : "=r" (esi), "=r" (edi), "=r" (esp), "=r" (ebp)
        :
        :);
    
    // Printing register values
    printf("Register values:");
    
    //printf("\n");
    printf("\nEAX: %x\nEAX before error: %x\n", eax,reg_old.eax);
    //printf("d\nd");
    printf("\nEBX: %x\nEBX before error: %x\n", ebx,reg_old.ebx);
    printf("\nECX: %x\nECX before error: %x\n", ecx, reg_old.ecx);
    printf("\nEDX: %x\nEDX before error: %x\n", edx,reg_old.edx);
    printf("\nESI: %x\nESI before error: %x\n", esi,reg_old.esi);
    printf("\nEDI: %x\nEDI before error: %x\n",edi,reg_old.edi);

    printf("\nStack Pointer: %x",esp);
    printf("\nOld Stack pointer: %x",reg_old.esp);
    printf("\nStack Base Pointer: %x",ebp);
    printf("\nOld Stack Base Pointer: %x",reg_old.ebp);
}

struct registers log_reg()
{
    int eax, ebx, ecx, edx,esi,edi,esp,ebp;

    // Inline assembly to move register values to variables
    asm volatile(
        "movl %%eax, %0\n\t"
        "movl %%ebx, %1\n\t"
        "movl %%ecx, %2\n\t"
        "movl %%edx, %3\n\t"
        
        : "=r" (eax), "=r" (ebx), "=r" (ecx), "=r" (edx)
        :
        :);
    asm volatile(
        "movl %%esi, %0\n\t"
        "movl %%edi, %1\n\t"
        "movl %%esp, %2\n\t"
        "movl %%ebp, %3\n\t"

        : "=r" (esi), "=r" (edi), "=r" (esp), "=r" (ebp)
        :
        :);
    registers_save.eax = eax;
    registers_save.ebx = ebx;
    registers_save.ecx = ecx;
    registers_save.edx = edx;
    registers_save.esi = esi;
    registers_save.edi = edi;
    registers_save.esp = esp;
    registers_save.ebp = ebp;
    return registers_save;
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
    //PANIC(msg);
    //for(;;);
    


}