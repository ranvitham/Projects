/*
 * movement.h
 *
 *  Created on: Feb 5, 2025
 *      Author: dbunt54
 */

#ifndef MOVEMENT_H_
#define MOVEMENT_H_


double move_forward (oi_t *sensor_data, double distance_mm);
double turn_right (oi_t *sensor_data, double degrees);
double move_backward (oi_t *sensor_data, double distance_mm);
double turn_left (oi_t *sensor_data, double degrees);


#endif /* MOVEMENT_H_ */
