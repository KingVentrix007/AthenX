#ifndef _IO_H
#define _IO_H 1
#include <stdint.h>
uint8_t input_bytes(uint16_t port);
void out_bytes(uint16_t port, uint8_t val);
uint8_t scan(void);
void output_bytes(uint16_t port, uint8_t val);
uint8_t inw(uint16_t port);
void outw(uint16_t port, uint16_t data);







#endif