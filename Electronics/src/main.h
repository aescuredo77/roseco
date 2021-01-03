#include <16F1503.h>
#device ADC=10

#FUSES NOMCLR                   //Master Clear pin used for I/O
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O

#use delay(internal=16MHz)
#use FIXED_IO( C_outputs=PIN_C5,PIN_C3 )
#use i2c(Slave,Fast,sda=PIN_C1,scl=PIN_C0,force_hw,address=0x22,STREAM=I2Cs)
int rcv_buf[16];
int cmd;
int aux=0;
signed int16    contador=0;
signed int16 pulsos=0;
unsigned char dato[2]={0,0};
int8 check=0;
signed int16 test=0;
int dir=0;// 0:stop,1:CW,2:CCW
int16 pwm=0;
int16 max=628,min=0;
int8 old=0;
