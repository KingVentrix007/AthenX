#include "../include/vga.h"
#include "../include/io.h"
#include "../include/keyboardmap.h"
#include "../include/memory.h"
#include "../include/string.h"
#include "../include/time.h"
#include "../include/def.h"
#include "../include/debug.h"
#include "../include/tty.h"
#include "../include/serial.h"
#include "../include/terminal.h"
#include "../include/gdt.h"
#include "../include/idt.h"
#include "../include/irq.h"
#include "../include/isrs.h"
int kernel_early()
{      
       

    
}
unsigned char kbdus[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',		/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,					/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};


void keyboard_handler(struct regs *r)
{
    unsigned char scancode;

    /* Read from the keyboard's data buffer */
    scancode = input_bytes(0x60);

    /* If the top bit of the byte we read from the keyboard is
    *  set, that means that a key has just been released */
    if (scancode & 0x80)
    {
        /* You can use this one to see if the user released the
        *  shift, alt, or control keys... */
    }
    else
    {
        /* Here, a key was just pressed. Please note that if you
        *  hold a key down, you will get repeated key press
        *  interrupts. */

        /* Just to show you how this works, we simply translate
        *  the keyboard scancode into an ASCII value, and then
        *  display it to the screen. You can get creative and
        *  use some flags to see if a shift is pressed and use a
        *  different layout, or you can add another 128 entries
        *  to the above layout to correspond to 'shift' being
        *  held. If shift is held using the larger lookup table,
        *  you would add 128 to the scancode when you look for it */
        printf(kbdus[scancode]);
    }
}

void keyboard_install()
{
    irq_install_handler(1, keyboard_handler);
}
int init_system()
{
       terminal_initialize(COLOR_WHITE,COLOR_BLACK);
       printf("Start");
       
       gdt_install();
       idt_install();
       isrs_install();
       irq_install();
       keyboard_install();
       __asm__ __volatile__ ("sti");
       //!ADD here
       printf("Done");
       
       //delay(10);
       init_serial(DEFAULT_COM_DEBUG_PORT);
       write_string_serial("DEBUG FROM COM1(0x3f8):\n\0",DEFAULT_COM_DEBUG_PORT);
       draw_terminal();


}
void on_enter(char *buffer)
{
       
              
       cls_command_output();
       terminal_set_colors(COLOR_MAGENTA,COLOR_BLACK);
       set_cursor(get_offset(0,1));
       printf("Command: ");
       terminal_set_colors(COLOR_LIGHT_GREEN,COLOR_BLACK);
       printf(buffer);
       buffer[0] = '\0';
       terminal_set_colors(COLOR_LIGHT_GREEN,COLOR_BLACK);
       reset_console(COLOR_LIGHT_GREEN,COLOR_BLACK);
       printf(">");
       terminal_set_colors(INPUT_TEXT_FR, INPUT_TEXT_BR);
}
char *ctos_old(char s[2], const char c)
{
    s[0] = c;
    s[1] = '\0';
    return s;
}
int mode = 1;
int main()
{
       size_t *log[1000];
       init_system();
       printf(">");
       terminal_set_colors(INPUT_TEXT_FR, INPUT_TEXT_BR);
       
       
       //write_serial(':');
       
       
       
       // for (int i = 1; i < 9; i++)
       // {
       //        write_serial_i(i);
       // }
       
       //write_serial_i(12);
       //putpixel(0,100,"4");
       //delay(40);
       unsigned char fis;
       
       
       
       char* numbers[] = {"01","02","03","04","05","06","07","08","09","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49","50","51","52","53","54","59","60"};
       
       char *buffer[512];
       int off = 0;
       uint8_t byte;
       
       
       // print_string("Current time: ",COLOR_LIGHT_RED);
       // get_time();
       // print_string(" \nCurrent Calendar: ",COLOR_LIGHT_RED);
       // get_year();
       // print_string("\n",default_font_color);
       // //set_int_at_video_memory(400,get_cursor(),default_font_color);
       // // time = ctos(time, second);
       // print_prompt(PROMPT,PROMPT_COLOR);
       //printf("%d",45);
       //print_string("\n",default_font_color);
       
       
       // for (size_t i = 0; i < string_length(fis); i++)
       // {
       //       write_serial(fis[i]);
       // }
       
       
       // if(fis == 255)
       // {
       //        print_string("\nREADY",COLOR_MAGENTA);
       // }
       
       // //print_string(time);
       // for (int i = 0; i < 900; i++)
       // {
       //        char* fake = i;
              
       //        if(i == second-1)
       //        {
       //              print_string(numbers[i]);
       //              break;
                    
       //        }
              
       // }

       // write_string(1,"kernel");
       // write_string(2,"kernel2");
       //write_serial(1);
       while(1==1)
       {
              while(byte = scan())
              {
                     
                     
                     
                     
                     
                     
                     char c = normalmap[byte];
                     // if (spec == SHIFT)
                     // {
                            
                     //       char sc = shiftmap[byte];
                     //       memory_copy(sc,c,string_length(sc));
                     // }
                     char *s;
			s = ctos(s, c);
                      append(log,s);
                     if(byte == ENTER)
                     {
                            if(strcmp(buffer, "dump") == 0)
                            {
                                   printf(log);
                            }
                            // else if(strcmp(buffer, "xx") == 0)
                            // {
                            //        set_cursor(get_offset(5,9));
                            //        printf("DAVE");

                            // }
                            //printf("\n");
                            on_enter(buffer);
                            
                            
                            

                     }
                     else if (byte == BACKSPACE)
                     {
                            //
                            if(backspace(buffer))
                            {
                                   // if(strlen(buffer) == 0)
                                   // {
                                   // printf(" ");
                                   // append(" ",buffer);
                                   // //set_cursor(get_cursor()+1);
                                   // }
                                   terminal_set_colors(COLOR_WHITE,COLOR_BLACK);
                                   set_cursor(get_cursor()+1);
                                   printf("\b");
                                   //buffer[strlen(buffer) - 1] = '\0';
                                   
                                   set_cursor(get_cursor()-2);
                                   terminal_set_colors(COLOR_BLACK,COLOR_WHITE);
                                   
                            }
                            // if(strlen(buffer) == 0)
                            // {
                            //        printf("");
                            //        append(buffer," ");
                            //        //set_cursor(get_cursor()+1);
                            // }
                            

                     }
                     else if (byte >= 60 && byte <=79)
                     {
                            //int byt = (char)(byte);
                            //printf("%c",byt);

                     }
                    
                     
                     else{
                            append(buffer,c);
                            //printf("\n");
                            // if(strcmp(s,"-") == 0)
                            // {
                            //        terminal_set_colors(COLOR_LIGHT_GREY,COLOR_BLACK);
                            // }
                            // else if(strcmp(s," ") == 0)
                            // {
                                   
                            //        terminal_set_colors(COLOR_LIGHT_GREEN,COLOR_BLACK);
                                   
                            // }
                            printf(s);
                     }
                    
                     
                     
                     
              }
              //int sec = get_second();
              //cursor_flash();
              update_time();

       }
    
}