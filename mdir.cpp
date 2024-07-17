#include "proto.h"
#include "./command.h"
#include <Arduino.h>

void Mdir::execute(Servo s[],uint8_t curr[],bool* halt){
  CommandServo::execute(s,curr,halt);
  uint8_t ng=this->angle;
  uint8_t i=this->_delay;
       s[i-1].write(ng);
       curr[i-1]=(ng);
       
}
