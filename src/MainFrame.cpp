// *****************************************************************************
// *                                                                           *
// *                       BACKUPAW : MainFrame.cpp                            *
// *                           Main Frame class                                *
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
// *   Last Modification : 07/10/2007                                          *
// *   Revision          : B                                                   *
// *                                                                           *
// *****************************************************************************

#include "MainFrame.h"
#include "Global.h"
#include "AboutBox.h"

// Chargement des icones
#include "backupaw.xpm"
#include "deco.xpm"
#include "connect.xpm"
#include "outils.xpm"
#include "earth.xpm"
#include "earth1.xpm"
#include "earth2.xpm"
#include "earth3.xpm"
#include "earth4.xpm"
#include "earth5.xpm"
#include "fileopen.xpm"
#include "filesave.xpm"
#include "filesaveas.xpm"
#include "target.xpm"
#include "loupe_m.xpm"
#include "loupe_p.xpm"

BEGIN_EVENT_TABLE(CMainFrame, wxFrame)

	EVT_MENU(MF_MENU_NEW,CMainFrame::OnNew)
	EVT_MENU(MF_MENU_OPEN,CMainFrame::OnLoad)
	EVT_MENU(MF_MENU_SAVE,CMainFrame::OnSave)
	EVT_MENU(MF_MENU_SAVE_AS,CMainFrame::OnSaveAs)
	EVT_MENU(MF_MENU_EXIT,CMainFrame::OnExit)
	EVT_MENU(MF_MENU_HELP,CMainFrame::OnHelp)
	EVT_MENU(MF_MENU_FORUM,CMainFrame::OnForum)
	EVT_MENU(MF_MENU_ABOUT,CMainFrame::OnAbout)
	EVT_MENU(MF_MENU_AWCON,CMainFrame::OnAwCon)
	EVT_MENU(MF_MENU_SCAN,CMainFrame::OnScan)
	EVT_MENU(MF_MENU_AWSETUP,CMainFrame::OnAwSetup)
	EVT_MENU(MF_MENU_SETORI,CMainFrame::OnSetOri)
	EVT_MENU(MF_MENU_ZOOM_OUT,CMainFrame::OnZoomOut)
	EVT_MENU(MF_MENU_ZOOM_IN,CMainFrame::OnZoomIn)
	EVT_MENU(MF_MENU_SET_REL,CMainFrame::OnSetRelative)
	EVT_TIMER(MF_UPDATE,CMainFrame::OnTUpdate)

END_EVENT_TABLE()

//------------------------------------------------------------------------------
// Constructeur

