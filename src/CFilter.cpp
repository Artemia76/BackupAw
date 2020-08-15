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
// *   Last Modification : 20/04/2014                                          *
// *   Revision          : B                                                   *
// *                                                                           *
// *****************************************************************************

#include "CFilter.h"

wxBEGIN_EVENT_TABLE (CFilter, wxPanel)
	EVT_BUTTON		( CF_UPDATE, CFilter::OnUpdate)
wxEND_EVENT_TABLE()

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
	item5 = new wxCheckBox( this, -1, _("Enable"), wxDefaultPosition, wxSize (100,-1), 0 );
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
	item14 = new wxCheckBox( this, -1, _("Enable"), wxDefaultPosition, wxSize (100,-1), 0 );
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
	item23 = new wxCheckBox( this, -1, _("Enable"), wxDefaultPosition, wxSize (100,-1), 0 );
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
	item33 = new wxCheckBox( this, -1, _("Enable"), wxDefaultPosition, wxSize (100,-1), 0 );
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
	item43 = new wxCheckBox( this, -1, _("Enable"), wxDefaultPosition, wxSize (100,-1), 0 );
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

	item4->Add( item5, 0, 0, 2 ); //Vertical Sizer with Enable Check Box
	item3->Add( item4, 0, wxALIGN_TOP, 2 ); //Add Enable group on Horizontal Sizer
	item6->Add( item7, 0, 0, 2 ); // Vertical Sizer with Exclude Citizen Check Box
	item3->Add( item6, 0, wxALIGN_TOP, 2 ); // Add Exclude group on Horizontal Sizer
	item8->Add( item9, 1, wxEXPAND, 2 ); // Citizen Text Box Sizer on Vertical Sizer
	item3->Add( item8, 1, wxEXPAND, 2 ); // Add Citizen TextBox on Horizontal Sizer
	item1->Add( item3, 1, wxEXPAND, 2 ); // Horizontal Sizer
	item0->Add( item1, 1, wxEXPAND, 2 ); // Add Sizer Citizen to Main Sizer

	item13->Add( item14, 0, 0, 2 ); //Vertical Sizer with Enable Check Box
	item12->Add( item13, 0, wxALIGN_TOP, 2 ); //Add Enable group on Horizontal
	item15->Add( item16, 0, 0, 2 ); // Vertical Sizer with Exclude Citizen Check
	item12->Add( item15, 0, wxALIGN_TOP, 2 ); // Add Exclude group on Horizontal Sizer
	item17->Add( item18, 1, wxEXPAND, 2 );// Model Text Box Sizer on Vertical Sizer
	item12->Add( item17, 1, wxEXPAND, 2 );
	item10->Add( item12, 1, wxEXPAND, 2 );
	item0->Add( item10, 1, wxEXPAND, 2 );

	item22->Add( item23, 0, 0, 2 ); //Vertical Sizer with Enable Check Box
	item21->Add( item22, 0, wxALIGN_TOP, 2 ); //Add Enable group on Horizontal Sizer
	item24->Add( item25, 0, 0, 2 ); // Add Exclude group on Horizontal Sizer
	item24->Add( item26, 0, 0, 2 ); // Add Exact Match group on Horizontal Sizer
	item21->Add( item24, 0, wxALIGN_TOP, 2 ); //Add Exclude and Exact Match group on Horizontal Sizer
	item27->Add( item28, 1, wxEXPAND, 2 ); // Description Text Box Sizer on Vertical Sizer
	item21->Add( item27, 1, wxEXPAND, 2 );
	item19->Add( item21, 1, wxEXPAND, 2 );
	item0->Add( item19, 1, wxEXPAND, 2  );

	item32->Add( item33, 0, 0, 2 );
	item31->Add( item32, 0, wxALIGN_TOP, 2  );
	item34->Add( item35, 0, 0, 2 );
	item34->Add( item36, 0, 0, 2 );
	item31->Add( item34, 0, wxALIGN_TOP, 2 );
	item37->Add( item38, 1, wxEXPAND, 2 );
	item31->Add( item37, 1, wxEXPAND, 2 );
	item29->Add( item31, 1, wxEXPAND, 2 );
	item0->Add( item29, 1, wxEXPAND, 2 );

	item42->Add( item43, 0, 0, 2 );
	item41->Add( item42, 0, wxALIGN_TOP, 2 );
	item44->Add( item45, 0, 0, 2 );
	item41->Add( item44, 0, wxALIGN_TOP, 2 );
	item47->Add( item48, 0, wxALIGN_CENTER, 2 );
	item47->Add( item49, 0, wxALIGN_CENTER, 2 );
	item46->Add( item47, 0, wxALIGN_CENTER_HORIZONTAL, 2 );
	item50->Add( item51, 0, wxALIGN_CENTER, 2 );
	item50->Add( item52, 0, wxALIGN_CENTER, 2 );
	item46->Add( item50, 0, wxALIGN_CENTER_HORIZONTAL, 2 );
	item41->Add( item46, 1, wxEXPAND, 2 );
	item39->Add( item41, 1, wxEXPAND, 2 );
	item0->Add( item39, 1, wxEXPAND, 2 );

	item53->Add(item54, 1, wxEXPAND|wxALIGN_TOP, 2 );
	item0->Add( item53, 1, wxEXPAND|wxALIGN_TOP, 2 );
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

