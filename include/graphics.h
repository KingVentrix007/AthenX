#ifndef __GRAPHICS_H
#define _GRAPHICS_H 1

void vga_init();
void VGA_put_pixel(unsigned int x, unsigned int y,unsigned int pixel_size, unsigned int color);
void putpixel(int pos_x, int pos_y, unsigned char VGA_COLOR);
void draw_char(unsigned char c,int fgcolor, int bgcolor, int x, int y, int base_address);
typedef unsigned       MEM_ADDR;

typedef unsigned char  BYTE;
#endif