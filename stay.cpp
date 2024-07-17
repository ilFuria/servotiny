#include "proto.h"
#include "./command.h"
#include <Arduino.h>
#include <avr/delay.h>
void Stay::execute(Servo s[], uint8_t curr[],bool* halt){
  CommandServo::execute(s,curr,halt);
  int del=((int)this->_delay)*((int)this->angle);
  for (int i=0;i<del;i++)
        
        _delay_ms(1);
}
