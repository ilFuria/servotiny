#ifndef command_h
#define command_h
#include <Arduino.h>
#include "proto.h"
#include <Servo_megaTinyCore.h>
#include <EEPROM.h>
class CommandServo;
 typedef void (*loggin)(CommandServo*);
class CommandServo{
       
        public:
                CommandServo(){};
                uint8_t _code;
                uint8_t _delay;
                uint8_t angle;             
                virtual void execute(Servo s[], uint8_t curr[]);
                static loggin l;
};


class Coreo : public CommandServo{
        public:
                virtual void execute(Servo s[],uint8_t curr[]) override;
};
class Mdir: public CommandServo{
        public:
                
                virtual void execute(Servo s[],uint8_t curr[]) override;
};

class MstpOne : public CommandServo{
        public:
                
                virtual void execute(Servo s[], uint8_t curr[]) override;
};
class MstpTwo : public CommandServo{
        public:
                virtual void execute(Servo s[], uint8_t curr[]) override;
};
class Stay : public CommandServo{
        public:
                virtual void execute(Servo s[], uint8_t curr[]) override;
};


static inline CommandServo* CreateServo (uint8_t cod, uint8_t del, uint8_t ang, CommandServo* old){
        CommandServo* cs;
        switch (cod){
                case 0x00:
                        proto p;
                        cs=(CommandServo*) new Coreo();
                        EEPROM.get(del*sizeof(proto),p);
                        cod=p.cod;
                        del=p.del;
                        ang=p.ang;
                        break;
                case 0x01:
                        cs= (CommandServo*) new Mdir();
                        break;
                case 0x02:
                        cs= (CommandServo*) new MstpOne();
                        break;
                case 0x03:
                        cs=(CommandServo*)new MstpTwo();
                        break;
                case 0x04:
                        cs=(CommandServo*)new Stay();
                        break;
                default:
                        cs=0;
                        break;
        }
        cs->_code=cod;
        cs->_delay=del;
        cs->angle=ang;
        if(old!=0)
          delete(old);

                        return cs;
                }
#endif
