// *****************************************************************************
// *                                                                           *
// *                           BACKUPAW : CBot.cpp                             *
// *                       Represent An ActiveWorld Bot                        *
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
// *   CopyRight 2005-2007 Neophile                                            *
// *   Creation          : 15/05/2005                                          *
// *   Last Modification : 07/10/2007                                          *
// *   Revision          : B                                                   *
// *                                                                           *
// *****************************************************************************

#include "CBot.h"

#include <aw.h>

#if AW_BUILD>41
    #define AwDefaultPort 6670
#else
	#define AwDefaultPort 5670
#endif

// Event du Serveur Xelagot

BEGIN_EVENT_TABLE(CBot,wxEvtHandler)
	EVT_TIMER  (CG_RECO,	CBot::OnCGRecoEvent)
	EVT_TIMER  (OBJ_TIME,	CBot::OnObjTimer)
END_EVENT_TABLE()

//------------------------------------------------------------------------------
// Contructeur

CBot::CBot ()
{
// D�claration des instances
	CGRecoTimer = new wxTimer(this, CG_RECO);
	ObjectTimer = new wxTimer(this, OBJ_TIME);
	Logger = CCtrlLog::Create();
	PassPriv = CPassPriv::Create();

// Initialisation des variables internes

	Global=true;
	On_Universe=false;
	On_World=false;
	Visible=false;
	CGRecoCnt=0;
	PerteUniv=false;
	PerteMonde=false;
	Instance=0;
	DemCon=false;
	ConEC=false;
	EntEC=false;
	DemDeco=false;
	ModeReco=false;
	Map=0;
	Scanning=false;
	Survey=false;
	Deleting=false;
	Building=false;
	BuildEC=0;
	DelEC=0;
	CellMax=0;
	CTBuild=false;
	Cell = CCtrlCell::Create();
}

//------------------------------------------------------------------------------
// Destructeur

CBot::~CBot ()
{
	if (On_World || On_Universe) Connection(false);
}

//------------------------------------------------------------------------------
// Methode de connection

void CBot::Connect()
{
	if ((!ConEC) && (!EntEC) && (!DemCon) && (!DemDeco) && (!On_Universe) && (!On_World)) DemCon=true;
}

//------------------------------------------------------------------------------
// Methode de D�connection

void CBot::Deconnect()
{
	if ((!ConEC) && (!EntEC) && (!DemCon) && (!DemDeco) && ((On_Universe) || (On_World))) DemDeco=true;
}

//------------------------------------------------------------------------------
// Methode d'entr�e/sortie d'univers

void CBot::Connection(bool flag)
{
// Variables Internes
	wxString Message, s;
	int rc;
	if (flag)
	{
#if AW_BUILD>77
		if ((rc=aw_create(Univers, Port, &Instance))!=0)
#else
        if ((rc=aw_create(Univers.mb_str(), Port, &Instance))!=0)
#endif
		{
			Logger->Log(_("Unable to create instance, Reason : "), _T("RED"), false, rc);
			DemCon=false;
			if (ModeReco) Tentative();
		}
		else
		{
			Logger->Log(_("Instance Initialized."), _T("BLUE"));
			aw_int_set (AW_LOGIN_OWNER, Citoyen);
#if AW_BUILD>77
            aw_string_set (AW_LOGIN_PRIVILEGE_PASSWORD,PassWord);
            aw_string_set (AW_LOGIN_APPLICATION, _T("BackupAw"));
            aw_string_set (AW_LOGIN_NAME,Nom);
#else
			aw_string_set (AW_LOGIN_PRIVILEGE_PASSWORD,PassWord.To8BitData());
			aw_string_set (AW_LOGIN_APPLICATION, "BackupAw");
			aw_string_set (AW_LOGIN_NAME,Nom.To8BitData());
#endif
			aw_login();
			ConEC=true;
		}
	}
	else
	{
		Scanning=false;
		Cell->DelGrid ();
		Map->BlockScroll=false;
		Map->BlockSelect=false;
		Survey=false;
		Building=false;
		Deleting =false;
		Map->Refresh ();
		CellMax=0;
		aw_destroy();
		Instance=0;
		Logger->Log(_("Disconnected from Universe "),_T("BLUE"));
		On_Universe=false;
		On_World=false;
		BuildEC=0;
		DelEC=0;
		DemDeco=false;
	}
}

