#include "../include/io.h"
#include "../include/vga.h"
#include "../include/string.h"
#include "../include/keyboardmap.h"
#include "../include/text.h"
void text_editor()
{
    while(1==1)
    {
        uint8_t byte;
        char *buffer[51200];
        while(byte=scan())
        {
            char c = normalmap[byte];
            // if (spec == SHIFT)
            // {
                
            //       char sc = shiftmap[byte];
            //       memory_copy(sc,c,string_length(sc));
            // }

            char *s;
            s = ctos(s, c);
            if (byte == BACKSPACE)
            {
                //
                if(backspace(buffer))
                {
                        
                        printf("\b");
                        
                        
                    
                        
                }
            

            }
            else if (byte >= 60 && byte <=79)
            {
                
                if(byte == 60)
                {
                    return buffer;
                }

            }
        
            
            else{
                
                
                append(buffer,c);
                printf(s);
                
            }
                        
        }


    }
    

}