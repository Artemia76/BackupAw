// *****************************************************************************
// *                                                                           *
// *                        BACKUPAW : OptionBox.cpp                           *
// *             Dialog Box for editing AW connexion parameters                *
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
// *   Creation          : 28/07/2006                                          *
// *   Last Modification : 20/04/2014                                          *
// *   Revision          : B                                                   *
// *                                                                           *
// *****************************************************************************

#include "OptionBox.h"

wxBEGIN_EVENT_TABLE (COptDial, wxDialog)
	EVT_BUTTON ( wxID_OK, COptDial::OnOk)
wxEND_EVENT_TABLE()


COptDial::COptDial
	(
		wxWindow* parent,
		CBot* Robot,
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
	pConfig=wxConfigBase::Get();
	wxString s;
	Bot=Robot;
// Création des Items
	item0 = new wxBoxSizer( wxVERTICAL );
	item1 = new wxBoxSizer( wxHORIZONTAL );

#ifndef VPBUILD
	item2 = new wxStaticText( this, -1, _("Citizen :"), wxDefaultPosition, wxSize(100,-1), wxALIGN_RIGHT );
	item3 = new wxTextCtrl( this, -1, wxString::Format(_T("%i"),Bot->Citoyen)) , wxDefaultPosition, wxSize(80,-1), 0 );
#else
    item2 = new wxStaticText( this, -1, _("User Name :"), wxDefaultPosition, wxSize(100,-1), wxALIGN_RIGHT );
    item3 = new wxTextCtrl( this, -1, Bot->UserName , wxDefaultPosition, wxSize(80,-1), 0 );
