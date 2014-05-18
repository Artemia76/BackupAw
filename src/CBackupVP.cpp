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

bool CBackupCtrl::Event( vp_event_t id, CBot* Bot)
{
    switch (id)
    {
    case VP_EVENT_OBJECT:
        Event_Object (Bot);
        return true;
    case VP_EVENT_OBJECT_CHANGE:
        Event_Object (Bot);
        return true;
    case VP_EVENT_OBJECT_DELETE:
        Event_Object_Delete (Bot);
        return true;
    case VP_EVENT_CELL_END:
        Event_Cell_End (Bot);
        return true;
    case VP_EVENT_UNIVERSE_DISCONNECT:
        Reset ();
        return true;
    case VP_EVENT_WORLD_DISCONNECT:
        Reset ();
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------

bool CBackupCtrl::CallBack (vp_callback_t id, int rc, int Handle, CBot* Bot)
{

    switch (id)
    {
    case VP_CALLBACK_OBJECT_ADD:
        CB_Object_Add (rc, Handle, Bot);
        return true;
    case VP_CALLBACK_OBJECT_DELETE:
        CB_Object_Delete (rc, Handle, Bot);
        return true;
    }
    return false;

}

//------------------------------------------------------------------------------

void CBackupCtrl::CB_Object_Add (int rc, int Handle, CBot* Bot)
{
    if (BuildEC)
    {
        if (rc) wxLogMessage(_("Unable to Build object. Reason : ") + Bot->GetRCString(rc));
        else
        {
			if (ObjectMap.find(Handle)!=ObjectMap.end())
			{
				ObjectMap[Handle].Number = vp_int(Bot->GetInstance(),VP_OBJECT_ID);
				Cell->AddObj (ObjectMap[Handle]);
				ObjectMap.erase(Handle);
				if (Map) Map->Refresh();
			}
			else wxLogMessage(_("There is no handle to add in object map"));
        }
    }
}


//------------------------------------------------------------------------------

void CBackupCtrl::CB_Object_Delete (int rc, int Handle, CBot* Bot)
{
    if (DelEC)
    {
        if (rc) wxLogMessage(_("Unable to Delete object. Reason : ") + Bot->GetRCString(rc));
        else
        {
			size_t ID;
			if (Cell->FindObjNum(ID,vp_int(Bot->GetInstance(),VP_OBJECT_ID))==CELL_OK)
			{
				Cell->DelObj(ID);
				if (Map) Map->Refresh();

			}
			else wxLogMessage(_("Object to delete not found on the grid"));
        }
    }
}


//------------------------------------------------------------------------------

void CBackupCtrl::Scan ()
{
    if ((!Scanning)&&CtrlAw->GetBot()->IsOnWorld())
    {
        memset (SequenceX, 0, sizeof (SequenceX));
        memset (SequenceZ, 0, sizeof (SequenceZ));
        // Init query5x5 Array
        int i,j;
        for (i=0 ; i < 15 ; i++)
        {
            SequenceX [i] = (OrigX - 7) +i;
            for (j=0; j < 15 ; j++)
            {
                SequenceZ [j] = (OrigY - 7) + j;
            }
        }
        PtrX = PtrZ = 0 ;
        wxLogMessage(_("Scanning..."));
        Scanning=true;
        BlockScroll=true;
        CellQueryCnt=0;
        AskCell(CtrlAw->GetBot());

    }
}

//------------------------------------------------------------------------------

void CBackupCtrl::Event_Object (CBot* Bot)
{
    CObject Obj;
    VPInstance Instance = Bot->GetInstance();
    unsigned char* DatPtr=0;
    unsigned int DatLen=0;
    Obj.Number = vp_int(Instance,VP_OBJECT_ID);
    Obj.X=vp_float(Instance,VP_OBJECT_X) * 1000.0 ;
    Obj.Z=vp_float(Instance,VP_OBJECT_Z) * 1000.0 ;
    Obj.Y=vp_float(Instance,VP_OBJECT_Y) * 1000.0 ;
    Obj.RotX=vp_float(Instance,VP_OBJECT_ROTATION_X);
    Obj.RotY=vp_float(Instance,VP_OBJECT_ROTATION_Y);
    Obj.RotZ=vp_float(Instance,VP_OBJECT_ROTATION_Z);
    Obj.RotR=vp_float(Instance,VP_OBJECT_ROTATION_ANGLE);
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
    Cell->AddObj (Obj);
    if (Map) Map->Refresh();
}

//------------------------------------------------------------------------------
// Cell query is finish

void CBackupCtrl::Event_Cell_End (CBot* Bot)
{
    VPInstance Instance = Bot->GetInstance();
    wxString CellStr = CoordToAw (vp_int(Instance, VP_CELL_X )*1000, vp_int(Instance, VP_CELL_Z )*1000);
    CellMap[CellStr]=true;
    CellQueryCnt --;
    if (Scanning) AskCell(Bot);
}

//------------------------------------------------------------------------------
// Ask Query Cell

void CBackupCtrl::AskCell(CBot* Bot)
{
    VPInstance Instance = Bot->GetInstance();
    int rc;
    wxString CellStr;
    do
    {
		CellStr = CoordToAw (SequenceX [PtrX]*1000, SequenceZ [PtrZ]*1000);
		if ( CellMap.find(CellStr) == CellMap.end())
		{
			if (rc=vp_query_cell(CtrlAw->GetBot()->GetInstance() , SequenceX [PtrX], SequenceZ [PtrZ]))
			{
				wxLogMessage(_("Unable to query cell. Reason : ") + CtrlAw->GetBot()->GetRCString(rc));
			}
			CellQueryCnt ++;
		}
        if ((PtrX == 14) && (PtrZ == 14))
        {
			wxLogMessage(_("End of scan. "));
			Scanning=false;
			BlockScroll=false;
			Survey=true;
			break;
        }
        if (PtrX ==14)
        {
            PtrX = 0;
            PtrZ ++;
        }
        else PtrX++;
    }
    while (CellQueryCnt < 32 );
}
//------------------------------------------------------------------------------

bool CBackupCtrl::IsScanning	()
{
    return Scanning;
}

//------------------------------------------------------------------------------

void CBackupCtrl::Event_Object_Delete(CBot* Bot)
{
	size_t Index;
	VPInstance Instance = Bot->GetInstance();
	if (Cell->FindObjNum (Index, vp_int (Instance,VP_OBJECT_ID))==CELL_OK)
	{
		Cell->DelObj(Index);
		if (Map) Map->Refresh ();
	}
}

//------------------------------------------------------------------------------

void CBackupCtrl::OnObjTimer (wxTimerEvent& WXUNUSED(event))
{

    size_t NbObj=10;
    size_t LenDat=0;
    unsigned char* Data=0;
    CObject Obj;
    if (!CtrlAw->GetBot()->IsOnWorld()) return;
    VPInstance Instance=CtrlAw->GetBot()->GetInstance();
    if (Deleting)
    {
        if (Cell->GetNbSel() < NbObj) NbObj=Cell->GetNbSel();
        for (size_t i=0; i < NbObj; i++)
        {
            Cell->GetObjSel(Obj,0);
#if VPSDK_VERSION >= 2
			ObjectMap[vp_object_delete (Instance, Obj.Number)]=Obj;
#else
			vp_int_set(Instance,VP_OBJECT_ID, Obj.Number);
			vp_object_delete (Instance);
#endif
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
            vp_float_set (Instance, VP_OBJECT_X, Obj.X / 1000);
            vp_float_set (Instance,VP_OBJECT_Y, Obj.Y / 1000);
            vp_float_set (Instance,VP_OBJECT_Z, Obj.Z / 1000);
			//If Axis Angle is null, convert from Euler
			if ((Obj.RotX==0) && (Obj.RotY==0) && (Obj.RotZ==0) && (Obj.RotR == 0))
			{ 
				CEuler Euler (Obj.Yaw / (1800.0/M_PI),Obj.Tilt / (1800.0/M_PI), Obj.Roll / (1800.0/M_PI));
				CAxisAngle AxisAngle  = Euler.GetAxisAngle();
				vp_float_set (Instance,VP_OBJECT_ROTATION_X, AxisAngle.z);
				vp_float_set (Instance,VP_OBJECT_ROTATION_Y, AxisAngle.y);
				vp_float_set (Instance,VP_OBJECT_ROTATION_Z, AxisAngle.x);
				vp_float_set (Instance,VP_OBJECT_ROTATION_ANGLE, AxisAngle.r);
			}
			else
			{
				vp_float_set (Instance,VP_OBJECT_ROTATION_X, Obj.RotX);
				vp_float_set (Instance,VP_OBJECT_ROTATION_Y, Obj.RotY);
				vp_float_set (Instance,VP_OBJECT_ROTATION_Z, Obj.RotZ);
				vp_float_set (Instance,VP_OBJECT_ROTATION_ANGLE, Obj.RotR);
			}
			vp_string_set (Instance,VP_OBJECT_MODEL, Obj.Model.utf8_str());
            vp_string_set (Instance,VP_OBJECT_DESCRIPTION, Obj.Description.utf8_str());
            vp_string_set (Instance,VP_OBJECT_ACTION, Obj.Action.utf8_str());
            vp_int_set (Instance,VP_OBJECT_TYPE, Obj.Type);
            if (Obj.Type>1)
            {
                LenDat = Obj.Data.Len()/2;
                Data= new unsigned char[LenDat];
                HexToBin(Obj.Data,Data);
                vp_data_set (Instance,VP_OBJECT_DATA, LenDat, (char*)Data);
                delete Data;
            }
			BuildEC++;
            ObjectMap[BuildEC]=Obj;
            vp_int_set(Instance, VP_REFERENCE_NUMBER,BuildEC );
            vp_object_add (Instance);
            Cell->DelObjSel(0);
        }
        if (Cell->GetNbSel() >0) ObjectTimer->Start (1000,true);
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
    if (Scanning || (!CtrlAw->GetBot()->IsOnWorld()) || Building) return;
    wxLogMessage (_("Start to deleting project.."));
    ObjectTimer->Start (1000,true);
    Deleting=true;
    DelEC=0;
    BlockSelect=true;
}

//------------------------------------------------------------------------------

void CBackupCtrl::StartBuild ()
{

    if (Scanning || (!CtrlAw->GetBot()->IsOnWorld()) || Deleting) return;
    wxLogMessage (_("Start to building project.."));
    ObjectTimer->Start (1000,true);
    Building=true;
    BuildEC=0;
    ObjectMap.clear();
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
    CellMap.clear();
}
#endif
