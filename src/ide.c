#include "../include/ide.h"
#include "../include/io.h"

char* read()
{
    char *bu = "k";
    out_bytes(0x1f6,0x0a0);
    out_bytes(0x1f2,1);
    out_bytes(0x1f3,1);
    out_bytes(0x1f4,0);
    out_bytes(0x1f5,0);
    out_bytes(0x1f7,0x31);
    out_bytes(0x1F0,bu);
    out_bytes(0x1f6,0x0a0);
    out_bytes(0x1f2,1);
    out_bytes(0x1f3,1);
    out_bytes(0x1f4,0);
    out_bytes(0x1f5,0);
    out_bytes(0x1f7,0x20);
    char* fis;
    fis = inw(0x1f0);
    return fis;
    
}

