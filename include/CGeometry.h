#ifndef CGEOMETRY_H
#define CGEOMETRY_H

#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
	#include "wx/wx.h"
#endif

class CAxisAngle;

class CEuler
{
	public:
		CEuler ();
		CEuler (double yaw0, double tilt0, double roll0);
		double yaw;
		double tilt;
		double roll;
		CAxisAngle GetAxisAngle();
};

class CAxisAngle
{
	public:
		CAxisAngle ();
		CAxisAngle (double x0, double y0, double z0, double r0);
		double r;
		double x;
		double y;
		double z;

		CEuler GetEuler();
};

#endif
