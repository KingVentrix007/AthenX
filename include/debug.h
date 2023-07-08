#ifndef _DEBUG_H
#define _DEBUG_H 1
#define PORT 0x3f8
#include "../include/serial.h"
#include <graphics.h>
typedef unsigned int u32;
typedef struct {
    u32 cr3;
    u32 esp;
    u32 cr2;
    u32 ds;
    u32 ebp;
    u32 edi;
    u32 esi;
    u32 edx;
    u32 ecx;
    u32 ebx;
    u32 eax;
    u32 vector;
    u32 err_code;
    u32 eip;
    u32 cs_old;
    u32 eflags;
} ir_context_t;
typedef struct registers
{
    int eax, ebx, ecx, edx,esi,edi,esp,ebp;
};

void reg();
struct registers log_reg();
void cmp_reg(struct registers reg_old);
void PANIC_T(char* msg);
#include "tty.h"
#define PANIC(...) do {cls_screen(COLOR_WHITE);kprintf("PANIC at %s@%d (%s):", __FILE__, __LINE__, __FUNCTION__); \
                     kprintf(__VA_ARGS__);kprintf("\n"); reg();\
                     } while(0);
#endif