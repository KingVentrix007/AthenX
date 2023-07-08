#ifndef _KB_H
#define _KB_H 1
#include "gdt.h"
char get_wait_key_in(char* wait_for);
char* wait_for_any_key();
extern void keyboard_install();
#endif