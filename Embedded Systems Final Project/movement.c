/*
 * movement.c
 *
 *  Created on: Feb 5, 2025
 *      Author: dbunt54
 */

#include "open_interface.h"
#include "lcd.h"


double move_forward (oi_t *sensor_data, double distance_mm) {
    int sum = 0;
            //   move_distance = uart_receive();
               char msg[20] = 'a';
                while(sum<distance_mm )
                    {
                    oi_update(sensor_data);
                    uint16_t FL = sensor_data->cliffFrontLeftSignal;
                    uint16_t FR = sensor_data->cliffFrontRightSignal;
                    uint16_t L = sensor_data->cliffLeftSignal;
                    uint16_t R = sensor_data->cliffRightSignal;
                    uint16_t bump_right = sensor_data->bumpRight;
                    uint16_t bump_left = sensor_data->bumpLeft;

                if (bump_left == 1 || bump_right == 1)
                    {
                        oi_setWheels(0, 0);
                        if((bump_left == 1) && (bump_right == 1))
                                {
                            move_backward(sensor_data, -50);
                            sprintf(msg,"Object Straight Ahead!!\r\n");
                            lcd_printf(msg);
                            //uart_sendStr(msg);
                            bump_left = 0;
                            bump_right = 0;
                            sum = sum+1500;
                                }
                        else if (bump_left == 1)
                        {
                            move_backward(sensor_data, -50);

                            bump_left = 0;
                            sprintf(msg,"Object to the Left!!\r\n");
                            lcd_printf(msg);
                             //uart_sendStr(msg);
                             sum = sum+1500;
                        }
                        else if (bump_right == 1)
                        {
                            move_backward(sensor_data, -50);
                            bump_right = 0;
                            sprintf(msg,"Object to the Right!!\r\n");
                            lcd_printf(msg);
                           // uart_sendStr(msg);
                            sum = sum+1500;
                        }
                    }
                       if (0<=L && L<=267)
                        {
                            oi_setWheels(0, 0);
                            move_backward(sensor_data, -50);
                            turn_right(sensor_data, -170);
                            sprintf(msg,"Hole to the left!!\r\n");
                            lcd_printf(msg);
                           // uart_sendStr(msg);
                            sum = sum+1500;

                        }
                         else  if (0<=R && R<=267)
                        {
                            oi_setWheels(0, 0);
                            move_backward(sensor_data, -50);
                            turn_right(sensor_data, -170);
                            sprintf(msg,"Hole to the right!!\r\n");
                             lcd_printf(msg);
                         // uart_sendStr(msg);
                            sum = sum+1500;
                        }
                        else if ((0<=FR && FR<=267) && (0<=FL && FL<=267))
                        {
                            move_backward(sensor_data, -50);
                            turn_right(sensor_data, -170);
                            sprintf(msg,"Hole to the Front!!\r\n");
                            lcd_printf(msg);
                          //uart_sendStr(msg);
                          sum = sum+1500;
                        }
                     else if ((0<=FR && FR<=267) && (0<=R && R<=267))
                           {
                            move_backward(sensor_data, -50);
                            turn_right(sensor_data, -170);
                            sprintf(msg,"Hole to the Front-Right!!\r\n");
                            lcd_printf(msg);
                           //  uart_sendStr(msg);
                            sum = sum+1500;
                           }
                           else if ((0<=FL && FL<=267) && (0<=L && L<=267))
                           {
                             move_backward(sensor_data, -50);
                            turn_right(sensor_data, -170);
                            sprintf(msg,"Hole to the Front-Left!!\r\n");
                            lcd_printf(msg);
                           //uart_sendStr(msg);
                           sum = sum+1500;
                           }
                    if (2600<=L && L<=2840)
                        {
                            oi_setWheels(0, 0);
                            move_backward(sensor_data, -50);
                            turn_right(sensor_data, -170);
                            sprintf(msg,"Border to the left!!\r\n");
                             lcd_printf(msg);
                            //uart_sendStr(msg);
                          sum = sum+1500;
                        }
                         else  if (2600<=R && R<=2840)
                        {
                            oi_setWheels(0, 0);
                            move_backward(sensor_data, -50);
                            turn_right(sensor_data, -170);
                            sprintf(msg,"Border to the Right!!\r\n");
                            lcd_printf(msg);
                            //uart_sendStr(msg);
                            sum = sum+1500;
                        }
                        else if ((2600<=FR && FR<=2840) && (2600<=FL && FL<=2840))
                        {
                            move_backward(sensor_data, -50);
                            turn_right(sensor_data, -170);
                            sprintf(msg,"Border to the front!!\r\n");
                            lcd_printf(msg);
                           // uart_sendStr(msg);
                            sum = sum+1500;
                        }
                     else if ((2600<=FR && FR<=2840) && (2600<=R && R<=2840))
                           {
                            move_backward(sensor_data, -50);
                            turn_right(sensor_data, -170);
                            sprintf(msg,"Border to the Front-Right!!\r\n");
                            lcd_printf(msg);
                           // uart_sendStr(msg);
                            sum = sum+1500;
                           }
                           else if ((2600<=FL && FL<=2840) && (2600<=L && L<=2840))
                           {
                             move_backward(sensor_data, -50);
                            turn_right(sensor_data, -170);
                            sprintf(msg,"Border to the Front-Left!!\r\n");
                            lcd_printf(msg);
                            //uart_sendStr(msg);
                            sum = sum+1500;
                           }
                           else{
                                 oi_setWheels(100,100);
                                 sum += sensor_data->distance;
                                 //sprintf(msg,"Nothing   ");
                           }
                    }
                if(msg[0] == 'a'){
                    sprintf(msg,"Nothing\r\n");
                }
                uart_sendStr(msg);
                lcd_printf(msg);

                oi_setWheels(0,0);
                //uart_sendStr(endmsg);
                timer_waitMillis(500);
                msg[0] = 'a';
}
double move_backward (oi_t *sensor_data, double distance_mm) {
double sum3 = 0; // distance member in oi_t struct is type double
oi_setWheels(-75,-75); //move forward at full speed
while (sum3 > distance_mm) {
oi_update(sensor_data);
sum3 +=sensor_data -> distance; // use -> notation since pointer
//lcd_printf("%lf",sum3);
}

oi_setWheels(0,0); //stop

}
// left turn
double turn_left (oi_t *sensor_data, double degrees) {
    double sum1 = 0.00;
    while((sum1*100) < (degrees *98)){
        oi_update(sensor_data);
        oi_setWheels(75,-75);
        sum1 += sensor_data -> angle;
        //lcd_printf("%lf",sum1);
    }
    oi_setWheels(0,0); //stop
}


//right turn
double turn_right (oi_t *sensor_data, double degrees) {
    double sum2 = 0.00;
    while((sum2*100) > ( degrees *98)){
        oi_update(sensor_data);
        oi_setWheels(-75,75);
        sum2 += sensor_data -> angle;
        //lcd_printf("%lf",sum2);
    }
    oi_setWheels(0,0); //stop
}



