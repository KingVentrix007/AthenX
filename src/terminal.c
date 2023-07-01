#include "../include/vga.h"
#include "../include/terminal.h"

void draw_terminal()
{
    set_cursor(get_offset(23,0));
    print_string("COM1: ",COLOR_MAGENTA);
       //Console
       
      
    int offset = get_offset(0,18);
    set_cursor(offset);
    print_string("\n--------------------------------Console-----------------------------------------",COLOR_WHITE);

}