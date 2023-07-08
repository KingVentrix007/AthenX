#include "../include/tty.h"
#include "../include/string.h"
#include "../include/debug.h"
#include "../include/def.h"
#include "../include/graphics.h"
size_t terminal_row;
size_t terminal_column;
static uint16_t *const VGA_MEMORY = (uint16_t *)0xb8000;
uint8_t terminal_color;
uint16_t *terminal_buffer;

#define BUFFER_SIZE 1024

static inline uint8_t make_color(enum vga_color fg, enum vga_color bg)
{
    return fg | bg << 4;
}

static inline uint16_t make_vgaentry(char c, uint8_t color)
{
    uint16_t c16 = c;
    uint16_t color16 = color;
    return c16 | color16 << 8;
}

void terminal_initialize(enum vga_color font_color, enum vga_color background_color)
{
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = make_color(font_color, background_color);
    terminal_buffer = VGA_MEMORY;
    size_t y;
    for (y = 0; y < VGA_HEIGHT; y++)
    {
        size_t x;
        for (x = 0; x < VGA_WIDTH; x++)
        {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = make_vgaentry(' ', terminal_color);
        }
    }
}

void terminal_scroll()
{
    VGA_clear_screen(Default_screen_color);
    terminal_column = 0;
    terminal_row = 0;
    // int i;
    // for (i = 0; i < VGA_HEIGHT; i++)
    // {
    //     int m;
    //     for (m = 0; m < VGA_WIDTH; m++)
    //     {
    //         terminal_buffer[i * VGA_WIDTH + m] = terminal_buffer[(i + 1) * VGA_WIDTH + m];
    //     }
    //     terminal_row--;
    // }
    // //terminal_row = VGA_HEIGHT - 1;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
    //draw_char(c,color,COLOR_WHITE,y,x,0);
    // if(strcmp(c," ") == 0)
    // {
    //     //printf("HERE");
    // }
    draw_char(c,color,Default_screen_color,y,x,0);
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = make_vgaentry(c, color);
}

void terminal_putchar(char c)
{
    if (c == '\n' || c == '\r')
    {
        terminal_column = terminal_column+8;
        terminal_row = 0;
        if (terminal_column == VGA_HEIGHT)
            terminal_scroll();
        return;
    }
    else if (c == '\t')
    {
        terminal_row = terminal_row +4*8;
        return;
    }
    else if (c == '\b')
    {
        terminal_row = terminal_row - 8;
       
        terminal_putentryat(' ', terminal_color, terminal_column, terminal_row);
        terminal_putentryat(' ', terminal_color, terminal_column, terminal_row);
         //printf(" ");
        return;
    }
    terminal_putentryat(c, default_font_color, terminal_column, terminal_row);
    terminal_row = terminal_row +8;
    //terminal_column = terminal_column;
   if(terminal_row >= VGA_WIDTH)
   {
        terminal_column = terminal_column+8;
        terminal_row = 0;
        //printf("90023");
        //write_serial("Q",DEFAULT_COM_DEBUG_PORT);
        

   }
    //terminal_column = terminal_column -1;
}

void terminal_write(const char *data, size_t size)
{
    size_t i;
    for (i = 0; i < size; i++)
        terminal_putchar(data[i]);
}

int putchar(int ic)
{
    char c = (char)ic;
    terminal_write(&c, sizeof(c));
    return ic;
}
void cls_screen(char *color)
{
    VGA_clear_screen(color);
    terminal_column = 0;
    terminal_row = 0;
}
void term_putc(char c, enum vga_color char_color)
{
    unsigned int i = 0; // place holder for text string position
    unsigned int j = 0; // place holder for video buffer position

    int index;
    // Remember - we don't want to display ALL characters!
    switch (c)
    {
    case '\n': // Newline characters should return the column to 0, and increment the row
    {
        terminal_column = 0;
        terminal_row += 2;
        break;
    }

    default: // Normal characters just get displayed and then increment the column
    {
        index = (VGA_WIDTH * terminal_row) + terminal_column; // Like before, calculate the buffer index
        VGA_MEMORY[index] = c;
        VGA_MEMORY[index + 1] = char_color;
        // terminal_column += 2;
        break;
    }
    }

    // What happens if we get past the last column? We need to reset the column to 0, and increment the row to get to a new line
    if (terminal_column >= VGA_WIDTH)
    {
        terminal_column = 0;
        terminal_row++;
    }

    // What happens if we get past the last row? We need to reset both column and row to 0 in order to loop back to the top of the screen
    if (terminal_row >= VGA_WIDTH)
    {
        terminal_column = 0;
        terminal_row = 0;
    }
}

// This function prints an entire string onto the screen
// void term_print(const char *str)
// {
//     int i;
//     for (i = 0; str[i] != '\0'; i++)
//     { // Keep placing characters until we hit the null-terminating character ('\0')
//         term_putc(str[i]);
//     }
// }

static void print(const char *data, size_t data_length)
{
    size_t i;
    for (i = 0; i < data_length; i++)
        putchar((int)((const unsigned char *)data)[i]);
}

