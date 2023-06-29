#ifndef _DEBUG_H
#define _DEBUG_H 1
#define PORT 0x3f8
void write_serial(char a);
int is_transmit_empty();
int init_serial();
void write_serial_i(int a);




#endif