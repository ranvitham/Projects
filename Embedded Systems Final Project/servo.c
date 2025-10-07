#include "servo.h"
#include "Timer.h"
int p_p = 320000;
int m_w = 22000;
void servo_init() {
SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R1;
SYSCTL_RCGCGPIO_R |=SYSCTL_RCGCGPIO_R1;
TIMER1_CTL_R &= ~TIMER_CTL_TBEN;
GPIO_PORTB_AFSEL_R |=0b100000;
GPIO_PORTB_PCTL_R |= 0x0700000;
GPIO_PORTB_DIR_R |= 0b0100000;
GPIO_PORTB_DEN_R |=0b0100000;

TIMER1_TBMR_R &= ~TIMER_TBMR_TBCMR;
TIMER1_CFG_R |= 0x04;
TIMER1_TBMR_R |= 0x02;
TIMER1_TBMR_R |= TIMER_TBMR_TBAMS;
TIMER1_TBILR_R = p_p & 0xFFFF;
TIMER1_TBPR_R = p_p >> 16;

TIMER1_TBMATCHR_R = (p_p - m_w) & 0xFFFF;
TIMER1_TBPMR_R = (p_p - m_w) >> 16;
TIMER1_CTL_R |= TIMER_CTL_TBEN;
}

void servo_move(uint16_t degrees) {
unsigned p_w;
p_w = ((36000 - 7500)*degrees/180 +7500);
TIMER1_TBMATCHR_R = ( p_p - p_w) & 0xFFFF;
TIMER1_TBPMR_R = (p_p - p_w) >> 16;
timer_waitMillis(100);
}
