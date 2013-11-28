#include <stdio.h>
#include <unistd.h>
#include "vectornav.h"
#include "MadgwickAHRS.h"

/* Change the connection settings to your configuration. */
const char* const COM_PORT = "//dev//ttyUSB0";
const int BAUD_RATE = 115200;

int main()
{
	// double gpsTime;
	// unsigned short gpsWeek, status;
	// VnVector3 ypr, latitudeLognitudeAltitude, nedVelocity;
	// float attitudeUncertainty, positionUncertainty, velocityUncertainty;
	
	VnVector3 magnetic, acceleration, angularRate;
	float temperature, pressure;

	float mx, my, mz, ax, ay, az, gx, gy, gz;

	Vn200 vn200;
	// Vn100 vn100;
	int i =	0;

	vn200_connect(&vn200, COM_PORT, BAUD_RATE);

	while(1) {

		vn200_getCalibratedSensorMeasurements(
			&vn200,
			&magnetic,
			&acceleration,
			&angularRate,
			&temperature,
			&pressure);

		mx	=	(float)	magnetic.c0;
		my	=	(float)	magnetic.c1;
		mz	=	(float)	magnetic.c2;
		ax	=	(float)	acceleration.c0;
		ay 	=	(float)	acceleration.c1;
		az	=	(float)	acceleration.c2;
		gx	=	(float)	angularRate.c0;
		gy	=	(float)	angularRate.c1;
		gz	=	(float)	angularRate.c2;

		MadgwickAHRSupdate(gx, gy, gz, ax, ay, az, mx, my, mz);

		// printf("IMU Solution: \n"
		// 	"i:					%d\n"
		// 	"magnetic.x:		%+#7.2f\n"
		// 	"magnetic.y:		%+#7.2f\n"
		// 	"magnetic.z:		%+#7.2f\n"
		// 	"acceleration.x:	%+#7.2f\n"
		// 	"acceleration.y:	%+#7.2f\n"
		// 	"acceleration.z:	%+#7.2f\n"
		// 	"angularRate.x:		%+#7.2f\n"
		// 	"angularRate.y:		%+#7.2f\n"
		// 	"angularRate.z:		%+#7.2f\n",
		// 	i,
		// 	magnetic.c0,
		// 	magnetic.c1,
		// 	magnetic.c2,
		// 	acceleration.c0,
		// 	acceleration.c1,
		// 	acceleration.c2,
		// 	angularRate.c0,
		// 	angularRate.c1,
		// 	angularRate.c2);

		// vn200_getInsSolution(
		// 	&vn200,
		// 	&gpsTime,
		// 	&gpsWeek,
		// 	&status,
		// 	&ypr,
		// 	&latitudeLognitudeAltitude,
		// 	&nedVelocity,
		// 	&attitudeUncertainty,
		// 	&positionUncertainty,
		// 	&velocityUncertainty);

		// printf("INS Solution:\n"
		// 	"  i:                      %d\n"	
		// 	"  GPS Time:               %f\n"
		// 	"  GPS Week:               %u\n"
		// 	"  INS Status:             %.4X\n"
		// 	"  YPR.Yaw:                %+#7.2f\n"
		// 	"  YPR.Pitch:              %+#7.2f\n"
		// 	"  YPR.Roll:               %+#7.2f\n"
		// 	"  LLA.Lattitude:          %+#7.2f\n"
		// 	"  LLA.Longitude:          %+#7.2f\n"
		// 	"  LLA.Altitude:           %+#7.2f\n"
		// 	"  Velocity.North:         %+#7.2f\n"
		// 	"  Velocity.East:          %+#7.2f\n"
		// 	"  Velocity.Down:          %+#7.2f\n"
		// 	"  Attitude Uncertainty:   %+#7.2f\n"
		// 	"  Position Uncertainty:   %+#7.2f\n"
		// 	"  Velocity Uncertainty:   %+#7.2f\n",
		// 	i,
		// 	gpsTime,
		// 	gpsWeek,
		// 	status,
		// 	ypr.c0,
		// 	ypr.c1,
		// 	ypr.c2,
		// 	latitudeLognitudeAltitude.c0,
		// 	latitudeLognitudeAltitude.c1,
		// 	latitudeLognitudeAltitude.c2,
		// 	nedVelocity.c0,
		// 	nedVelocity.c1,
		// 	nedVelocity.c2,
		// 	attitudeUncertainty,
		// 	positionUncertainty,
		// 	velocityUncertainty);

		printf("\n\n");

		// sleep(0.05);
		i++;
	}
	
	vn200_disconnect(&vn200);

	return 0;
}


