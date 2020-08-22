// *****************************************************************************
// *                                                                           *
// *                         BACKUPAW : CFilter.cpp                            *
// *                         The Filter Options Tab                            *
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
// *   Creation          : 05/08/2006                                          *
// *   Last Modification : 20/04/2014                                          *
// *   Revision          : B                                                   *
// *                                                                           *
// *****************************************************************************

#include "CFilter.h"

wxBEGIN_EVENT_TABLE (CFilter, wxPanel)
	EVT_BUTTON		( CF_UPDATE, CFilter::OnUpdate)
wxEND_EVENT_TABLE()

CFilter::CFilter(wxWindow* pParent) : wxPanel
	(
		pParent,
		-1,
		wxDefaultPosition,
		wxDefaultSize
	)
{
	m_Owner = pParent;
	Map = nullptr;
	m_Cell = CCtrlCell::Create();
	m_Item0 = new wxBoxSizer( wxVERTICAL );
	m_Item2 = new wxStaticBox( this, -1, _("Citizen") );
	m_Item1 = new wxStaticBoxSizer(m_Item2, wxHORIZONTAL );
	m_Item3 = new wxBoxSizer( wxHORIZONTAL);
	m_Item4 = new wxBoxSizer( wxVERTICAL );
	m_Item5 = new wxCheckBox( this, -1, _("Enable"), wxDefaultPosition, wxSize (100,-1), 0 );
	m_Item5->SetValue(m_Cell->CitFilt);
	m_Item6 = new wxBoxSizer( wxVERTICAL );
	m_Item7 = new wxCheckBox( this, -1, _("Exclude"), wxDefaultPosition, wxSize (100,-1), 0 );
	m_Item7->SetValue(m_Cell->CitExcl);
	m_Item8 = new wxBoxSizer( wxVERTICAL );
	m_Item9 = new wxTextCtrl( this, -1, _T(""), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	m_Item9->SetValue(m_Cell->CitList);
	m_Item11 = new wxStaticBox( this, -1, _("Model") );
	m_Item10 = new wxStaticBoxSizer(m_Item11, wxHORIZONTAL );
	m_Item12 = new wxBoxSizer( wxHORIZONTAL );
	m_Item13 = new wxBoxSizer( wxVERTICAL );
	m_Item14 = new wxCheckBox( this, -1, _("Enable"), wxDefaultPosition, wxSize (100,-1), 0 );
	m_Item14->SetValue(m_Cell->ModelFilt);
	m_Item15 = new wxBoxSizer( wxVERTICAL );
	m_Item16 = new wxCheckBox( this, -1, _("Exclude"), wxDefaultPosition, wxSize (100,-1), 0 );
	m_Item16->SetValue(m_Cell->ModelExcl);
	m_Item17 = new wxBoxSizer( wxVERTICAL );
	m_Item18 = new wxTextCtrl( this, -1, _T(""), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	m_Item18->SetValue(m_Cell->ModelName);
	m_Item20 = new wxStaticBox( this, -1, _("Description") );
	m_Item19 = new wxStaticBoxSizer(m_Item20, wxHORIZONTAL);
	m_Item21 = new wxBoxSizer( wxHORIZONTAL);
	m_Item22 = new wxBoxSizer( wxVERTICAL );
	m_Item23 = new wxCheckBox( this, -1, _("Enable"), wxDefaultPosition, wxSize (100,-1), 0 );
	m_Item23->SetValue(m_Cell->DescrFilt);
	m_Item24 = new wxBoxSizer( wxVERTICAL );
	m_Item25 = new wxCheckBox( this, -1, _("Exclude"), wxDefaultPosition, wxSize (100,-1), 0 );
	m_Item25->SetValue(m_Cell->DescrExcl);
	m_Item26 = new wxCheckBox( this, -1, _("Exact Match"), wxDefaultPosition, wxSize (100,-1), 0 );
	m_Item26->SetValue(m_Cell->DescrMatch);
	m_Item27 = new wxBoxSizer( wxVERTICAL);
	m_Item28 = new wxTextCtrl( this, -1, _T(""), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE );
	m_Item28->SetValue(m_Cell->DescrName);
	m_Item30 = new wxStaticBox( this, -1, _("Action") );
	m_Item29 = new wxStaticBoxSizer(m_Item30, wxHORIZONTAL );
	m_Item31 = new wxBoxSizer( wxHORIZONTAL );
	m_Item32 = new wxBoxSizer( wxVERTICAL );
	m_Item33 = new wxCheckBox( this, -1, _("Enable"), wxDefaultPosition, wxSize (100,-1), 0 );
	m_Item33->SetValue(m_Cell->ActionFilt);
	m_Item34 = new wxBoxSizer( wxVERTICAL );
	m_Item35 = new wxCheckBox( this, -1, _("Exclude"), wxDefaultPosition, wxSize (100,-1), 0 );
	m_Item35->SetValue(m_Cell->ActionExcl);
	m_Item36 = new wxCheckBox( this, -1, _("Exact Match"), wxDefaultPosition, wxSize (100,-1), 0 );
	m_Item36->SetValue(m_Cell->ActionMatch);
	m_Item37 = new wxBoxSizer( wxVERTICAL );
	m_Item38 = new wxTextCtrl( this, -1, _T(""), wxDefaultPosition,wxDefaultSize, wxTE_MULTILINE );
	m_Item38->SetValue(m_Cell->ActionName);
	m_Item40 = new wxStaticBox( this, -1, _("Region") );
	m_Item39 = new wxStaticBoxSizer(m_Item40, wxHORIZONTAL );
	m_Item41 = new wxBoxSizer( wxHORIZONTAL );
	m_Item42 = new wxBoxSizer( wxVERTICAL );
	m_Item43 = new wxCheckBox( this, -1, _("Enable"), wxDefaultPosition, wxSize (100,-1), 0 );
	m_Item43->SetValue(m_Cell->RegioFilt);
	m_Item44 = new wxBoxSizer( wxVERTICAL );
	m_Item45 = new wxCheckBox( this, -1, _("Exclude"), wxDefaultPosition, wxSize (100,-1), 0 );
	m_Item45->SetValue(m_Cell->RegioExcl);
	m_Item46 = new wxBoxSizer( wxVERTICAL );
	m_Item47 = new wxBoxSizer( wxHORIZONTAL );
	m_Item48 = new wxStaticText( this, -1, _("NW Corner:"), wxDefaultPosition, wxSize (80,-1), 0 );
	m_Item49 = new wxTextCtrl( this, -1, _T(""), wxDefaultPosition, wxSize(60,-1), 0 );
	m_Item49->SetValue(CoordToAw(m_Cell->RegioW,m_Cell->RegioN));
	m_Item50 = new wxBoxSizer( wxHORIZONTAL );
	m_Item51 = new wxStaticText( this, -1, _("SE Corner:"), wxDefaultPosition, wxSize (80,-1), 0 );
	m_Item52 = new wxTextCtrl( this, -1, _T(""), wxDefaultPosition, wxSize(60,-1), 0 );
	m_Item52->SetValue(CoordToAw(m_Cell->RegioE,m_Cell->RegioS));
	m_Item53 = new wxBoxSizer( wxVERTICAL );
	m_Item54 = new wxButton (this, CF_UPDATE, _("Update"), wxDefaultPosition, wxDefaultSize, 0);

	m_Item4->Add( m_Item5, 0, 0, 2 ); //Vertical Sizer with Enable Check Box
	m_Item3->Add( m_Item4, 0, wxALIGN_TOP, 2 ); //Add Enable group on Horizontal Sizer
	m_Item6->Add( m_Item7, 0, 0, 2 ); // Vertical Sizer with Exclude Citizen Check Box
	m_Item3->Add( m_Item6, 0, wxALIGN_TOP, 2 ); // Add Exclude group on Horizontal Sizer
	m_Item8->Add( m_Item9, 1, wxEXPAND, 2 ); // Citizen Text Box Sizer on Vertical Sizer
	m_Item3->Add( m_Item8, 1, wxEXPAND, 2 ); // Add Citizen TextBox on Horizontal Sizer
	m_Item1->Add( m_Item3, 1, wxEXPAND, 2 ); // Horizontal Sizer
	m_Item0->Add( m_Item1, 1, wxEXPAND, 2 ); // Add Sizer Citizen to Main Sizer

	m_Item13->Add( m_Item14, 0, 0, 2 ); //Vertical Sizer with Enable Check Box
	m_Item12->Add( m_Item13, 0, wxALIGN_TOP, 2 ); //Add Enable group on Horizontal
	m_Item15->Add( m_Item16, 0, 0, 2 ); // Vertical Sizer with Exclude Citizen Check
	m_Item12->Add( m_Item15, 0, wxALIGN_TOP, 2 ); // Add Exclude group on Horizontal Sizer
	m_Item17->Add( m_Item18, 1, wxEXPAND, 2 );// Model Text Box Sizer on Vertical Sizer
	m_Item12->Add( m_Item17, 1, wxEXPAND, 2 );
	m_Item10->Add( m_Item12, 1, wxEXPAND, 2 );
	m_Item0->Add( m_Item10, 1, wxEXPAND, 2 );

	m_Item22->Add( m_Item23, 0, 0, 2 ); //Vertical Sizer with Enable Check Box
	m_Item21->Add( m_Item22, 0, wxALIGN_TOP, 2 ); //Add Enable group on Horizontal Sizer
	m_Item24->Add( m_Item25, 0, 0, 2 ); // Add Exclude group on Horizontal Sizer
	m_Item24->Add( m_Item26, 0, 0, 2 ); // Add Exact Match group on Horizontal Sizer
	m_Item21->Add( m_Item24, 0, wxALIGN_TOP, 2 ); //Add Exclude and Exact Match group on Horizontal Sizer
	m_Item27->Add( m_Item28, 1, wxEXPAND, 2 ); // Description Text Box Sizer on Vertical Sizer
	m_Item21->Add( m_Item27, 1, wxEXPAND, 2 );
	m_Item19->Add( m_Item21, 1, wxEXPAND, 2 );
	m_Item0->Add( m_Item19, 1, wxEXPAND, 2  );

	m_Item32->Add( m_Item33, 0, 0, 2 );
	m_Item31->Add( m_Item32, 0, wxALIGN_TOP, 2  );
	m_Item34->Add( m_Item35, 0, 0, 2 );
	m_Item34->Add( m_Item36, 0, 0, 2 );
	m_Item31->Add( m_Item34, 0, wxALIGN_TOP, 2 );
	m_Item37->Add( m_Item38, 1, wxEXPAND, 2 );
	m_Item31->Add( m_Item37, 1, wxEXPAND, 2 );
	m_Item29->Add( m_Item31, 1, wxEXPAND, 2 );
	m_Item0->Add( m_Item29, 1, wxEXPAND, 2 );

	m_Item42->Add( m_Item43, 0, 0, 2 );
	m_Item41->Add( m_Item42, 0, wxALIGN_TOP, 2 );
	m_Item44->Add( m_Item45, 0, 0, 2 );
	m_Item41->Add( m_Item44, 0, wxALIGN_TOP, 2 );
	m_Item47->Add( m_Item48, 0, wxALIGN_CENTER, 2 );
	m_Item47->Add( m_Item49, 0, wxALIGN_CENTER, 2 );
	m_Item46->Add( m_Item47, 0, wxALIGN_CENTER_HORIZONTAL, 2 );
	m_Item50->Add( m_Item51, 0, wxALIGN_CENTER, 2 );
	m_Item50->Add( m_Item52, 0, wxALIGN_CENTER, 2 );
	m_Item46->Add( m_Item50, 0, wxALIGN_CENTER_HORIZONTAL, 2 );
	m_Item41->Add( m_Item46, 1, wxEXPAND, 2 );
	m_Item39->Add( m_Item41, 1, wxEXPAND, 2 );
	m_Item0->Add( m_Item39, 1, wxEXPAND, 2 );

	m_Item53->Add(m_Item54, 1, wxEXPAND|wxALIGN_TOP, 2 );
	m_Item0->Add( m_Item53, 1, wxEXPAND|wxALIGN_TOP, 2 );
	SetAutoLayout ( TRUE );
	SetSizer( m_Item0 );
	m_Item0->Fit(this);
	m_Item0->SetSizeHints(this);
}

//------------------------------------------------------------------------------

CFilter::~CFilter ()
{

}

//------------------------------------------------------------------------------

void CFilter::OnUpdate (wxCommandEvent& WXUNUSED(event))
{
	m_Cell->CitFilt=m_Item5->GetValue();
	m_Cell->CitExcl=m_Item7->GetValue();
	m_Cell->CitList=m_Item9->GetValue();
	m_Cell->ModelFilt=m_Item14->GetValue();
	m_Cell->ModelExcl=m_Item16->GetValue();
	m_Cell->ModelName=m_Item18->GetValue();
	m_Cell->DescrFilt=m_Item23->GetValue();
	m_Cell->DescrExcl=m_Item25->GetValue();
	m_Cell->DescrMatch=m_Item26->GetValue();
	m_Cell->DescrName=m_Item28->GetValue();
	m_Cell->ActionFilt=m_Item33->GetValue();
	m_Cell->ActionExcl=m_Item35->GetValue();
	m_Cell->ActionMatch=m_Item36->GetValue();
	m_Cell->ActionName=m_Item38->GetValue();
	m_Cell->RegioFilt=m_Item43->GetValue();
	m_Cell->RegioExcl=m_Item45->GetValue();
	AwToCoord (m_Cell->RegioW, m_Cell->RegioN,m_Item49->GetValue());
	AwToCoord (m_Cell->RegioE, m_Cell->RegioS,m_Item52->GetValue());
	m_Cell->SortObj();
	if (Map)
	{
		Map->Refresh();
	}

}

