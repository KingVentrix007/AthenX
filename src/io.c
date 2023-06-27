#include "../include/io.h"
void out_bytes(uint16_t port, uint8_t val)
{
    asm volatile ("outb %0,%1" : : "a"(val),"Nd"(port):"memory");
}

uint8_t input_bytes(uint16_t port)
{
    uint8_t ret;
    __asm__ __volatile__("inb %1, %0"
                         : "= a"(ret)
                         : "Nd"(port));
    return ret;
}


uint8_t scan(void)
{
    unsigned char brk;
    static uint8_t key = 0;
    uint8_t read_char = input_bytes(0x60); // keyboard port
    brk = read_char & 0x80;
    read_char = read_char & 0x7f;
    if (brk)
    {
        return key = 0;
    }
    else if (read_char != key)
    {
        return key = read_char;
    }
    else
    {
        return 0;
    }
}
