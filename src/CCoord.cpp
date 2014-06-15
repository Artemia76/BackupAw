// *****************************************************************************
// *                                                                           *
// *                         BACKUPAW : CCoord.cpp                             *
// *                          The Build Option Tab                             *
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
// *   CopyRight 2012 Neophile                                                 *
// *   Creation          : 25/05/2012                                          *
// *   Last Modification :                                                     *
// *   Revision          : A                                                   *
// *                                                                           *
// *****************************************************************************

#include "CCoord.h"

BEGIN_EVENT_TABLE (CCoord, wxPanel)
	EVT_CHECKBOX	( CC_COORD_X, CCoord::OnChkRelative)
END_EVENT_TABLE()

CCoord::CCoord(wxWindow* Parent) : wxPanel
	(
		Parent,
		-1,
		wxDefaultPosition,
		wxDefaultSize
	)
{
	Owner = Parent;
	Map = 0;
	CtrlAw = CCtrlAw::Create();
	Bot=CtrlAw->GetBot ();
	Cell = CCtrlCell::Create();
	item2 = new wxStaticText( this, -1, _("Relative X ="), wxDefaultPosition, wxSize(-1,40),0 );
	item3 = new wxTextCtrl( this, -1, _T(""), wxDefaultPosition, wxDefaultSize,0);
	item3->SetValue (wxString::Format(_T("%i"),Cell->RelX));
	item1 = new wxBoxSizer( wxHORIZONTAL );
	item1->Add( item2, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5 );
	item1->Add( item3, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5 );
	item5 = new wxStaticText( this, -1, _("Relative Z ="), wxDefaultPosition, wxSize(-1,40),0 );
	item6 = new wxTextCtrl( this, -1, _T(""), wxDefaultPosition, wxDefaultSize,0);
	item6->SetValue (wxString::Format(_T("%i"),Cell->RelZ));
	item4 = new wxBoxSizer( wxHORIZONTAL );
	item4->Add( item5, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5 );
	item4->Add( item6, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5 );
	item0 = new wxBoxSizer( wxVERTICAL );
	item0->Add( item1, 0, wxGROW|wxALIGN_CENTER_VERTICAL, 5 );
	item0->Add( item4, 0, wxGROW|wxALIGN_CENTER_VERTICAL, 5 );
	SetAutoLayout ( TRUE );
	SetSizer( item0 );
	item0->Fit(this);
	item0->SetSizeHints(this);
}

//------------------------------------------------------------------------------

CCoord::~CCoord ()
{

}

//------------------------------------------------------------------------------
/*
void CCoord::OnBuild (wxCommandEvent& WXUNUSED(event))
{
	wxMessageDialog BoiteOuiNon
	(
		this,
		_("Are you sure to want building all object in the project?"),
		_("Warning"),
		wxYES_NO|wxICON_EXCLAMATION
	);
	if (BoiteOuiNon.ShowModal()==wxID_YES)
	{
		Bot->StartBuild	();
	}
}
*/
//------------------------------------------------------------------------------

void CCoord::OnChkCTBuild (wxCommandEvent& WXUNUSED(event))
{
	if (Bot)
	{
		Bot->CTBuild=item3->GetValue ();
		Bot->Sauve();
	}
}