//------------------------------------------------------------------------------
// Retour Callback d'une demande de connection

void CBot::Login_CB(int rc)
{
	ConEC=false;
	if (rc)
	{
		DemCon=false;
		Logger->Log(_("Unable to join the universe, Reason :"), _T("RED"), false, rc);
		aw_destroy();
		if (ModeReco) Tentative();
	}
	else
	{
		Logger->Log(_("Connected on Universe"), _T("BLUE"));
		On_Universe=true;
	}
}

//------------------------------------------------------------------------------
// Retour Callback d'une demande d'entr�e sur un monde

void CBot::Enter_CB(int rc)
{
	wxString Message;
	EntEC=false;
	DemCon=false;
	if (rc)
	{
		DemCon=false;
		Message.Append (_("Unable to connect on world "));
		Message.Append (Monde);
		Message.Append (_(",Reason: "));
		Logger->Log(Message, _T("RED"), false, rc);
		On_World=false;
		On_Universe=false;
		aw_destroy();
		if (ModeReco) Tentative();
	}
	else
	{
		Message.Append (_("Connected on world "));
		Message.Append (Monde);
		Logger->Log(Message, _T("BLUE"));
		On_World=true;
		ModeReco=false;
		if (Visible)
		{
			aw_state_change();
		}
	}
}

//------------------------------------------------------------------------------
// Retour Callback d'un query

void CBot::Query_CB(int rc)
{
	if (rc)
	{
		Logger->Log(_("Unable to query properties. Reason :"), _T("RED"), false, rc);
		Scanning=false;
		Map->BlockScroll=false;
	}
	else
	{
		if (aw_bool(AW_QUERY_COMPLETE))
		{
			Scanning=false;
			Map->BlockScroll=false;
			Survey=true;
		}
		else aw_query_5x5 (aw_sector_from_cell (Map->OrigX), aw_sector_from_cell (Map->OrigY), sequence);
	}
}

//------------------------------------------------------------------------------
// Methode d'entr�e ou de sortie d'un monde

void CBot::Enter()
{
	aw_bool_set (AW_ENTER_GLOBAL, Global);
	#if AW_BUILD>77
        aw_enter(Monde);
	#else
        aw_enter(Monde.mb_str());
    #endif
	EntEC=true;
}

//------------------------------------------------------------------------------
// Charge les Param�tres du bot

void CBot::Charge ()
{
	wxString ParcPath = ::wxGetCwd();
	wxString s;
	wxConfigBase::Set(pConfig);
	Univers=pConfig->Read(_T("Bot/Univers") , _T("auth.activeworlds.com"));
	Monde=pConfig->Read(_T("Bot/Monde") , _T(""));
	Citoyen=pConfig->Read(_T("Bot/Citoyen") , 0l);
	s=pConfig->Read(_T("Bot/PassPriv") , _T(""));
	PassWord=PassPriv->Decode(s);
	Nom=pConfig->Read(_T("Bot/Nom") , _T("Bot"));
	Port=pConfig->Read(_T("Bot/Port") , AwDefaultPort);
	CGConAuto=pConfig->Read(_T("Bot/AutoConnect") , 0l);
	CGRecoDelay=pConfig->Read(_T("Bot/Delai") , 15l);
	CGRecoRetry=pConfig->Read(_T("Bot/Essais") , 3l);
	if (CGRecoRetry != 0) CGRecoEna=true;
	else CGRecoEna=false;
	CTBuild=pConfig->Read(_T("Bot/BuildMode"), 1l);
}

//------------------------------------------------------------------------------
// Sauvegarde les param�tres du bot

