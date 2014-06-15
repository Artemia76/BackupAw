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
// *   Last Modification : 20/04/2014                                          *
// *   Revision          : C                                                   *
// *                                                                           *
// *****************************************************************************

#include "MainFrame.h"
#include "Global.h"
#include "AboutBox.h"
#include "wx/numdlg.h"

// Chargement des icones
#ifndef VP_BUILD
	#include "backupaw.xpm"
#else
	#include "backupvp.xpm"
#endif
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

wxBEGIN_EVENT_TABLE(CMainFrame, wxFrame)

	EVT_MENU	(MF_MENU_NEW,		CMainFrame::OnNew)
	EVT_MENU	(MF_MENU_OPEN,		CMainFrame::OnLoad)
	EVT_MENU	(MF_MENU_SAVE,		CMainFrame::OnSave)
	EVT_MENU	(MF_MENU_SAVE_AS,	CMainFrame::OnSaveAs)
	EVT_MENU	(MF_MENU_EXIT,		CMainFrame::OnExit)
	EVT_MENU	(MF_MENU_HELP,		CMainFrame::OnHelp)
	EVT_MENU	(MF_MENU_FORUM,		CMainFrame::OnForum)
	EVT_MENU	(MF_MENU_ABOUT,		CMainFrame::OnAbout)
	EVT_MENU	(MF_MENU_AWCON,		CMainFrame::OnUniverseCon)
	EVT_MENU	(MF_MENU_SCAN,		CMainFrame::OnScan)
	EVT_MENU	(MF_MENU_AWSETUP,	CMainFrame::OnUniverseSetup)
	EVT_MENU	(MF_MENU_SETORI,	CMainFrame::OnSetOri)
	EVT_MENU	(MF_MENU_ZOOM_OUT,	CMainFrame::OnZoomOut)
	EVT_MENU	(MF_MENU_ZOOM_IN,	CMainFrame::OnZoomIn)
	EVT_MENU	(MF_MENU_SET_REL,	CMainFrame::OnSetRelative)
	EVT_MENU	(MF_MENU_SET_SCAN_SIZE, CMainFrame::OnSetScanSize)
	EVT_TIMER	(MF_UPDATE,			CMainFrame::OnTUpdate)
	EVT_CLOSE	(					CMainFrame::OnCloseWindow)

wxEND_EVENT_TABLE()

//------------------------------------------------------------------------------
// Constructeur