CMainFrame::CMainFrame
	(
		wxLocale& locale,
		wxFileConfig* fConfig
	) : wxFrame
	(
		(wxWindow*)NULL,
		wxID_ANY,
		_T("BackupAw"),
		wxDefaultPosition,
		wxDefaultSize,
		wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxRESIZE_BORDER | wxSYSTEM_MENU |
		wxCAPTION | wxCLOSE_BOX
	),
	m_locale (locale)
{
	pConfig = fConfig;
	wxConfigBase::Set(pConfig);

	AConnect=false;

	wxMenu* MenuFile = new wxMenu;
	MenuFile->Append(MF_MENU_NEW, _("&New"),_("New project"));
	MenuFile->Append(MF_MENU_OPEN, _("&Open"),_("Open a project file"));
	MenuFile->Append(MF_MENU_SAVE, _("&Save"),_("Save the project to file"));
	MenuFile->Append(MF_MENU_SAVE_AS, _("&Save As"),_("Save the project to file"));
	MenuFile->AppendSeparator ();
    MenuFile->Append(MF_MENU_EXIT, _("E&xit"),_("Exiting BackupAw"));

	wxMenu* MenuAw = new wxMenu;
    MenuAw->Append(MF_MENU_AWCON, _("Connect"),_("Connecting AW"));
    MenuAw->Append(MF_MENU_AWSETUP, _("&Setup"),_("AW Setup"));

    wxMenu* MenuGrid = new wxMenu;
    MenuGrid->Append(MF_MENU_SETORI, _("Set Origin"),_("Set the origin of the grid"));
    MenuGrid->Append(MF_MENU_SET_REL, _("Set Relative"), _("Set the relative origin for project save"));
    MenuGrid->Append(MF_MENU_ZOOM_IN, _("Zoom In"),_("Make the grid cells bigger"));
    MenuGrid->Append(MF_MENU_ZOOM_OUT, _("Zoom Out"),_("Make the grid cells smaller"));

    wxMenu* MenuTools = new wxMenu;
    MenuTools->Append(MF_MENU_SCAN, _("S&can"),_("Scan World"));

    wxMenu* MenuHelp = new wxMenu;

	MenuHelp->Append(MF_MENU_HELP, _("&?"), _("Help on BackupAw"));

	MenuHelp->Append(MF_MENU_FORUM, _("&Forum"), _("Official forum for BackupAw"));
	MenuHelp->Append(MF_MENU_ABOUT, _("A&bout"), _("About the BackupAw"));

	wxMenuBar* Menu = new wxMenuBar;
	Menu->Append(MenuFile, _("&Project"));
	Menu->Append(MenuAw, _("&Aw"));
    Menu->Append(MenuGrid, _("&Grid"));
	Menu->Append(MenuTools, _("&World"));
	Menu->Append(MenuHelp, _("&Help"));

    SetMenuBar(Menu);

	ToolBar = CreateToolBar(wxTB_HORIZONTAL/*|wxTB_HORZ_LAYOUT*/);
	ToolBar->SetToolBitmapSize (wxSize (24,24));
	ToolBar->AddTool ( MF_MENU_OPEN, _("Open"), wxBitmap(fileopen_xpm), _("Open Project"));
	ToolBar->AddTool ( MF_MENU_SAVE, _("Save"), wxBitmap(filesave_xpm), _("Save Project"));
	ToolBar->AddTool ( MF_MENU_SAVE_AS, _("Save As"), wxBitmap(filesaveas_xpm), _("Save Project"));
	ToolBar->AddTool ( MF_MENU_AWCON, _("deco"), wxBitmap(deco_xpm), _("Connect"));
	ToolBar->AddTool ( MF_MENU_AWSETUP, _("Aw Setup"), wxBitmap(outils_xpm), _("Aw Setup"));
	ToolBar->AddTool ( MF_MENU_SCAN, _("Scan World"), wxBitmap(earth_xpm), _("Scan World"));
	ToolBar->AddTool ( MF_MENU_SETORI, _("Set Origin"),wxBitmap(target_xpm), _("Set Grid Origin"));
	ToolBar->AddTool ( MF_MENU_ZOOM_IN, _("Zoom In"),wxBitmap(loupe_p_xpm), _("Make the grid cells bigger"));
	ToolBar->AddTool ( MF_MENU_ZOOM_OUT, _("Zoom Out"),wxBitmap(loupe_m_xpm), _("Make the grid cells smaller"));
	ToolBar->Realize ();

    SetIcon (wxIcon(backupaw_xpm));
    CreateStatusBar(3);
	LogZone = new wxTextCtrl
		(
			this,
			wxID_ANY,
			wxEmptyString,
			wxDefaultPosition,
			wxDefaultSize,
			wxTE_MULTILINE |
			wxTE_READONLY |
			wxTE_RICH
		);
	Logger = CCtrlLog::Create ();
	Logger->SetLogZone(LogZone);
	Cell = CCtrlCell::Create();
	SizerPrin = new wxBoxSizer(wxVERTICAL);
	SizerSec = new wxBoxSizer(wxHORIZONTAL);
	MapCanvas = new CMapCanvas (this);
	CtrlAw = CCtrlAw::Create (pConfig,MapCanvas);
	int rc=CtrlAw->Init(true);
	if (rc)
	{
		wxMessageDialog ErrorBox
		(
			this,
			_("The Program Can't continue : Please check the log"),
			_("Error"),
			wxOK|wxICON_ERROR
		);
		ErrorBox.ShowModal ();
		Close();
	}
	Tools = new CToolBook(this);
	Tools->Filter->Map=MapCanvas;
	MapCanvas->Filter=Tools->Filter;
	Tools->Delete->Map=MapCanvas;
	Tools->Modify->Map=MapCanvas;
	Bot=CtrlAw->GetBot();
	Tools->Delete->Bot=Bot;
	SizerSec->Add(MapCanvas, 1 , wxEXPAND);
	SizerSec->Add(Tools, 1, wxEXPAND);
	SizerPrin->Add(SizerSec, 3, wxEXPAND);
	SizerPrin->Add(LogZone, 1, wxEXPAND);
	SetSizer(SizerPrin);
	Logger->Log(_("BackupAw Started."),_T("BLUE"));

	int	x = pConfig->Read(_T("/Fenetre/prinx"), 50),
		y = pConfig->Read(_T("/Fenetre/priny"), 50),
		w = pConfig->Read(_T("/Fenetre/prinw"), 665),
		h = pConfig->Read(_T("/Fenetre/prinh"), 660);
    if ((x<1) || (x<1))
    {
        x=50;
        y=50;
    }
	SetSize(wxSize(w,h));
	SetPosition (wxPoint(x,y));
	SetSizeHints (665,660);
	CntEarth=0;
	CntSens=false;
	Cnt =0;
	TUpdate=new wxTimer (this, MF_UPDATE);
	TUpdate->Start (100, false);
}


