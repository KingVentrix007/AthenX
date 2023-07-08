#include "../include/io.h"
#include "../include/string.h"
#include "../include/sound.h"
#include "../include/time.h"

void play_sound(uint32_t nFrequency)
{
    uint32_t Div;
    uint8_t tmp;
    Div = 1193180 / nFrequency;
    out_bytes(0x43,0xb6);
    out_bytes(0x42,(uint8_t)(Div));
    out_bytes(0x42,(uint8_t)(Div >> 8));

    tmp = input_bytes(0x61);
    if(tmp != (tmp | 3))
    {
        out_bytes(0x61,tmp | 3);
    }

}

void nosound()
{
    uint8_t tmp = input_bytes(0x61) & 0xFC;
    out_bytes(0x61, tmp);
}

void beep()
{
    play_sound(1000);
    delay(1);
    nosound();
}