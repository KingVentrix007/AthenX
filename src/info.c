#include "../include/vga.h"
#include "../include/info.h"
#include "../include/string.h"
#include "../include/tty.h"
char *log_function;

void write_info(char c)
{
    set_char_at_video_memory(c, get_offset(30,0),default_font_color);
    //log_info(c);
}

void log_info(char*c)
{
    append(log_function,c);
}
void dump_log()
{
    printf(log_function);
}
