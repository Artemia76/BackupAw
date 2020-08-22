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

#ifdef VP_BUILD

#include "CBackupVP.h"
#include "CGeometry.h"

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
    Map=0;
	m_ScanSize=15;
    m_Config=wxConfigBase::Get();
    m_Config->Read(_T("Bot/BuildMode"), &CTBuild, true);
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

bool CBackupCtrl::Event( vp_event_t pID, CBot* pBot)
{
    switch (pID)
    {
    case VP_EVENT_OBJECT:
        Event_Object (pBot);
        return true;
    case VP_EVENT_OBJECT_CHANGE:
        Event_Object (pBot);
        return true;
    case VP_EVENT_OBJECT_DELETE:
        Event_Object_Delete (pBot);
        return true;
    case VP_EVENT_CELL_END:
        Event_Cell_End (pBot);
        return true;
    case VP_EVENT_UNIVERSE_DISCONNECT:
        Reset ();
        return true;
    case VP_EVENT_WORLD_DISCONNECT:
        Reset ();
        return true;
    default:
        return false;
    }
    return false;
}

//------------------------------------------------------------------------------

bool CBackupCtrl::CallBack (vp_callback_t pID, int pRC, int pHandle, CBot* pBot)
{

    switch (pID)
    {
        case VP_CALLBACK_OBJECT_LOAD:
        case VP_CALLBACK_OBJECT_ADD:
            CB_Object_Add (pRC, pHandle, pBot);
            return true;
        case VP_CALLBACK_OBJECT_DELETE:
            CB_Object_Delete (pRC, pHandle, pBot);
            return true;
        default:
            return false;
    }
    return false;

}

//------------------------------------------------------------------------------

void CBackupCtrl::CB_Object_Add (int pRC, int pHandle, CBot* pBot)
{
    if (m_BuildEC)
    {
        if (pRC) wxLogMessage(_("Unable to Build object. Reason : ") + pBot->GetRCString(pRC));
        else
        {
			if (m_ObjectMap.find(pHandle)!=m_ObjectMap.end())
			{
				m_ObjectMap[pHandle].Number = vp_int(pBot->GetInstance(),VP_OBJECT_ID);
				m_Cell->AddObj (m_ObjectMap[pHandle]);
				m_ObjectMap.erase(pHandle);
				if (Map) Map->Refresh();
			}
			else wxLogMessage(_("There is no handle to add in object map"));
        }
    }
}


//------------------------------------------------------------------------------

void CBackupCtrl::CB_Object_Delete (int pRC, int pHandle, CBot* pBot)
{
    if (m_DelEC)
    {
        if (pRC) wxLogMessage(_("Unable to Delete object. Reason : ") + pBot->GetRCString(pRC));
        else
        {
			size_t ID;
			if (m_Cell->FindObjNum(ID,vp_int(pBot->GetInstance(),VP_OBJECT_ID))==CELL_OK)
			{
				m_Cell->DelObj(ID);
				if (Map) Map->Refresh();

			}
			else wxLogMessage(_("Object to delete not found on the grid"));
        }
    }
}


//------------------------------------------------------------------------------

void CBackupCtrl::Scan ()
{
    if ((!m_Scanning)&&CtrlAw->GetBot()->IsOnWorld())
    {
		m_SequenceX.resize(m_ScanSize, 0 );
		m_SequenceZ.resize(m_ScanSize, 0 );

        int i,j,DemiScan;
		DemiScan=(int)floor ((double)m_ScanSize/2);
        for (i=0 ; i < m_ScanSize ; i++)
        {
            m_SequenceX [i] = (OrigX - DemiScan) +i;
            for (j=0; j < m_ScanSize ; j++)
            {
                m_SequenceZ [j] = (OrigY - DemiScan) + j;
            }
        }
        m_PtrX = m_PtrZ = 0 ;
        wxLogMessage(_("Scanning..."));
        m_Scanning=true;
        BlockScroll=true;
        m_CellQueryCnt=0;
        AskCell(CtrlAw->GetBot());

    }
}

//------------------------------------------------------------------------------

