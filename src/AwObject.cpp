// *****************************************************************************
// *                                                                           *
// *                         BACKUPAW : AwObject.cpp                           *
// *                 Represent An ActiveWorld Object Array                     *
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
		,int Obj_Type,
		wxString Obj_Dat,
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
	Type=Obj_Type;
	Data=Obj_Dat;
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
