#include <REG51.H>

sbit DHT11 = P1^6;

void timer_delay20ms();
void timer_delay30us();
void Request();
void Response();
int Receive_data();