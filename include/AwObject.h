// *****************************************************************************
// *                                                                           *
// *                         BACKUPAW : AwObject.h                             *
// *          Represent An ActiveWorld Object Array : Class Header             *
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

#ifndef AWOBJECT_H
#define AWOBJECT_H

#ifndef  WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/wxprec.h>

#include <Aw.h>

class CObject
{
	public:
				CObject
					(
						int Obj_Numb=0,
						int Obj_Owner=0,
						int Obj_Build_Time=0,
						int Obj_X=0,
						int Obj_Y=0,
						int Obj_Z=0,
						int Obj_Yaw=0,
						int Obj_Tilt=0,
						int	Obj_Roll=0,
						wxString Obj_Model=_T(""),
						wxString Obj_Descr=_T(""),
						wxString Obj_Action=_T("")
#if AW_BUILD>76
						,int Type=0,
						wxString Dat=_T(""),
						int id=0
#endif
					);
				CObject (const CObject& Obj);
				~CObject ();

		int			Number;
		int			Owner;
		int			BuildTime;
		int			X;
		int			Y;
		int			Z;
		int			Yaw;
		int			Tilt;
		int			Roll;
#if AW_BUILD>76
		int			Type;
		wxString	DataV4;
        int			ID;
#endif
		wxString	Model;
		wxString	Description;
		wxString	Action;
};

#endif


