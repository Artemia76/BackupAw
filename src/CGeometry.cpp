// *****************************************************************************
// *                                                                           *
// *                         BACKUPAW : CGeometry.cpp                          *
// *                         3D Geometry calculation                           *
// *                                                                           *
// *****************************************************************************
// * This file is part of BackupAw project.                                    *
// * BackupAw is free software; you can redistribute it and/or modify          *
// * it under the terms of BSD Revision 3 License :                            *
// *                                                                           *
// * Copyright 2020 Neophile                                                   *
// *                                                                           *
// * Redistributionand use in source and binary forms, with or without         *
// * modification, are permitted provided that the following conditions are    *
// * met :                                                                     *
// *                                                                           *
// * 1. Redistributions of source code must retain the above copyright notice, *
// * this list of conditionsand the following disclaimer.                      *
// *                                                                           *
// * 2. Redistributions in binary form must reproduce the above copyright      *
// * notice, this list of conditionsand the following disclaimer in the        *
// * documentation and /or other materials provided with the distribution.     *
// *                                                                           *
// * 3. Neither the name of the copyright holder nor the names of its          *
// * contributors may be used to endorse or promote products derived from this *
// * software without specific prior written permission.                       *
// *                                                                           *
// * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS       *
// * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED *
// * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A           *
// * PARTICULAR PURPOSE ARE DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDER  *
// * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,  *
// * EXEMPLARY, OR CONSEQUENTIAL DAMAGES(INCLUDING, BUT NOT LIMITED TO,        *
// * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR        *
// * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF    *
// * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT                 *
// * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF  *
// * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.         *
// *                                                                           *
// * BackupAW is distributed in the hope that it will be useful,               *
// * but WITHOUT ANY WARRANTY; without even the implied warranty of            *
// * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
// *                                                                           *
// * BackupAW use third part library copyrighted by ActiveWorlds Inc.          *
// * For more details please read attached AW_SDK_License_(aw.dll).txt         *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *   CopyRight 2015 Neophile                                                 *
// *   Creation          : 11/02/2015                                          *
// *   Last Modification :                                                     *
// *   Revision          : A                                                   *
// *                                                                           *
// *****************************************************************************

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
	return Euler;
}
