#include <Arduino.h>
#include<Servo_megaTinyCore.h>
#include <Wire.h>
#include <avr/delay.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#define LCDA 0x27
#include "./proto.h"
#include "./command.h"
volatile uint8_t cmds[3];
volatile Servo mot[2];
LiquidCrystal_I2C lcd(LCDA, 16, 2);
volatile CommandServo* command;
volatile bool toProcess;
volatile uint8_t curz[2]={0};
volatile bool* halt;

void writeToDiag(CommandServo* c) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Executing:");
        lcd.setCursor(0,1);
        lcd.print(c->_code,HEX);
        lcd.print(" ");
        lcd.print(c->_delay,HEX);
        lcd.print(" ");
        lcd.print(c->angle,HEX);

  }
  loggin CommandServo::l = writeToDiag;
  

  void setup() {
          *halt=false;
          // put your setup code here, to run once:
          toProcess = false;
          const Servo s = Servo();
          const Servo s2=Servo();
          s.attach(PIN_PA4);
          PORTA.DIRSET |= (0x01 << 5);
          s2.attach(PIN_PA3);
          mot[0] = s;
          mot[1] = s2;
          Wire.begin(0x50);
          Wire.onReceive(receiveCmd);
          initLCD();
          curz[0]=0;
          curz[1]=0;
          attachInterrupts();
  }

void initMotors(){
        mot[0].write(curz[0]);
        mot[1].write(curz[1]);
}
void initLCD() {
        Wire.begin();
        lcd.init();
        lcd.backlight();
        lcd.setCursor(0, 0);
        lcd.clear();
        lcd.blink();
        lcd.cursor();

}

void loop() {
        if (toProcess)
        {
                go();
        }
        if((*halt))
                attachInterrupts();
}
void receiveCmd(int bytes) {
        uint8_t i = 0;
        while (1 < Wire.available()) { // loop through all but the last
                uint8_t c = Wire.read(); // receive byte as a character
                cmds[i] = c;
                i++;
        }
        uint8_t x = Wire.read();
        cmds[2] = x;
        command = CreateServo(cmds[0], cmds[1], cmds[2],command);
        toProcess = true;
}

void setBusy() {
        VPORTA.OUT |= (1 << 5);
}
void unsetBusy() {
        VPORTA.OUT &= ~(1 << 5);
}

void go() {
        toProcess = false;
        setBusy();
        command->execute(mot,curz,halt);
        unsetBusy();
}
void attachInterrupts(){
        PORTA.PIN2CTRL&=~PORT_ISC_gm;
        PORTA.PIN2CTRL|=PORT_ISC_FALLING_gc;
        *halt=!(*halt);
}
