// *****************************************************************************
// *                                                                           *
// *                       BACKUPAW : CBackupCtrl.h                            *
// *                  The Grid Canvas to display project                       *
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
// *   CopyRight 2014 Neophile                                                 *
// *   Creation          : 21/04/2014                                          *
// *   Last Modification :                                                     *
// *   Revision          : A                                                   *
// *                                                                           *
// *****************************************************************************
#ifndef VPBUILD
#include "CBackupCtrl.h"

wxBEGIN_EVENT_TABLE(CBackupCtrl, wxEvtHandler)
	EVT_TIMER  (OBJ_TIME,	CBackupCtrl::OnObjTimer)
wxEND_EVENT_TABLE()

//------------------------------------------------------------------------------
// SingleTon Private pointer

CBackupCtrl* CBackupCtrl::PtCBackupCtrl = 0;

//------------------------------------------------------------------------------
// Creator
CBackupCtrl* CBackupCtrl::Create()
{
	if (!PtCBackupCtrl)
	{
		PtCBackupCtrl = new CBackupCtrl();
	}
	return PtCBackupCtrl;
}

//------------------------------------------------------------------------------
// Singleton killer

void CBackupCtrl::Kill()
{
	if (PtCBackupCtrl != 0) delete PtCBackupCtrl;
	PtCBackupCtrl=0;
}

//------------------------------------------------------------------------------
// Private Constructor

CBackupCtrl::CBackupCtrl ()
{
	Scanning=false;
	Survey=false;
	Deleting=false;
	Building=false;
	BuildEC=0;
	DelEC=0;
	OrigX=0;
	OrigY=0;
	BlockScroll=false;
	BlockSelect=false;
	Map=0;
	pConfig=wxConfigBase::Get();
	pConfig->Read(_T("Bot/BuildMode"), &CTBuild, true);
	ObjectTimer = new wxTimer(this, OBJ_TIME);
	Cell = CCtrlCell::Create();
}

//------------------------------------------------------------------------------
// Private Destructor

CBackupCtrl::~CBackupCtrl()
{
}

//------------------------------------------------------------------------------
// Event Dispatcher

bool CBackupCtrl::Event( AW_EVENT_ATTRIBUTE id, CBot* Bot)
{
	switch (id)
	{
		case AW_EVENT_CELL_BEGIN:
			Cell_Begin (Bot);
			return true;
		case AW_EVENT_CELL_OBJECT:
			Cell_Object (Bot);
			return true;
		case AW_EVENT_OBJECT_ADD:
			Cell_Object(Bot);
			return true;
		case AW_EVENT_OBJECT_DELETE:
			Object_Delete (Bot);
			return true;
		case AW_EVENT_UNIVERSE_DISCONNECT:
			Reset ();
			return true;
		case AW_EVENT_WORLD_DISCONNECT:
			Reset ();
			return true;
	}
	return false;
}

//------------------------------------------------------------------------------
// CallBack Dispatcher

bool CBackupCtrl::CallBack (AW_CALLBACK id, int rc, CBot* Bot)
{
	switch (id)
	{
		case AW_CALLBACK_QUERY:
			Query_CB(rc, Bot);
			return true;
		case AW_CALLBACK_OBJECT_RESULT:
			Object_CB(rc,Bot);
			return true;
	}
	return false;
}
//------------------------------------------------------------------------------
// Retour Callback d'un query

void CBackupCtrl::Query_CB(int rc, CBot* Bot)
{
	if (rc)
	{
		wxLogMessage(_("Unable to query properties. Reason :") + Bot->GetRCString (rc));
		Scanning=false;
		BlockScroll=false;
	}
	else
	{
		if (aw_bool(AW_QUERY_COMPLETE))
		{
			Scanning=false;
			BlockScroll=false;
			Survey=true;
		}
		else aw_query_5x5 (aw_sector_from_cell (OrigX), aw_sector_from_cell (OrigY), sequence);
	}
}

//------------------------------------------------------------------------------
// Object Callback