//------------------------------------------------------------------------------
// Destructeur

CMainFrame::~CMainFrame()
{
	wxConfigBase::Set(pConfig);
	int x, y, w, h;
	if (IsMaximized())
	{
		Maximize(false);
	}
	if (IsIconized())
	{
	    Iconize (false);
	}
	GetSize(&w, &h);
	GetPosition(&x, &y);
	pConfig->Write(_T("/Fenetre/prinx"), x);
	pConfig->Write(_T("/Fenetre/priny"), y);
	pConfig->Write(_T("/Fenetre/prinw"), w);
	pConfig->Write(_T("/Fenetre/prinh"), h);
	pConfig->Flush();
	CtrlAw->Init(false);
	CCtrlAw::Kill ();
	Logger->Log(CGVersion + _(" Stopped."), _T("VIOLET RED"), true);
	CCtrlLog::Kill ();
}

//------------------------------------------------------------------------------

void CMainFrame::OnAwCon (wxCommandEvent& WXUNUSED(event))
{
	if (Bot->ModeReco)
	{
		wxMessageDialog BoiteOuiNon
		(
			this,
			_("Are you sure want abording attempts of reconnection?"),
			_("Warning"),
			wxYES_NO|wxICON_EXCLAMATION
		);
		if (BoiteOuiNon.ShowModal()==wxID_YES)
		{
			Bot->ModeReco=false;
			Logger->Log(_("Abording Attempts of reconnections"),_T("RED"));
		}
	}
	else if (!Bot->IsOnWorld())
	{
		Bot->Global=true;
		Bot->Connect();
	}
	else
	{
		Bot->Deconnect();
	}
}

//------------------------------------------------------------------------------

void CMainFrame::OnAwSetup (wxCommandEvent& WXUNUSED(event))
{
	COptDial Option
	(
		this,
		Bot,
		pConfig,
		_("Active Worlds Setting"),
		wxPoint(100,100),
		wxSize(200,200),
		wxDEFAULT_DIALOG_STYLE
	);
	Option.ShowModal();
}

//------------------------------------------------------------------------------

void CMainFrame::OnScan (wxCommandEvent& WXUNUSED(event))
{
	Bot->Scan ();
}

//------------------------------------------------------------------------------