void CBot::Sauve ()
{
	wxConfigBase::Set(pConfig);
	pConfig->Write(_T("Bot/Univers") ,Univers);
	pConfig->Write(_T("Bot/Monde") ,Monde);
	pConfig->Write(_T("Bot/Citoyen") ,Citoyen);
	pConfig->Write(_T("Bot/PassPriv") ,PassPriv->Code(PassWord));
	pConfig->Write(_T("Bot/Nom") ,Nom);
	pConfig->Write(_T("Bot/Port") ,Port);
	pConfig->Write(_T("Bot/AutoConnect") , CGConAuto);
	pConfig->Write(_T("Bot/Delai")  , CGRecoDelay);
	pConfig->Write(_T("Bot/Essais") , CGRecoRetry);
	pConfig->Write(_T("Bot/BuildMode"), CTBuild);
	pConfig->Flush(true);
}

//------------------------------------------------------------------------------
// M�thode de reconnection automatique du chat global

void CBot::OnCGRecoEvent (wxTimerEvent& WXUNUSED(event))
{
	Connect();
}

//------------------------------------------------------------------------------
// Tentatives de nouvelle connection

void CBot::Tentative ()
{
	wxString Tampon;
	if ((CGRecoCnt<CGRecoRetry) || (CGRecoRetry < 0))
	{
		Tampon.Printf(_("A reconnection will be tryed in %d sec."),CGRetente);
		Logger->Log(Tampon,_T("RED"));
		CGRecoTimer->Start(CGRetente * 1000,wxTIMER_ONE_SHOT);
		if (CGRecoRetry > (-1)) CGRecoCnt++;
		if (CGRetente < 900) CGRetente = CGRetente * 2;
	}
	else
	{
		Logger->Log(_("End of attempts"),_T("RED"));
		ModeReco=false;
	}
}

//------------------------------------------------------------------------------
// Retourne l'�tat connection sur un monde

bool CBot::IsOnWorld()
{
	return On_World;
}

//------------------------------------------------------------------------------
// Retourne l'�tat connect� sur l'univers

bool CBot::IsOnUniverse()
{
	return On_Universe;
}

//------------------------------------------------------------------------------
// Mises � jours p�riodiques

void CBot::Update ()
{
	wxString Message;
	if (PerteUniv || PerteMonde)
	{
		if (PerteUniv) Message=_("Connection lost with universe ") + Univers + _T(".");
		else Message=_("Connection lost with the world ") + Monde + _T(".");
		Logger->Log(Message, _T("RED") );
		PerteUniv=false;
		PerteMonde=false;
		On_Universe=false;
		On_World=false;
		Scanning=false;
		Map->BlockScroll=false;
		Map->BlockSelect=false;
		Survey=false;
		Building=false;
		Deleting =false;
		BuildEC=0;
		DelEC=0;
		Cell->DelGrid ();
		CellMax=0;
		Map->Refresh ();
		aw_destroy();
		Instance=0;
		if (CGRecoEna)
		{
			CGRecoCnt=0;
			CGRetente=CGRecoDelay;
			Tentative();
			ModeReco=true;
		}
	}
	if (Map->MapChange && (!Scanning))
	{
		if (On_World && Survey) Scan ();
		Map->MapChange=false;
	}
	if (DemCon && (!On_Universe) && (!ConEC)) Connection(true);
	if (DemCon && On_Universe && (!On_World) && (!EntEC)) Enter();
	if (DemDeco) Connection(false);
	if (CGRecoTimer->IsRunning() && (!ModeReco)) CGRecoTimer->Stop();
}

//------------------------------------------------------------------------------

void CBot::Scan ()
{
	if ((!Scanning)&&On_World)
	{
		memset (sequence, 0, sizeof (sequence));
		aw_query_5x5 (aw_sector_from_cell (Map->OrigX), aw_sector_from_cell (Map->OrigY), sequence);
		Scanning=true;
		Map->BlockScroll=true;
	}
}

//------------------------------------------------------------------------------

