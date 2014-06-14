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
// *   Last Modification : 14/04/2014                                          *
// *   Revision          : B                                                   *
// *                                                                           *
// *****************************************************************************

#include "Ctrlaw.h"


CAwListenner::CAwListenner ()
{
	CtrlAw = CCtrlAw::Create ();
	CtrlAw->AddListenner(this);
}

CAwListenner::~CAwListenner ()
{
	CtrlAw->DelListenner(this);
}

wxBEGIN_EVENT_TABLE(CCtrlAw, wxEvtHandler)
	EVT_TIMER (HEARTBEAT, CCtrlAw::On_HeartBeat)
wxEND_EVENT_TABLE()

//------------------------------------------------------------------------------
// SingleTon Private pointer

CCtrlAw* CCtrlAw::PtCCtrlAw = 0;

//------------------------------------------------------------------------------
// Creator
CCtrlAw* CCtrlAw::Create()
{
	if (!PtCCtrlAw)
	{
		PtCCtrlAw = new CCtrlAw();
	}
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

CCtrlAw::CCtrlAw ()
{
	AwInit=false;
	pConfig=wxConfigBase::Get();
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

int CCtrlAw::Init (bool flag, size_t NbBot)
{
	int rc;
	if (NbBot<1) NbBot=1;
	if ((flag) && (!AwInit))
	{
#ifndef VP_BUILD
		if ((rc=aw_init (AW_BUILD)))
#else
        if ((rc=vp_init ()))
#endif // VP_BUILD
		{
			wxLogMessage(_("Unable to init the SDK, Reason :")+ CBot::GetRCString(rc));
			return rc;
		}
		else
		{
			wxLogMessage(_("SDK Initialized"));
		}
		// Install AW Events
#ifndef VP_BUILD
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
#endif // VP_BUILD
		AwInit=true;
		for (size_t i=0 ; i<NbBot ; i++)
		{
			Bot.push_back(new CBot());
			Bot.back()->Charge ();
			if (Bot.back()->CGConAuto)
			{
				Bot.back()->Global=true;
				if (Bot.back()->CGRecoEna)
				{
					Bot.back()->CGRecoCnt=0;
					Bot.back()->CGRetente=Bot.back()->CGRecoDelay;
					Bot.back()->ModeReco=true;
				}
				Bot.back()->Connect();
			}
		}
		Heart->Start(200);
		return 0;
	}
	else if((!flag) && (AwInit))
	{
		Heart->Stop();
		for (wxVector<CBot*>::iterator i = Bot.begin() ; i < Bot.end(); i++)
		{
#ifndef VP_BUILD
			if ( (*i)->SetInstance())
			{
				(*i)->Connection(false);
			}
#else
            (*i)->Connection(false);
#endif // VP_BUILD
			(*i)->Sauve();
			delete (*i);
		}
		Bot.clear();
		AwInit=false;
#ifndef VP_BUILD
		aw_term();
#endif
		wxLogMessage(_("SDK Stopped."));
		return 0;
	}
	return 1000;
}

#ifndef VP_BUILD
//------------------------------------------------------------------------------
// Cell Begin to be downloaded

void CCtrlAw::On_Cell_Begin(void)
{
	CBot* Robot=PtCCtrlAw->GetBotInst(aw_instance());
	PtCCtrlAw->EventDispatch (AW_EVENT_CELL_BEGIN, Robot);
}
#endif // VP_BUILD

//------------------------------------------------------------------------------
#ifdef VP_BUILD
void CCtrlAw::On_Cell_End(VPInstance Instance)
{
	CBot* Robot=PtCCtrlAw->GetBotInst(Instance);
	PtCCtrlAw->EventDispatch (VP_EVENT_CELL_END, Robot);
}
#endif // VP_BUILD

//------------------------------------------------------------------------------
#ifndef VP_BUILD
void CCtrlAw::On_Cell_Object(void)
{
	CBot* Robot=PtCCtrlAw->GetBotInst(aw_instance());
	PtCCtrlAw->EventDispatch (AW_EVENT_CELL_OBJECT, Robot);
}
#endif // VP_BUILD

//------------------------------------------------------------------------------
#ifndef VP_BUILD
void CCtrlAw::On_Object_Add(void)
{
	CBot* Robot=PtCCtrlAw->GetBotInst(aw_instance());
	PtCCtrlAw->EventDispatch (AW_EVENT_OBJECT_ADD, Robot);
}
#endif // VP_BUILD

//------------------------------------------------------------------------------
#ifdef VP_BUILD
void CCtrlAw::On_Object(VPInstance Instance)
{
	CBot* Robot=PtCCtrlAw->GetBotInst(Instance);
	PtCCtrlAw->EventDispatch (VP_EVENT_OBJECT, Robot);
}
#endif // VP_BUILD


//------------------------------------------------------------------------------
#ifdef VP_BUILD
void CCtrlAw::On_Object_Change(VPInstance Instance)
{
	CBot* Robot=PtCCtrlAw->GetBotInst(Instance);
	PtCCtrlAw->EventDispatch (VP_EVENT_OBJECT_CHANGE, Robot);
}
#endif // VP_BUILD

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
#ifndef VP_BUILD
void CCtrlAw::On_Object_Delete(void)
{
	CBot* Robot=PtCCtrlAw->GetBotInst(aw_instance());
	PtCCtrlAw->EventDispatch (AW_EVENT_OBJECT_DELETE, Robot);
}
#else
void CCtrlAw::On_Object_Delete(VPInstance Instance)
{
	CBot* Robot=PtCCtrlAw->GetBotInst(Instance);
	PtCCtrlAw->EventDispatch (VP_EVENT_OBJECT_DELETE, Robot);
}
#endif // VP_BUILD

//------------------------------------------------------------------------------
#ifndef VP_BUILD
void CCtrlAw::On_World_Disconnect(void)
{
	CBot* Robot=PtCCtrlAw->GetBotInst(aw_instance());
	Robot->PerteMonde=true;
	PtCCtrlAw->EventDispatch (AW_EVENT_WORLD_DISCONNECT, Robot);
}
#else
void CCtrlAw::On_World_Disconnect(VPInstance Instance)
{
	CBot* Robot=PtCCtrlAw->GetBotInst(Instance);
	Robot->PerteMonde=true;
	PtCCtrlAw->EventDispatch (VP_EVENT_WORLD_DISCONNECT, Robot);
}
#endif // VP_BUILD

//------------------------------------------------------------------------------
#ifndef VP_BUILD
void CCtrlAw::On_Universe_Disconnect(void)
{
	CBot* Robot=PtCCtrlAw->GetBotInst(aw_instance());
	Robot->PerteUniv=true;
	PtCCtrlAw->EventDispatch (AW_EVENT_UNIVERSE_DISCONNECT, Robot);
}
#else

void CCtrlAw::On_Universe_Disconnect(VPInstance Instance)
{
	CBot* Robot=PtCCtrlAw->GetBotInst(Instance);
	Robot->PerteUniv=true;
	PtCCtrlAw->EventDispatch (VP_EVENT_UNIVERSE_DISCONNECT, Robot);
}
#endif // VP_BUILD
//------------------------------------------------------------------------------
// Callbacks Events
#ifndef VP_BUILD
void CCtrlAw::On_Login (int rc)
{
	CBot* Robot=PtCCtrlAw->GetBotInst(aw_instance());
	Robot->Login_CB(rc);
	PtCCtrlAw->CallBackDispatch (AW_CALLBACK_LOGIN,rc,Robot);
}

//------------------------------------------------------------------------------

void CCtrlAw::On_Enter (int rc)
{
	CBot* Robot=PtCCtrlAw->GetBotInst(aw_instance());
	Robot->Enter_CB(rc);
	PtCCtrlAw->CallBackDispatch (AW_CALLBACK_ENTER,rc,Robot);
}

//------------------------------------------------------------------------------

void CCtrlAw::On_Query (int rc)
{
	PtCCtrlAw->CallBackDispatch (AW_CALLBACK_QUERY,rc,PtCCtrlAw->GetBotInst(aw_instance()));
}

//------------------------------------------------------------------------------

void CCtrlAw::On_Object (int rc)
{
	PtCCtrlAw->CallBackDispatch (AW_CALLBACK_OBJECT_RESULT, rc, PtCCtrlAw->GetBotInst(aw_instance()));
}
#else

//------------------------------------------------------------------------------

void CCtrlAw::On_Object_Add_CB (VPInstance Instance,int rc , int Handle)
{
    CBot* Robot=PtCCtrlAw->GetBotInst(Instance);
    PtCCtrlAw->CallBackDispatch (VP_CALLBACK_OBJECT_ADD,rc,Handle,Robot);
}

//------------------------------------------------------------------------------

void CCtrlAw::On_Object_Load_CB (VPInstance Instance,int rc , int Handle)
{
    CBot* Robot=PtCCtrlAw->GetBotInst(Instance);
    PtCCtrlAw->CallBackDispatch (VP_CALLBACK_OBJECT_LOAD,rc,Handle,Robot);
}

//------------------------------------------------------------------------------

void CCtrlAw::On_Object_Delete_CB (VPInstance Instance,int rc , int Handle)
{
    CBot* Robot=PtCCtrlAw->GetBotInst(Instance);
    PtCCtrlAw->CallBackDispatch (VP_CALLBACK_OBJECT_DELETE,rc,Handle,Robot);
}

//------------------------------------------------------------------------------

void CCtrlAw::On_Login_CB (VPInstance Instance,int rc , int Handle)
{
    CBot* Robot=PtCCtrlAw->GetBotInst(Instance);
	Robot->Login_CB(rc);
    PtCCtrlAw->CallBackDispatch (VP_CALLBACK_LOGIN,rc,Handle,Robot);
}

//------------------------------------------------------------------------------

void CCtrlAw::On_Enter_CB (VPInstance Instance,int rc , int Handle)
{
    CBot* Robot=PtCCtrlAw->GetBotInst(Instance);
	Robot->Enter_CB(rc);
    PtCCtrlAw->CallBackDispatch (VP_CALLBACK_LOGIN,rc,Handle,Robot);
}

#endif



//------------------------------------------------------------------------------

CBot* CCtrlAw::GetBot (unsigned int num)
{
	if ( (num >= Bot.size()) || (!AwInit) ) return 0;
	return Bot[num];
}

//------------------------------------------------------------------------------
#ifndef VP_BUILD
CBot* CCtrlAw::GetBotInst(void* Instance)
#else
CBot* CCtrlAw::GetBotInst(VPInstance Instance)
#endif
{
	for (wxVector<CBot*>::iterator i = Bot.begin(); i< Bot.end(); i++)
	{
		if ((*i)->GetInstance()==Instance)
		{
			return (*i);
		}
	}
	return 0;
}

//------------------------------------------------------------------------------
// Controller HeartBeat for SDK update

void CCtrlAw::On_HeartBeat (wxTimerEvent& WXUNUSED(event))
{
#ifndef VP_BUILD
	aw_wait(0);
#endif
	for (wxVector<CBot*>::iterator i = Bot.begin(); i< Bot.end(); i++)
	{
#ifndef VP_BUILD
		(*i)->SetInstance();
#else
        VPInstance Instance = (*i)->GetInstance();
        if ((*i)->GetInstance()) vp_wait((*i)->GetInstance(),0);
#endif // VP_BUILD
		(*i)->Update();
	}
}

//------------------------------------------------------------------------------
// Add a listenner to list

void CCtrlAw::AddListenner (CAwListenner* pListenner)
{
	if (pListenner)
	{
		Listenners.push_back(pListenner);
	}
}

//------------------------------------------------------------------------------
// Del a listenner from list

void CCtrlAw::DelListenner (CAwListenner* pListenner)
{
	if (pListenner)
	{
		for (wxVector<CAwListenner*>::iterator i = Listenners.begin(); i != Listenners.end();)
		{
			if ( *i == pListenner)
			{
				i = Listenners.erase(i);
				break;
			}
			else ++i;
		}
	}
}

//------------------------------------------------------------------------------
// Dispatch Event to suscribers
#ifndef VP_BUILD
void CCtrlAw::EventDispatch (AW_EVENT_ATTRIBUTE id, CBot* Bot)
#else
void CCtrlAw::EventDispatch (vp_event_t id, CBot* Bot)
#endif // VP_BUILD
{
	for (wxVector<CAwListenner*>::iterator i = Listenners.begin(); i != Listenners.end();i++)
	{
		(*i)->Event (id, Bot);
	}
}

//------------------------------------------------------------------------------
// Dispatch CallBacks to suscribers
#ifndef VP_BUILD
void CCtrlAw::CallBackDispatch (AW_CALLBACK id, int rc, CBot* Bot)
#else
void CCtrlAw::CallBackDispatch (vp_callback_t id, int rc, int Handle, CBot* Bot)
#endif
{
	for (wxVector<CAwListenner*>::iterator i = Listenners.begin(); i != Listenners.end();i++)
	{
#ifndef VP_BUILD
		(*i)->CallBack (id,rc,Bot);
#else
		(*i)->CallBack (id,rc,Handle,Bot);
#endif // VP_BUILD
	}
}
