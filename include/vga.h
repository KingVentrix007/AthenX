#ifndef _VGA_H
#define _VGA_H 1

#include "stdint.h"
#include "stddef.h"
#include "stdarg.h"
#define VIDEO_ADDRESS 0xb8000
#define VIDEO_PIXEL_MEMORY 0xb0000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f
#define VGA_CTRL_REGISTER 0x3d4
#define VGA_DATA_REGISTER 0x3d5
#define VGA_OFFSET_LOW 0x0f
#define VGA_OFFSET_HIGH 0x0e
#include "tty.h"
void print_string(unsigned char *string, enum vga_color color);
void set_char_at_video_memory(unsigned char character, int offset, enum vga_color color);
unsigned char port_byte_in(unsigned short port);
void port_byte_out(unsigned short port, unsigned char data);
int get_cursor();
void set_cursor(int offset);
int get_row_from_offset(int offset);
int get_offset(int col, int row);
int move_offset_to_new_line(int offset);
void print_backspace();
void display_init();
int cursor_flash();
void print_prompt(char *prompt,enum vga_color color);
//void putpixel(int pos_x, int pos_y, unsigned char VGA_COLOR);
void set_int_at_video_memory(unsigned int character, int offset, enum vga_color color);
void print_int(unsigned int *string, enum vga_color color);




#endif