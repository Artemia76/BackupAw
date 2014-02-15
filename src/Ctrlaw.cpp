// *****************************************************************************
// *                                                                           *
// *                        BACKUPAW : Ctrlaw.cpp                              *
// *                        Controller For AW Sdk                              *
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
// *   CopyRight 2005 Neophile                                                 *
// *   Creation          : 22/04/2005                                          *
// *   Last Modification :                                                     *
// *   Revision          : A                                                   *
// *                                                                           *
// *****************************************************************************

#include "Ctrlaw.h"

#include <aw.h>

BEGIN_EVENT_TABLE(CCtrlAw, wxEvtHandler)
	EVT_TIMER (HEARTBEAT, CCtrlAw::On_HeartBeat)
END_EVENT_TABLE()

//------------------------------------------------------------------------------
// SingleTon Private pointer

CCtrlAw* CCtrlAw::PtCCtrlAw = 0;

//------------------------------------------------------------------------------
// Creator
CCtrlAw* CCtrlAw::Create( wxFileConfig *fConfig, CMapCanvas* Carte)
{
	if (!PtCCtrlAw)
	{
		PtCCtrlAw = new CCtrlAw(fConfig, Carte);
	}
	return PtCCtrlAw;
}

//------------------------------------------------------------------------------
// Get Singleton pointer

CCtrlAw* CCtrlAw::Get()
{
	return PtCCtrlAw;
}


//------------------------------------------------------------------------------
// Singleton killer

void CCtrlAw::Kill()
{
	if (PtCCtrlAw != 0) delete PtCCtrlAw;
	PtCCtrlAw=0;
}

//------------------------------------------------------------------------------
// Private Constructor

CCtrlAw::CCtrlAw ( wxFileConfig *fConfig, CMapCanvas* Carte)
{
	Bot=0;
	Map=Carte;
	AwInit=false;
	Logger=CCtrlLog::Create();
	pConfig=fConfig;
	Heart = new wxTimer (this, HEARTBEAT);
}

//------------------------------------------------------------------------------
// Private Destructor

CCtrlAw::~CCtrlAw()
{
}

//------------------------------------------------------------------------------
// SDK Initialization and Bots instance creation
// bool flag = TRUE : Initialization
//           = FALSE : Close SDK

int CCtrlAw::Init (bool flag)
{
	int rc;
	if ((flag) && (!AwInit))
	{
		Bot = new CBot;
		if ((rc=aw_init (AW_BUILD)))
		{
			Logger->Log(_("Unable to init the SDK, Reason :"), _T("RED"), false, rc);
			return rc;
		}
		else
		{
			Logger->Log(_("SDK Initialized"), _T("BLUE"));
		}
		// Install AW Events
		aw_event_set (AW_EVENT_WORLD_DISCONNECT, CCtrlAw::On_World_Disconnect);
		aw_event_set (AW_EVENT_UNIVERSE_DISCONNECT, CCtrlAw::On_Universe_Disconnect);
		aw_event_set (AW_EVENT_CELL_BEGIN, CCtrlAw::On_Cell_Begin);
		aw_event_set (AW_EVENT_CELL_OBJECT, CCtrlAw::On_Cell_Object);
		aw_event_set (AW_EVENT_OBJECT_ADD, CCtrlAw::On_Object_Add);
		aw_event_set (AW_EVENT_OBJECT_DELETE, CCtrlAw::On_Object_Delete);
		// Installe AW Callbacks
		aw_callback_set (AW_CALLBACK_LOGIN, CCtrlAw::On_Login);
		aw_callback_set (AW_CALLBACK_ENTER, CCtrlAw::On_Enter);
		aw_callback_set (AW_CALLBACK_QUERY, CCtrlAw::On_Query);
		aw_callback_set (AW_CALLBACK_OBJECT_RESULT, CCtrlAw::On_Object);
		AwInit=true;
		Bot->pConfig=pConfig;
		Bot->Map=Map;
		Bot->Charge ();
		if (Bot->CGConAuto)
		{
			Bot->Global=true;
			if (Bot->CGRecoEna)
			{
				Bot->CGRecoCnt=0;
				Bot->CGRetente=Bot->CGRecoDelay;
				Bot->ModeReco=true;
			}
			Bot->Connect();
		}
		Heart->Start(200);
		return 0;
	}
	else if((!flag) && (AwInit))
	{
		if (Bot->IsOnWorld())
		{
			Bot->Connection(false);
		}
		Heart->Stop();
		delete Bot;
		aw_term();
		Logger->Log(_("SDK Stopped."), _T("BLUE"));
		return 0;
	}
	return 1000;
}

