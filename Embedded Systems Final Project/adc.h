#ifndef ADC_H_
#define ADC_H_

#include "Timer.h"
#include "lcd.h"
#include "stdio.h"
#include "string.h"
#include "open_interface.h"
#include "movement.h"
#include "cyBot_uart.h"
#include "cyBot_Scan.h"
#include <stdint.h>

void adc_init(void);

uint16_t adc_read(void);
#endif
