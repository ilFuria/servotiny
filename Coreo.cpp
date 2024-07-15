#include "proto.h"
#include <Arduino.h>
#include "./command.h"
#include <avr/delay.h>
#include <EEPROM.h>

void Coreo::execute(Servo s[],uint8_t curr[]){
        CommandServo::execute(s,curr);
        proto x;
        for (uint8_t i=0;i<this->angle;i++)
        {
          uint8_t sz=((i+this->_delay)*sizeof(proto));
          
               EEPROM.get(sz,x);
               (CreateServo(x.cod,x.del,x.ang))->execute(s,curr); 
        }
}
