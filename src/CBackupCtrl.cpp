// *****************************************************************************
// *                                                                           *
// *                       BACKUPAW : CBackupCtrl.h                            *
// *                  The Grid Canvas to display project                       *
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
// *   CopyRight 2014 Neophile                                                 *
// *   Creation          : 21/04/2014                                          *
// *   Last Modification :                                                     *
// *   Revision          : A                                                   *
// *                                                                           *
// *****************************************************************************
#ifndef VP_BUILD
#include "CBackupCtrl.h"

wxBEGIN_EVENT_TABLE(CBackupCtrl, wxEvtHandler)
	EVT_TIMER  (OBJ_TIME,	CBackupCtrl::OnObjTimer)
wxEND_EVENT_TABLE()

//------------------------------------------------------------------------------
// SingleTon Private pointer

CBackupCtrl* CBackupCtrl::m_PtrCBackupCtrl = nullptr;

//------------------------------------------------------------------------------
// Creator
CBackupCtrl* CBackupCtrl::Create()
{
	if (!m_PtrCBackupCtrl)
	{
		m_PtrCBackupCtrl = new CBackupCtrl();
	}
	return m_PtrCBackupCtrl;
}

//------------------------------------------------------------------------------
// Singleton killer

void CBackupCtrl::Kill()
{
	if (m_PtrCBackupCtrl != 0) delete m_PtrCBackupCtrl;
	m_PtrCBackupCtrl =0;
}

//------------------------------------------------------------------------------
// Private Constructor

CBackupCtrl::CBackupCtrl ()
{
	m_CellX = 0;
	m_CellZ = 0;
	//m_Sequence = 0;
	m_Scanning=false;
	m_Survey=false;
	Deleting=false;
	Building=false;
	m_BuildEC=0;
	m_DelEC=0;
	OrigX=0;
	OrigY=0;
	BlockScroll=false;
	BlockSelect=false;
	Map=nullptr;
	m_Config=wxConfigBase::Get();
	wxString BAPVersion = wxString::Format(_T("AW%i"), AW_BUILD);

	m_Config->Read(BAPVersion + _T("/BuildMode"), &CTBuild, true);
	m_Config->Read(BAPVersion + _T("/ScanSize"), &m_ScanSize, 15);
	m_ObjectTimer = new wxTimer(this, OBJ_TIME);
	m_Cell = CCtrlCell::Create();
}

//------------------------------------------------------------------------------
// Private Destructor

CBackupCtrl::~CBackupCtrl()
{
}

//------------------------------------------------------------------------------
// Event Dispatcher