CMainFrame::CMainFrame
	(
	) : wxFrame
	(
		(wxWindow*)NULL,
		wxID_ANY,

		AppName,
		wxDefaultPosition,
		wxDefaultSize,
		wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxRESIZE_BORDER | wxSYSTEM_MENU |
		wxCAPTION | wxCLOSE_BOX
	)
{
	pConfig = wxConfigBase::Get();

	AConnect=false;

	wxMenu* MenuFile = new wxMenu;
	MenuFile->Append(MF_MENU_NEW, _("&New"),_("New project"));
	MenuFile->Append(MF_MENU_OPEN, _("&Open"),_("Open a project file"));
	MenuFile->Append(MF_MENU_SAVE, _("&Save"),_("Save the project to file"));
	MenuFile->Append(MF_MENU_SAVE_AS, _("&Save As"),_("Save the project to file"));
	MenuFile->AppendSeparator ();
    MenuFile->Append(MF_MENU_EXIT, _("E&xit"),_("Exiting BackupAw"));

	wxMenu* MenuAw = new wxMenu;
    MenuAw->Append(MF_MENU_AWCON, _("Connect"),_("Connecting Universe"));
    MenuAw->Append(MF_MENU_AWSETUP, _("&Setup"),_("Connection Setup"));

    wxMenu* MenuGrid = new wxMenu;
    MenuGrid->Append(MF_MENU_SETORI, _("Set Origin"),_("Set the origin of the grid"));
    MenuGrid->Append(MF_MENU_SET_REL, _("Set Relative"), _("Set the relative origin for project save"));
    MenuGrid->Append(MF_MENU_ZOOM_IN, _("Zoom In"),_("Make the grid cells bigger"));
    MenuGrid->Append(MF_MENU_ZOOM_OUT, _("Zoom Out"),_("Make the grid cells smaller"));
	MenuGrid->Append(MF_MENU_SET_SCAN_SIZE, _("Set Scan Size"),_("Set the size of each scan (square of cells)"));

    wxMenu* MenuTools = new wxMenu;
    MenuTools->Append(MF_MENU_SCAN, _("S&can"),_("Scan World"));

    wxMenu* MenuHelp = new wxMenu;

	MenuHelp->Append(MF_MENU_HELP, _("&?"), _("Help on BackupAw"));

	MenuHelp->Append(MF_MENU_FORUM, _("&Forum"), _("Official forum for BackupAw"));
	MenuHelp->Append(MF_MENU_ABOUT, _("A&bout"), _("About the BackupAw"));

	wxMenuBar* Menu = new wxMenuBar;
	Menu->Append(MenuFile, _("&Project"));
	Menu->Append(MenuAw, _("&Universe"));
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
	ToolBar->AddTool ( MF_MENU_AWSETUP, _("Connection Setup"), wxBitmap(outils_xpm), _("Connection Setup"));
	ToolBar->AddTool ( MF_MENU_SCAN, _("Scan World"), wxBitmap(earth_xpm), _("Scan World"));
	ToolBar->AddTool ( MF_MENU_SETORI, _("Set Origin"),wxBitmap(target_xpm), _("Set Grid Origin"));
	ToolBar->AddTool ( MF_MENU_ZOOM_IN, _("Zoom In"),wxBitmap(loupe_p_xpm), _("Make the grid cells bigger"));
	ToolBar->AddTool ( MF_MENU_ZOOM_OUT, _("Zoom Out"),wxBitmap(loupe_m_xpm), _("Make the grid cells smaller"));
	ToolBar->Realize ();
#ifndef VP_BUILD
    SetIcon (wxIcon(backupaw_xpm));
#else
	SetIcon (wxIcon(backupvp_xpm));
#endif
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
	wxLog::SetActiveTarget(new wxLogTextCtrl(LogZone));
	Cell = CCtrlCell::Create();
	SizerPrin = new wxBoxSizer(wxVERTICAL);
	SizerSec = new wxBoxSizer(wxHORIZONTAL);
	CtrlAw = CCtrlAw::Create ();
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
	BackupCtrl = CBackupCtrl::Create();
	MapCanvas = new CMapCanvas (this);
	Tools = new CToolBook(this);
	MapCanvas->Filter=Tools->Filter;
	Tools->Filter->Map = MapCanvas;
	Tools->Modify->Map = MapCanvas;
	Bot=CtrlAw->GetBot();
	SizerSec->Add(MapCanvas, 1 , wxEXPAND);
	SizerSec->Add(Tools, 1, wxEXPAND);
	SizerPrin->Add(SizerSec, 3, wxEXPAND);
	SizerPrin->Add(LogZone, 1, wxEXPAND);
	SetSizer(SizerPrin);
	wxLogMessage (AppName + _(" Started."));

	int	x = pConfig->Read(_T("/Fenetre/prinx"), 50),
		y = pConfig->Read(_T("/Fenetre/priny"), 50),
		w = pConfig->Read(_T("/Fenetre/prinw"), 665),
		h = pConfig->Read(_T("/Fenetre/prinh"), 660);
    if ((x<1) || (y<1))
    {
        x=50;
        y=50;
    }
    Cell->FileName=pConfig->Read(_T("/Project/LastFileName"), _T("default.bap"));
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
}

//------------------------------------------------------------------------------
// Click sur le menu Exit

void CMainFrame::OnExit(wxCommandEvent& WXUNUSED(event))
{
    Close();
}

//------------------------------------------------------------------------------
// Fermeture de la fenetre

void CMainFrame::OnCloseWindow(wxCloseEvent& WXUNUSED(event))
{
	TUpdate->Stop();
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
	Destroy();
}

//------------------------------------------------------------------------------

void CMainFrame::OnUniverseCon (wxCommandEvent& WXUNUSED(event))
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
			wxLogMessage(_("Abording Attempts of reconnections"));
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
		BackupCtrl->Reset();
	}
}

//------------------------------------------------------------------------------

