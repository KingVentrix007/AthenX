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
#include "../include/maths.h"
#include "../include/kb.h"
#include "../include/utils.h"
#include "../include/sound.h"
#include "../include/text.h"
#include <iso646.h>

 char key;
int kernel_early()
{      

       init_system();
       

    
}

int init_system()
{     
       
       // terminal_initialize(Default_font_color,Default_screen_color);
       // // printf("d");
       // // printf("e");
       // get_wait_key_in("1");
       int graphics_mode = 1;


       if(graphics_mode == 1)
       {
              vga_init(Default_screen_color);
              // printf_graphics("Hello world!",Default_font_color);
              // printf_graphics("\n",Default_font_color);
              //printf_graphics("Bye world!G",Default_font_color);
              printf("You are in graphics mode!\n");
              key = display_logo();

              //VGA_clear_screen(Default_screen_color);
              set_terminal_colum(0);
              set_terminal_row(0);
              //delay(200);
              // printf_graphics(5,Default_font_color);
              //putpixel(5,5,0x00);
              // putpixel(4,6,0x04);
              // putpixel(6,4,0x00);
              // putpixel(7,5,0x4);
              // putpixel(8,6,0x00);
              // putpixel(9,7,0x00);
              // putpixel(10,8,0x00);
              //terminal_initialize(COLOR_WHITE,Default_screen_color);
       }
       else if (graphics_mode == 0)
       {
             terminal_initialize(COLOR_WHITE,Default_screen_color);
       }
       
       //delay(10);
       
       //set_cursor(get_offset(0,0));
       //printf("GDT init\n");
       gdt_install();
       
       idt_install();
       //printf("ISRS init\n");
       isrs_install();
       //printf("IRQ init\n");
       irq_install();
       //keyboard_install();
       __asm__ __volatile__ ("sti");
       //!ADD here
       //printf("Done");
       
       //delay(10);
       //printf("Initializing serial\n");
       init_serial(DEFAULT_COM_DEBUG_PORT);
       write_string_serial("DEBUG FROM COM1(0x3f8):\n\0",DEFAULT_COM_DEBUG_PORT);

       //printf("Drawing terminal\n");
       //delay(5);
      //cls_screen(COLOR_BLUE);
      //printChar(0,0,'c');
      //delay(1000);


}
void on_enter(char *buffer)
{
       
              
       // cls_command_output();
       // refresh_row(0,0);
       // set_cursor(get_offset(23,0));
       // print_string("COM1: ",COLOR_MAGENTA);
       // 
       
       // set_cursor(get_offset(0,1));
       // printf("Command: ");
       // 
       
       // printf(buffer);
       printf("\n");
       // //delay(100);
       buffer[0] = '\0';
       // 
      
       // reset_console(COLOR_LIGHT_GREEN,Default_screen_color);
       // //delay(10);
       printf(">");
       // 
       
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
       if(strcmp(key,"h") == 0)
       {
              help("boot");
       }
       int counter_go = 0;
       size_t *log[1000];
       printf(">");
      
       
       (INPUT_TEXT_FR, INPUT_TEXT_BR);
       
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
                            //set_cursor(get_offset(0,4));
                            if(strcmp(buffer, "dump") == 0)
                            {
                                   //
                                   (COLOR_MAGENTA,COLOR_LIGHT_GREY);
                                   //printf("F\n");
                                   set_font_mode("small");
                                   cls_screen(Default_screen_color);
                                   cmp_reg(reg_old);
                                   set_font_mode("normal");
                            }
                            else if(strcmp(buffer,"test") == 0)
                            {
                                   printf("Sound");
                                   play_sound(58584);
                                   beep();
                                  
                                 
                                 //printf("█");
                                   
                            }
                            else if(strcmp(buffer,"rand") == 0)
                            {
                                  
                                 cls_screen(Default_screen_color);
                                 draw_rand_img();
                                 
                                   
                            }
                            else if (strcmp(buffer,"text") == 0)
                            {
                                   VGA_clear_screen(Default_screen_color);
                                   text_editor();
                            }



                            else
                            {

                                   //set_terminal_row(get_terminal_row()+20);
                                   //printf_graphics(buffer,COLOR_RED);
                                   terminal_set_colors(COLOR_LIGHT_RED,COLOR_BLACK);
                                   printf("\n%s is not a reconsigned command",buffer);
                                   terminal_set_colors(Default_font_color,COLOR_BLACK);
                            }
                            
                            
                                
                            
                           
                            on_enter(buffer);
                            
                            
                            

                     }
                     else if (byte == BACKSPACE)
                     {
                            //
                            if(backspace(buffer))
                            {
                                  
                                   printf("\b");
                                   
                                   
                                
                                   
                            }
                       

                     }
                     else if (byte >= 60 && byte <=79)
                     {
                            
                            printf("%d",byte);

                     }
                    
                     
                     else{
                            
                           
                            
                          
                            if(counter_go != 0)
                            {
                                   append(buffer,c);
                                   printf(s);
                            }
                            else
                            {
                                   counter_go = counter_go +1;
                            }
                            
                     }
                    
                     
                     
                     
              }
             
              int old_cursor = get_cursor();
              set_cursor(0);
            
              print_string("Current time: ",COLOR_LIGHT_RED);
              get_time();
              set_cursor(old_cursor);

       }
    
}