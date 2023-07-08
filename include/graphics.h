#ifndef __GRAPHICS_H
#define _GRAPHICS_H 1
typedef unsigned char u8;
#define BIOS_VGA_GET_FONT 4
void vga_init(char *color);
void VGA_put_pixel(unsigned int x, unsigned int y,unsigned int pixel_size, unsigned int color);
void putpixel(int pos_x, int pos_y, unsigned char VGA_COLOR);
void draw_char(unsigned char c,int fgcolor, int bgcolor, int x, int y, int base_address);
void printf_graphics(char *string,char*color);
typedef unsigned       MEM_ADDR;
void VGA_clear_screen(char *color);
void draw_img(int img[][31], int start_x, int start_y,int img_h,int img_w);
void draw_logo(int start_x, int start_y);
int printChar(int x, int y, char c);
void draw_rand_img();
char set_font_mode(char* mode);
char* display_logo();
typedef unsigned char  BYTE;


#define Default_screen_color COLOR_BLACK
#define Default_font_color COLOR_GREEN
#endif