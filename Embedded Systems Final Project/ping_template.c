/**
 * Driver for ping sensor
 * @file ping.c
 * @author
 *

#include "ping_template.h"
#include "Timer.h"
#include "driverlib/interrupt.h"
// Global shared variables
// Use extern declarations in the header file

volatile uint32_t g_start_time = 0;
volatile uint32_t g_end_time = 0;
volatile enum{LOW, HIGH, DONE} g_state = LOW; // State of ping echo pulse

void ping_init (void){

  // YOUR CODE HERE

    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;
    GPIO_PORTB_DEN_R |= 0x08;
    GPIO_PORTB_PCTL_R |= 0x07000;
    SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R3;

    while ((SYSCTL_PRGPIO_R & 0x00000002) == 0) {};
      while ((SYSCTL_PRTIMER_R & 0x00000008) == 0) {};
    // Configure and enable the timer
    TIMER3_CTL_R &= ~TIMER_CTL_TBEN; // Disable timer
    TIMER3_CFG_R = TIMER_CFG_16_BIT;
    TIMER3_TBMR_R = TIMER_TBMR_TBMR_CAP | TIMER_TBMR_TBCMR | TIMER_TBMR_TBCDIR;

       TIMER3_TBILR_R = 0xFFFF;
       TIMER3_TBPR_R = 0xFF;
       TIMER3_ICR_R = TIMER_ICR_CBECINT;
       TIMER3_IMR_R |= TIMER_IMR_CBEIM;
       NVIC_EN1_R |= 0b10000;
       IntRegister(INT_TIMER3B, TIMER3B_Handler);

           IntMasterEnable();
       TIMER3_CTL_R |= (TIMER_CTL_TBEN | TIMER_CTL_TBEVENT_BOTH);
       GPIO_PORTB_DATA_R &= 0xF7;
          GPIO_PORTB_DIR_R &= ~0xF7;

}

void ping_trigger (void){
    g_state = LOW;


    // Disable timer and disable timer interrupt
    TIMER3_CTL_R &= ~TIMER_CTL_TBEN;
    TIMER3_IMR_R &= ~TIMER_IMR_CBEIM;
    // Disable alternate function (disconnect timer from port pin)
    GPIO_PORTB_AFSEL_R &= ~0x08;
    GPIO_PORTB_PCTL_R &= 0x0000;
    // YOUR CODE HERE FOR PING TRIGGER/START PULSE

    GPIO_PORTB_DIR_R |= 0x08;

    GPIO_PORTB_DATA_R |= 0x08;

    timer_waitMillis(5);

    GPIO_PORTB_DATA_R &= 0xF7;
              GPIO_PORTB_DIR_R &= 0xF7;


    // Clear an interrupt that may have been erroneously triggered
    TIMER3_ICR_R |= TIMER_ICR_CBECINT;
    // Re-enable alternate function, timer interrupt, and timer
    GPIO_PORTB_AFSEL_R |=0x08;
    GPIO_PORTB_PCTL_R |= 0x00007000;
    TIMER3_IMR_R |= TIMER_IMR_CBEIM;
    TIMER3_CTL_R |= TIMER_CTL_TBEN;


}

void TIMER3B_Handler(void){
if(TIMER3_ICR_R & TIMER_ICR_CBECINT) {
    TIMER3_ICR_R |= TIMER_ICR_CBECINT;
    uint32_t time = TIMER3_TBR_R;

    if (g_state == LOW) {
        time = TIMER3_TBR_R;
        g_start_time = time;
        g_state = HIGH;
        lcd_printf("q");
    }
    else if (g_state == HIGH) {
        time = TIMER3_TBR_R;
        g_end_time = time;
        g_state = DONE;
        lcd_printf("q");
    }
}}

float ping_getDistance(void){
    ping_trigger();

    while(g_state != DONE);


    uint32_t delta = (g_end_time - g_start_time) & 0xFFFFFF;

   // float time_us = delta *
    //float distance_cm = (time_us /

    return 0;// distance_cm;
} */


