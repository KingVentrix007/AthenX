#include "../include/vga.h"
#include "../include/memory.h"
#include "../include/keyboardmap.h"
#include "../include/time.h"
#include "../include/def.h"
unsigned char port_byte_in(unsigned short port) {
    unsigned char result;
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void port_byte_out(unsigned short port, unsigned char data) {
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}
void set_char_at_video_memory(char character, int offset, enum vga_color color) {
    unsigned char *vidmem = (unsigned char *) VIDEO_ADDRESS;
    vidmem[offset] = character;
    vidmem[offset + 1] = color;
}
void set_cursor(int offset) {
    offset /= 2;
    port_byte_out(VGA_CTRL_REGISTER, VGA_OFFSET_HIGH);
    port_byte_out(VGA_DATA_REGISTER, (unsigned char) (offset >> 8));
    port_byte_out(VGA_CTRL_REGISTER, VGA_OFFSET_LOW);
    port_byte_out(VGA_DATA_REGISTER, (unsigned char) (offset & 0xff));
}

int get_cursor() {
    port_byte_out(VGA_CTRL_REGISTER, VGA_OFFSET_HIGH);
    int offset = port_byte_in(VGA_DATA_REGISTER) << 8;
    port_byte_out(VGA_CTRL_REGISTER, VGA_OFFSET_LOW);
    offset += port_byte_in(VGA_DATA_REGISTER);
    return offset * 2;
}


int get_row_from_offset(int offset) {
    return offset / (2 * MAX_COLS);
}

int get_offset(int col, int row) {
    return 2 * (row * MAX_COLS + col);
}


int move_offset_to_new_line(int offset) {
    return get_offset(0, get_row_from_offset(offset) + 1);
}

void print_string(char *string, enum vga_color color) {
    int offset = get_cursor();
    int i = 0;
    while (string[i] != 0) {
        if (offset >= MAX_COLS*MAX_ROWS*2) 
        {
            offset = scroll(offset);

        }
        if (string[i] == '\n' || string == ENTER)
        {
            
            set_char_at_video_memory(' ', get_cursor(),color);
            offset = move_offset_to_new_line(offset);
            
        }
        else
        {
            set_char_at_video_memory(string[i], offset,color);
            
            offset += 2;

        }
        i++;
       
    }
    set_cursor(offset);
}
void print_backspace() {
    int newCursor = get_cursor() - 2;
    set_char_at_video_memory(' ', newCursor,default_font_color);
    set_char_at_video_memory(' ', newCursor+1,default_font_color);
    set_char_at_video_memory(' ', newCursor+2,default_font_color);
    set_cursor(newCursor);
}

void display_init()
{
    set_cursor(0);
    for (int i = 0; i < MAX_COLS*MAX_ROWS; i++)
    {
        set_char_at_video_memory(' ',i*2,default_font_color);
    }
    set_cursor(0);
}

int scroll(int offset)
{
    memory_copy((char *)(get_offset(0,1)+VIDEO_ADDRESS),(char *)(get_offset(0,0)+VIDEO_ADDRESS),MAX_COLS*(MAX_ROWS-1)*2);
    for (int col = 0; col < MAX_COLS; col++)
    {
        set_char_at_video_memory(' ',get_offset(col,MAX_ROWS-1),default_font_color);
    }
    return offset - 2*MAX_COLS;
    

}
void print_prompt(char *prompt,enum vga_color color)
{
    print_string(prompt,color);
}
int cursor_flash()
{
    set_char_at_video_memory('_',get_cursor(),default_font_color);
}