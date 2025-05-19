// *****************************************************************************
// *                                                                           *
// *                           BACKUPAW : CBot.cpp                             *
// *                       Represent An ActiveWorld Bot                        *
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
// *   CopyRight 2005-2007 Neophile                                            *
// *   Creation          : 15/05/2005                                          *
// *   Last Modification : 20/04/2014                                          *
// *   Revision          : B                                                   *
// *                                                                           *
// *****************************************************************************

#include "CBot.h"
#include "Ctrlaw.h"

#ifdef VP_BUILD
	#include "VPSDK/rc.h"
	#define DefaultPort 57000
#else
	#if AW_BUILD>41
		#define DefaultPort 6670
	#else
		#define DefaultPort 5670
	#endif
#endif // VP_BUILD

// Events

wxBEGIN_EVENT_TABLE(CBot,wxEvtHandler)
	EVT_TIMER  (CG_RECO,	CBot::OnCGRecoEvent)
wxEND_EVENT_TABLE()

//------------------------------------------------------------------------------
// Contructeur

CBot::CBot ()
{
	m_Config = wxConfigBase::Get();
// Déclaration des instances
	m_CGRecoTimer = new wxTimer(this, CG_RECO);
	m_PassPriv = CPassPriv::Create();

// Initialisation des variables internes

	Global=true;
	m_On_Universe=false;
	m_On_World=false;
	m_Visible=false;
	CGRecoCnt=0;
	m_PerteUniv=false;
	m_PerteMonde=false;
	m_Instance=0;
	m_DemCon=false;
	m_ConEC=false;
	m_EntEC=false;
	m_DemDeco=false;
	ModeReco=false;
	m_Visible=false;
	m_Instance=0;
}

//------------------------------------------------------------------------------
// Destructeur

CBot::~CBot ()
{
	if (m_On_World || m_On_Universe) Connection(false);
}

//------------------------------------------------------------------------------
// Methode de connection

void CBot::Connect()
{
	if ((!m_ConEC) && (!m_EntEC) && (!m_DemCon) && (!m_DemDeco) && (!m_On_Universe) && (!m_On_World)) m_DemCon=true;
}

//------------------------------------------------------------------------------
// Methode de Déconnection

void CBot::Deconnect()
{
	if ((!m_ConEC) && (!m_EntEC) && (!m_DemCon) && (!m_DemDeco) && ((m_On_Universe) || (m_On_World))) m_DemDeco=true;
}

//------------------------------------------------------------------------------
// Methode d'entrée/sortie d'univers

void CBot::Connection(bool pFlag)
{
// Variables Internes
	wxString Message, s;
	int rc;
	if (pFlag && (!m_On_Universe))
	{
#ifdef VP_BUILD
        if (!m_Instance) m_Instance=vp_create(NULL);
		if ((rc=vp_connect_universe(m_Instance,Univers.utf8_str(),Port ))!=0)
#else
	#if AW_BUILD>77
		if ((rc=aw_create(Univers, Port, &m_Instance))!=0)
	#else
        if ((rc=aw_create(Univers.mb_str(), Port, &m_Instance))!=0)
	#endif
#endif // VP_BUILD
		{
			wxLogMessage (_("Unable to create instance, Reason : ") + GetRCString(rc));
			m_DemCon=false;
			if (ModeReco) Tentative();
#ifdef VP_BUILD
            vp_destroy(m_Instance);
			m_Instance=0;
#endif
		}
		else
		{

			wxLogMessage (_("Instance Initialized."));
			m_ConEC=true;
#ifndef VP_BUILD
			aw_int_set (AW_LOGIN_OWNER, Citoyen);
#if AW_BUILD>77
            aw_string_set (AW_LOGIN_PRIVILEGE_PASSWORD,PassWord);
            aw_string_set (AW_LOGIN_APPLICATION, _T("BackupAw"));
            aw_string_set (AW_LOGIN_NAME,Nom);
#else
			aw_string_set (AW_LOGIN_PRIVILEGE_PASSWORD,PassWord.mb_str());
			aw_string_set (AW_LOGIN_APPLICATION, "BackupAw");
			aw_string_set (AW_LOGIN_NAME,Nom.mb_str());
#endif
			if (rc=aw_login())
#else
			vp_callback_set(m_Instance, VP_CALLBACK_LOGIN, CCtrlAw::On_Login_CB);
			if ((rc=vp_login (m_Instance, UserName.utf8_str(), PassWord.utf8_str(),Nom.utf8_str())))
#endif
			{
				wxLogMessage (_("Unable to join the universe, Reason :") + GetRCString(rc));
				m_DemCon = false;
				if (ModeReco) Tentative();
			}
		}
	}
	else if ((!pFlag) && m_On_Universe)
	{
#ifndef VP_BUILD
		aw_destroy();
#else
        if (IsOnWorld()) vp_leave(m_Instance);
		vp_destroy(m_Instance);
#endif
		m_Instance=0;
		wxLogMessage (_("Disconnected from Universe "));
		m_On_Universe=false;
		m_On_World=false;
		m_DemDeco=false;
	}
}

