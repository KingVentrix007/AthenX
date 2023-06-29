#include "../include/vga.h"
#include "../include/memory.h"
#include "../include/keyboardmap.h"
#include "../include/time.h"
#include "../include/def.h"
#include "../include/debug.h"
#include "../include/string.h"
unsigned char port_byte_in(unsigned short port) {
    unsigned char result;
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void port_byte_out(unsigned short port, unsigned char data) {
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}
void set_char_at_video_memory(unsigned char character, int offset, enum vga_color color) {
    unsigned char *vidmem = (unsigned char *) VIDEO_ADDRESS;
    vidmem[offset] = character;
    vidmem[offset + 1] = color;
}

void set_int_at_video_memory(unsigned int character, int offset, enum vga_color color)
{
    unsigned int *vidmem = (unsigned int *) VIDEO_ADDRESS;
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

void print_string(unsigned char *string, enum vga_color color) {
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
            write_serial("\n");
            offset = move_offset_to_new_line(offset);
            
        }
        else
        {
            set_char_at_video_memory(string[i], offset,color);
             write_serial(string[i]);
            offset += 2;

        }
        i++;
       
    }
    set_cursor(offset);
}

void print_int(unsigned int *string, enum vga_color color)
{
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
            write_serial("\n");
            offset = move_offset_to_new_line(offset);
            
        }
        else
        {
            set_int_at_video_memory(string[i], offset,color);
             write_serial(string[i]);
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

void putpixel(int pos_x, int pos_y, unsigned char VGA_COLOR)
{
    unsigned char* location = (unsigned char*)0xA0000 + 320 * pos_y + pos_x;
    *location = VGA_COLOR;
}


void terminal_write(const char *data, size_t size)
{
    size_t i;
    for (i = 0; i < size; i++)
        print_string(data[i],default_font_color);
}

int putchar(int ic)
{
    char c = (char)ic;
    terminal_write(&c, sizeof(c));
    return ic;
}

static void print(const char *data, size_t data_length)
{
    size_t i;
    for (i = 0; i < data_length; i++)
        putchar((int)((const unsigned char *)data)[i]);
}

int printf(const char *format, ...)
{
    va_list parameters;
    va_start(parameters, format);
    int written = 0;
    size_t amount;
    int rejected_bad_specifier = 0;
    while (*format != '\0')
    {
        if (*format != '%')
        {
        print_c:
            amount = 1;
            while (format[amount] && format[amount] != '%')
                amount++;
            print(format, amount);
            format += amount;
            written += amount;
            continue;
        }
        const char *format_begun_at = format;
        if (*(++format) == '%')
            goto print_c;
        if (rejected_bad_specifier)
        {
        incomprehensible_conversion:
            rejected_bad_specifier = 1;
            format = format_begun_at;
            goto print_c;
        }
        if (*format == 'c')
        {
            format++;
            char c = (char)va_arg(parameters, int /* char promotes to int */);
            print(&c, sizeof(c));
        }
        else if (*format == 'd')
        {
            format++;
            char *s;
            itoa(s, va_arg(parameters, int), 10);
            print(s, strlen(s));
        }
        else if (*format == 'f')
        {
            format++;
            char *s;
            ftoa_fixed(s, va_arg(parameters, double));
            print(s, strlen(s));
        }
        else if (*format == 'e')
        {
            format++;
            char *s;
            ftoa_sci(s, va_arg(parameters, double));
            print(s, strlen(s));
        }
        else if (*format == 'x')
        {
            format++;
            char *s;
            itoa(s, va_arg(parameters, unsigned int), 16);
            print("0x", 2);
            print(s, strlen(s));
        }
        else if (*format == 'p')
        {
            format++;
            char *s;
            const void *ptr = va_arg(parameters, void *);
            uintptr_t uptr = (uintptr_t)ptr;
            itoa(s, uptr, 16);
            print("0x", 2);
            print(s, strlen(s));
        }
        else if (*format == 's')
        {
            format++;
            const char *s = va_arg(parameters, const char *);
            print(s, strlen(s));
        }
        else
        {
            goto incomprehensible_conversion;
        }
    }
    va_end(parameters);
    return written;
}