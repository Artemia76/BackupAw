// *****************************************************************************
// *                                                                           *
// *                       BACKUPAW : MainFrame.cpp                            *
// *                           Main Frame class                                *
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
		nullptr,
		wxID_ANY,

		AppName,
		wxDefaultPosition,
		wxDefaultSize,
		wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxRESIZE_BORDER | wxSYSTEM_MENU |
		wxCAPTION | wxCLOSE_BOX
	)
{
	m_Config = wxConfigBase::Get();

	m_AConnect=false;

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

	m_ToolBar = CreateToolBar(wxTB_HORIZONTAL/*|wxTB_HORZ_LAYOUT*/);
	m_ToolBar->SetToolBitmapSize (wxSize (24,24));
	m_ToolBar->AddTool ( MF_MENU_OPEN, _("Open"), wxBitmap(fileopen_xpm), _("Open Project"));
	m_ToolBar->AddTool ( MF_MENU_SAVE, _("Save"), wxBitmap(filesave_xpm), _("Save Project"));
	m_ToolBar->AddTool ( MF_MENU_SAVE_AS, _("Save As"), wxBitmap(filesaveas_xpm), _("Save Project"));
	m_ToolBar->AddTool ( MF_MENU_AWCON, _("deco"), wxBitmap(deco_xpm), _("Connect"));
	m_ToolBar->AddTool ( MF_MENU_AWSETUP, _("Connection Setup"), wxBitmap(outils_xpm), _("Connection Setup"));
	m_ToolBar->AddTool ( MF_MENU_SCAN, _("Scan World"), wxBitmap(earth_xpm), _("Scan World"));
	m_ToolBar->AddTool ( MF_MENU_SETORI, _("Set Origin"),wxBitmap(target_xpm), _("Set Grid Origin"));
	m_ToolBar->AddTool ( MF_MENU_ZOOM_IN, _("Zoom In"),wxBitmap(loupe_p_xpm), _("Make the grid cells bigger"));
	m_ToolBar->AddTool ( MF_MENU_ZOOM_OUT, _("Zoom Out"),wxBitmap(loupe_m_xpm), _("Make the grid cells smaller"));
	m_ToolBar->Realize ();
#ifndef VP_BUILD
    SetIcon (wxIcon(backupaw_xpm));
#else
	SetIcon (wxIcon(backupvp_xpm));
#endif
    CreateStatusBar(3);
	m_LogZone = new wxTextCtrl
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
	wxLog::SetActiveTarget(new wxLogTextCtrl(m_LogZone));
	m_Cell = CCtrlCell::Create();
	m_SizerPrin = new wxBoxSizer(wxVERTICAL);
	m_SizerSec = new wxBoxSizer(wxHORIZONTAL);
	m_CtrlAw = CCtrlAw::Create ();
	int rc= m_CtrlAw->Init(true);
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
	m_BackupCtrl = CBackupCtrl::Create();
	m_MapCanvas = new CMapCanvas (this);
	m_Tools = new CToolBook(this);
	m_MapCanvas->Filter= m_Tools->Filter;
	m_Tools->Filter->Map = m_MapCanvas;
	m_Tools->Modify->Map = m_MapCanvas;
	m_Bot= m_CtrlAw->GetBot();
	m_SizerSec->Add(m_MapCanvas, 1 , wxEXPAND);
	m_SizerSec->Add(m_Tools, 1, wxEXPAND);
	m_SizerPrin->Add(m_SizerSec, 3, wxEXPAND);
	m_SizerPrin->Add(m_LogZone, 1, wxEXPAND);
	SetSizer(m_SizerPrin);
	wxLogMessage (AppName + _(" Started."));

	int	x = m_Config->Read(_T("/Fenetre/prinx"), 50),
		y = m_Config->Read(_T("/Fenetre/priny"), 50),
		w = m_Config->Read(_T("/Fenetre/prinw"), 665),
		h = m_Config->Read(_T("/Fenetre/prinh"), 660);
    if ((x<1) || (y<1))
    {
        x=50;
        y=50;
    }
	m_Cell->FileName= m_Config->Read(_T("/Project/LastFileName"), _T("default.bap"));
	SetSize(wxSize(w,h));
	SetPosition (wxPoint(x,y));
	SetSizeHints (665,660);
	m_CntEarth=0;
	m_CntSens=false;
	m_Cnt =0;
	m_TUpdate=new wxTimer (this, MF_UPDATE);
	m_TUpdate->Start (100, false);
}


