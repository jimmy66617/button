#include "LPC11xx.h"                        /* LPC11xx definitions */
#include "timer16.h"
#include "clkconfig.h"
#include "gpio.h"

#define TEST_TIMER_NUM  0  /* 0 or 1 for 16-bit timers only */

extern volatile uint32_t timer16_0_counter;
extern volatile uint32_t timer16_1_counter;
int i,j;
/* Main Program */

int main (void) {
  uint32_t interval;

 SystemInit();

  /* Config CLKOUT, mostly used for debugging. */
  CLKOUT_Setup( CLKOUTCLK_SRC_MAIN_CLK );
  LPC_IOCON->PIO0_1 &= ~0x07; 
  LPC_IOCON->PIO0_1 |= 0x01;  /* CLK OUT */

  /* Enable AHB clock to the GPIO domain. */
  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6);

  /* TEST_TIMER_NUM is either 0 or 1 for 16-bit timer 0 or 1. */
  interval = SystemAHBFrequency/1000 - 1;
  if ( interval > 0xFFFF )
  {
 interval = 0xFFFF;
  }
  init_timer16(TEST_TIMER_NUM, interval);
  enable_timer16(TEST_TIMER_NUM);

  /* Set port 0_7 to output */
  GPIOSetDir(2,7,1); 
  GPIOSetDir(2,6,0);
  while (1)                                /* Loop forever */
  { 
		if((LPC_GPIO2->DATA&(1<<6))==0){
         timer16_0_counter = 0;
         while((LPC_GPIO2->DATA&(1<<6))==0) {                               
    if((timer16_0_counter>0)&&(timer16_0_counter<=500)){		
		i=0;		
		}
		else if(timer16_0_counter>500){
		 timer16_0_counter = 0;
		while((LPC_GPIO2->DATA&(1<<6))==0) { 
		if((timer16_0_counter>0)&&(timer16_0_counter<=500)){		
		LPC_GPIO2->DATA|=(1<<7);		
		}else if((timer16_0_counter>500)&&(timer16_0_counter<=1000)){
         LPC_GPIO2->DATA&=~(1<<7);     
		}else if((timer16_0_counter>1000)){
            timer16_0_counter = 0;  
        }if((LPC_GPIO2->DATA&(1<<6))!=0){
          LPC_GPIO2->DATA&=~(1<<7);}                             
	}
}
}if(i==0){
    { LPC_GPIO2->DATA^=(1<<7);
    }      	
	}
}
		}
	}