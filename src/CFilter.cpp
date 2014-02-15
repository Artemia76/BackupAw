// *****************************************************************************
// *                                                                           *
// *                         BACKUPAW : CFilter.cpp                            *
// *                         The Filter Options Tab                            *
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
// *   Creation          : 05/08/2006                                          *
// *   Last Modification :                                                     *
// *   Revision          : A                                                   *
// *                                                                           *
// *****************************************************************************

#include "CFilter.h"

BEGIN_EVENT_TABLE (CFilter, wxPanel)
	EVT_BUTTON		( CF_UPDATE, CFilter::OnUpdate)
END_EVENT_TABLE()

CFilter::CFilter(wxWindow* Parent) : wxPanel
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
	item0 = new wxBoxSizer( wxVERTICAL );
	item2 = new wxStaticBox( this, -1, _("Citizen") );
	item1 = new wxStaticBoxSizer( item2, wxHORIZONTAL );
	item3 = new wxBoxSizer( wxHORIZONTAL);
	item4 = new wxBoxSizer( wxVERTICAL );
	item5 = new wxCheckBox( this, -1, _("Enable"), wxDefaultPosition, wxSize (80,-1), 0 );
	item5->SetValue(Cell->CitFilt);
	item6 = new wxBoxSizer( wxVERTICAL );
	item7 = new wxCheckBox( this, -1, _("Exclude"), wxDefaultPosition, wxSize (100,-1), 0 );
	item7->SetValue(Cell->CitExcl);
	item8 = new wxBoxSizer( wxVERTICAL );
	item9 = new wxTextCtrl( this, -1, _T(""), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	item9->SetValue(Cell->CitList);
	item11 = new wxStaticBox( this, -1, _("Model") );
	item10 = new wxStaticBoxSizer( item11, wxHORIZONTAL );
	item12 = new wxBoxSizer( wxHORIZONTAL );
	item13 = new wxBoxSizer( wxVERTICAL );
	item14 = new wxCheckBox( this, -1, _("Enable"), wxDefaultPosition, wxSize (80,-1), 0 );
	item14->SetValue(Cell->ModelFilt);
	item15 = new wxBoxSizer( wxVERTICAL );
	item16 = new wxCheckBox( this, -1, _("Exclude"), wxDefaultPosition, wxSize (100,-1), 0 );
	item16->SetValue(Cell->ModelExcl);
	item17 = new wxBoxSizer( wxVERTICAL );
	item18 = new wxTextCtrl( this, -1, _T(""), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	item18->SetValue(Cell->ModelName);
	item20 = new wxStaticBox( this, -1, _("Description") );
	item19 = new wxStaticBoxSizer( item20, wxHORIZONTAL);
	item21 = new wxBoxSizer( wxHORIZONTAL);
	item22 = new wxBoxSizer( wxVERTICAL );
	item23 = new wxCheckBox( this, -1, _("Enable"), wxDefaultPosition, wxSize (80,-1), 0 );
	item23->SetValue(Cell->DescrFilt);
	item24 = new wxBoxSizer( wxVERTICAL );
	item25 = new wxCheckBox( this, -1, _("Exclude"), wxDefaultPosition, wxSize (100,-1), 0 );
	item25->SetValue(Cell->DescrExcl);
	item26 = new wxCheckBox( this, -1, _("Exact Match"), wxDefaultPosition, wxSize (100,-1), 0 );
	item26->SetValue(Cell->DescrMatch);
	item27 = new wxBoxSizer( wxVERTICAL);
	item28 = new wxTextCtrl( this, -1, _T(""), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	item28->SetValue(Cell->DescrName);
	item30 = new wxStaticBox( this, -1, _("Action") );
	item29 = new wxStaticBoxSizer( item30, wxHORIZONTAL );
	item31 = new wxBoxSizer( wxHORIZONTAL );
	item32 = new wxBoxSizer( wxVERTICAL );
	item33 = new wxCheckBox( this, -1, _("Enable"), wxDefaultPosition, wxSize (80,-1), 0 );
	item33->SetValue(Cell->ActionFilt);
	item34 = new wxBoxSizer( wxVERTICAL );
	item35 = new wxCheckBox( this, -1, _("Exclude"), wxDefaultPosition, wxSize (100,-1), 0 );
	item35->SetValue(Cell->ActionExcl);
	item36 = new wxCheckBox( this, -1, _("Exact Match"), wxDefaultPosition, wxSize (100,-1), 0 );
	item36->SetValue(Cell->ActionMatch);
	item37 = new wxBoxSizer( wxVERTICAL );
	item38 = new wxTextCtrl( this, -1, _T(""), wxDefaultPosition,wxDefaultSize, wxTE_MULTILINE );
	item38->SetValue(Cell->ActionName);
	item40 = new wxStaticBox( this, -1, _("Region") );
	item39 = new wxStaticBoxSizer( item40, wxHORIZONTAL );
	item41 = new wxBoxSizer( wxHORIZONTAL );
	item42 = new wxBoxSizer( wxVERTICAL );
	item43 = new wxCheckBox( this, -1, _("Enable"), wxDefaultPosition, wxSize (80,-1), 0 );
	item43->SetValue(Cell->RegioFilt);
	item44 = new wxBoxSizer( wxVERTICAL );
	item45 = new wxCheckBox( this, -1, _("Exclude"), wxDefaultPosition, wxSize (100,-1), 0 );
	item45->SetValue(Cell->RegioExcl);
	item46 = new wxBoxSizer( wxVERTICAL );
	item47 = new wxBoxSizer( wxHORIZONTAL );
	item48 = new wxStaticText( this, -1, _("NW Corner:"), wxDefaultPosition, wxSize (80,-1), 0 );
	item49 = new wxTextCtrl( this, -1, _T(""), wxDefaultPosition, wxSize(60,-1), 0 );
	item49->SetValue(CoordToAw(Cell->RegioW,Cell->RegioN));
	item50 = new wxBoxSizer( wxHORIZONTAL );
	item51 = new wxStaticText( this, -1, _("SE Corner:"), wxDefaultPosition, wxSize (80,-1), 0 );
	item52 = new wxTextCtrl( this, -1, _T(""), wxDefaultPosition, wxSize(60,-1), 0 );
	item52->SetValue(CoordToAw(Cell->RegioE,Cell->RegioS));
	item53 = new wxBoxSizer( wxVERTICAL );
	item54 = new wxButton (this, CF_UPDATE, _("Update"), wxDefaultPosition, wxDefaultSize, 0);

	item4->Add( item5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	item3->Add( item4, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 0 );
	item6->Add( item7, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	item3->Add( item6, 0, wxGROW|wxALIGN_CENTER_VERTICAL, 5 );
	item8->Add( item9, 0, wxALIGN_CENTER|wxALL, 5 );
	item3->Add( item8, 0, wxGROW|wxALIGN_CENTER_VERTICAL, 5 );
	item1->Add( item3, 0, wxGROW|wxALIGN_CENTER_HORIZONTAL, 5 );
	item0->Add( item1, 0, wxGROW|wxALIGN_CENTER_VERTICAL, 5 );
	item13->Add( item14, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	item12->Add( item13, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 0 );
	item15->Add( item16, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	item12->Add( item15, 0, wxGROW|wxALIGN_CENTER_VERTICAL, 5 );
	item17->Add( item18, 0, wxALIGN_CENTER|wxALL, 5 );
	item12->Add( item17, 0, wxGROW|wxALIGN_CENTER_VERTICAL, 5 );
	item10->Add( item12, 0, wxGROW|wxALIGN_CENTER_HORIZONTAL, 5 );
	item0->Add( item10, 0, wxGROW|wxALIGN_CENTER_VERTICAL, 5 );
	item22->Add( item23, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	item21->Add( item22, 0, wxGROW, 0 );
	item24->Add( item25, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	item24->Add( item26, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	item21->Add( item24, 0, wxGROW|wxALIGN_CENTER_VERTICAL, 5 );
	item27->Add( item28, 0, wxALIGN_CENTER|wxALL, 5 );
	item21->Add( item27, 0, wxGROW|wxALIGN_CENTER_VERTICAL, 5 );
	item19->Add( item21, 0, wxGROW|wxALIGN_CENTER_HORIZONTAL, 5 );
	item0->Add( item19, 0, wxGROW|wxALIGN_CENTER_VERTICAL, 5 );
	item32->Add( item33, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	item31->Add( item32, 0, wxGROW, 5 );
	item34->Add( item35, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	item34->Add( item36, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	item31->Add( item34, 0, wxGROW|wxALIGN_CENTER_VERTICAL, 5 );
	item37->Add( item38, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	item31->Add( item37, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	item29->Add( item31, 0, wxGROW|wxALIGN_CENTER_HORIZONTAL, 5 );
	item0->Add( item29, 0, wxGROW|wxALIGN_CENTER_VERTICAL, 5 );
	item42->Add( item43, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	item41->Add( item42, 0, 0, 0 );
	item44->Add( item45, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	item41->Add( item44, 0, wxGROW, 5 );
	item47->Add( item48, 0, wxALIGN_CENTER|wxALL, 5 );
	item47->Add( item49, 0, wxALIGN_CENTER|wxALL, 5 );
	item46->Add( item47, 0, wxGROW|wxALIGN_CENTER_VERTICAL, 5 );
	item50->Add( item51, 0, wxALIGN_CENTER|wxALL, 5 );
	item50->Add( item52, 0, wxALIGN_CENTER|wxALL, 5 );
	item46->Add( item50, 0, wxGROW|wxALIGN_CENTER_VERTICAL, 5 );
	item41->Add( item46, 0, wxALIGN_CENTER, 5 );
	item39->Add( item41, 0, wxGROW|wxALIGN_CENTER_HORIZONTAL, 5 );
	item0->Add( item39, 0, wxGROW|wxALIGN_CENTER_VERTICAL, 5 );
	item53->Add(item54, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	item0->Add( item53, 0, wxGROW|wxALIGN_CENTER|wxALL, 5 );
	SetAutoLayout ( TRUE );
	SetSizer( item0 );
	item0->Fit(this);
	item0->SetSizeHints(this);
}

//------------------------------------------------------------------------------

CFilter::~CFilter ()
{

}

//------------------------------------------------------------------------------

void CFilter::OnUpdate (wxCommandEvent& WXUNUSED(event))
{
	Cell->CitFilt=item5->GetValue();
	Cell->CitExcl=item7->GetValue();
	Cell->CitList=item9->GetValue();
	Cell->ModelFilt=item14->GetValue();
	Cell->ModelExcl=item16->GetValue();
	Cell->ModelName=item18->GetValue();
	Cell->DescrFilt=item23->GetValue();
	Cell->DescrExcl=item25->GetValue();
	Cell->DescrMatch=item26->GetValue();
	Cell->DescrName=item28->GetValue();
	Cell->ActionFilt=item33->GetValue();
	Cell->ActionExcl=item35->GetValue();
	Cell->ActionMatch=item36->GetValue();
	Cell->ActionName=item38->GetValue();
	Cell->RegioFilt=item43->GetValue();
	Cell->RegioExcl=item45->GetValue();
	AwToCoord (Cell->RegioW,Cell->RegioN,item49->GetValue());
	AwToCoord (Cell->RegioE,Cell->RegioS,item52->GetValue());
	Cell->SortObj();
	if (Map)
	{
		Map->Refresh();
	}

}