void CMainFrame::OnUniverseSetup (wxCommandEvent& WXUNUSED(event))
{
	COptDial Option
	(
		this,
		Bot,
		_("Universe Setting"),
		wxPoint(100,100),
		wxSize(200,200),
		wxDEFAULT_DIALOG_STYLE
	);
	Option.ShowModal();
}

//------------------------------------------------------------------------------

void CMainFrame::OnScan (wxCommandEvent& WXUNUSED(event))
{
	BackupCtrl->Scan ();
}

//------------------------------------------------------------------------------

void CMainFrame::OnSetOri (wxCommandEvent& WXUNUSED(event))
{
    wxString s = wxGetTextFromUser (_("Please Enter an AW Coord location :"),_("Set Grid Origin"),_T("0N 0W"));
    AwToCoord (BackupCtrl->OrigX, BackupCtrl->OrigY,s);
    MapCanvas->Refresh();
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
								_("About..."),
								wxPoint(100,100),
								wxSize(400,300),
								wxDEFAULT_DIALOG_STYLE
							);
	aboutDialog.ShowModal();
}

//------------------------------------------------------------------------------
// Mise a jour périodique des éléments dynamiques de la fenêtre principale

void CMainFrame::OnTUpdate (wxTimerEvent& WXUNUSED(event))
{
	wxString s;
	wxMenuBar* Menu = GetMenuBar ();
	wxMenuItem* ItemScan = Menu->FindItem (MF_MENU_SCAN);
	wxMenuItem* ItemAwCon = Menu->FindItem (MF_MENU_AWCON);
	// Mise à jour des icones de connection
	if ((Bot->IsOnWorld())&&(!AConnect))
	{
		ItemAwCon->SetItemLabel (_("Disconnect"));
		ItemAwCon->SetHelp (_("Universe Disconnection"));
		ToolBar->DeleteTool (MF_MENU_AWCON);
		ToolBar->InsertTool ( 3,MF_MENU_AWCON,_("Disconnect"), wxBitmap(connect_xpm), wxNullBitmap, wxITEM_NORMAL,_("Universe Disconnection") );
		AConnect=true;
		ToolBar->Realize();
	}
	else if ((!Bot->IsOnWorld())&&(AConnect))
	{
		ItemAwCon->SetItemLabel (_("Connect"));
		ItemAwCon->SetHelp (_("Universe Connecting"));
        ToolBar->DeleteTool (MF_MENU_AWCON);
		ToolBar->InsertTool ( 3,MF_MENU_AWCON,_("Connect"), wxBitmap(deco_xpm), wxNullBitmap, wxITEM_NORMAL,_("Universe Connecting") );
		AConnect=false;
		ToolBar->Realize();
	}
	// Animation de l'icone Earth pendant un scan
	if (BackupCtrl->IsScanning	())
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
				ToolBar->InsertTool ( 5,MF_MENU_SCAN,_("Scan World"), wxBitmap(earth1_xpm),wxNullBitmap, wxITEM_NORMAL, _("Scan World"));
                break;
			case 1 :
				ToolBar->InsertTool ( 5,MF_MENU_SCAN,_("Scan World"), wxBitmap(earth2_xpm),wxNullBitmap, wxITEM_NORMAL, _("Scan World"));
				break;
			case 2 :
				ToolBar->InsertTool ( 5,MF_MENU_SCAN,_("Scan World"), wxBitmap(earth3_xpm),wxNullBitmap, wxITEM_NORMAL, _("Scan World"));
				break;
			case 3 :
				ToolBar->InsertTool ( 5,MF_MENU_SCAN,_("Scan World"), wxBitmap(earth4_xpm),wxNullBitmap, wxITEM_NORMAL, _("Scan World"));
				break;
			case 4 :
				ToolBar->InsertTool ( 5,MF_MENU_SCAN,_("Scan World"), wxBitmap(earth5_xpm),wxNullBitmap, wxITEM_NORMAL, _("Scan World"));
				break;
			default :
				ToolBar->InsertTool ( 5,MF_MENU_SCAN,_("Scan World"), wxBitmap(earth_xpm),wxNullBitmap, wxITEM_NORMAL, _("Scan World"));
		}
		ACntEarth=CntEarth;
		ToolBar->Realize ();
	}
	if (Bot->IsOnWorld())
	{
		SetTitle ( AppName + _(" : On ")+Bot->Monde);
		if (!ItemScan->IsEnabled ()) ItemScan->Enable(true);
		ToolBar->EnableTool(MF_MENU_SCAN,true);

	}
	else
	{
		SetTitle ( AppName + _(" : Disconnected"));
		if (ItemScan->IsEnabled ()) ItemScan->Enable(false);
		ToolBar->EnableTool(MF_MENU_SCAN,false);
	}
	SetStatusText (wxString::Format(_("Objects in project = %i , Total = %i"), Cell->GetNbSel(), Cell->GetNbObj()),1);
	if (MapCanvas->MapChange && (!BackupCtrl->IsScanning()))
	{
		if (Bot->IsOnWorld() && BackupCtrl->IsSurvey()) BackupCtrl->Scan ();
		MapCanvas->MapChange=false;
	}
}

