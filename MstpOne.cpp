#include "proto.h"
#include <Arduino.h>
#include "./command.h"
#include <avr/delay.h>
void MstpOne::execute(Servo s[],uint8_t*curr,bool* halt){
  CommandServo::execute(s,curr,halt);
        uint8_t c=curr[0];
        uint8_t ng=this->angle;
        uint8_t inc= c>this->angle?-1:1;
        for(uint8_t i=c;i<=ng;i+=inc){
                s[0].write(i);
                int x=this->_delay;
                while(x>0)
                {
                  _delay_ms(1);
                  x--;
                }
                
        }
        curr[0]=ng;
}
