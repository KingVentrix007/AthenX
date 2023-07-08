#include "../include/kb.h"
#include "../include/io.h"
#include "../include/gdt.h"
#include "../include/idt.h"
#include "../include/irq.h"
#include "../include/isrs.h"
#include "../include/string.h"
#include "../include/keyboardmap.h"
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

 char *buffer[512];;
void console_handler()
{
    unsigned char scancode;

    /* Read from the keyboard's data buffer */
    scancode = input_bytes(0x60);

    /* If the top bit of the byte we read from the keyboard is
    *  set, that means that a key has just been released */
    if (scancode & 0x80)
    {
        //printf("%d",scancode);
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
        
       if(scancode == 14)
       {
          //printf("b");
          if(backspace(buffer) == true)
          {
            printf("b");
            printf("\b");
          }
       }
       else if (scancode == 28)
       {
          printf("\n");
          printf(&buffer[strlen(buffer)]);
       }
       else
       {
           char character = kbdus[scancode];
        
            char *decode;
            decode = ctos(decode, character);
            //append(&buffer,decode);
            strcpy(&buffer[strlen(buffer)], decode);
            printf(decode);
            //printf("%d",scancode);
       }
        // // read_char1 = read_char1 & 0x7f;
     
    }
}

void keyboard_install()
{
    irq_install_handler(1, console_handler);
}
char* wait_for_any_key()
{
  char* keys[24] = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","p","q","r","t","s","u","v","w","x","y","z"};
  int run = 0;
  while(run==0)
    {
       
        unsigned char scancode;
        scancode = input_bytes(0x60);

        char character = kbdus[scancode];
        
        char *decode;
		    decode = ctos(decode, character);
        for (size_t i = 0; i < 24; i++)
        {
          if(strcmp(decode,keys[i]) == 0)
          {
            run = 1;
            return decode;
            break;
          }
        }
        

    }

}
char get_wait_key_in(char* wait_for)
{
    //printf(wait_for);
  
    while(1==1)
    {
        unsigned char scancode;
        scancode = input_bytes(0x60);

        char character = kbdus[scancode];
        
        char *decode;
		    decode = ctos(decode, character);
        if(strcmp(wait_for,"ENTER") == 0)
        {
          if(scancode == ENTER)
          {
            break;
          }
        }
        if(strcmp(decode,wait_for) == 0)
        {
          break;
        }
        //memory_copy(decode, buffer,strlen(decode));
        

    }
}