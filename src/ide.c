#include "../include/ide.h"
#include "../include/io.h"
#include "../include/debug.h"
#include "../include/string.h"

static __inline unsigned char inb(int port)
{
  unsigned char data;
  asm __volatile("inb %w1,%0" : "=a" (data) : "d" (port));
  return data;
}
static __inline void outb(int port, unsigned char data)
{
  asm __volatile("outb %0,%w1" : : "a" (data), "d" (port));
}
unsigned char read(int sec)
{
    char* bu = 'k';

    outb(0x1f6,0x0a0);
    outb(0x1f2,1);
    outb(0x1f3,sec);
    outb(0x1f4,0);
    outb(0x1f5,0);
    outb(0x1f0,'g');
    outb(0x1f7,IDE_CMD_WRITE);
    
    outb(0x1f6,0x0a0);
    outb(0x1f2,1);
    outb(0x1f3,sec);
    outb(0x1f4,0);
    outb(0x1f5,0);
    outb(0x1f7,IDE_CMD_READ);
    unsigned char fis;
    
    fis = inb(0x1f0);
    if(fis == 255)
    {
        //write_serial(fis);
        print_string("HELLO");   
    }
    //write_serial(fis);
    //write_serial(inb(0x1f0));
   
    
    return inb(0x1f0);
    
}



