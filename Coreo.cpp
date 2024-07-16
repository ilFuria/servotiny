#include "proto.h"
#include <Arduino.h>
#include "./command.h"
#include <avr/delay.h>
#include <EEPROM.h>

void Coreo::execute(Servo s[],uint8_t curr[]){
        CommandServo::execute(s,curr);
        
        CommandServo* ks=0;
        for (uint8_t i=0;i<this->angle;i++)
        {
          proto x;
          uint8_t sz=((i+this->_delay)*sizeof(proto));
          
              EEPROM.get(sz,x);
              ks= (CreateServo(x.cod,x.del,x.ang,ks));
              ks->execute(s,curr);
              
        }
        if(ks!=0)
         delete(ks);
}