//------------------------------------------------------------------------------
// Destructeur

CMainFrame::~CMainFrame()
{
}

//------------------------------------------------------------------------------
// Click sur le menu Exit

void CMainFrame::OnExit(wxCommandEvent& WXUNUSED(pEvent))
{
    Close();
}

//------------------------------------------------------------------------------
// Fermeture de la fenetre

void CMainFrame::OnCloseWindow(wxCloseEvent& WXUNUSED(pEvent))
{
	m_TUpdate->Stop();
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
	m_Config->Write(_T("/Fenetre/prinx"), x);
	m_Config->Write(_T("/Fenetre/priny"), y);
	m_Config->Write(_T("/Fenetre/prinw"), w);
	m_Config->Write(_T("/Fenetre/prinh"), h);
	m_Config->Flush();
	m_CtrlAw->Init(false);
	CCtrlAw::Kill ();
	Destroy();
}

//------------------------------------------------------------------------------

void CMainFrame::OnUniverseCon (wxCommandEvent& WXUNUSED(pEvent))
{
	if (m_Bot->ModeReco)
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
			m_Bot->ModeReco=false;
			wxLogMessage(_("Abording Attempts of reconnections"));
		}
	}
	else if (!m_Bot->IsOnWorld())
	{
		m_Bot->Global=true;
		m_Bot->Connect();
	}
	else
	{
		m_Bot->Deconnect();
		m_BackupCtrl->Reset();
	}
}

//------------------------------------------------------------------------------

void CMainFrame::OnUniverseSetup (wxCommandEvent& WXUNUSED(pEvent))
{
	COptDial Option
	(
		this,
		m_Bot,
		_("Universe Setting"),
		wxPoint(100,100),
		wxSize(200,200),
		wxDEFAULT_DIALOG_STYLE
	);
	Option.ShowModal();
}

//------------------------------------------------------------------------------

void CMainFrame::OnScan (wxCommandEvent& WXUNUSED(pEvent))
{
	m_BackupCtrl->Scan ();
}

//------------------------------------------------------------------------------

void CMainFrame::OnSetOri (wxCommandEvent& WXUNUSED(pEvent))
{
    wxString s = wxGetTextFromUser (_("Please Enter an AW Coord location :"),_("Set Grid Origin"),_T("0N 0W"));
    AwToCoord (m_BackupCtrl->OrigX, m_BackupCtrl->OrigY,s);
	m_MapCanvas->Refresh();
}

//------------------------------------------------------------------------------

void CMainFrame::OnHelp(wxCommandEvent& WXUNUSED(pEvent))
{
	::wxLaunchDefaultBrowser (BackupAW_Help);
}

//------------------------------------------------------------------------------

void CMainFrame::OnForum(wxCommandEvent& WXUNUSED(pEvent))
{
	::wxLaunchDefaultBrowser (BackupAW_Forum);
}


//------------------------------------------------------------------------------
// Click sur About

void CMainFrame::OnAbout (wxCommandEvent& WXUNUSED(pEvent))
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