void CBackupCtrl::Object_CB (int rc, CBot* Bot)
{
	if (BuildEC)
	{
		if (rc) wxLogMessage(_("Unable to Build object. Reason : ") + Bot->GetRCString(rc));
		BuildEC--;
	}
	else if (DelEC)
	{
		if (rc) wxLogMessage(_("Unable to Delete object. Reason : ") + Bot->GetRCString(rc));
		DelEC--;
	}
}


//------------------------------------------------------------------------------

void CBackupCtrl::Scan ()
{
	if ((!Scanning)&&CtrlAw->GetBot()->IsOnWorld())
	{
		memset (sequence, 0, sizeof (sequence));
		aw_query_5x5 (aw_sector_from_cell (OrigX), aw_sector_from_cell (OrigY), sequence);
		Scanning=true;
		BlockScroll=true;
	}
}

//------------------------------------------------------------------------------

void CBackupCtrl::Cell_Begin(CBot* Bot)
{
	int sector_x;
	int sector_z;
	int sectorxmax = 2 - aw_sector_from_cell (OrigX);
	int sectorzmax = 2 - aw_sector_from_cell (OrigY);
	CellX = aw_int (AW_CELL_X);
	CellZ = aw_int (AW_CELL_Z);
	sector_x = aw_sector_from_cell (CellX);
	sector_z = aw_sector_from_cell (CellZ);
	sequence[sectorzmax+sector_z][sectorxmax+sector_x] = aw_int (AW_CELL_SEQUENCE);
}

//------------------------------------------------------------------------------

void CBackupCtrl::Cell_Object (CBot* Bot)
{
	CObject NObj;
    #if AW_BUILD>41
	unsigned char* DatPtr=0;
	unsigned int DatLen=0;
	#endif
	NObj.Number = aw_int (AW_OBJECT_NUMBER);
	NObj.X=aw_int (AW_OBJECT_X);
	NObj.Y=aw_int (AW_OBJECT_Y);
	NObj.Z=aw_int (AW_OBJECT_Z);
	NObj.Yaw=aw_int (AW_OBJECT_YAW);
	NObj.Roll=aw_int (AW_OBJECT_ROLL);
	NObj.Tilt=aw_int (AW_OBJECT_TILT);
	NObj.Owner=aw_int (AW_OBJECT_OWNER);
	NObj.BuildTime=aw_int (AW_OBJECT_BUILD_TIMESTAMP);
	#if AW_BUILD>77
        NObj.Model= aw_string (AW_OBJECT_MODEL);
        NObj.Description = aw_string (AW_OBJECT_DESCRIPTION);
        NObj.Action = aw_string (AW_OBJECT_ACTION);
	#else
        NObj.Model= wxString::From8BitData(aw_string (AW_OBJECT_MODEL));
        NObj.Description = 	wxString::From8BitData(aw_string (AW_OBJECT_DESCRIPTION));
        NObj.Action = wxString::From8BitData(aw_string (AW_OBJECT_ACTION));
	#endif

    #if AW_BUILD>41
	NObj.ID = aw_int (AW_OBJECT_ID);
	NObj.Type = aw_int (AW_OBJECT_TYPE);
	if (NObj.Type>1)
	{
		DatPtr = (unsigned char*) aw_data (AW_OBJECT_DATA, &DatLen);
		NObj.Data = BinToHex (DatPtr,DatLen);
	}
	#endif
	Cell->AddObj (NObj);
	if (Map) Map->Refresh();
}

//------------------------------------------------------------------------------

bool CBackupCtrl::IsScanning	()
{
	return Scanning;
}

//------------------------------------------------------------------------------

void CBackupCtrl::Object_Delete(CBot* Bot)
{
	if (Survey)
	{
		size_t Index;
		if (Cell->FindObjNum (Index, aw_int (AW_OBJECT_NUMBER))==CELL_OK)
		{
			Cell->DelObj(Index);
			if (Map) Map->Refresh ();
		}
	}
}

//------------------------------------------------------------------------------

