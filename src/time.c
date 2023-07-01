#include "../include/io.h"
#include "../include/time.h"
#include "../include/string.h"
#include "../include/vga.h"
enum {
      cmos_address = 0x70,
      cmos_data    = 0x71
};
unsigned char get_RTC_register(int reg) {
    out_bytes(cmos_address, reg);
    return input_bytes(cmos_data);
}
char* get_year()
{
    char* numbers[] = {"01","02","03","04","05","06","07","08","09","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49","50","51","52","53","54","59","60"};
    unsigned int day;
    unsigned int month;
    unsigned int year;
    day = get_RTC_register(0x07);
    month = get_RTC_register(0x08);
    year = get_RTC_register(0x09);
    day = (day & 0x0F) + ((day / 16) * 10);
    month = (month & 0x0F) + ((month / 16) * 10);
    year = (year & 0x0F) + ((year / 16) * 10);
    print_string(numbers[day-1],COLOR_MAGENTA);
    print_string("/",default_font_color);
    print_string(numbers[month-1],COLOR_MAGENTA);
    print_string("/",default_font_color);
    print_string(numbers[year-1],COLOR_MAGENTA);

    
}
char* get_time()
{
    char* numbers[] = {"00","01","02","03","04","05","06","07","08","09","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49","50","51","52","53","54","55","56","57","58","59","60"};
    char* times[3];
    unsigned char second;
    unsigned char minute;
    unsigned char hour;
    unsigned char day;
    unsigned char month;
    unsigned int year;
    second = get_RTC_register(0x00);
    minute = get_RTC_register(0x02);
    hour = get_RTC_register(0x04);
    day = get_RTC_register(0x07);
    month = get_RTC_register(0x08);
    year = get_RTC_register(0x09);
    second = (second & 0x0F) + ((second / 16) * 10);
    minute = (minute & 0x0F) + ((minute / 16) * 10);
    hour = ( (hour & 0x0F) + (((hour & 0x70) / 16) * 10) ) | (hour & 0x80);
    day = (day & 0x0F) + ((day / 16) * 10);
    month = (month & 0x0F) + ((month / 16) * 10);
    year = (year & 0x0F) + ((year / 16) * 10);
    for (int i = 0; i < 900; i++)
    {
            
              
            if(i == hour+2)
            {
                hour = numbers[i];
                print_string(numbers[i],COLOR_GREEN);
                break;
                    
            }
              
    }
    print_string(":",default_font_color);
     for (int i = 0; i < 900; i++)
    {
            
              
            if(i == minute+0)
            {
                minute = numbers[i];
                print_string(numbers[i],COLOR_GREEN);
                break;
                    
            }
              
    }
    print_string(".",default_font_color);
    for (int i = 0; i < 900; i++)
    {
            
              
            if(i == second)
            {
                second = numbers[i];
                print_string(numbers[i],COLOR_GREEN);
                break;
                    
            }
              
    }
    
   
   
    
    
    
    

    
}

void delay(int seconds)
{
    //get_time();
    //!print_string("Delay started\n");
     unsigned int second;
     second = get_RTC_register(0x00);
     second = (second & 0x0F) + ((second / 16) * 10);
     //print_string(second);
    char* numbers[] = {"01","02","03","04","05","06","07","08","09","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49","50","51","52","53","54","59","60"};
    // print_string("\n");
    // print_string(numbers[second]);
    // print_string("\n");
    int st = second;
    int end_time = st+seconds;
    if (end_time > 59)
    {
        //!print_string("\nGreater\n");
        end_time = 59-end_time;
    }
    while (1==1)
    {
        second = get_RTC_register(0x00);
        second = (second & 0x0F) + ((second / 16) * 10);
        if(second == end_time)
        {
            //!print_string("Delay done\n");
            break;
        }
        // if((st + seconds) == second)
        // {
        //     print_string("\nDelay\n");
        //     break;
        // }
        // else if ((st+seconds > 59) && (second == ))
        // {
        //     /* code */
        // }
        
    }
    
}
int get_second()
{
     unsigned int second;
     second = get_RTC_register(0x00);
     second = (second & 0x0F) + ((second / 16) * 10);
     return second;

}

void update_time()
{
    int old_cursor = get_cursor();
    set_cursor(0);
    print_string("Current time: ",COLOR_LIGHT_RED);
    get_time();
    set_cursor(old_cursor);
}