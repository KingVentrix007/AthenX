#include "../include/vga.h"
#include "../include/io.h"
#include "../include/keyboardmap.h"
#include "../include/memory.h"
#include "../include/string.h"
#include "../include/time.h"
int kernel_early()
{
       
    
}
char *ctos(char s[2], const char c)
{
    s[0] = c;
    s[1] = '\0';
    return s;
}

int main()
{
       char* numbers[] = {"01","02","03","04","05","06","07","08","09","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49","50","51","52","53","54","59","60"};
       display_init();
       char *buffer[512];
       int off = 0;
       uint8_t byte;
       int second;
       second = get_RTC_register(0x02);
       second = (second & 0x0F) + ((second / 16) * 10);
       char *time;
       print_string("Current time: ");
       get_time();

       // time = ctos(time, second);
       print_string("\n>");
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

       while(1==1)
       {
              while(byte = scan())
              {
                     
                     char spec = shiftcode[byte];
                     
                     
                     
                     
                     char c = normalmap[byte];
                     // if (spec == SHIFT)
                     // {
                            
                     //       char sc = shiftmap[byte];
                     //       memory_copy(sc,c,string_length(sc));
                     // }
                     char *s;
			s = ctos(s, c);
                     
                     if(byte == ENTER)
                     {
                            print_string("\n");
                            buffer[0] = '\0';
                            
                            

                     }
                     else if (byte == BACKSPACE)
                     {
                            if(backspace(buffer))
                            {
                                   print_backspace();
                            }
                            

                     }
                    
                     
                     else{
                            append(buffer,c);
                            print_string(s);
                     }
                     
                     
                     
              }
              
              cursor_flash();
       }
    
}