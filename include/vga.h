#ifndef _VGA_H
#define _VGA_H 1

#include "stdint.h"
#include "stddef.h"
#include "stdarg.h"
#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f
#define VGA_CTRL_REGISTER 0x3d4
#define VGA_DATA_REGISTER 0x3d5
#define VGA_OFFSET_LOW 0x0f
#define VGA_OFFSET_HIGH 0x0e
enum vga_color
{
    COLOR_BLACK = 0,
    COLOR_BLUE = 1,
    COLOR_GREEN = 2,
    COLOR_CYAN = 3,
    COLOR_RED = 4,
    COLOR_MAGENTA = 5,
    COLOR_BROWN = 6,
    COLOR_LIGHT_GREY = 7,
    COLOR_DARK_GREY = 8,
    COLOR_LIGHT_BLUE = 9,
    COLOR_LIGHT_GREEN = 10,
    COLOR_LIGHT_CYAN = 11,
    COLOR_LIGHT_RED = 12,
    COLOR_LIGHT_MAGENTA = 13,
    COLOR_LIGHT_BROWN = 14,
    COLOR_WHITE = 15,
};
static enum vga_color default_font_color = COLOR_WHITE;
void print_string(char *string, enum vga_color color);
void set_char_at_video_memory(char character, int offset,enum vga_color);
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


#endif