void CBackupCtrl::Event_Object (CBot* pBot)
{
    CObject Obj;
    VPInstance Instance = pBot->GetInstance();
    unsigned char* DatPtr=0;
    unsigned int DatLen=0;
    Obj.Number = vp_int(Instance,VP_OBJECT_ID);
	Obj.X = vp_double(Instance, VP_OBJECT_X) * 1000.0 ;
	Obj.Z = vp_double(Instance, VP_OBJECT_Z) * 1000.0 ;
	Obj.Y = vp_double(Instance, VP_OBJECT_Y) * 1000.0 ;
	Obj.RotX = vp_double(Instance, VP_OBJECT_ROTATION_X);
	Obj.RotY = vp_double(Instance, VP_OBJECT_ROTATION_Y);
	Obj.RotZ = vp_double(Instance, VP_OBJECT_ROTATION_Z);
	Obj.RotR = vp_double(Instance, VP_OBJECT_ROTATION_ANGLE);
    CAxisAngle  Rotation (Obj.RotZ, Obj.RotY,Obj.RotX,Obj.RotR);
    CEuler Euler = Rotation.GetEuler();
	Obj.Yaw = Euler.yaw * (1800.0 / M_PI);
	Obj.Tilt = Euler.tilt * (1800.0 / M_PI);
	Obj.Roll = Euler.roll * (1800.0 / M_PI);
    Obj.Owner=vp_int (Instance, VP_OBJECT_USER_ID);
    Obj.BuildTime=vp_int(Instance, VP_OBJECT_TIME);
    Obj.Model=wxString::FromUTF8 (vp_string(Instance, VP_OBJECT_MODEL));
    Obj.Description = 	wxString::FromUTF8(vp_string(Instance, VP_OBJECT_DESCRIPTION));
    Obj.Action = wxString::FromUTF8(vp_string(Instance, VP_OBJECT_ACTION));
    Obj.Type = vp_int (Instance, VP_OBJECT_TYPE);
    if (Obj.Type>1)
    {
        DatPtr = (unsigned char*) vp_data(Instance, VP_OBJECT_DATA, (int*)(&DatLen));
        Obj.Data = BinToHex (DatPtr,DatLen);
    }
    m_Cell->AddObj (Obj);
    if (Map) Map->Refresh();
}

//------------------------------------------------------------------------------
// Cell query is finish

void CBackupCtrl::Event_Cell_End (CBot* pBot)
{
    VPInstance Instance = pBot->GetInstance();
    wxString CellStr = CoordToAw (vp_int(Instance, VP_CELL_X )*1000, vp_int(Instance, VP_CELL_Z )*1000);
    m_CellMap[CellStr]=true;
    m_CellQueryCnt --;
    if (m_Scanning) AskCell(pBot);
}

//------------------------------------------------------------------------------
// Ask Query Cell

void CBackupCtrl::AskCell(CBot* WXUNUSED(pBot))
{
    int rc;
    wxString CellStr;
    do
    {
		CellStr = CoordToAw (m_SequenceX [m_PtrX]*1000, m_SequenceZ [m_PtrZ]*1000);
		if ( m_CellMap.find(CellStr) == m_CellMap.end())
		{
			if ((rc=vp_query_cell(CtrlAw->GetBot()->GetInstance() , m_SequenceX [m_PtrX], m_SequenceZ [m_PtrZ])))
			{
				wxLogMessage(_("Unable to query cell. Reason : ") + CtrlAw->GetBot()->GetRCString(rc));
			}
			m_CellQueryCnt ++;
		}
        if ((m_PtrX == ( m_ScanSize-1)) && (m_PtrZ == (m_ScanSize-1)))
        {
			wxLogMessage(_("End of scan. "));
			m_Scanning=false;
			BlockScroll=false;
			m_Survey=true;
			break;
        }
        if (m_PtrX ==(m_ScanSize -1))
        {
            m_PtrX = 0;
            m_PtrZ ++;
        }
        else m_PtrX++;
    }
    while (m_CellQueryCnt < 32 );
}
//------------------------------------------------------------------------------

bool CBackupCtrl::IsScanning	()
{
    return m_Scanning;
}

//------------------------------------------------------------------------------

void CBackupCtrl::Event_Object_Delete(CBot* pBot)
{
	size_t Index;
	VPInstance Instance = pBot->GetInstance();
	if (m_Cell->FindObjNum (Index, vp_int (Instance,VP_OBJECT_ID))==CELL_OK)
	{
        m_Cell->DelObj(Index);
		if (Map) Map->Refresh ();
	}
}

//------------------------------------------------------------------------------

