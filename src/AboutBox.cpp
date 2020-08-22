// *****************************************************************************
// *                                                                           *
// *                          BACKUPAW : About.cpp                             *
// *                              About Dialog                                 *
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
// *   CopyRight 2006 Neophile                                                 *
// *   Creation          : 23/02/2014                                          *
// *   Last Modification : 20/04/2014                                          *
// *   Revision          : B                                                   *
// *                                                                           *
// *****************************************************************************

#include "AboutBox.h"

#include "Global.h"
#include "buildwithwxwidgets.xpm"
#include "home.xpm"

//------------------------------------------------------------------------------
// Event definition

wxBEGIN_EVENT_TABLE (AboutBox, wxDialog)
	EVT_BUTTON (ID_BTHOME, AboutBox::On_lien_site)
	EVT_BUTTON (ID_SB_WXWINDOWS, AboutBox::On_lien_wxwidget)
wxEND_EVENT_TABLE()


//------------------------------------------------------------------------------
// Constructor

AboutBox::AboutBox
	(
		wxWindow *pParent,
		const wxString &pTitle,
		const wxPoint &pPosition,
		const wxSize &pSize,
		long pStyle
	)	:
	wxDialog
	(
		pParent,
		-1,
		pTitle,
		pPosition,
		pSize,
		pStyle
	)
{
	m_Config = wxConfigBase::Get();
	//wxPlatformInfo* info = new wxPlatformInfo();

	wxBoxSizer *item0 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer *item13= new wxBoxSizer( wxHORIZONTAL );
	wxStaticText *item3 = new wxStaticText
	(
		this,
		-1,
		AppVersion,
		wxDefaultPosition,
		wxDefaultSize,
		wxALIGN_CENTRE
	);
	item3->SetForegroundColour( *wxBLUE );
	item3->SetFont( wxFont( 14, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD ) );
	item13->Add( item3, 0, wxALIGN_CENTER|wxALL, 5 );
	item0->Add( item13, 0, wxALIGN_CENTER|wxALL, 5 );

	wxTextCtrl *item5 = new wxTextCtrl
	(
		this,
		-1,
		AppLicence,
		wxDefaultPosition,
		wxSize(-1,200),
		wxTE_LEFT|wxTE_MULTILINE|wxTE_READONLY
	);
	item0->Add( item5, 1, wxEXPAND, 2 );

	wxBoxSizer *item6 = new wxBoxSizer( wxHORIZONTAL );

	wxBitmap item9bitmap(home_xpm);
	wxBitmapButton *item7 = new wxBitmapButton( this, ID_BTHOME, item9bitmap, wxDefaultPosition, wxDefaultSize );
	item6->Add( item7, 0, wxALIGN_CENTER|wxALL, 5 );
	wxBitmap item10Bitmap(builtwithwx_xpm);
	wxBitmapButton* item10 = new wxBitmapButton(this, ID_SB_WXWINDOWS, item10Bitmap, wxDefaultPosition, wxDefaultSize );
	item6->Add( item10, 0, wxALIGN_CENTER|wxALL, 5 );
	item0->Add( item6, 0, wxALIGN_CENTER|wxALL, 5 );

	wxBoxSizer *item11 = new wxBoxSizer( wxHORIZONTAL );
	wxButton * item8 = new wxButton ( this, wxID_OK, _T("OK"), wxPoint(60,130), wxDefaultSize);
	item11->Add(item8, 0, wxALIGN_CENTER|wxALL, 5);
	item0->Add( item11, 0, wxALIGN_CENTER|wxALL, 5 );
	SetAutoLayout ( TRUE );
	SetSizer( item0 );
	item0->Fit(this);
	item0->SetSizeHints(this);
	int	x = static_cast<int>(m_Config->Read(_T("/Fenetre/propx"), 50)),
		y = static_cast<int>(m_Config->Read(_T("/Fenetre/propy"), 50));
	Move(x, y);
}

//------------------------------------------------------------------------------
// Destructor

AboutBox::~AboutBox ()
{
	int x, y;
	GetPosition(&x, &y);
	m_Config->Write(_T("/Fenetre/propx"), static_cast<long>(x));
	m_Config->Write(_T("/Fenetre/propy"), static_cast<long>(y));
}

//------------------------------------------------------------------------------
// Link Sitehome when click button

void AboutBox::On_lien_site (wxCommandEvent& WXUNUSED(pEvent))
{
	::wxLaunchDefaultBrowser (BackupAW_Website);
}

//------------------------------------------------------------------------------
// Link for wxWidget pages

void AboutBox::On_lien_wxwidget (wxCommandEvent& WXUNUSED(pEvent))
{
	::wxLaunchDefaultBrowser (_T("http://www.wxwidgets.org/"));
}