//------------------------------------------------------------------------------
// Retour Callback d'une demande de connection

void CBot::Login_CB(int pRC)
{
	m_ConEC=false;
	if (m_CGRecoTimer->IsRunning()) m_CGRecoTimer->Stop();
	if (pRC)
	{
		m_DemCon=false;
		wxLogMessage (_("Unable to join the universe, Reason :") + GetRCString(pRC));
#ifdef VP_BUILD
		vp_destroy(m_Instance);
		m_Instance=0;
#else
		aw_destroy();
#endif
		if (ModeReco) Tentative();
	}
	else
	{
		wxLogMessage (_("Connected on Universe"));
		m_On_Universe=true;
#ifdef VP_BUILD
		vp_event_set(m_Instance, VP_EVENT_WORLD_DISCONNECT, CCtrlAw::On_World_Disconnect);
		vp_event_set(m_Instance, VP_EVENT_UNIVERSE_DISCONNECT, CCtrlAw::On_Universe_Disconnect);
		vp_event_set(m_Instance, VP_EVENT_CELL_END, CCtrlAw::On_Cell_End);
		vp_event_set(m_Instance, VP_EVENT_OBJECT, CCtrlAw::On_Object);
		vp_event_set(m_Instance, VP_EVENT_OBJECT_CHANGE, CCtrlAw::On_Object_Change);
		vp_event_set(m_Instance, VP_EVENT_OBJECT_DELETE, CCtrlAw::On_Object_Delete);

		vp_callback_set(m_Instance, VP_CALLBACK_OBJECT_ADD, CCtrlAw::On_Object_Add_CB);
		vp_callback_set(m_Instance, VP_CALLBACK_OBJECT_LOAD, CCtrlAw::On_Object_Load_CB);
		vp_callback_set(m_Instance, VP_CALLBACK_OBJECT_DELETE, CCtrlAw::On_Object_Delete_CB);
#endif
	}
}

//------------------------------------------------------------------------------
// Retour Callback d'une demande d'entrée sur un monde

void CBot::Enter_CB(int pRC)
{
	wxString Message;
	m_EntEC=false;
	m_DemCon=false;
	if (pRC)
	{
		m_DemCon=false;
		wxLogMessage (_("Unable to connect on world ") + Monde + _(",Reason: ") + GetRCString (pRC));
#ifndef VP_BUILD
		aw_destroy();
#else
        vp_destroy(m_Instance);
#endif // VP_BUILD
		m_On_World=false;
		m_On_Universe=false;
		if (ModeReco) Tentative();
	}
	else
	{
		wxLogMessage (_("Connected on world ")+Monde);
		m_On_World=true;
		ModeReco=false;
#ifndef VP_BUILD
		if (m_Visible)
		{
			aw_state_change();
		}
#endif
	}
}

