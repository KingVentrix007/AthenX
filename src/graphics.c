#include "../include/graphics.h"
#include "../include/vga.h"
#include "../include/tty.h"
#include "../include/string.h"
#include "../include/time.h"
#include "../include/fonts.h"
#include "../include/maths.h"
#include <font.h>
#include "../include/logos.h"
static u8 __bios_font_data[FONTS_MAX_CHARS*16];
static u8 __have_bios_data = 0;
#define VGA_AC_INDEX 0x3C0
#define VGA_AC_WRITE 0x3C0
#define VGA_AC_READ 0x3C1
#define VGA_MISC_WRITE 0x3C2
#define VGA_SEQ_INDEX 0x3C4
#define VGA_SEQ_DATA 0x3C5
#define VGA_DAC_READ_INDEX 0x3C7
#define VGA_DAC_WRITE_INDEX 0x3C8
#define VGA_DAC_DATA 0x3C9
#define VGA_MISC_READ 0x3CC
#define VGA_GC_INDEX 0x3CE
#define VGA_GC_DATA 0x3CF
#define VGA_CRTC_INDEX 0x3D4 /* 0x3B4 */
#define VGA_CRTC_DATA 0x3D5 /* 0x3B5 */
#define VGA_INSTAT_READ 0x3DA
#define VGA_NUM_SEQ_REGS 5
#define VGA_NUM_CRTC_REGS 25
#define VGA_NUM_GC_REGS 9
#define VGA_NUM_AC_REGS 21
#define VGA_NUM_REGS (1 + VGA_NUM_SEQ_REGS + VGA_NUM_CRTC_REGS + VGA_NUM_GC_REGS + VGA_NUM_AC_REGS)

unsigned int   VGA_width;
unsigned int   VGA_height;
unsigned int   VGA_bpp;
unsigned char *VGA_address;
unsigned int VGA_colum;
unsigned int VGA_row;

 

unsigned char mode_320_200_256[] = {
	/* MISC
    *
    * 0x63 => 01100011
    * 7 6 5 4 3 2 1 0
    * 1 1 0 0 0 1 1 0
    * VSP HSP - - CS CS ERAM IOS
    * 7,6 - 480 lines
    * 5,4 - free
    * 3,2 - 28,322 MHZ Clock
    * 1 - Enable Ram
    * 0 - Map 0x3d4 to 0x3b4
    */
	0x63,
	/* SEQ */
	/**
    * index 0x00 - Reset
    * 0x03 = 11
    * Bits 1,0 Synchronous reset
    */
	0x03,
	/**
    * index 0x01
    * Clocking mode register
    * 8/9 Dot Clocks
    */
	0x01,
	/**
    * Map Mask Register, 0x02
    * 0x0F = 1111
    * Enable all 4 Maps Bits 0-3
    * chain 4 mode
    */
	0x0F,
	/**
    * map select register, 0x03
    * no character map enabled
    */
	0x00,
	/**
    * memory mode register 0x04
    * enables ch4,odd/even,extended memory
    */
	0x0E,
	/* CRTC */
	0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0xBF, 0x1F,
	0x00, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x9C, 0x0E, 0x8F, 0x28, 0x40, 0x96, 0xB9, 0xA3,
	0xFF,
	/* GC */
	0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x05, 0x0F,
	0xFF,
	/* AC */
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
	0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
	0x41, 0x00, 0x0F, 0x00, 0x00
};

