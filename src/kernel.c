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
#include "../include/graphics.h"
#include <iso646.h>


int kernel_early()
{      
       init_system(1);
       

    
}

int init_system(int graph_mode)
{      
       if(graph_mode == 1)
       {
              vga_init();
              draw_char('I',0,50,0,0,0);
              draw_char(' ',0,50,8,0,0);
              draw_char('G',0,50,16,0,0);
              draw_char('O',0,50,24,0,0);
              draw_char('T',0,50,32,0,0);
              draw_char(' ',0,50,40,0,0);
              draw_char('G',0,50,48,0,0);
              draw_char('R',0,50,56,0,0);
              draw_char('A',0,50,64,0,0);
              draw_char('P',0,50,72,0,0);
              draw_char('H',0,50,80,0,0);
              draw_char('I',0,50,88,0,0);
              draw_char('C',0,50,96,0,0);
              draw_char('S',0,50,104,0,0);
              //putpixel(5,5,0x00);
              // putpixel(4,6,0x04);
              // putpixel(6,4,0x00);
              // putpixel(7,5,0x4);
              // putpixel(8,6,0x00);
              // putpixel(9,7,0x00);
              // putpixel(10,8,0x00);
              //terminal_initialize(COLOR_WHITE,COLOR_BLACK);
       }
       else if (graph_mode == 0)
       {
             terminal_initialize(COLOR_WHITE,COLOR_BLACK);
       }
       
       //delay(10);
       
       set_cursor(get_offset(0,0));
       printf("GDT init\n");
       gdt_install();
       printf("IDT init\n");
       idt_install();
       printf("ISRS init\n");
       isrs_install();
       printf("IRQ init\n");
       irq_install();
       //keyboard_install();
       __asm__ __volatile__ ("sti");
       //!ADD here
       //printf("Done");
       
       //delay(10);
       printf("Initializing serial\n");
       init_serial(DEFAULT_COM_DEBUG_PORT);
       write_string_serial("DEBUG FROM COM1(0x3f8):\n\0",DEFAULT_COM_DEBUG_PORT);
       printf("Drawing terminal");
       //delay(5);
       draw_terminal();


}
void on_enter(char *buffer)
{
       
              
       cls_command_output();
       refresh_row(0,0);
       set_cursor(get_offset(23,0));
       print_string("COM1: ",COLOR_MAGENTA);
       terminal_set_colors(COLOR_MAGENTA,COLOR_BLACK);
       set_cursor(get_offset(0,1));
       printf("Command: ");
       terminal_set_colors(COLOR_LIGHT_GREEN,COLOR_BLACK);
       printf(buffer);
       //delay(100);
       buffer[0] = '\0';
       terminal_set_colors(COLOR_LIGHT_GREEN,COLOR_BLACK);
       reset_console(COLOR_LIGHT_GREEN,COLOR_BLACK);
       //delay(10);
       printf(">");
       terminal_set_colors(INPUT_TEXT_FR, INPUT_TEXT_BR);
}
// // char *ctos_old(char s[2], const char c)
// // {
// //     s[0] = c;
// //     s[1] = '\0';
// //     return s;
/// }
int mode = 1;
int main()
{
       size_t *log[1000];
       printf(">");
      
       terminal_set_colors(INPUT_TEXT_FR, INPUT_TEXT_BR);
       
       unsigned char fis;
       
       
       
       char* numbers[] = {"01","02","03","04","05","06","07","08","09","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49","50","51","52","53","54","59","60"};
       
       char *buffer[512];
       int off = 0;
       uint8_t byte;
       
       while(1==1)
       {
              while(byte = scan())
              {
                     
                     
                     
                     
                     struct registers reg_old;
                     reg_old = log_reg();
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
                            set_cursor(get_offset(0,4));
                            if(strcmp(buffer, "dump") == 0)
                            {
                                   //terminal_set_colors(COLOR_MAGENTA,COLOR_LIGHT_GREY);
                                   //printf("F\n");
                                  cmp_reg(reg_old);
                            }
                            if(strcmp(buffer,"test") == 0)
                            {
                                  
                                 PANIC("ERROR");
                                   
                            }
                            // else if (strcmp(buffer,"go") == 0)
                            // {
                                    
                                    
                            // }
                            
                           
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
                            terminal_set_colors(COLOR_BLACK,COLOR_WHITE);
                            printf(s);
                     }
                    
                     
                     
                     
              }
              // //int sec = get_second();
              // //cursor_flash();
              int old_cursor = get_cursor();
              set_cursor(0);
              //print_string
              //terminal_set_colors(COLOR_RED,COLOR_BLACK);
              print_string("Current time: ",COLOR_LIGHT_RED);
              get_time();
              set_cursor(old_cursor);

       }
    
}