//------------------------------------------------------------------------------
// Static Members for AW events

void CCtrlAw::On_Admin_Worlds_Delete(void)
{

}

//------------------------------------------------------------------------------

void CCtrlAw::On_Admin_Worlds_Info(void)
{

}

//------------------------------------------------------------------------------

void CCtrlAw::On_Avatar_Add(void)
{

}

//------------------------------------------------------------------------------

void CCtrlAw::On_Avatar_Change(void)
{

}

//------------------------------------------------------------------------------

void CCtrlAw::On_Avatar_Delete(void)
{

}

//------------------------------------------------------------------------------

void CCtrlAw::On_Avatar_Click(void)
{

}

//------------------------------------------------------------------------------
// Cell Begin to be downloaded

void CCtrlAw::On_Cell_Begin(void)
{
	CBot* Robot=PtCCtrlAw->Bot;
	Robot->Cell_Begin ();
}

//------------------------------------------------------------------------------

void CCtrlAw::On_Cell_End(void)
{

}

//------------------------------------------------------------------------------

void CCtrlAw::On_Cell_Object(void)
{
	CBot* Robot=PtCCtrlAw->Bot;
	Robot->Cell_Object ();
}

//------------------------------------------------------------------------------

void CCtrlAw::On_Chat(void)
{

}

//------------------------------------------------------------------------------

void CCtrlAw::On_Console_Message(void)
{

}

//------------------------------------------------------------------------------

void CCtrlAw::On_Object_Add(void)
{
	CBot* Robot=PtCCtrlAw->Bot;
	Robot->Object_Add ();
}

//------------------------------------------------------------------------------

void CCtrlAw::On_Object_Click(void)
{

}

//------------------------------------------------------------------------------

void CCtrlAw::On_Object_Delete(void)
{
	CBot* Robot=PtCCtrlAw->Bot;
	Robot->Object_Delete ();
}

//------------------------------------------------------------------------------

void CCtrlAw::On_Object_select(void)
{

}

//------------------------------------------------------------------------------

void CCtrlAw::On_Teleport(void)
{

}

//------------------------------------------------------------------------------

void CCtrlAw::On_Universe_Attributes(void)
{

}

//------------------------------------------------------------------------------

void CCtrlAw::On_Url(void)
{

}

//------------------------------------------------------------------------------

void CCtrlAw::On_World_Attributes(void)
{

}

//------------------------------------------------------------------------------

void CCtrlAw::On_World_Disconnect(void)
{
	CBot* Robot;
	Robot=PtCCtrlAw->GetBot();
	Robot->PerteMonde=true;
}

//------------------------------------------------------------------------------

void CCtrlAw::On_World_Info(void)
{

}

//------------------------------------------------------------------------------

void CCtrlAw::On_Terrain_Begin(void)
{

}

void CCtrlAw::On_Terrain_Changed(void)
{

}

//------------------------------------------------------------------------------

void CCtrlAw::On_Terrain_Data(void)
{

}

//------------------------------------------------------------------------------

void CCtrlAw::On_Terrain_End(void)
{

}

//------------------------------------------------------------------------------

void CCtrlAw::On_Universe_Disconnect(void)
{
	CBot* Robot;
	Robot=PtCCtrlAw->GetBot();
	Robot->PerteUniv=true;
}

//------------------------------------------------------------------------------
// Callbacks Events

void CCtrlAw::On_Login (int rc)
{
	CBot* Robot;
	Robot=PtCCtrlAw->GetBot();
	Robot->Login_CB(rc);
}

//------------------------------------------------------------------------------

void CCtrlAw::On_Enter (int rc)
{
	CBot* Robot;
	Robot=PtCCtrlAw->GetBot();
	Robot->Enter_CB(rc);
}

//------------------------------------------------------------------------------

void CCtrlAw::On_Query (int rc)
{
	CBot* Robot;
	Robot=PtCCtrlAw->GetBot();
	Robot->Query_CB (rc);
}

//------------------------------------------------------------------------------

void CCtrlAw::On_Object (int rc)
{
	CBot* Robot;
	Robot=PtCCtrlAw->GetBot();
	Robot->Object_CB (rc);
}


//------------------------------------------------------------------------------
// Return Current Bot Pointer

CBot* CCtrlAw::GetBot ()
{
	return Bot;
}

//------------------------------------------------------------------------------
// Controller HeartBeat for SDK update

void CCtrlAw::On_HeartBeat (wxTimerEvent& WXUNUSED(event))
{
	aw_wait(0);
	Bot->Update();
}