//------------------------------------------------------------------------------

void CMainFrame::OnNew (wxCommandEvent& WXUNUSED(event))
{
	Cell->DelSel ();
	Cell->FileName=_T("");
	MapCanvas->Refresh ();
}

//------------------------------------------------------------------------------

void CMainFrame::OnLoad (wxCommandEvent& WXUNUSED(event))
{
	wxFileDialog ProjectFile
	(
		this,
		_("Open Project"),
		Cell->FileName.GetPath(),
		_T("*.bap"),
		_("BackupAw Project (*.bap)|*.bap|All Files (*.*)|*.*"),
		wxFD_OPEN | wxFD_CHANGE_DIR,
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

void CMainFrame::OnSave (wxCommandEvent& event)
{
	if (Cell->FileName==_T("")) OnSaveAs (event);
	else
	{
		Cell->SaveSel();
	}
}

//------------------------------------------------------------------------------

void CMainFrame::OnSaveAs (wxCommandEvent& WXUNUSED(event))
{
	wxFileDialog ProjectFile
	(
		this,
		_("Save Project"),
		Cell->FileName.GetPath(),
		_T("*.bap"),
		_("BackupAw Project (*.bap)|*.bap|All Files (*.*)|*.*"),
		wxFD_SAVE | wxFD_OVERWRITE_PROMPT | wxFD_CHANGE_DIR,
		wxDefaultPosition
	);
	if (ProjectFile.ShowModal() == wxID_OK)
	{
		Cell->FileName=ProjectFile.GetPath();
		pConfig->Write(_T("/Project/LastFileName"),Cell->FileName.GetFullPath());
		pConfig->Flush();
		Cell->SaveSel();
	}
}

//------------------------------------------------------------------------------

void CMainFrame::OnZoomIn (wxCommandEvent& WXUNUSED(event))
{
	MapCanvas->ZoomIn();
}

//------------------------------------------------------------------------------

void CMainFrame::OnZoomOut (wxCommandEvent& WXUNUSED(event))
{
	MapCanvas->ZoomOut();
}

//------------------------------------------------------------------------------

void CMainFrame::OnSetRelative(wxCommandEvent& WXUNUSED(event))
{
	wxString Depart = CoordToAwF(Cell->RelX, Cell->RelZ);
    wxString s = wxGetTextFromUser (_("Please Enter an AW Coord Relative :"),_("Set Relative Object Coord"),Depart);
    double x,z,y;
    AwToCoord (x,z,y,s);
    Cell->RelX = (int) floor(x * 1000);
    Cell->RelZ = (int) floor(z * 1000);
    wxString LogMess;
    LogMess << _("Set Relative Coord to ") << Cell->RelX << _T(" / ") << Cell->RelZ;
    wxLogMessage(LogMess);
}

//------------------------------------------------------------------------------

void CMainFrame::OnSetScanSize(wxCommandEvent& WXUNUSED(event))
{
	long i = wxGetNumberFromUser(_("Please Enter a value between 5 and 200"),_("Scan size:"), _("Set scan size"), BackupCtrl->GetScanSize(), 5,200);
	BackupCtrl->SetScanSize((int)i);
	wxString LogMess;
	LogMess << _("Set ScanSize to ") << BackupCtrl->GetScanSize();
    wxLogMessage(LogMess);
}