//------------------------------------------------------------------------------
// Methode d'entrée ou de sortie d'un monde

void CBot::Enter()
{
	m_EntEC=true;
	#ifndef VP_BUILD
	aw_bool_set (AW_ENTER_GLOBAL, Global);
		#if AW_BUILD>77
	aw_enter(Monde);
		#else
    aw_enter(Monde.mb_str());
		#endif
	#else
	vp_callback_set (m_Instance, VP_CALLBACK_ENTER,CCtrlAw::On_Enter_CB);
	vp_enter(m_Instance, Monde.utf8_str());
	#endif // VP_BUILD
}

//------------------------------------------------------------------------------
// Charge les Paramètres du bot

void CBot::Charge ()
{
	#ifndef VP_BUILD
	wxString BAPVersion = wxString::Format(_T("AW%i"),AW_BUILD);
	Univers= m_Config->Read(BAPVersion + _T("/Univers") , _T("auth.activeworlds.com"));
	Citoyen= m_Config->Read(BAPVersion + _T("/Citoyen") , 0l);
	#else
	wxString BAPVersion = _T("VP");
	Univers=m_Config->Read(BAPVersion + _T("/Univers") , _T("universe.virtualparadise.org"));
	UserName=m_Config->Read(BAPVersion + _T("/UserName") , _T(""));
	#endif // VP_BUILD
	Monde= m_Config->Read(BAPVersion + _T("/Monde") , _T(""));
	Port=static_cast<int>(m_Config->Read(BAPVersion + _T("/Port") , DefaultPort));
	PassWord= m_PassPriv->Decode(m_Config->Read(BAPVersion + _T("/PassPriv"), _T("")));
	Nom= m_Config->Read(BAPVersion + _T("/Nom") , _T("BackupAw"));
	m_Config->Read(BAPVersion + _T("/AutoConnect"), &CGConAuto, false);
	CGRecoDelay= static_cast<int>(m_Config->Read(BAPVersion + _T("/Delai") , 15l));
	CGRecoRetry= static_cast<int>(m_Config->Read(BAPVersion + _T("/Essais") , 3l));
	if (CGRecoRetry != 0) CGRecoEna=true;
	else CGRecoEna=false;
}

//------------------------------------------------------------------------------
// Sauvegarde les paramètres du bot

void CBot::Sauve ()
{
	#ifndef VP_BUILD
	wxString BAPVersion = wxString::Format(_T("AW%i"),AW_BUILD);
	m_Config->Write(BAPVersion + _T("/Univers") ,Univers);
	m_Config->Write(BAPVersion + _T("/Citoyen") ,Citoyen);
	#else
	wxString BAPVersion = _T("vp");
	m_Config->Write(BAPVersion + _T("/Univers") ,Univers);
	m_Config->Write(BAPVersion + _T("/UserName") ,UserName);
	#endif // VP_BUILD
	m_Config->Write(BAPVersion + _T("/Monde") ,Monde);
	m_Config->Write(BAPVersion + _T("/PassPriv") ,m_PassPriv->Code(PassWord));
	m_Config->Write(BAPVersion + _T("/Nom") ,Nom);
	m_Config->Write(BAPVersion + _T("/Port") ,Port);
	m_Config->Write(BAPVersion + _T("/AutoConnect") , CGConAuto);
	m_Config->Write(BAPVersion + _T("/Delai")  , CGRecoDelay);
	m_Config->Write(BAPVersion + _T("/Essais") , CGRecoRetry);
	m_Config->Flush(true);
}

//------------------------------------------------------------------------------
// Méthode de reconnection automatique du chat global

void CBot::OnCGRecoEvent (wxTimerEvent& WXUNUSED(event))
{
	if (m_ConEC)
	{
		Login_CB(1000);
	}
	else
	{
		Connect();
	}
}

//------------------------------------------------------------------------------
// Tentatives de nouvelle connection