void CMainFrame::OnTUpdate (wxTimerEvent& WXUNUSED(pEvent))
{
	wxString s;
	wxMenuBar* Menu = GetMenuBar ();
	wxMenuItem* ItemScan = Menu->FindItem (MF_MENU_SCAN);
	wxMenuItem* ItemAwCon = Menu->FindItem (MF_MENU_AWCON);
	// Mise à jour des icones de connection
	if ((m_Bot->IsOnWorld())&&(!m_AConnect))
	{
		ItemAwCon->SetItemLabel (_("Disconnect"));
		ItemAwCon->SetHelp (_("Universe Disconnection"));
		m_ToolBar->DeleteTool (MF_MENU_AWCON);
		m_ToolBar->InsertTool ( 3,MF_MENU_AWCON,_("Disconnect"), wxBitmap(connect_xpm), wxNullBitmap, wxITEM_NORMAL,_("Universe Disconnection") );
		m_AConnect=true;
		m_ToolBar->Realize();
	}
	else if ((!m_Bot->IsOnWorld())&&(m_AConnect))
	{
		ItemAwCon->SetItemLabel (_("Connect"));
		ItemAwCon->SetHelp (_("Universe Connecting"));
		m_ToolBar->DeleteTool (MF_MENU_AWCON);
		m_ToolBar->InsertTool ( 3,MF_MENU_AWCON,_("Connect"), wxBitmap(deco_xpm), wxNullBitmap, wxITEM_NORMAL,_("Universe Connecting") );
		m_AConnect=false;
		m_ToolBar->Realize();
	}
	// Animation de l'icone Earth pendant un scan
	if (m_BackupCtrl->IsScanning	())
	{
		m_Cnt++;
		if (m_Cnt>5)
		{
			if (m_CntSens) m_CntEarth++;
			else m_CntEarth--;
			m_Cnt=0;
		}
		if (m_CntEarth > 4)
		{
			m_CntSens=false;
			m_CntEarth=4;
		}
		if (m_CntEarth < 0)
		{
			m_CntSens=true;
			m_CntEarth=0;
		}
	}
	else
	{
		m_CntEarth=5;
		m_CntSens=false;
	}
	if (m_ACntEarth!= m_CntEarth)
	{
		m_ToolBar->DeleteTool (MF_MENU_SCAN);
		switch (m_CntEarth)
		{
			case 0 :
				m_ToolBar->InsertTool ( 5,MF_MENU_SCAN,_("Scan World"), wxBitmap(earth1_xpm),wxNullBitmap, wxITEM_NORMAL, _("Scan World"));
                break;
			case 1 :
				m_ToolBar->InsertTool ( 5,MF_MENU_SCAN,_("Scan World"), wxBitmap(earth2_xpm),wxNullBitmap, wxITEM_NORMAL, _("Scan World"));
				break;
			case 2 :
				m_ToolBar->InsertTool ( 5,MF_MENU_SCAN,_("Scan World"), wxBitmap(earth3_xpm),wxNullBitmap, wxITEM_NORMAL, _("Scan World"));
				break;
			case 3 :
				m_ToolBar->InsertTool ( 5,MF_MENU_SCAN,_("Scan World"), wxBitmap(earth4_xpm),wxNullBitmap, wxITEM_NORMAL, _("Scan World"));
				break;
			case 4 :
				m_ToolBar->InsertTool ( 5,MF_MENU_SCAN,_("Scan World"), wxBitmap(earth5_xpm),wxNullBitmap, wxITEM_NORMAL, _("Scan World"));
				break;
			default :
				m_ToolBar->InsertTool ( 5,MF_MENU_SCAN,_("Scan World"), wxBitmap(earth_xpm),wxNullBitmap, wxITEM_NORMAL, _("Scan World"));
		}
		m_ACntEarth= m_CntEarth;
		m_ToolBar->Realize ();
	}
	if (m_Bot->IsOnWorld())
	{
		SetTitle ( AppName + _(" : On ")+ m_Bot->Monde);
		if (!ItemScan->IsEnabled ()) ItemScan->Enable(true);
		m_ToolBar->EnableTool(MF_MENU_SCAN,true);

	}
	else
	{
		SetTitle ( AppName + _(" : Disconnected"));
		if (ItemScan->IsEnabled ()) ItemScan->Enable(false);
		m_ToolBar->EnableTool(MF_MENU_SCAN,false);
	}
	SetStatusText (wxString::Format(_("Objects in project = %i , Total = %i"), m_Cell->GetNbSel(), m_Cell->GetNbObj()),1);
	if (m_MapCanvas->MapChange && (!m_BackupCtrl->IsScanning()))
	{
		if (m_Bot->IsOnWorld() && m_BackupCtrl->IsSurvey()) m_BackupCtrl->Scan ();
		m_MapCanvas->MapChange=false;
	}
}

