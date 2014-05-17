// *****************************************************************************
// *                                                                           *
// *                         BACKUPAW : AwObject.cpp                           *
// *                 Represent An ActiveWorld Object Array                     *
// *                                                                           *
// *****************************************************************************
// * This file is part of BackupAw.                                            *
// * BackupAw is free software; you can redistribute it and/or modify          *
// * it under the terms of the GNU General Public License as published by      *
// * the Free Software Foundation; either version 2 of the License, or         *
// * (at your option) any later version.                                       *
// *                                                                           *
// * BackupAw is distributed in the hope that it will be useful,               *
// * but WITHOUT ANY WARRANTY; without even the implied warranty of            *
// * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
// * GNU General Public License for more details.                              *
// *                                                                           *
// * You should have received a copy of the GNU General Public License         *
// * along with BackupAw; if not, write to the Free Software                   *
// * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *   CopyRight 2006-2007 Neophile                                            *
// *   Creation          : 28/07/2006                                          *
// *   Last Modification : 20/04/2014                                          *
// *   Revision          : D                                                   *
// *                                                                           *
// *****************************************************************************

#include "AwObject.h"
CObject::CObject
	(
		int Obj_Numb,
		int Obj_Owner,
		int Obj_Build_Time,
		double Obj_X,
		double Obj_Y,
		double Obj_Z,
		double Obj_Yaw,
		double Obj_Tilt,
		double Obj_Roll,
		double Obj_RotX,
		double Obj_RotY,
		double Obj_RotZ,
        double Obj_RotR,
		wxString Obj_Model,
		wxString Obj_Descr,
		wxString Obj_Action
#if AW_BUILD>76 || VP_BUILD
		,int Type,
		wxString Dat,
		int id
#endif
	)
{
	Number=Obj_Numb;
	Owner=Obj_Owner;
	BuildTime=Obj_Build_Time;
	X=Obj_X;
	Y=Obj_Y;
	Z=Obj_Z;
	Yaw=Obj_Yaw;
	Tilt=Obj_Tilt;
	Roll=Obj_Roll;
	RotX=Obj_RotX;
	RotY=Obj_RotY;
	RotZ=Obj_RotZ;
	RotR=Obj_RotR;
	Model=Obj_Model;
	Description=Obj_Descr;
	Action=Obj_Action;
#if AW_BUILD>76 || VP_BUILD
	Type=Type;
	Data=Dat;
#if AW_BUILD>76
	ID=id;
#endif // AW_BUILD
#endif
}

CObject::CObject (const CObject& Obj)
{
	Number=Obj.Number;
	Owner=Obj.Owner;
	BuildTime=Obj.BuildTime;
	X=Obj.X;
	Y=Obj.Y;
	Z=Obj.Z;
	Yaw=Obj.Yaw;
	Tilt=Obj.Tilt;
	Roll=Obj.Roll;
	RotX=Obj.RotX;
	RotY=Obj.RotY;
	RotZ=Obj.RotZ;
	RotR=Obj.RotR;
	Model=Obj.Model;
	Description=Obj.Description;
	Action=Obj.Action;
#if AW_BUILD>76 || VP_BUILD
	Type=Obj.Type;
	Data=Obj.Data;
#if AW_BUILD>76
	ID=Obj.ID;
#endif
#endif
}

CObject::~CObject()
{

}
