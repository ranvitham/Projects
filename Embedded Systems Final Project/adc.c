#include "adc.h"


void adc_init(void) {
    SYSCTL_RCGCADC_R |= 0x01;
    SYSCTL_RCGCGPIO_R |= 0x02;
    while ((SYSCTL_PRGPIO_R & 0x02) == 0);

    GPIO_PORTB_DIR_R &= ~0x10;
    GPIO_PORTB_AFSEL_R |= 0x10;
    GPIO_PORTB_DEN_R &= ~0x10;
    GPIO_PORTB_AMSEL_R |= 0x10;

    ADC0_ACTSS_R &= ~0x08;
    ADC0_EMUX_R &= ~0xF000;
    ADC0_SSMUX3_R = 10;
    ADC0_SSCTL3_R = 0x06;
    ADC0_ACTSS_R |= 0x08;
}

uint16_t adc_read(void) {
    ADC0_PSSI_R = 0x08;
    while ((ADC0_RIS_R & 0x08) == 0);
    uint16_t result = ADC0_SSFIFO3_R & 0xFFF;
    ADC0_ISC_R = 0x08;
    return result;
}