void CBot::Tentative ()
{
	wxString Tampon;
	if ((CGRecoCnt<CGRecoRetry) || (CGRecoRetry < 0))
	{
		wxLogMessage(wxString::Format(_("A reconnection will be tryed in %i sec."),CGRetente));
		m_CGRecoTimer->Start(CGRetente * 1000,wxTIMER_ONE_SHOT);
		if (CGRecoRetry > (-1)) CGRecoCnt++;
		if (CGRetente < 900) CGRetente = CGRetente * 2;
	}
	else
	{
		wxLogMessage("End of attempts");
		ModeReco=false;
	}
}

//------------------------------------------------------------------------------
// Retourne l'état connection sur un monde

bool CBot::IsOnWorld()
{
	return m_On_World;
}

//------------------------------------------------------------------------------
// Retourne l'état connecté sur l'univers

bool CBot::IsOnUniverse()
{
	return m_On_Universe;
}

//------------------------------------------------------------------------------
// On Règle l'instance sur notre bot actuel

#ifndef VP_BUILD
bool CBot::SetInstance ()
{
	if (!m_Instance) return false;
	aw_instance_set(m_Instance);
	return true;
}
#endif // VP_BUILD

//------------------------------------------------------------------------------
// On retourne l'instance du bot
#ifndef VP_BUILD
void* CBot::GetInstance ()
#else
VPInstance CBot::GetInstance ()
#endif
{
	return m_Instance;
}

//------------------------------------------------------------------------------
// Mises à jours périodiques

void CBot::Update ()
{
	wxString Message;
	if (m_PerteUniv || m_PerteMonde)
	{
		if (m_PerteUniv) wxLogMessage(_("Connection lost with universe ") + Univers + _T("."));
		else wxLogMessage(_("Connection lost with the world ") + Monde + _T("."));
		m_PerteUniv=false;
		m_PerteMonde=false;
		m_On_Universe=false;
		m_On_World=false;
#ifndef VP_BUILD
		aw_destroy();
#else
        vp_destroy(m_Instance);
#endif // VP_BUILD
		m_Instance=0;
		if (CGRecoEna)
		{
			CGRecoCnt=0;
			CGRetente=CGRecoDelay;
			Tentative();
			ModeReco=true;
		}
	}
	if (m_DemCon && (!m_On_Universe) && (!m_ConEC)) Connection(true);
	if (m_DemCon && m_On_Universe && (!m_On_World) && (!m_EntEC)) Enter();
	if (m_DemDeco) Connection(false);
	if (m_CGRecoTimer->IsRunning() && (!m_ConEC) && (!ModeReco)) m_CGRecoTimer->Stop();
}


//------------------------------------------------------------------------------
// Methode de Traduction du codes d'erreurs

