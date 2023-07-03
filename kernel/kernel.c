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
// int kernel_early()
// {
       
       
    
// }
int init_system()
{
       terminal_initialize(COLOR_WHITE,COLOR_BLACK);
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