void CBackupCtrl::OnObjTimer (wxTimerEvent& WXUNUSED(event))
{
	size_t NbObj=10;
	#if AW_BUILD>41
    size_t LenDat=0;
	unsigned char* Data=0;
	#endif
	CObject Obj;
	if (!CtrlAw->GetBot()->IsOnWorld()) return;
	if (Deleting)
	{
		if (Cell->GetNbSel() < NbObj) NbObj=Cell->GetNbSel();
		for (size_t i=0; i < NbObj; i++)
		{
			Cell->GetObjSel(Obj,0);
			aw_int_set (AW_OBJECT_NUMBER, Obj.Number);
			aw_int_set (AW_OBJECT_X, Obj.X);
			aw_int_set (AW_OBJECT_Z, Obj.Z);
			aw_object_delete ();
			Cell->DelObjSel(0);
			DelEC++;
		}
		if (Cell->GetNbSel() >0) ObjectTimer->Start (1000,true);
		else
		{
			Deleting=false;
			BlockSelect=false;
			wxLogMessage(_("End of deleting project.."));
		}
		if (Map) Map->Refresh ();
		return;
	}
	if (Building)
	{
		if (Cell->GetNbSel() < NbObj) NbObj=Cell->GetNbSel();
		for (size_t i=0; i < NbObj; i++)
		{
			Cell->GetObjSel(Obj,0);
			aw_int_set (AW_OBJECT_X, Obj.X);
			aw_int_set (AW_OBJECT_Y, Obj.Y);
			aw_int_set (AW_OBJECT_Z, Obj.Z);
			aw_int_set (AW_OBJECT_YAW, Obj.Yaw);
			aw_int_set (AW_OBJECT_TILT, Obj.Tilt);
			aw_int_set (AW_OBJECT_ROLL, Obj.Roll);
            #if AW_BUILD>77
                aw_string_set (AW_OBJECT_MODEL, Obj.Model);
                aw_string_set (AW_OBJECT_DESCRIPTION, Obj.Description);
                aw_string_set (AW_OBJECT_ACTION, Obj.Action);
            #else
                aw_string_set (AW_OBJECT_MODEL, Obj.Model.To8BitData());
                aw_string_set (AW_OBJECT_DESCRIPTION, Obj.Description.To8BitData());
                aw_string_set (AW_OBJECT_ACTION, Obj.Action.To8BitData());
            #endif
			aw_int_set (AW_OBJECT_OWNER, Obj.Owner);
			aw_int_set (AW_OBJECT_BUILD_TIMESTAMP, Obj.BuildTime);
            #if AW_BUILD>41
			aw_int_set (AW_OBJECT_TYPE, Obj.Type);
			if (Obj.Type>1)
			{
				LenDat = Obj.Data.Len()/2;
				Data= new unsigned char[LenDat];
				HexToBin(Obj.Data,Data);
				aw_data_set (AW_OBJECT_DATA, (char*)Data,LenDat);
				delete Data;
			}
			#endif
			if (CTBuild)	aw_object_load ();
			else if (Obj.Owner==CtrlAw->GetBot()->Citoyen) aw_object_add ();
			Cell->DelObjSel(0);
			BuildEC++;
		}
		if (Cell->GetNbSel() >0) ObjectTimer->Start (1000,true);
		else
		{
			Building=false;
			BlockSelect=false;
			wxLogMessage (_("End of building project.."));
		}
		if (Map) Map->Refresh ();
		return;
	}
}

//------------------------------------------------------------------------------

void CBackupCtrl::StartDelete ()
{
	if (Scanning || (!CtrlAw->GetBot()->IsOnWorld()) || Building) return;
	wxLogMessage (_("Start to deleting project.."));
	ObjectTimer->Start (1000,true);
	Deleting=true;
	BlockSelect=true;
}

//------------------------------------------------------------------------------

void CBackupCtrl::StartBuild ()
{
	if (Scanning || (!CtrlAw->GetBot()->IsOnWorld()) || Deleting) return;
	wxLogMessage (_("Start to building project.."));
	ObjectTimer->Start (1000,true);
	Building=true;
	BlockSelect=true;
}

//------------------------------------------------------------------------------

bool CBackupCtrl::IsSurvey()
{
	return Survey;
}

//------------------------------------------------------------------------------

void CBackupCtrl::Reset()
{
	Scanning=false;
	Cell->DelGrid ();
	BlockScroll=false;
	BlockSelect=false;
	Survey=false;
	Building=false;
	Deleting =false;
	BuildEC=0;
	DelEC=0;
	if (Map) Map->Refresh ();
}
#endif
