#include "../include/string.h"
#include "../include/tty.h"
#include "../include/graphics.h"
#include "../include/utils.h"
#include "../include/kb.h"
help(char* cmd)
{
    if(strcmp(cmd,"boot") == 0)
    {   
        VGA_clear_screen(Default_font_color);
        set_terminal_row(0);
        set_terminal_colum(0);
        printf("Boot command options(Press enter when done)\n");
        printf("'b': Proced with boot\n");
        printf("'h' Display this screen");
        
        get_wait_key_in("ENTER");
        VGA_clear_screen(Default_screen_color);
        set_terminal_row(0);
        set_terminal_colum(0);
    }
}




