#ifndef _TIME_H
#define _TIME_H 1


unsigned char get_RTC_register(int reg);
char* get_time();
void delay(int seconds);
int get_second();
char* get_year();
void update_time();

#endif