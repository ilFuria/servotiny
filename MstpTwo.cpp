#include "proto.h"
#include "./command.h"
#include <Arduino.h>
#include <avr/delay.h>

void MstpTwo::execute(Servo s[],uint8_t curr[]){
  CommandServo::execute(s,curr);
  uint8_t c=curr[1];
        uint8_t inc= c>this->angle?-1:1;
        for(uint8_t i=c;i<=this->angle;i+=inc){
                s[1].write(i);
                int x=this->_delay;
                while(x>0)
                {
                  _delay_ms(1);
                  x--;
                }
                
        }
        curr[1]=(this->angle);
}