//------------------------------------------------------------------------------

void CMainFrame::OnNew (wxCommandEvent& WXUNUSED(pEvent))
{
	m_Cell->DelSel ();
	m_Cell->FileName=_T("");
	m_MapCanvas->Refresh ();
}

//------------------------------------------------------------------------------

void CMainFrame::OnLoad (wxCommandEvent& WXUNUSED(pEvent))
{
	wxFileDialog ProjectFile
	(
		this,
		_("Open Project"),
		m_Cell->FileName.GetPath(),
		_T("*.bap"),
		_("BackupAw Project (*.bap)|*.bap|All Files (*.*)|*.*"),
		wxFD_OPEN | wxFD_CHANGE_DIR,
		wxDefaultPosition
	);
	if (ProjectFile.ShowModal() == wxID_OK)
	{
		m_Cell->FileName=ProjectFile.GetPath();
		m_Cell->LoadSel();
	}
	m_MapCanvas->Refresh ();
}

//------------------------------------------------------------------------------

void CMainFrame::OnSave (wxCommandEvent& event)
{
	if (m_Cell->FileName==_T("")) OnSaveAs (event);
	else
	{
		m_Cell->SaveSel();
	}
}

//------------------------------------------------------------------------------

void CMainFrame::OnSaveAs (wxCommandEvent& WXUNUSED(pEvent))
{
	wxFileDialog ProjectFile
	(
		this,
		_("Save Project"),
		m_Cell->FileName.GetPath(),
		_T("*.bap"),
		_("BackupAw Project (*.bap)|*.bap|All Files (*.*)|*.*"),
		wxFD_SAVE | wxFD_OVERWRITE_PROMPT | wxFD_CHANGE_DIR,
		wxDefaultPosition
	);
	if (ProjectFile.ShowModal() == wxID_OK)
	{
		m_Cell->FileName=ProjectFile.GetPath();
		m_Config->Write(_T("/Project/LastFileName"), m_Cell->FileName.GetFullPath());
		m_Config->Flush();
		m_Cell->SaveSel();
	}
}

//------------------------------------------------------------------------------

void CMainFrame::OnZoomIn (wxCommandEvent& WXUNUSED(pEvent))
{
	m_MapCanvas->ZoomIn();
}

//------------------------------------------------------------------------------

void CMainFrame::OnZoomOut (wxCommandEvent& WXUNUSED(pEvent))
{
	m_MapCanvas->ZoomOut();
}

//------------------------------------------------------------------------------

void CMainFrame::OnSetRelative(wxCommandEvent& WXUNUSED(pEvent))
{
	wxString Depart = CoordToAwF(m_Cell->RelX, m_Cell->RelZ);
    wxString s = wxGetTextFromUser (_("Please Enter an AW Coord Relative :"),_("Set Relative Object Coord"),Depart);
    if (!s.IsEmpty())
    {
        double x,z,y;
        AwToCoord (x,z,y,s);
		m_Cell->RelX = (int) floor(x * 1000);
		m_Cell->RelZ = (int) floor(z * 1000);
        wxString LogMess;
        LogMess << _("Set Relative Coord to ") << m_Cell->RelX << _T(" / ") << m_Cell->RelZ;
        wxLogMessage(LogMess);
    }
}

//------------------------------------------------------------------------------

void CMainFrame::OnSetScanSize(wxCommandEvent& WXUNUSED(pEvent))
{
	long i = wxGetNumberFromUser(_("Please Enter a value between 5 and 200"),_("Scan size:"), _("Set scan size"), m_BackupCtrl->GetScanSize(), 5,200);
    if (i > 0)
    {
		m_BackupCtrl->SetScanSize((int)i);
        wxString LogMess;
        LogMess << _("Set ScanSize to ") << m_BackupCtrl->GetScanSize();
        wxLogMessage(LogMess);
    }
}