void write_registers(unsigned char *regs)
{
	unsigned i;

	/* write MISCELLANEOUS reg */
	output_bytes(VGA_MISC_WRITE, *regs);
	regs++;
	/* write SEQUENCER regs */
	for (i = 0; i < VGA_NUM_SEQ_REGS; i++)
	{
		output_bytes(VGA_SEQ_INDEX, i);
		output_bytes(VGA_SEQ_DATA, *regs);
		regs++;
	}
	/* unlock CRTC registers */
	output_bytes(VGA_CRTC_INDEX, 0x03);
	output_bytes(VGA_CRTC_DATA, input_bytes(VGA_CRTC_DATA) | 0x80);
	output_bytes(VGA_CRTC_INDEX, 0x11);
	output_bytes(VGA_CRTC_DATA, input_bytes(VGA_CRTC_DATA) & ~0x80);
	/* make sure they remain unlocked */
	regs[0x03] |= 0x80;
	regs[0x11] &= ~0x80;
	/* write CRTC regs */
	for (i = 0; i < VGA_NUM_CRTC_REGS; i++)
	{
		output_bytes(VGA_CRTC_INDEX, i);
		output_bytes(VGA_CRTC_DATA, *regs);
		regs++;
	}
	/* write GRAPHICS CONTROLLER regs */
	for (i = 0; i < VGA_NUM_GC_REGS; i++)
	{
		output_bytes(VGA_GC_INDEX, i);
		output_bytes(VGA_GC_DATA, *regs);
		regs++;
	}
	/* write ATTRIBUTE CONTROLLER regs */
	for (i = 0; i < VGA_NUM_AC_REGS; i++)
	{
		(void)input_bytes(VGA_INSTAT_READ);
		output_bytes(VGA_AC_INDEX, i);
		output_bytes(VGA_AC_WRITE, *regs);
		regs++;
	}

	/* lock 16-color palette and unblank display */
	(void)input_bytes(VGA_INSTAT_READ);
	output_bytes(VGA_AC_INDEX, 0x20);
}
void VGA_clear_screen(char *color)
{
	unsigned int x = 0;
	unsigned int y = 0;

	for (y = 0; y < VGA_height; y++)
	{
		for (x = 0; x < VGA_width; x++)
		{
			VGA_address[VGA_width * y + x] = color;
		}
	}
}
void VGA_put_pixel(unsigned int x, unsigned int y,unsigned int pixel_size, unsigned int color)
{
	for (int py = y; py < y+pixel_size; py++)
	{
		for (int px = x; px < x+pixel_size; px++)
		{
			VGA_address[VGA_width * (py) + (px)] = color;
		}
		
	}
	
	
}
void putpixel(int pos_x, int pos_y, unsigned char VGA_COLOR)
{
    unsigned char* location = (unsigned char*)0xA0000 + 320 * pos_y + pos_x;
    *location = VGA_COLOR;
}

void vga_init(char *color)
{
	int width  = 320;
	int height = 200;
	int bpp    = 256;
	int colum = 0;
	int row = 0;
    //set_t(row,colum);
	//setup the vga struct
	VGA_width   = (unsigned int)width;
	VGA_height  = (unsigned int)height;
	VGA_bpp     = bpp;
	VGA_address = (void *)0xA0000;
	VGA_colum = (unsigned int)colum;
	VGA_row = (unsigned int)row;

	//enables the mode 13 state
	write_registers(mode_320_200_256);

	//clears the screen
	VGA_clear_screen(color);
	//_kill();
}
char* font_mode = "normal";
void draw_char(unsigned char c,int fgcolor, int bgcolor, int x, int y, int base_address){
	if(strcmp(font_mode,"normal")==0)
	{
		char *bitmap = arr_8x8_font;
		int x_char,y_char;
		static unsigned mask[] = {
			1u << 0u, //            1
			1u << 1u, //            2
			1u << 2u, //            4
			1u << 3u, //            8
			1u << 4u, //           16
			1u << 5u, //           32
			1u << 6u, //           64
			1u << 7u, //          128
			1u << 8u, //          256
		};
		unsigned char *gylph=bitmap+(int)c*8;
		for(y_char=0;y_char<8;++y_char){
			for(x_char=0;x_char<8;++x_char){
				plot_pixel(x+(8-x_char),y+y_char,base_address,gylph[y_char]&mask[x_char]?fgcolor:bgcolor);
			}
		}

	}
	else if (strcmp(font_mode,"small") == 0)
	{
		printChar(x,y,c);
	}
	
	
}