void CMainFrame::OnSetOri (wxCommandEvent& WXUNUSED(event))
{
    wxString s = wxGetTextFromUser (_("Please Enter an AW Coord location :"),_("Set Grid Origin"),_T("0N 0W"));
    AwToCoord (MapCanvas->OrigX, MapCanvas->OrigY,s);
    MapCanvas->Refresh();
}

//------------------------------------------------------------------------------
// Click sur le menu Exit

void CMainFrame::OnExit(wxCommandEvent& WXUNUSED(event))
{
    Close();
}

//------------------------------------------------------------------------------

void CMainFrame::OnHelp(wxCommandEvent& WXUNUSED(event))
{
	::wxLaunchDefaultBrowser (BackupAW_Help);
}

//------------------------------------------------------------------------------

void CMainFrame::OnForum(wxCommandEvent& WXUNUSED(event))
{
	::wxLaunchDefaultBrowser (BackupAW_Forum);
}


//------------------------------------------------------------------------------
// Click sur About

void CMainFrame::OnAbout (wxCommandEvent& WXUNUSED(event))
{
    AboutBox aboutDialog	(	this,
								pConfig,
								_("About..."),
								wxPoint(100,100),
								wxSize(300,300),
								wxDEFAULT_DIALOG_STYLE
							);
	aboutDialog.ShowModal();
}

//------------------------------------------------------------------------------
// Mise a jour périodique des éléments dynamiques de la fenêtre principale

void CMainFrame::OnTUpdate (wxTimerEvent& WXUNUSED(event))
{
	wxString s,t;
	wxMenuBar* Menu = GetMenuBar ();
	wxMenuItem* ItemScan = Menu->FindItem (MF_MENU_SCAN);
	wxMenuItem* ItemAwCon = Menu->FindItem (MF_MENU_AWCON);
	// Mise à jour des icones de connection
	if ((Bot->IsOnWorld())&&(!AConnect))
	{
		ItemAwCon->SetText (_("Disconnect"));
		ItemAwCon->SetHelp (_("AW Disconnection"));
		ToolBar->DeleteTool (MF_MENU_AWCON);
		ToolBar->InsertTool ( 3, MF_MENU_AWCON, wxBitmap(connect_xpm));
		AConnect=true;
		ToolBar->Realize();
	}
	else if ((!Bot->IsOnWorld())&&(AConnect))
	{
		ItemAwCon->SetText (_("Connect"));
		ItemAwCon->SetHelp (_("Connecting AW"));
		ToolBar->DeleteTool (MF_MENU_AWCON);
		ToolBar->InsertTool ( 3, MF_MENU_AWCON, wxBitmap(deco_xpm));
		AConnect=false;
		ToolBar->Realize();
	}
	// Animation de l'icone Earth pendant un scan
	if (Bot->IsScanning	())
	{
		Cnt++;
		if (Cnt>5)
		{
			if (CntSens) CntEarth++;
			else CntEarth--;
			Cnt=0;
		}
		if (CntEarth > 4)
		{
			CntSens=false;
			CntEarth=4;
		}
		if (CntEarth < 0)
		{
			CntSens=true;
			CntEarth=0;
		}
	}
	else
	{
		CntEarth=5;
		CntSens=false;
	}
	if (ACntEarth!=CntEarth)
	{
		ToolBar->DeleteTool (MF_MENU_SCAN);
		switch (CntEarth)
		{
			case 0 :
				ToolBar->InsertTool ( 5, MF_MENU_SCAN, wxBitmap(earth1_xpm));
				break;
			case 1 :
				ToolBar->InsertTool ( 5, MF_MENU_SCAN, wxBitmap(earth2_xpm));
				break;
			case 2 :
				ToolBar->InsertTool ( 5, MF_MENU_SCAN, wxBitmap(earth3_xpm));
				break;
			case 3 :
				ToolBar->InsertTool ( 5, MF_MENU_SCAN, wxBitmap(earth4_xpm));
				break;
			case 4 :
				ToolBar->InsertTool ( 5, MF_MENU_SCAN, wxBitmap(earth5_xpm));
				break;
			default :
				ToolBar->InsertTool ( 5, MF_MENU_SCAN, wxBitmap(earth_xpm));
		}
		ACntEarth=CntEarth;
		ToolBar->SetToolShortHelp(MF_MENU_SCAN,_("Scan World"));
		ToolBar->Realize ();
	}
	if (Bot->IsOnWorld())
	{
		SetTitle (_("BackupAw : On ")+Bot->Monde);
		if (!ItemScan->IsEnabled ()) ItemScan->Enable(true);
		ToolBar->EnableTool(MF_MENU_SCAN,true);

	}
	else
	{
		SetTitle (_("BackupAw : Disconnected"));
		if (ItemScan->IsEnabled ()) ItemScan->Enable(false);
		ToolBar->EnableTool(MF_MENU_SCAN,false);
	}
	t.Printf (_("Total Objects : %d"),Cell->GetNbObj());
	SetStatusText (t,1);
}

