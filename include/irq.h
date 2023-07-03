#ifndef _IRQ_H
#define _IRQ_H 1
#include "gdt.h"
extern void irq_install_handler(int irq, void (*handler)(struct regs *r));
extern void irq_uninstall_handler(int irq);
extern void irq_install();
#endif