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
// *   Last Modification : 07/10/2007                                          *
// *   Revision          : C                                                   *
// *                                                                           *
// *****************************************************************************

#include "AwObject.h"

#include <wx/arrimpl.cpp>

WX_DEFINE_OBJARRAY(AObject);

CObject::CObject
	(
		int Obj_Numb,
		int Obj_Owner,
		int Obj_Build_Time,
		int Obj_X,
		int Obj_Y,
		int Obj_Z,
		int Obj_Yaw,
		int Obj_Tilt,
		int	Obj_Roll,
		wxString Obj_Model,
		wxString Obj_Descr,
		wxString Obj_Action
        #if AW_BUILD>76
		,int ObjType,
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
	Model=Obj_Model;
	Description=Obj_Descr;
	Action=Obj_Action;
	#if AW_BUILD>76
	Obj_Type=ObjType;
	DataV4=Dat;
	ID=id;
	#endif
}

CObject::~CObject()
{

}