void CBot::Cell_Begin()
{
	int sector_x;
	int sector_z;
	int sectorxmax = 2 - aw_sector_from_cell (Map->OrigX);
	int sectorzmax = 2 - aw_sector_from_cell (Map->OrigY);
	CellX = aw_int (AW_CELL_X);
	CellZ = aw_int (AW_CELL_Z);
	sector_x = aw_sector_from_cell (CellX);
	sector_z = aw_sector_from_cell (CellZ);
	sequence[sectorzmax+sector_z][sectorxmax+sector_x] = aw_int (AW_CELL_SEQUENCE);
}

//------------------------------------------------------------------------------

void CBot::Cell_Object ()
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
	NObj.Obj_Type = aw_int (AW_OBJECT_TYPE);
	if (NObj.Obj_Type>1)
	{
		DatPtr = (unsigned char*) aw_data (AW_OBJECT_DATA, &DatLen);
		NObj.DataV4 = BinToHex (DatPtr,DatLen);
	}
	#endif
	Cell->AddObj (NObj);
	Map->Refresh ();
}

//------------------------------------------------------------------------------

bool CBot::IsScanning	()
{
	return Scanning;
}

//------------------------------------------------------------------------------

void CBot::Object_Add()
{
	Cell_Object ();
}

//------------------------------------------------------------------------------

void CBot::Object_Delete()
{
	if (Survey)
	{
		size_t Index;
		if (Cell->FindObjNum (Index, aw_int (AW_OBJECT_NUMBER))==CELL_OK)
		{
			Cell->DelObj(Index);
			Map->Refresh ();
		}
	}
}

//------------------------------------------------------------------------------

void CBot::World_Attribute()
{
	CellMax=aw_int (AW_WORLD_CELL_LIMIT);
}

//------------------------------------------------------------------------------

void CBot::Object_CB (int rc)
{
	if (BuildEC)
	{
		if (rc) Logger->Log (_("Unable to Build object. Reason : "),_T("RED"),false,rc);
		BuildEC--;
	}
	else if (DelEC)
	{
		if (rc) Logger->Log (_("Unable to Delete object. Reason : "),_T("RED"),false,rc);
		DelEC--;
	}
}

//------------------------------------------------------------------------------

void CBot::OnObjTimer (wxTimerEvent& WXUNUSED(event))
{
	size_t NbObj=10;
	#if AW_BUILD>41
    size_t LenDat=0;
	unsigned char* DataV4=0;
	#endif
	CObject Obj;
	if (!On_World) return;
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
			Map->BlockSelect=false;
			Logger->Log (_("End of deleting project.."), _T("BLUE"));
		}
		Map->Refresh ();
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
			aw_int_set (AW_OBJECT_TYPE, Obj.Obj_Type);
			if (Obj.Obj_Type>1)
			{
				LenDat = Obj.DataV4.Len()/2;
				DataV4= new unsigned char[LenDat];
				HexToBin(Obj.DataV4,DataV4);
				aw_data_set (AW_OBJECT_DATA, (char*)DataV4,LenDat);
				delete DataV4;
			}
			#endif
			if (CTBuild)	aw_object_load ();
			else if (Obj.Owner==Citoyen) aw_object_add ();
			Cell->DelObjSel(0);
			BuildEC++;
		}
		if (Cell->GetNbSel() >0) ObjectTimer->Start (1000,true);
		else
		{
			Building=false;
			Map->BlockSelect=false;
			Logger->Log (_("End of building project.."), _T("BLUE"));
		}
		Map->Refresh ();
		return;
	}
}

//------------------------------------------------------------------------------

void CBot::StartDelete ()
{
	if (Scanning || (!On_World) || Building) return;
	Logger->Log (_("Start to deleting project.."), _T("BLUE"));
	ObjectTimer->Start (1000,true);
	Deleting=true;
	Map->BlockSelect=true;
}

//------------------------------------------------------------------------------

void CBot::StartBuild ()
{
	if (Scanning || (!On_World) || Deleting) return;
	Logger->Log (_("Start to building project.."), _T("BLUE"));
	ObjectTimer->Start (1000,true);
	Building=true;
	Map->BlockSelect=true;
}

//------------------------------------------------------------------------------

bool CBot::IsSurvey()
{
	return Survey;
}
