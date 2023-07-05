#ifndef __GRAPHICS_H
#define _GRAPHICS_H 1
typedef unsigned char u8;

void vga_init(char *color);
void VGA_put_pixel(unsigned int x, unsigned int y,unsigned int pixel_size, unsigned int color);
void putpixel(int pos_x, int pos_y, unsigned char VGA_COLOR);
void draw_char(unsigned char c,int fgcolor, int bgcolor, int x, int y, int base_address);
void printf_graphics(char *string,char*color);
typedef unsigned       MEM_ADDR;

typedef unsigned char  BYTE;
#endif