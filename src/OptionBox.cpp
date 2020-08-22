// *****************************************************************************
// *                                                                           *
// *                        BACKUPAW : OptionBox.cpp                           *
// *             Dialog Box for editing AW connexion parameters                *
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
		wxWindow* pParent,
		CBot* pRobot,
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
	m_Config=wxConfigBase::Get();
	wxString s;
	m_Bot=pRobot;
// Création des Items
	m_Item0 = new wxBoxSizer( wxVERTICAL );
	m_Item1 = new wxBoxSizer( wxHORIZONTAL );

#ifndef VP_BUILD
	m_Item2 = new wxStaticText( this, -1, _("Citizen :"), wxDefaultPosition, wxSize(100,-1), wxALIGN_RIGHT );
	m_Item3 = new wxTextCtrl( this, -1, wxString::Format(_T("%i"),m_Bot->Citoyen) , wxDefaultPosition, wxSize(80,-1), 0 );
#else
    m_Item2 = new wxStaticText( this, -1, _("User Name :"), wxDefaultPosition, wxSize(100,-1), wxALIGN_RIGHT );
    m_Item3 = new wxTextCtrl( this, -1, m_Bot->UserName , wxDefaultPosition, wxSize(80,-1), 0 );
#endif
	m_Item4 = new wxStaticText( this, -1, _("PassWord :"), wxDefaultPosition, wxSize(100,-1), wxALIGN_RIGHT );
	m_Item5 = new wxTextCtrl( this, -1, m_Bot->PassWord, wxDefaultPosition, wxSize(80,-1),wxTE_PASSWORD );
	m_Item6 = new wxBoxSizer( wxHORIZONTAL );
	m_Item7 = new wxStaticText( this, -1, _("Universe :"), wxDefaultPosition, wxSize(100,-1), wxALIGN_RIGHT );
	m_Item8 = new wxTextCtrl( this, -1, m_Bot->Univers, wxDefaultPosition, wxSize(120,-1), 0 );
	m_Item9 = new wxStaticText( this, -1, _("Port :"), wxDefaultPosition, wxSize(60,-1), wxALIGN_RIGHT );
	s.Printf(_T("%d"), m_Bot->Port);
	m_Item10 = new wxSpinCtrl( this, -1, s , wxDefaultPosition, wxSize(120,-1), wxSP_ARROW_KEYS, 0 ,65535, m_Bot->Port ); //wxTE_READONLY
	m_Item11 = new wxBoxSizer( wxHORIZONTAL );
	m_Item12 = new wxStaticText( this, -1, _("Bot Name :"), wxDefaultPosition, wxSize(100,-1), wxALIGN_RIGHT );
	m_Item13 = new wxTextCtrl( this, -1, m_Bot->Nom, wxDefaultPosition, wxSize(80,-1), 0 );
	m_Item14 = new wxStaticText( this, -1, _("World :"), wxDefaultPosition, wxSize(100,-1), wxALIGN_RIGHT );
	m_Item15 = new wxTextCtrl( this, -1, m_Bot->Monde, wxDefaultPosition, wxSize(80,-1), 0 );
	m_Item16 = new wxBoxSizer( wxHORIZONTAL );
	m_Item17 = new wxButton( this, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	m_Item18 = new wxButton( this, wxID_OK, _("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	m_Item19 = new wxCheckBox (this, -1, _("Auto connection on startup"),wxDefaultPosition, wxDefaultSize, 0 );
	m_Item19->SetValue(m_Bot->CGConAuto);
	m_Item20 = new wxBoxSizer( wxHORIZONTAL );
	m_Item21 = new wxStaticText( this, -1, _("Reconnection Delay (sec) :"), wxDefaultPosition, wxSize(160,-1), wxALIGN_RIGHT );
	s.Printf(_T("%d"), m_Bot->CGRecoDelay);
	m_Item22 = new wxSpinCtrl( this, -1, s , wxDefaultPosition, wxSize(50,-1), wxSP_ARROW_KEYS, 0 ,300, m_Bot->CGRecoDelay );
	m_Item23 = new wxStaticText( this, -1, _("Number of attempts :"), wxDefaultPosition, wxSize(130,-1), wxALIGN_RIGHT );
	s.Printf(_T("%d"), m_Bot->CGRecoRetry);
	m_Item24 = new wxSpinCtrl( this, -1, s , wxDefaultPosition, wxSize(50,-1), wxSP_ARROW_KEYS, -1 ,10, m_Bot->CGRecoRetry );

// Affectation des Items

	m_Item1->Add( m_Item2, 0, wxALIGN_CENTER|wxALL, 5 );
	m_Item1->Add( m_Item3, 0, wxGROW|wxALL, 5 );
	m_Item1->Add( m_Item4, 0, wxALIGN_CENTER|wxALL, 5 );
	m_Item1->Add( m_Item5, 0, wxALIGN_CENTER|wxALL, 5 );
	m_Item0->Add( m_Item1, 0, wxGROW|wxALL, 5 );
	m_Item6->Add( m_Item7, 0, wxALIGN_CENTER|wxALL, 5 );
	m_Item6->Add( m_Item8, 0, wxALIGN_CENTER|wxALL, 5 );
	m_Item6->Add( m_Item9, 0, wxALIGN_CENTER|wxALL, 5 );
	m_Item6->Add( m_Item10, 0, wxALIGN_CENTER|wxALL, 5 );
	m_Item0->Add( m_Item6, 0, wxGROW|wxALL, 5 );
	m_Item11->Add( m_Item12, 0, wxALIGN_CENTER|wxALL, 5 );
	m_Item11->Add( m_Item13, 0, wxALIGN_CENTER|wxALL, 5 );
	m_Item11->Add( m_Item14, 0, wxALIGN_CENTER|wxALL, 5 );
	m_Item11->Add( m_Item15, 0, wxALIGN_CENTER|wxALL, 5 );
	m_Item0->Add( m_Item11, 0, wxGROW|wxALL, 5 );
	m_Item20->Add( m_Item21, 0, wxALIGN_CENTER|wxALL, 5 );
	m_Item20->Add( m_Item22, 0, wxALIGN_CENTER|wxALL, 5 );
	m_Item20->Add( m_Item23, 0, wxALIGN_CENTER|wxALL, 5 );
	m_Item20->Add( m_Item24, 0, wxALIGN_CENTER|wxALL, 5 );
	m_Item0->Add( m_Item20, 0, wxGROW|wxALL, 5 );
	m_Item16->Add( 30, 20, 0, wxGROW|wxALL, 5 );
	m_Item16->Add( m_Item19, 0, wxGROW|wxALL, 5 );
	m_Item16->Add( 30, 20, 0, wxGROW|wxALL, 5 );
	m_Item16->Add( m_Item17, 0, wxALIGN_CENTER|wxALL, 5 );
	m_Item16->Add( m_Item18, 0, wxALIGN_CENTER|wxALL, 5 );
	m_Item0->Add( m_Item16, 0, wxGROW|wxALL, 5 );

	SetAutoLayout ( TRUE );
	SetSizer( m_Item0 );
	m_Item0->Fit(this);
	m_Item0->SetSizeHints(this);
	int	x = m_Config->Read(_T("/Fenetre/optx"), 50),
		y = m_Config->Read(_T("/Fenetre/opty"), 50);
	Move(x, y);
}

//------------------------------------------------------------------------------

COptDial::~COptDial ()
{
	int x, y;
	GetPosition(&x, &y);
	m_Config->Write(_T("/Fenetre/optx"), static_cast<long>(x));
	m_Config->Write(_T("/Fenetre/opty"), static_cast<long>(y));
	m_Config->Flush(true);
}

//------------------------------------------------------------------------------

void COptDial::OnOk(wxCommandEvent& WXUNUSED(pEvent))
{
#ifndef VP_BUILD
	long Valeur;
	m_Item3->GetValue().ToLong(&Valeur);
	m_Bot->Citoyen=static_cast<int>(Valeur);
#else
    m_Bot->UserName=m_Item3->GetValue();
#endif
	m_Bot->Sauve();
	m_Bot->PassWord=m_Item5->GetValue();
	m_Bot->Univers=m_Item8->GetValue();
	m_Bot->Port=m_Item10->GetValue();
	m_Bot->Nom=m_Item13->GetValue();
	m_Bot->Monde=m_Item15->GetValue();
	m_Bot->CGConAuto=m_Item19->GetValue();
	m_Bot->CGRecoDelay=m_Item22->GetValue();
	m_Bot->CGRecoRetry=m_Item24->GetValue();
	if (m_Item24->GetValue() != 0) m_Bot->CGRecoEna=true;
	else m_Bot->CGRecoEna=false;
	m_Bot->Sauve();
	EndModal (1);
}

//------------------------------------------------------------------------------

bool COptDial::Validate()
{
	return true;
}