void CBackupCtrl::OnObjTimer (wxTimerEvent& WXUNUSED(pEvent))
{

    size_t NbObj=10;
    size_t LenDat=0;
    unsigned char* Data=0;
    CObject Obj;
    if (!CtrlAw->GetBot()->IsOnWorld()) return;
    VPInstance Instance=CtrlAw->GetBot()->GetInstance();
    if (Deleting)
    {
        if (m_Cell->GetNbSel() < NbObj) NbObj= m_Cell->GetNbSel();
        for (size_t i=0; i < NbObj; i++)
        {
            m_Cell->GetObjSel(Obj,0);
#if VPSDK_VERSION >= 2
            m_ObjectMap[vp_object_delete (Instance, Obj.Number)]=Obj;
#else
			vp_int_set(Instance,VP_OBJECT_ID, Obj.Number);
			vp_object_delete (Instance);
#endif
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
			vp_double_set (Instance, VP_OBJECT_X, Obj.X / 1000);
			vp_double_set(Instance, VP_OBJECT_Y, Obj.Y / 1000);
			vp_double_set(Instance, VP_OBJECT_Z, Obj.Z / 1000);
			//If Axis Angle is null, convert from Euler
			if ((Obj.RotX==0) && (Obj.RotY==0) && (Obj.RotZ==0) && (Obj.RotR == 0))
			{ 
				CEuler Euler (Obj.Yaw / (1800.0/M_PI),Obj.Tilt / (1800.0/M_PI), Obj.Roll / (1800.0/M_PI));
				CAxisAngle AxisAngle  = Euler.GetAxisAngle();
				vp_double_set(Instance, VP_OBJECT_ROTATION_X, AxisAngle.z);
				vp_double_set(Instance, VP_OBJECT_ROTATION_Y, AxisAngle.y);
				vp_double_set(Instance, VP_OBJECT_ROTATION_Z, AxisAngle.x);
				vp_double_set(Instance, VP_OBJECT_ROTATION_ANGLE, AxisAngle.r);
			}
			else
			{
				vp_double_set (Instance, VP_OBJECT_ROTATION_X, Obj.RotX);
				vp_double_set (Instance, VP_OBJECT_ROTATION_Y, Obj.RotY);
				vp_double_set (Instance, VP_OBJECT_ROTATION_Z, Obj.RotZ);
				vp_double_set(Instance, VP_OBJECT_ROTATION_ANGLE, Obj.RotR);
			}
			vp_string_set (Instance,VP_OBJECT_MODEL, Obj.Model.utf8_str());
            vp_string_set (Instance,VP_OBJECT_DESCRIPTION, Obj.Description.utf8_str());
            vp_string_set (Instance,VP_OBJECT_ACTION, Obj.Action.utf8_str());
			vp_int_set (Instance,VP_OBJECT_USER_ID, Obj.Owner);
            vp_int_set (Instance,VP_OBJECT_TYPE, Obj.Type);
            if (Obj.Type>1)
            {
                LenDat = Obj.Data.Len()/2;
                Data= new unsigned char[LenDat];
                HexToBin(Obj.Data,Data);
                vp_data_set (Instance,VP_OBJECT_DATA, (int)LenDat, (char*)Data);
                delete Data;
            }
			m_BuildEC++;
            m_ObjectMap[(int)m_BuildEC]=Obj;
            vp_int_set(Instance, VP_REFERENCE_NUMBER,(int)m_BuildEC );
			if (CTBuild) vp_object_load (Instance);
			else vp_object_add (Instance);
            m_Cell->DelObjSel(0);
        }
        if (m_Cell->GetNbSel() >0) m_ObjectTimer->Start (1000,true);
        else
        {
            Building=false;
            BlockSelect=false;
            wxLogMessage (_("End of building project.."));
        }
        //if (Map) Map->Refresh ();
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
    m_DelEC=0;
    BlockSelect=true;
}

//------------------------------------------------------------------------------

void CBackupCtrl::StartBuild ()
{

    if (m_Scanning || (!CtrlAw->GetBot()->IsOnWorld()) || Deleting) return;
    wxLogMessage (_("Start to building project.."));
    m_ObjectTimer->Start (1000,true);
    Building=true;
    m_BuildEC=0;
    m_ObjectMap.clear();
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
    m_CellMap.clear();
}

int	CBackupCtrl::GetScanSize()
{
	return m_ScanSize;
}

void CBackupCtrl::SetScanSize(int pSize)
{
	if (((pSize >5) || (pSize < 200)) && (!m_Scanning))
	{
		m_ScanSize = pSize;
	}
}

#endif