bool CBackupCtrl::Event( AW_EVENT_ATTRIBUTE pID, CBot* pBot)
{
	switch (pID)
	{
		case AW_EVENT_CELL_BEGIN:
			Cell_Begin (pBot);
			return true;
		case AW_EVENT_CELL_OBJECT:
			Cell_Object (pBot);
			return true;
		case AW_EVENT_OBJECT_ADD:
			Cell_Object(pBot);
			return true;
		case AW_EVENT_OBJECT_DELETE:
			Object_Delete (pBot);
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

bool CBackupCtrl::CallBack (AW_CALLBACK pID, int pRC, CBot* pBot)
{
	switch (pID)
	{
		case AW_CALLBACK_QUERY:
			Query_CB(pRC, pBot);
			return true;
		case AW_CALLBACK_OBJECT_RESULT:
			Object_CB(pRC,pBot);
			return true;
	}
	return false;
}
//------------------------------------------------------------------------------
// Retour Callback d'un query

void CBackupCtrl::Query_CB(int pRC, CBot* pBot)
{
	if (pRC)
	{
		wxLogMessage(_("Unable to query properties. Reason :") + pBot->GetRCString (pRC));
		m_Scanning=false;
		BlockScroll=false;
	}
	else
	{
		if (aw_bool(AW_QUERY_COMPLETE))
		{
			m_Scanning=false;
			BlockScroll=false;
			m_Survey=true;
		}
		else aw_query_5x5 (aw_sector_from_cell (OrigX), aw_sector_from_cell (OrigY), m_Sequence);
	}
}

//------------------------------------------------------------------------------
// Object Callback

void CBackupCtrl::Object_CB (int pRC, CBot* pBot)
{
	if (m_BuildEC)
	{
		if (pRC) wxLogMessage(_("Unable to Build object. Reason : ") + pBot->GetRCString(pRC));
		m_BuildEC--;
	}
	else if (m_DelEC)
	{
		if (pRC) wxLogMessage(_("Unable to Delete object. Reason : ") + pBot->GetRCString(pRC));
		m_DelEC--;
	}
}


//------------------------------------------------------------------------------

void CBackupCtrl::Scan ()
{
	if ((!m_Scanning)&&CtrlAw->GetBot()->IsOnWorld())
	{
		memset (m_Sequence, 0, sizeof (m_Sequence));
		aw_query_5x5 (aw_sector_from_cell (OrigX), aw_sector_from_cell (OrigY), m_Sequence);
		m_Scanning =true;
		BlockScroll=true;
	}
}

//------------------------------------------------------------------------------

void CBackupCtrl::Cell_Begin(CBot* WXUNUSED(pBot))
{
	int sector_x;
	int sector_z;
	int sectorxmax = 2 - aw_sector_from_cell (OrigX);
	int sectorzmax = 2 - aw_sector_from_cell (OrigY);
	m_CellX = aw_int (AW_CELL_X);
	m_CellZ = aw_int (AW_CELL_Z);
	sector_x = aw_sector_from_cell (m_CellX);
	sector_z = aw_sector_from_cell (m_CellZ);
	m_Sequence[sectorzmax+sector_z][sectorxmax+sector_x] = aw_int (AW_CELL_SEQUENCE);
}

//------------------------------------------------------------------------------

void CBackupCtrl::Cell_Object (CBot* WXUNUSED(pBot))
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
	m_Cell->AddObj (NObj);
	if (Map) Map->Refresh();
}

//------------------------------------------------------------------------------

bool CBackupCtrl::IsScanning	()
{
	return m_Scanning;
}

//------------------------------------------------------------------------------

void CBackupCtrl::Object_Delete(CBot* WXUNUSED(pBot))
{
	if (m_Survey)
	{
		size_t Index;
		if (m_Cell->FindObjNum (Index, aw_int (AW_OBJECT_NUMBER))==CELL_OK)
		{
			m_Cell->DelObj(Index);
			if (Map) Map->Refresh ();
		}
	}
}

//------------------------------------------------------------------------------

void CBackupCtrl::OnObjTimer (wxTimerEvent& WXUNUSED(pEvent))
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
		if (m_Cell->GetNbSel() < NbObj) NbObj= m_Cell->GetNbSel();
		for (size_t i=0; i < NbObj; i++)
		{
			m_Cell->GetObjSel(Obj,0);
			aw_int_set (AW_OBJECT_NUMBER, Obj.Number);
			aw_int_set (AW_OBJECT_X, Obj.X);
			aw_int_set (AW_OBJECT_Z, Obj.Z);
			aw_object_delete ();
			m_Cell->DelObjSel(0);
			m_DelEC++;
		}
		if (m_Cell->GetNbSel() >0) m_ObjectTimer->Start (1000,true);
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
		if (m_Cell->GetNbSel() < NbObj) NbObj= m_Cell->GetNbSel();
		for (size_t i=0; i < NbObj; i++)
		{
			m_Cell->GetObjSel(Obj,0);
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
				delete[] Data;
			}
			#endif
			if (CTBuild)	aw_object_load ();
			else if (Obj.Owner==CtrlAw->GetBot()->Citoyen) aw_object_add ();
			m_Cell->DelObjSel(0);
			m_BuildEC++;
		}
		if (m_Cell->GetNbSel() >0) m_ObjectTimer->Start (1000,true);
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
	if (m_Scanning || (!CtrlAw->GetBot()->IsOnWorld()) || Building) return;
	wxLogMessage (_("Start to deleting project.."));
	m_ObjectTimer->Start (1000,true);
	Deleting=true;
	BlockSelect=true;
}

//------------------------------------------------------------------------------

void CBackupCtrl::StartBuild ()
{
	if (m_Scanning || (!CtrlAw->GetBot()->IsOnWorld()) || Deleting) return;
	wxLogMessage (_("Start to building project.."));
	m_ObjectTimer->Start (1000,true);
	Building=true;
	BlockSelect=true;
}

//------------------------------------------------------------------------------

bool CBackupCtrl::IsSurvey()
{
	return m_Survey;
}

//------------------------------------------------------------------------------

void CBackupCtrl::Reset()
{
	m_Scanning=false;
	m_Cell->DelGrid ();
	BlockScroll=false;
	BlockSelect=false;
	m_Survey=false;
	Building=false;
	Deleting =false;
	m_BuildEC=0;
	m_DelEC=0;
	if (Map) Map->Refresh ();
}

//------------------------------------------------------------------------------

int	CBackupCtrl::GetScanSize()
{
	return m_ScanSize;
}

//------------------------------------------------------------------------------

void CBackupCtrl::SetScanSize(int pSize)
{
	if (((pSize >5) || (pSize < 200)) && (!m_Scanning))
	{
		m_ScanSize = pSize;
		wxString BAPVersion = wxString::Format(_T("AW%i"), AW_BUILD);
		m_Config->Write(BAPVersion + _T("/ScanSize"), pSize);
		m_Config->Flush();
	}
}

#endif