#ifndef _IDT_H
#define _IDT_H 1

extern void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
extern void idt_install();
#endif