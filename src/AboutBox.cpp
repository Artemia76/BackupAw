// *****************************************************************************
// *                                                                           *
// *                          BACKUPAW : About.cpp                             *
// *                              About Dialog                                 *
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
		wxWindow *parent,
		const wxString &title,
		const wxPoint &position,
		const wxSize &size,
		long style
	)	:
	wxDialog
	(
		parent,
		-1,
		title,
		position,
		size,
		style
	)
{
	pConfig = wxConfigBase::Get();
	wxPlatformInfo* info = new wxPlatformInfo();

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
	item3->SetFont( wxFont( 14, wxROMAN, wxNORMAL, wxBOLD ) );
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
	int	x = (int)pConfig->Read(_T("/Fenetre/propx"), 50),
		y = (int)pConfig->Read(_T("/Fenetre/propy"), 50);
	Move(x, y);
}

//------------------------------------------------------------------------------
// Destructor

AboutBox::~AboutBox ()
{
	int x, y;
	GetPosition(&x, &y);
	pConfig->Write(_T("/Fenetre/propx"), (long) x);
	pConfig->Write(_T("/Fenetre/propy"), (long) y);
}

//------------------------------------------------------------------------------
// Link Sitehome when click button

void AboutBox::On_lien_site (wxCommandEvent& WXUNUSED(event))
{
	::wxLaunchDefaultBrowser (BackupAW_Website);
}

//------------------------------------------------------------------------------
// Link for wxWidget pages

void AboutBox::On_lien_wxwidget (wxCommandEvent& WXUNUSED(event))
{
	::wxLaunchDefaultBrowser (_T("http://www.wxwidgets.org/"));
}
