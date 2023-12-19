/*
  This program detects the free fall of a DualShock 4 controller and prints narration of what is 
happening during its run time. The program indicates when it is receiving data, falling, how far
and long it fell, and calculates air resistance with percent error. The narration of the program 
includes “Ok, I'm now receiving data.” after receiving the first line of data, “I’m Waiting” with 
a period for every 10 lines of data read after the application starts reading data and before the 
DS4 starts falling, and once the DS4 drops it should “Help me! I'm falling” with exclamation points 
for 100 milliseconds the DS4 continues to drop. At the end of the program, the application should 
output the results of the application.
  To use 
*/

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

double mag (double num1, double num2, double num3);
int close_to(double tolerance, double point, double value);

int main(void) {
    int t;
    double gx, gy, gz;
    double tolerance;
    double point;
	int counter = 0;
	double distance;
	int timeSince;
	int timeRe;
	bool timeDiv;
	
	scanf("%d, %lf, %lf, %lf", &t, &gx, &gy, &gz ); 
	printf("Ok, I'm now receiving data.\nI'm Waiting ");
	fflush(stdout);
	
	while (close_to(0.2, 1, mag (gx, gy, gz))){
		scanf("%d, %lf, %lf, %lf", &t, &gx, &gy, &gz );
		counter++;
			
		if (counter % 10 == 0){
			printf(".");
			fflush(stdout);
		}
	}
	
	printf("\n\n     Help me! I'm falling");

	if (mag(gx, gy, gz) > 0.5){
		timeSince = t;
		counter = 0;
		}

	while (mag(gx, gy, gz) < 0.8){
		scanf("%d, %lf, %lf, %lf", &t, &gx, &gy, &gz );

		timeRe = t % 100;
		timeDiv = close_to(20, 0, timeRe);
		
		if (timeDiv == true){
			printf("!");
			fflush(stdout);
		}
	}

	
	double time2;
	time2 = (t - timeSince)/1000.0;
	distance = (0.5) * (9.8) * pow(time2, 2);
	printf("\n          Ouch! I fell %lf meters in %lf seconds.", distance, time2);
	return 0;
}


double mag (double num1, double num2, double num3){
    double magResult;
    magResult = pow(num1, 2) + pow(num2, 2) + pow(num3, 2);
    magResult = sqrt(magResult);
    return magResult;
    }

int close_to(double tolerance, double point, double value){
    return tolerance > fabs(point - value);
    }