int normalize(double *val)
{
    int exponent = 0;
    double value = *val;

    while (value >= 1.0)
    {
        value /= 10.0;
        ++exponent;
    }

    while (value < 0.1)
    {
        value *= 10.0;
        --exponent;
    }
    *val = value;
    return exponent;
}

static void ftoa_fixed(char *buffer, double value)
{
    /* carry out a fixed conversion of a double value to a string, with a precision of 5 decimal digits.
     * Values with absolute values less than 0.000001 are rounded to 0.0
     * Note: this blindly assumes that the buffer will be large enough to hold the largest possible result.
     * The largest value we expect is an IEEE 754 double precision real, with maximum magnitude of approximately
     * e+308. The C standard requires an implementation to allow a single conversion to produce up to 512
     * characters, so that's what we really expect as the buffer size.
     */

    int exponent = 0;
    int places = 0;
    static const int width = 4;

    if (value == 0.0)
    {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }

    if (value < 0.0)
    {
        *buffer++ = '-';
        value = -value;
    }

    exponent = normalize(&value);

    while (exponent > 0)
    {
        int digit = value * 10;
        *buffer++ = digit + '0';
        value = value * 10 - digit;
        ++places;
        --exponent;
    }

    if (places == 0)
        *buffer++ = '0';

    *buffer++ = '.';

    while (exponent < 0 && places < width)
    {
        *buffer++ = '0';
        --exponent;
        ++places;
    }

    while (places < width)
    {
        int digit = value * 10.0;
        *buffer++ = digit + '0';
        value = value * 10.0 - digit;
        ++places;
    }
    *buffer = '\0';
}

void ftoa_sci(char *buffer, double value)
{
    int exponent = 0;
    int places = 0;
    static const int width = 4;

    if (value == 0.0)
    {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }

    if (value < 0.0)
    {
        *buffer++ = '-';
        value = -value;
    }

    exponent = normalize(&value);

    int digit = value * 10.0;
    *buffer++ = digit + '0';
    value = value * 10.0 - digit;
    --exponent;

    *buffer++ = '.';

    for (int i = 0; i < width; i++)
    {
        int digit = value * 10.0;
        *buffer++ = digit + '0';
        value = value * 10.0 - digit;
    }

    *buffer++ = 'e';
    itoa(buffer, exponent, 10);
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

int get_terminal_row(void)
{
    return terminal_row;
}

int get_terminal_col(void)
{
    return terminal_column;
}
int set_terminal_row(int row)
{
    terminal_row = row;
}

int set_terminal_colum(int col)
{
    return terminal_column = col;
}

void terminal_set_colors(enum vga_color font_color, enum vga_color background_color)
{
    terminal_color = make_color(font_color, background_color);
    default_font_color = font_color;

    // terminal_buffer = VGA_MEMORY;
    // size_t y;
    // for (y = 0; y < VGA_HEIGHT; y++)
    // {
    //     size_t x;
    //     for (x = 0; x < VGA_WIDTH; x++)
    //     {
    //         const size_t index = y * VGA_WIDTH + x;
    //         terminal_buffer[index] = make_vgaentry('\0', terminal_color);
    //     }
    // }
}

void kprintf(char * template,...)
{
    //PANIC_T("null");
    va_list parameters;
    va_start(parameters, template);
    int written = 0;
    size_t amount;
    int rejected_bad_specifier = 0;
    while (*template != '\0')
    {
        if (*template != '%')
        {
        print_c:
            amount = 1;
            while (template[amount] && template[amount] != '%')
                amount++;
            print(template, amount);
            template += amount;
            written += amount;
            continue;
        }
        const char *template_begun_at = template;
        if (*(++template) == '%')
            goto print_c;
        if (rejected_bad_specifier)
        {
        incomprehensible_conversion:
            rejected_bad_specifier = 1;
            template = template_begun_at;
            goto print_c;
        }
        if (*template == 'c')
        {
            template++;
            char c = (char)va_arg(parameters, int /* char promotes to int */);
            print(&c, sizeof(c));
        }
        else if (*template == 'd')
        {
            template++;
            char *s;
            itoa(s, va_arg(parameters, int), 10);
            print(s, strlen(s));
        }
        else if (*template == 'f')
        {
            template++;
            char *s;
            ftoa_fixed(s, va_arg(parameters, double));
            print(s, strlen(s));
        }
        else if (*template == 'e')
        {
            template++;
            char *s;
            ftoa_sci(s, va_arg(parameters, double));
            print(s, strlen(s));
        }
        else if (*template == 'x')
        {
            template++;
            char *s;
            itoa(s, va_arg(parameters, unsigned int), 16);
            print("0x", 2);
            print(s, strlen(s));
        }
        else if (*template == 'p')
        {
            template++;
            char *s;
            const void *ptr = va_arg(parameters, void *);
            uintptr_t uptr = (uintptr_t)ptr;
            itoa(s, uptr, 16);
            print("0x", 2);
            print(s, strlen(s));
        }
        else if (*template == 's')
        {
            template++;
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