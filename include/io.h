#ifndef _IO_H
#define _IO_H 1
#include <stdint.h>
uint8_t input_bytes(uint16_t port);
void out_bytes(uint16_t port, uint8_t val);
uint8_t scan(void);







#endif