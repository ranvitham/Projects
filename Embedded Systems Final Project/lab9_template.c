/**
 * @file lab9_template.c
 * @author
 * Template file for CprE 288 Lab 9
 *
#include "Timer.h"
#include "lcd.h"
#include "stdio.h"
#include "string.h"
#include "open_interface.h"
#include "movement.h"
#include "uart-interrupt.h"
#include "cyBot_Scan.h"
#include <stdint.h>
#include "ping_template.h"
#include "driverlib/interrupt.h"
#include "servo.h"

// Uncomment or add any include directives that are needed

#warning "Possible unimplemented functions"
#define REPLACEME 0

int main(void)
{
    timer_init(); // Must be called before lcd_init(), which uses timer functions
    lcd_init();
    uart_interrupt_init();
    ping_init();
    servo_init();
    adc_init();

    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);
    oi_t *sensor_right = oi_alloc();
    oi_init(sensor_right);
    oi_t *sensor_left = oi_alloc();
    oi_init(sensor_left);
    uint16_t bump_right = sensor_data->bumpRight;
    uint16_t bump_left = sensor_data->bumpLeft;
    char msg[100] = 0;
    int i = 0;
    int a = 0;
    int objcnt = 0;
    int sum = 0;
    double smdist = 1230;
    int size[12] = 0;
    int of = 0;
    int ang[90] = 0;
    int angleofobj[12] = 0;
    double distofobj[12] = 0;
    int tinyangle = 0;
    double tinydist = 0;
    int objectamo = 0;
    double base = 0;
    double sot = 0;
    int tinyone = 1000;

    // YOUR CODE HERE
    while (1)
    {
        char mode = 't';
        float data[90] = 0;
        float value = 0;
        // uint16_t  val2[90] = 0;
        double val[90] = 0;

//"scan" for objects, once done will drive to smallest object, *if there is no object it will go forward 30 centimeters*
        if (mode == 's')
        {
            servo_move(3);

            for (i = 30; i < 120; i += 3)
            {
                servo_move(i);
                timer_waitMillis(10);
                value = ping_getDistance();
                int overflow = check_of();
                int pw = ping_trigger();

                if (overflow == 1)
                {
                    of++;
                }

                data[a] = value;
                uint16_t val2 = adc_read();
                val[a] = 2820000 * (pow(val2, -1.57));
                ang[a] = i;
                lcd_printf("%f   %lf", data[a], val[a]);
                sprintf(msg, "%f  %lf  %d\r\n", data[a], val[a], i);
                    uart_sendStr(msg);
               // timer_waitMillis(100);
                a++;
            }
            for (i = 0; i <= a; i++)
            {
                if (data[i] <= 50 && val[i] <= 50)
                {
                    //set inobj = 1; if not already 1
                    // if inobj = 1, add one to object[b] size
                    // if data is different then end obj and start new one
                    //if outside val inobj =
                   // if (data[i] <= base + 4)
                    {
                        objcnt++;
                        angleofobj[objcnt] = ang[i];
                        distofobj[objcnt] = data[i];
                        size[objcnt] = size[objcnt] + 1;
                    }
                }
                else if ((base - 4) <= data[i] && data[i] <= (base + 4))
                {

                    size[objcnt] = size[objcnt] + 1;
                }
                base = data[i];
            }
            for (i = 0; i <= objcnt; i++)
            {
                if (size[i] >= 4)
                {
                    objectamo = objectamo + 1;
                }
            }
            for (i = 1; i <= objcnt; i++)
            {
                if (size[i] < sot && size[i] > 3)
                {
                    tinyone = i;
                    sot = size[i];
                    tinyangle = angleofobj[i];
                    tinydist = distofobj[i];
                }
            }
            lcd_printf("%f %d %d %d", tinydist, tinyangle, objectamo, sot);
            timer_waitMillis(1000);
            smdist = tinydist;
            mode = 's';
            break;
        }
//"rotate" to face object
        else if (mode == 'r')
        {
            int aoo = tinyangle - 90;
            if (aoo < 0)
            {
                turn_right(sensor_data, (-1 * aoo));
            }
            else if (aoo > 0)
            {
                turn_left(sensor_data, aoo);
            }
            mode == 'd';
        }
        //"drive" to destination, distance depends on what calls drive. Drives forward with sensor updates constantly
        else if (mode == 'd')
        {
            while (sum < smdist * .8)
            {
                oi_setWheels(100,100);
                oi_update(sensor_data);
                sum += sensor_data->distance;
                oi_update(sensor_data);
                bump_right = sensor_data->bumpRight;
                oi_update(sensor_data);
                bump_left = sensor_data->bumpLeft;
                uint16_t FL = sensor_data->cliffFrontLeftSignal;
                uint16_t FR = sensor_data->cliffFrontRightSignal;
                uint16_t L = sensor_data->cliffLeftSignal;
                uint16_t R = sensor_data->cliffRightSignal;

                if (bump_left == 1 || bump_right == 1 || FL == 1 || FR == 1
                        || L == 1 || R == 1)
                {
                    oi_setWheels(0, 0);
                    if (bump_left == 1)
                    {
                        move_backward(sensor_data, -100);
                        turn_right(sensor_data, -84);
                        move_forward(sensor_data, 100);
                        turn_left(sensor_data, 84);
                        bump_left = 0;
                    }
                    else if (bump_right == 1)
                    {
                        move_backward(sensor_data, -100);
                        turn_left(sensor_data, 84);
                        move_forward(sensor_data, 100);
                        turn_right(sensor_data, -84);
                        bump_right = 0;
                    }
                    else if (FL == 1 || L == 1)
                    {
                        move_backward(sensor_data, -100);
                        turn_right(sensor_data, -170);
                        //move_forward(sensor_data, 200);
                        //turn_left(sensor_data, 84);
                    }
                    else if (FR == 1 || R == 1)
                    {
                        move_backward(sensor_data, -100);
                        turn_right(sensor_data, -170);
                        //move_forward(sensor_data, 200);
                        //turn_left(sensor_data, 84);
                    }
                    else if (L == 1)
                    {
                    }
                    else if (R == 1)
                    {
                    }

                }

            }
                oi_setWheels(0, 0);


        }
        else if(mode == 't') {
            oi_update(sensor_data);
                            bump_left = sensor_data->bumpLeft;
                            uint16_t FL = sensor_data->cliffFrontLeftSignal;
                            uint16_t FR = sensor_data->cliffFrontRightSignal;
                            uint16_t L = sensor_data->cliffLeftSignal;
                            uint16_t R = sensor_data->cliffRightSignal;
                            sprintf(msg,"%d %d %d %d\r\n", FL, FR,L,R);
                            uart_sendStr(msg);
                            timer_waitMillis(100);
                            if((0<=FR && FR<=267) && (0<=FL && FL<=267)) {
                                lcd_printf("its in front");}
                                else if((0<=FR && FR<=267) && (0<=R && R<=267))
                                                      {

                                                       lcd_printf("its in front-right");
                                                      }
                                                      else if((0<=FL && FL<=267) && (0<=L && L<=267))
                                                      {

                                                       lcd_printf("its in front-lrft");
                                                      }

                            else { lcd_printf("\n");}

        }
    }


}*/