//------------------------------------------------------------------------------

void	CMainFrame::OnNew (wxCommandEvent& WXUNUSED(event))
{
	Cell->DelSel ();
	Cell->FileName=_T("");
	MapCanvas->Refresh ();
}

//------------------------------------------------------------------------------

void	CMainFrame::OnLoad (wxCommandEvent& WXUNUSED(event))
{
	wxFileDialog ProjectFile
	(
		this,
		_("Open Project"),
		_T(""),
		Cell->FileName,
		_("BackupAw Project (*.bap)|*.bap|All Files (*.*)|*.*"),
		wxFD_OPEN,
		wxDefaultPosition
	);
	if (ProjectFile.ShowModal() == wxID_OK)
	{
		Cell->FileName=ProjectFile.GetPath();
		Cell->LoadSel();
	}
	MapCanvas->Refresh ();
}

//------------------------------------------------------------------------------

void	CMainFrame::OnSave (wxCommandEvent& event)
{
	if (Cell->FileName==_T("")) OnSaveAs (event);
	else
	{
		Cell->SaveSel();
	}
}

//------------------------------------------------------------------------------

void	CMainFrame::OnSaveAs (wxCommandEvent& WXUNUSED(event))
{
	wxFileDialog ProjectFile
	(
		this,
		_("Save Project"),
		_T(""),
		Cell->FileName,
		_("BackupAw Project (*.bap)|*.bap|All Files (*.*)|*.*"),
		wxFD_SAVE|wxFD_OVERWRITE_PROMPT,
		wxDefaultPosition
	);
	if (ProjectFile.ShowModal() == wxID_OK)
	{
		Cell->FileName=ProjectFile.GetPath();
		Cell->SaveSel();
	}
}

//------------------------------------------------------------------------------

void	CMainFrame::OnZoomIn (wxCommandEvent& WXUNUSED(event))
{
	MapCanvas->ZoomIn();
}

//------------------------------------------------------------------------------

void	CMainFrame::OnZoomOut (wxCommandEvent& WXUNUSED(event))
{
	MapCanvas->ZoomOut();
}

//------------------------------------------------------------------------------

void	CMainFrame::OnSetRelative(wxCommandEvent& WXUNUSED(event))
{
	wxString Depart = CoordToAwF(Cell->RelX, Cell->RelZ);
    wxString s = wxGetTextFromUser (_("Please Enter an AW Coord Relative :"),_("Set Relative Object Coord"),Depart);
    double x,z,y;
    AwToCoord (x,z,y,s);
    Cell->RelX = (int) floor(x * 1000);
    Cell->RelZ = (int) floor(z * 1000);
    wxString LogMess;
    LogMess << _("Set Relative Coord to ") << Cell->RelX << _T(" / ") << Cell->RelZ;
    Logger->Log (LogMess);
}