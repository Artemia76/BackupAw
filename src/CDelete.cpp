// *****************************************************************************
// *                                                                           *
// *                         BACKUPAW : CDelete.cpp                            *
// *                         The Deletion Option Tab                           *
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
// *   Creation          : 09/08/2006                                          *
// *   Last Modification :                                                     *
// *   Revision          : A                                                   *
// *                                                                           *
// *****************************************************************************

#include "CDelete.h"

BEGIN_EVENT_TABLE (CDelete, wxPanel)
	EVT_BUTTON ( CD_DELETE, CDelete::OnDelete)
END_EVENT_TABLE()

CDelete::CDelete(wxWindow* Parent) : wxPanel
	(
		Parent,
		-1,
		wxDefaultPosition,
		wxDefaultSize
	)
{
	Owner = Parent;
	Map = 0;
	Cell = CCtrlCell::Create();
	item1 = new wxStaticText( this, -1, _("Warning This function can make irreversible destruction."), wxDefaultPosition, wxSize (-1,40),0 );
	item2 = new wxButton (this, CD_DELETE, _("Delete"), wxDefaultPosition, wxDefaultSize, 0);
	item0 = new wxBoxSizer( wxVERTICAL );
	item0->Add( item1, 0, wxGROW|wxALIGN_CENTER_VERTICAL, 5 );
	item0->Add( item2, 0, wxGROW|wxALIGN_CENTER_VERTICAL, 5 );
	SetAutoLayout ( TRUE );
	SetSizer( item0 );
	item0->Fit(this);
	item0->SetSizeHints(this);
}

//------------------------------------------------------------------------------

CDelete::~CDelete ()
{

}

//------------------------------------------------------------------------------

void CDelete::OnDelete (wxCommandEvent& WXUNUSED(event))
{
	wxMessageDialog BoiteOuiNon
	(
		this,
		_("Are you sure to want deleting all object in the project?"),
		_("Warning"),
		wxYES_NO|wxICON_EXCLAMATION
	);
	if (BoiteOuiNon.ShowModal()==wxID_YES)
	{
		Bot->StartDelete	();
	}
}