void plot_pixel(int x, int y, int base_address, char* pixel_color){
  int pixel_location = (y*VGA_width) + x;
  //putpixel(x,y,pixel_color);
   unsigned char* location = (VGA_address+pixel_location+base_address);
	*location = pixel_color;
  //poke_b ((0xA0000 + pixel_location + base_address), pixel_color);
}

void putchar_graphics_mode(char * c,int x, int y, char* color)
{
	draw_char(c,color,Default_screen_color,x,y,0);
}

void print(char *c,char*color)
{
	if(c == '\n')
	{
			VGA_colum = VGA_colum+8;
			VGA_row = -8;
	}
	else if (c == '\t')
	{
		VGA_row = VGA_row +(8*4);
	}
	
	
	putchar_graphics_mode(c,VGA_row,VGA_colum,color);
	VGA_row = VGA_row + 8;
}

void printf_graphics(char *string,char*color)
{
	for (int i = 0; i < strlen(string); i++)
	{
		
		print(string[i],color);
	}
	
}


void draw_img(int img[][31], int start_x, int start_y,int img_h,int img_w)
{
	set_terminal_row(0);
	set_terminal_colum(0);
	
	// for (int h = 0; h < img_h; h++)
	// {
	// 	for (int w = 0; w < img_w; w++)
	// 	{
	// 		putpixel(start_x+w,start_y+h,img[h][w]);
	// 	}
		
	// }
	
}

int printChar(int x, int y, char c) {
	// Loop to "null terminator character"
	int match = 0;
	for (int l = 0; font[l].letter != 0; l++) {
		if (font[l].letter == c) {
			match = l;
			break;
		}
	}

	// Loop through 7 high 5 wide monochrome font
	int maxLength = 0;
	for (int py = 0; py < 7; py++) {
		for (int px = 0; px < 5; px++) {
			if (font[match].code[py][px] == '#') {
				putpixel(x + px, y + py,Default_font_color);

				// Dynamix width character spacing
				if (px > maxLength) {
					maxLength = px;
				}
			}
		}
	}

	return maxLength;
}


void draw_logo(int start_x, int start_y)
{
	//char *logo = log_img;
	cls_screen(COLOR_LIGHT_GREEN);
	int img_h = 201;
	int img_w = 320;
	for (int h = 0; h < img_h; h++)
	{
		for (int w = 0; w < img_w; w++)
		{
			if(strcmp(logo_img[h][w],'#') == 0){
				putpixel(start_x+w,start_y+h,Default_screen_color);
			}
			else
			{
				putpixel(start_x+w,start_y+h,Default_font_color);
			}
			
		}
		
	}
}

void draw_rand_img()
{
	cls_screen(COLOR_LIGHT_GREEN);
	int img_h = VGA_height;
	int img_w = VGA_width;
	for (int h = 0; h < img_h; h++)
	{
		for (int w = 0; w < img_w; w++)
		{
			char* color = small_rand();
			
			putpixel(w,h,color);
		}
		
	}

}

//internal function

// char draw_shape(char shape)
// {


// }

void put_pixel(int x, int y, int pixel_size,char color)
{
	

}
char set_font_mode(char* mode)
{
	font_mode = mode;
}

char* display_logo()
{
	cls_screen(Default_screen_color);
	draw_logo(0,0);
	set_terminal_row(20);
	set_terminal_colum(192);
	printf("Press 'b' to boot or 'h' for help");
	set_terminal_row(125);
	set_terminal_colum(120);
	printf("AthenX");
	char* key = wait_for_any_key();
	//get_wait_key_in("b");
	VGA_clear_screen(Default_screen_color);
	set_terminal_colum(30);
	set_terminal_row(30);
	//key = 'g';
	//printf("g");
	//printf(key);
	set_terminal_colum(0);
	set_terminal_row(0);
	return key;
              //delay(200);
}