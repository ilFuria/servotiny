#include "command.h"
#include <avr/delay.h>
void CommandServo::execute(Servo s[],uint8_t curr[]){
  _delay_ms(1000);
        CommandServo::logCommand();
}
