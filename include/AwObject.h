// *****************************************************************************
// *                                                                           *
// *                         BACKUPAW : AwObject.h                             *
// *          Represent An ActiveWorld Object Array : Class Header             *
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

#ifndef AWOBJECT_H
#define AWOBJECT_H

#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
	#include "wx/wx.h"
#endif

#ifndef VP_BUILD
#include <Aw.h>
#else
#include <VP.h>
#endif // VP_BUILD

class CObject
{
	public:
				CObject
					(
						int Obj_Numb=0,
						int Obj_Owner=0,
						int Obj_Build_Time=0,
						double Obj_X=0,
						double Obj_Y=0,
						double Obj_Z=0,
						double Obj_Yaw=0,
						double Obj_Tilt=0,
						double Obj_Roll=0,
						double Obj_RotX=0,
						double Obj_RotY=0,
						double Obj_RotZ=0,
						double Obj_RotR=0,
						wxString Obj_Model=_T(""),
						wxString Obj_Descr=_T(""),
						wxString Obj_Action=_T("")
#if AW_BUILD>76 || VP_BUILD
						,int Obj_Type=0,
						wxString Obj_Dat=_T(""),
						int id=0
#endif
					);
				CObject (const CObject& Obj);
				~CObject ();

		int			Number;
		int			Owner;
		int			BuildTime;
		double		X;
		double  	Y;
		double  	Z;
		double		Yaw;
		double		Tilt;
		double		Roll;
		double      RotX;
		double      RotY;
		double      RotZ;
		double      RotR;
#if AW_BUILD>76 || VP_BUILD
		int			Type;
		wxString	Data;
#if AW_BUILD>76
        int			ID;
#endif
#endif
		wxString	Model;
		wxString	Description;
		wxString	Action;
};

#endif


