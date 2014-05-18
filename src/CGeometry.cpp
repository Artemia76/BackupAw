#include "CGeometry.h"

CEuler::CEuler()
{
	yaw =0;
	tilt=0;
	roll=0;
}

CEuler::CEuler(double yaw0, double tilt0, double roll0)
{
	yaw=yaw0;
	tilt=tilt0;
	roll=roll0;
}

CAxisAngle CEuler::GetAxisAngle ()
{
	CAxisAngle AxisAngle;
	double c1= cos (yaw/2.0);
	double s1= sin (yaw/2.0);
	double c2= cos (tilt/2.0);
	double s2= sin (tilt/2.0);
	double c3= cos (roll/2.0);
	double s3= sin (roll/2.0);
	double c1c2 = c1 * c2;
	double s1s2 = s1 * s2;
	double w =c1c2*c3 - s1s2*s3;
	AxisAngle.x =c1c2*s3 + s1s2*c3;
	AxisAngle.y =s1*c2*c3 + c1*s2*s3;
	AxisAngle.z =c1*s2*c3 - s1*c2*s3;
	AxisAngle.r = 2.0 * acos(w);
	double norm = AxisAngle.x*AxisAngle.x+AxisAngle.y*AxisAngle.y+AxisAngle.z*AxisAngle.z;
	if (norm < 0.001)
	{
		AxisAngle.x=1;
		AxisAngle.y=AxisAngle.z=0;
	} else
	{
		norm = sqrt(norm);
    	AxisAngle.x /= norm;
    	AxisAngle.y /= norm;
    	AxisAngle.z /= norm;
	}
	return AxisAngle;
}

CAxisAngle::CAxisAngle ()
{
	x=0;
	y=0;
	z=0;
	r=0;
}

CAxisAngle::CAxisAngle (double x0, double y0, double z0, double r0)
{
	x=x0;
	y=y0;
	z=z0;
	r=r0;
}

CEuler CAxisAngle::GetEuler ()
{
	CEuler Euler;
	double s = sin(r);
	double c = cos(r);
	double t=1.0 - c;
	//  if axis is not already normalised then uncomment this
	double magnitude = sqrt(x*x + y*y + z*z);
	if (magnitude==0) return Euler;
	x /= magnitude;
	y /= magnitude;
	z /= magnitude;
	if ((x*y*t + z*s) > 0.998) { // north pole singularity detected
		Euler.yaw = 2*atan2(x*sin(r/2.0),cos(r/2.0));
		Euler.tilt = M_PI/2.0;
		Euler.roll = 0;
		return Euler;
	}
	if ((x*y*t + z*s) < -0.998) { // south pole singularity detected
		Euler.yaw = -2*atan2(x*sin(r/2.0),cos(r/2.0));
		Euler.tilt = -M_PI/2.0;
		Euler.roll = 0;
		return Euler;
	}
	Euler.yaw = atan2(y * s- x * z * t , 1 - (y*y+ z*z ) * t);
	Euler.tilt = asin(x * y * t + z * s) ;
	Euler.roll = atan2(x * s - y * z * t , 1 - (x*x + z*z) * t);
}
