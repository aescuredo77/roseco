#include <main.h>
#include <stdlib.h>

#INT_RA
void  RA_isr(void) 
{
   int8 value;
   int8 new=input_a()&0x14; //Masks A2 & A4
   value=new^old;
   if(value!=0){
      if (interrupt_active (INT_IOC_A2)){
      clear_interrupt(INT_IOC_A2);
            if (input(PIN_A2))
             {  
               //ext_int_edge(H_TO_L);
               if (input(PIN_A4))contador++;   // if -- right  ++ left
               else contador --;
      
            }
            else                        
            {  
               //ext_int_edge(L_TO_H);
               if (input(PIN_A4)) contador--;
               else contador ++;
            }
      }
      else if(interrupt_active (INT_IOC_A4))
      {
      clear_interrupt(INT_IOC_A4);
         if (input(PIN_A4))
             {  
               //ext_int_edge(H_TO_L);
               if (input(PIN_A2))contador--;
               else contador ++;
      
            }
            else                        
            {  
               //ext_int_edge(L_TO_H);
               if (input(PIN_A2)) contador++;
               else contador --;
            }
  
      }
   }
 old=new;     
}

#INT_TIMER2
void  TIMER2_isr(void) 
{
    if(check==0){ // modo velocidad
      if(dir==1) { //CW
          set_pwm1_duty(pwm);
          set_pwm2_duty(min);
      }else if (dir==2){ //CCW
         set_pwm1_duty(min);
         set_pwm2_duty(pwm);
      }
      else{//stop
         set_pwm1_duty(min);
         set_pwm2_duty(min);
      }
   }
   else if (check==1){ // modo posicion 
   
      test=pulsos-contador;
      if(abs(test)>10){
      //if(pulsos!=contador) {
      
         if (pulsos>contador) {
            set_pwm1_duty(min);
            set_pwm2_duty(pwm);
         } else if (pulsos<contador) {
            set_pwm1_duty(pwm);
            set_pwm2_duty(min);
         }
      } else {
        contador=pulsos;
        set_pwm1_duty(min);
        set_pwm2_duty(min);
      }
   }

}

#INT_SSP
void  SSP_isr(void) 
{
   
   int state, incoming;
   state = i2c_isr_state(I2CS); 
   if(state < 0x80) //master sending Data <128
    { 
        incoming = i2c_read(I2CS); 
        if (state == 1) 
        { 
            cmd = incoming; 
        } 
        
        else if (state > 1) 
        { 
            rcv_buf[state-2]=incoming; 
        } 
    } 
        
    else if (state==0x80)
    { //disable_interrupts(INT_EXT);
      dato[0]=make8( contador,0);
      dato[1]=make8( contador,1);
      i2c_write(I2CS,dato[aux]);
      aux++;
      if(aux>1) aux=0;
      //enable_interrupts(INT_EXT);    
    }
}



int16 convert(int pwm)
{
   int16 bux=0;
   float coe=(max-min)/255;
   float aux=pwm*coe+min;
   bux=aux;
   return bux;
}

void main()
{
  setup_timer_2(T2_DIV_BY_16,156,16);      //628 us overflow, 10,0 ms interrupt
   //enable_interrupts(INT_EXT);
   
   enable_interrupts(INT_RA);
   enable_interrupts(INT_IOC_A2);
   enable_interrupts(INT_IOC_A4);
   enable_interrupts(INT_TIMER2);
   enable_interrupts(INT_SSP);
   
   enable_interrupts(GLOBAL);
   
   setup_pwm1(PWM_ENABLED|PWM_OUTPUT); 
   setup_pwm2(PWM_ENABLED|PWM_OUTPUT); 
   set_pwm1_duty(min);
   set_pwm2_duty(min);

   while(TRUE)
   {

      
     switch(cmd)
     {
       
       case 0x10://Direction motor control 
         check=0;
         dir=rcv_buf[0];
         pwm=max;
         break;
       case 0x11://Direction and speed motor control
         check=0;
         dir=rcv_buf[0];
         pwm=convert(rcv_buf[1]);
         break;
       case 0x20://Position motor control
         check=1;
         pulsos=rcv_buf[0];
         pulsos=pulsos<<8;
         pulsos|=rcv_buf[1];
         pwm=max;
         cmd=0;
         break; 
       case 0x21://Position and speed motor control
         check=1;
         pulsos=rcv_buf[0];
         pulsos=pulsos<<8;
         pulsos|=rcv_buf[1];
         pwm=convert(rcv_buf[2]);
         cmd=0;
         break;   
       case 0x30:// Read contador variable
         dato[0]=make8( contador,0);
         dato[1]=make8( contador,1);
         cmd=0;
         break;
       case 0x40://
         contador=0;
         pulsos=0;
         cmd=0;
         break;   
       } 
   
   }
      
  

}