#endif
	item4 = new wxStaticText( this, -1, _("PassWord :"), wxDefaultPosition, wxSize(100,-1), wxALIGN_RIGHT );
	item5 = new wxTextCtrl( this, -1, Bot->PassWord, wxDefaultPosition, wxSize(80,-1),wxTE_PASSWORD );
	item6 = new wxBoxSizer( wxHORIZONTAL );
	item7 = new wxStaticText( this, -1, _("Universe :"), wxDefaultPosition, wxSize(100,-1), wxALIGN_RIGHT );
	item8 = new wxTextCtrl( this, -1, Bot->Univers, wxDefaultPosition, wxSize(120,-1), 0 );
	item9 = new wxStaticText( this, -1, _("Port :"), wxDefaultPosition, wxSize(60,-1), wxALIGN_RIGHT );
	s.Printf(_T("%d"),Bot->Port);
	item10 = new wxSpinCtrl( this, -1, s , wxDefaultPosition, wxSize(120,-1), wxSP_ARROW_KEYS, 0 ,65535, Bot->Port ); //wxTE_READONLY
	item11 = new wxBoxSizer( wxHORIZONTAL );
	item12 = new wxStaticText( this, -1, _("Bot Name :"), wxDefaultPosition, wxSize(100,-1), wxALIGN_RIGHT );
	item13 = new wxTextCtrl( this, -1, Bot->Nom, wxDefaultPosition, wxSize(80,-1), 0 );
	item14 = new wxStaticText( this, -1, _("World :"), wxDefaultPosition, wxSize(100,-1), wxALIGN_RIGHT );
	item15 = new wxTextCtrl( this, -1, Bot->Monde, wxDefaultPosition, wxSize(80,-1), 0 );
	item16 = new wxBoxSizer( wxHORIZONTAL );
	item17 = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	item18 = new wxButton( this, wxID_OK, _("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	item19 = new wxCheckBox (this, -1, _("Auto connection on startup"),wxDefaultPosition, wxDefaultSize, 0 );
	item19->SetValue(Bot->CGConAuto);
	item20 = new wxBoxSizer( wxHORIZONTAL );
	item21 = new wxStaticText( this, -1, _("Reconnection Delay (sec) :"), wxDefaultPosition, wxSize(160,-1), wxALIGN_RIGHT );
	s.Printf(_T("%d"),Bot->CGRecoDelay);
	item22 = new wxSpinCtrl( this, -1, s , wxDefaultPosition, wxSize(50,-1), wxSP_ARROW_KEYS, 0 ,300, Bot->CGRecoDelay );
	item23 = new wxStaticText( this, -1, _("Number of attempts :"), wxDefaultPosition, wxSize(130,-1), wxALIGN_RIGHT );
	s.Printf(_T("%d"),Bot->CGRecoRetry);
	item24 = new wxSpinCtrl( this, -1, s , wxDefaultPosition, wxSize(50,-1), wxSP_ARROW_KEYS, -1 ,10, Bot->CGRecoRetry );

// Affectation des Items

	item1->Add( item2, 0, wxALIGN_CENTER|wxALL, 5 );
	item1->Add( item3, 0, wxGROW|wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	item1->Add( item4, 0, wxALIGN_CENTER|wxALL, 5 );
	item1->Add( item5, 0, wxALIGN_CENTER|wxALL, 5 );
	item0->Add( item1, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	item6->Add( item7, 0, wxALIGN_CENTER|wxALL, 5 );
	item6->Add( item8, 0, wxALIGN_CENTER|wxALL, 5 );
	item6->Add( item9, 0, wxALIGN_CENTER|wxALL, 5 );
	item6->Add( item10, 0, wxALIGN_CENTER|wxALL, 5 );
	item0->Add( item6, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	item11->Add( item12, 0, wxALIGN_CENTER|wxALL, 5 );
	item11->Add( item13, 0, wxALIGN_CENTER|wxALL, 5 );
	item11->Add( item14, 0, wxALIGN_CENTER|wxALL, 5 );
	item11->Add( item15, 0, wxALIGN_CENTER|wxALL, 5 );
	item0->Add( item11, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	item20->Add( item21, 0, wxALIGN_CENTER|wxALL, 5 );
	item20->Add( item22, 0, wxALIGN_CENTER|wxALL, 5 );
	item20->Add( item23, 0, wxALIGN_CENTER|wxALL, 5 );
	item20->Add( item24, 0, wxALIGN_CENTER|wxALL, 5 );
	item0->Add( item20, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	item16->Add( 30, 20, 0, wxGROW|wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	item16->Add( item19, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	item16->Add( 30, 20, 0, wxGROW|wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	item16->Add( item17, 0, wxALIGN_CENTER|wxALL, 5 );
	item16->Add( item18, 0, wxALIGN_CENTER|wxALL, 5 );
	item0->Add( item16, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	SetAutoLayout ( TRUE );
	SetSizer( item0 );
	item0->Fit(this);
	item0->SetSizeHints(this);
	int	x = pConfig->Read(_T("/Fenetre/optx"), 50),
		y = pConfig->Read(_T("/Fenetre/opty"), 50);
	Move(x, y);
}

//------------------------------------------------------------------------------

COptDial::~COptDial ()
{
	int x, y;
	GetPosition(&x, &y);
	pConfig->Write(_T("/Fenetre/optx"), (long) x);
	pConfig->Write(_T("/Fenetre/opty"), (long) y);
	pConfig->Flush(true);
}

//------------------------------------------------------------------------------

void COptDial::OnOk(wxCommandEvent& WXUNUSED(event))
{
#ifndef VPBUILD
	wxString s;
	s=item3->GetValue();
	s.ToLong(&Valeur);
	Bot->Citoyen=(int)Valeur;
#else
    Bot->UserName=item3->GetValue();
#endif
	Bot->Sauve();
	Bot->PassWord=item5->GetValue();
	Bot->Univers=item8->GetValue();
	Bot->Port=item10->GetValue();
	Bot->Nom=item13->GetValue();
	Bot->Monde=item15->GetValue();
	Bot->CGConAuto=item19->GetValue();
	Bot->CGRecoDelay=item22->GetValue();
	Bot->CGRecoRetry=item24->GetValue();
	if (item24->GetValue() != 0) Bot->CGRecoEna=true;
	else Bot->CGRecoEna=false;
	Bot->Sauve();
	EndModal (1);
}

//------------------------------------------------------------------------------

bool COptDial::Validate()
{
	return true;
}
