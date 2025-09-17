/**
 * @file ping_tmeplate.c
 * @brief C file for functions related with ping sensor
* @author
* @date
 *
 */


#include "ping_template.h"

volatile int ed;
volatile int read;
volatile int g_s_time;
volatile int g_e_time;

void ping_init()
{
    ed = 1;
    read = 0;
    SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R3;
    TIMER3_CTL_R &= ~(TIMER_CTL_TBEN);
    TIMER3_CFG_R |= 0x04;
    TIMER3_TBMR_R |= 0x10 | 0x04 | 0x03;
    TIMER3_TBILR_R = 0xFFFF;
    TIMER3_ICR_R |= TIMER_IMR_CBEIM;
    TIMER3_IMR_R |= TIMER_IMR_CBEIM;
    TIMER3_CTL_R |= TIMER_CTL_TBEVENT_BOTH;
    TIMER3_CTL_R |= TIMER_CTL_TBEN;
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;

    GPIO_PORTB_AFSEL_R |= 0x08;

    GPIO_PORTB_DIR_R &= 0xF7;
    GPIO_PORTB_DEN_R |= 0x08;

    NVIC_EN1_R |= 0x10;
    IntRegister(INT_TIMER3B, TIMER3B_Handler);
    IntMasterEnable();
}

int ping_trigger()
{

    int pw = 0;
    read= 1;
    GPIO_PORTB_PCTL_R &= ~(GPIO_PCTL_PB3_T3CCP1);
    GPIO_PORTB_AFSEL_R &= 0xF7;
    GPIO_PORTB_DIR_R |= 0x08;
    GPIO_PORTB_DATA_R |= 0x08;
    timer_waitMicros(5);
    GPIO_PORTB_DATA_R &= 0xF7;
    GPIO_PORTB_DIR_R &= 0xF7;
    GPIO_PORTB_AFSEL_R |= 0x08;
    GPIO_PORTB_PCTL_R |= GPIO_PCTL_PB3_T3CCP1;
    /*while (read); */ timer_waitMillis(50);
    int overflow = check_of(g_e_time, g_s_time);
    pw = ((unsigned) overflow << 24) + g_e_time - g_s_time;


    return pw;
}


int check_of(g_e_time, g_s_time)
{
    if (g_e_time < g_s_time)
    {  return 1;
    }
    else
    {
        return 0;
    }
}

void TIMER3B_Handler(void)
{

    TIMER3_ICR_R |= TIMER_IMR_CBEIM;

    if (ed)
    {
        g_s_time = TIMER3_TBV_R;
        ed = 0;
    }

    else
    {
        g_e_time = TIMER3_TBV_R;
        read = 0;
        ed = 1;
    }
}
float ping_getDistance(void)
{

    return ((ping_trigger() * 0.0010852) - 0.07114);
}