wxString CBot::GetRCString (int pRC)
{
	wxString rcs;
	switch (pRC)
	{
#ifndef VP_BUILD
		case 0 :
			rcs=_T("");
			break;
		case 1 :
			rcs=_("Citizen Ship Expired");
			break;
		case 2 :
			rcs=_("Land Limit Exceeded");
			break;
		case 3 :
			rcs=_("No Such Citizen");
			break;
		case 4 :
			rcs=_("Message Length Bad");
			break;
		case 5 :
			rcs=_("License Password Contains Space");
			break;
		case 6 :
			rcs=_("License Password Too Long");
			break;
		case 7 :
    	    rcs=_("License Password Too Short");
    	    break;
		case 8 :
			rcs=_("License Range Too Large");
			break;
		case 9 :
			rcs=_("License Range Too Small");
			break;
		case 10 :
			rcs=_("License Users Too Large");
			break;
		case 11 :
			rcs=_("License Users Too Small");
			break;
		case 12 :
			rcs=_("License Contains Invalid Char");
			break;
		case 13 :
			rcs=_("Invalid Password");
			break;
		case 14 :
			rcs=_("Unable To Mail Back Number");
			break;
		case 15 :
			rcs=_("License World Too Short");
			break;
		case 16 :
			rcs=_("License World Too Long");
			break;
		case 17 :
			rcs=_("Server Out Of Memory");
			break;
		case 20 :
			rcs=_("Invalid World");
			break;
		case 21 :
			rcs=_("Server Outdated");
			break;
		case 22 :
			rcs=_("World Already Started");
			break;
		case 27 :
			rcs=_("No Such World");
			break;
		case 31 :
			rcs=_("Not Logged In");
			break;
		case 32 :
			rcs=_("Unauthorized");
			break;
		case 33 :
			rcs=_("World Already Exists");
			break;
		case 34 :
			rcs=_("No Such License");
			break;
		case 39 :
			rcs=_("Identity Already In Use");
			break;
		case 40 :
			rcs=_("Unable To Report Location");
			break;
		case 41 :
			rcs=_("Invalid Email");
			break;
		case 42 :
			rcs=_("No Such Acting Citizen");
			break;
		case 43 :
			rcs=_("Acting Password Invalid");
			break;
		case 45 :
			rcs=_("Universe Full");
			break;
		case 46 :
			rcs=_("Billing Timeout");
			break;
		case 47 :
			rcs=_("Billing Recv Failed");
			break;
		case 48 :
			rcs=_("Billing Response Invalid");
			break;
		case 55 :
			rcs=_("Billing Rejected");
			break;
		case 56 :
			rcs=_("Billing_Blocked");
			break;
		case 57 :
			rcs=_("Too Many Worlds");
			break;
		case 58 :
			rcs=_("Must Upgrade");
			break;
		case 59 :
			rcs=_("Bot Limit Exceeded");
			break;
		case 61 :
			rcs=_("World_Expired");
			break;
		case 62 :
			rcs=_("Citizen Does Not Expire");
			break;
		case 64 :
			rcs=_("License Sarts With Number");
			break;
		case 66 :
			rcs=_("No Such Ejection");
			break;
		case 67 :
			rcs=_("No Such Session");
			break;
		case 69 :
			rcs=_("Ejection Expired");
			break;
		case 70 :
			rcs=_("Acting Citizen Expired");
			break;
		case 71 :
			rcs=_("Already_Started");
			break;
		case 72 :
			rcs=_("World Running");
			break;
		case 73 :
			rcs=_("World Not Set");
			break;
		case 74 :
			rcs=_("No Such Cell");
			break;
		case 75 :
			rcs=_("No Registry");
			break;
		case 76 :
			rcs=_("Can't Open Registry");
			break;
		case 77 :
			rcs=_("Citizen_Disabled");
			break;
		case 78 :
			rcs=_("World Disabled");
			break;
		case 79 :
			rcs=_("Beta Required");
			break;
		case 80 :
			rcs=_("Acting Citizen Disabled");
			break;
		case 81 :
			rcs=_("Invalid User Count");
			break;
		case 91 :
			rcs=_("Private World");
			break;
		case 92 :
			rcs=_("No Tourists");
			break;
		case 100 :
			rcs=_("EMail Contains Invalid Char");
			break;
		case 101 :
			rcs=_("EMail Ends With Blank");
			break;
		case 102 :
			rcs=_("EMail Missing Dot");
			break;
		case 103 :
			rcs=_("EMail Missing At");
			break;
		case 104 :
			rcs=_("EMail Starts With Blank");
			break;
		case 105 :
			rcs=_("EMail Too Long");
			break;
		case 106 :
			rcs=_("EMail Too Short");
			break;
		case 107 :
			rcs=_("Name Already Used");
			break;
		case 108 :
			rcs=_("Name Contains Nonalphanumeric Char");
			break;
		case 109 :
			rcs=_("Name Contains Invalid Blank");
			break;
		case 110 :
			rcs=_("Name Doesn't Exist");
			break;
		case 111 :
			rcs=_("Name Ends With Blank");
			break;
		case 112 :
			rcs=_("Name Too Long");
			break;
      	case 113 :
			rcs=_("Name Too Short");
			break;
		case 114 :
			rcs=_("Name Unused");
			break;
		case 115 :
			rcs=_("Password Too Long");
			break;
		case 116 :
			rcs=_("Password Too Short");
			break;
		case 117 :
			rcs=_("Password Wrong");
			break;
		case 119 :
			rcs=_("Unable To Delete Name");
			break;
		case 120 :
			rcs=_("Unable To Get Citizen");
			break;
		case 121 :
			rcs=_("Unable To Insert Citizen");
			break;
		case 122 :
			rcs=_("Unable To Insert Name");
			break;
		case 123 :
			rcs=_("Unable To Put Citizen Count");
			break;
		case 124 :
			rcs=_("Unable To Delete Citizen");
			break;
		case 126 :
			rcs=_("Number Already Used");
			break;
		case 127 :
			rcs=_("Number Out Of Range");
			break;
		case 128 :
			rcs=_("Privilege Password Is Too Short");
			break;
		case 129 :
			rcs=_("Privilege Password Is Too Long");
			break;
		case 203 :
			rcs=_("Not Change Owner");
			break;
		case 204 :
			rcs=_("Can't Find Old Element");
			break;
		case 210 :
			rcs=_("Unable To Change Attribute");
			break;
		case 211 :
			rcs=_("Can't Change Owner");
			break;
		case 212 :
			rcs=_("Imposter");
			break;
		case 213 :
			rcs=_("Invalid Request");
			break;
		case 216 :
			rcs=_("Can't Build Here");
			break;
		case 300 :
			rcs=_("Encroaches");
			break;
		case 301 :
			rcs=_("No Such Object");
			break;
		case 302 :
			rcs=_("Not Delete Owner");
			break;
		case 303 :
			rcs=_("Too Many Bytes");
			break;
		case 305 :
			rcs=_("Unable To Store");
			break;
		case 306 :
			rcs=_("Unregistered Object");
			break;
		case 308 :
			rcs=_("Element Already Exists");
			break;
		case 309 :
			rcs=_("Restricted Command");
			break;
		case 310 :
			rcs=_("No Build Rights");
			break;
		case 311 :
			rcs=_("Out Of Bounds");
			break;
		case 313 :
			rcs=_("Restricted Object");
			break;
		case 314 :
			rcs=_("Restricted Area");
			break;
		case 400 :
			rcs=_("Out Of Memory");
			break;
		case 401 :
			rcs=_("Not Yet");
			break;
		case 402 :
			rcs=_("Timeout");
			break;
		case 403 :
			rcs=_("Null Pointer");
			break;
		case 404 :
			rcs=_("Unable To Contact Universe");
			break;
		case 405 :
			rcs=_("Unable To Contact World");
			break;
		case 406 :
			rcs=_("Invalid World Name");
			break;
		case 415 :
			rcs=_("Send Failed");
			break;
		case 416 :
			rcs=_("Receive Failed");
			break;
		case 421 :
			rcs=_("Stream Empty");
			break;
		case 422 :
			rcs=_("Stream Message Too Long");
			break;
		case 423 :
			rcs=_("World Name Too Long");
			break;
		case 426 :
			rcs=_("Message Too Long");
			break;
		case 427 :
			rcs=_("Too Many Resets");
			break;
		case 428 :
			rcs=_("Unable To Create Socket");
			break;
		case 429 :
			rcs=_("Unable To Connect");
			break;
		case 430 :
			rcs=_("Unable To Set NonBlocking");
			break;
		case 434 :
			rcs=_("Can't Open Stream");
			break;
		case 435 :
			rcs=_("Can't Write Stream");
			break;
		case 436 :
			rcs=_("Can't Close Stream");
			break;
		case 439 :
			rcs=_("No Connection");
			break;
		case 442 :
			rcs=_("Unable To Initialize Network");
			break;
		case 443 :
			rcs=_("Incorrect Message Length");
			break;
		case 444 :
			rcs=_("Not Initialized");
			break;
		case 445 :
			rcs=_("No Instance");
			break;
		case 446 :
			rcs=_("Out Buffer Full");
			break;
		case 447 :
			rcs=_("Invalid Callback");
			break;
		case 448 :
			rcs=_("Invalid Attribute");
			break;
		case 449 :
			rcs=_("Type Mismatch");
			break;
		case 450 :
			rcs=_("String Too Long");
			break;
		case 451 :
			rcs=_("Read Only");
			break;
		case 452 :
			rcs=_("Unable To Register Resolve");
			break;
		case 453 :
			rcs=_("Invalid Instance");
			break;
		case 454 :
			rcs=_("Version Mismatch");
			break;
		case 461 :
			rcs=_("In Buffer Full");
			break;
		case 463 :
			rcs=_("Protocol Error");
			break;
		case 464 :
			rcs=_("Query In Progress");
			break;
		case 465 :
			rcs=_("World Full");
			break;
		case 466 :
			rcs=_("Ejected");
			break;
		case 467 :
			rcs=_("Not Welcome");
			break;
		case 468 :
			rcs=_("Unable To Bind");
			break;
		case 469 :
			rcs=_("Unable To Listen");
			break;
		case 470 :
			rcs=_("Unable To Accept");
			break;
		case 471 :
			rcs=_("Connection Lost");
			break;
		case 473 :
			rcs=_("No Stream");
			break;
		case 474 :
			rcs=_("Not Available");
			break;
		case 487 :
			rcs=_("Old Universe");
			break;
		case 488 :
			rcs=_("Old World");
			break;
		case 489 :
			rcs=_("World Not Running");
			break;
		case 505 :
			rcs=_("Invalid Argument");
			break;
#else
		case VP_RC_SUCCESS :
			rcs=_T("");
			break;
		case VP_RC_VERSION_MISMATCH :
			rcs=_("Version Mismatch");
			break;
		case VP_RC_NOT_INITIALIZED :
			rcs=_("Not Initialized");
			break;
		case VP_RC_ALREADY_INITIALIZED :
			rcs=_("Already Initialized");
			break;
		case VP_RC_STRING_TOO_LONG :
			rcs=_("String Too Long");
			break;
		case VP_RC_INVALID_LOGIN :
			rcs=_("Invalid User");
			break;
		case VP_RC_WORLD_NOT_FOUND :
			rcs=_("No Such World");
			break;
		case VP_RC_WORLD_LOGIN_ERROR :
			rcs=_("World login error");
			break;
		case VP_RC_NOT_IN_WORLD :
			rcs=_("Not in world");
			break;
		case VP_RC_CONNECTION_ERROR :
			rcs=_("Connection Error");
			break;
		case VP_RC_NO_INSTANCE :
			rcs=_("No Instance");
			break;
		case VP_RC_NOT_IMPLEMENTED :
			rcs=_("Not implemented");
			break;
		case VP_RC_NO_SUCH_ATTRIBUTE :
			rcs=_("No such attribute");
			break;
		case VP_RC_NOT_ALLOWED :
			rcs=_("Not Allowed");
			break;
		case VP_RC_DATABASE_ERROR :
			rcs=_("Database Error");
			break;
		case VP_RC_NO_SUCH_USER :
			rcs=_("No such user");
			break;
		case VP_RC_TIMEOUT :
			rcs=_("Timeout");
			break;
		case VP_RC_NOT_IN_UNIVERSE :
			rcs=_("Not in universe");
			break;
		case VP_RC_INVALID_ARGUMENTS :
			rcs=_("Invalid arguments");
			break;
		case VP_RC_OBJECT_NOT_FOUND :
			rcs=_("Object not found");
			break;
		case VP_RC_UNKNOWN_ERROR :
#endif // VP_BUILD
		default:
			rcs=_("Unknow Raison Code");
			break;
   }
   return rcs;
}
