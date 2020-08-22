// *****************************************************************************
// *                                                                           *
// *                         BACKUPAW : CModify.cpp                            *
// *                        The Modifier Options Tab                           *
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
// *   Creation          : 12/08/2006                                          *
// *   Last Modification : 20/04/2014                                          *
// *   Revision          : B                                                   *
// *                                                                           *
// *****************************************************************************

#include "CModify.h"

wxBEGIN_EVENT_TABLE (CModify, wxPanel)
	EVT_BUTTON ( CM_CHANGE_CIT, CModify::OnChange)
	EVT_BUTTON ( CM_MOVE, CModify::OnMove)
    EVT_BUTTON ( CM_ROTATE, CModify::OnRotate)
wxEND_EVENT_TABLE()

CModify::CModify(wxWindow* pParent) : wxPanel
	(
		pParent,
		-1,
		wxDefaultPosition,
		wxDefaultSize
	)
{
	Map=nullptr;
	m_Owner = pParent;
	m_Cell = CCtrlCell::Create();
	m_Item0 = new wxBoxSizer( wxVERTICAL );
	m_Item2 = new wxStaticBox( this, -1, _("Citizen Modifier") );
	m_Item1 = new wxStaticBoxSizer( m_Item2, wxVERTICAL );
	m_Item3 = new wxBoxSizer( wxHORIZONTAL );
	m_Item4 = new wxTextCtrl( this,  -1, _T(""), wxDefaultPosition, wxSize (250,100), wxTE_MULTILINE|wxTE_READONLY );
	m_Item5 = new wxBoxSizer( wxHORIZONTAL );
	m_Item6 = new wxTextCtrl( this,  -1, _T(""), wxDefaultPosition, wxSize(50,-1), 0 );
	m_Item7 = new wxStaticText( this,  -1, _("to"), wxDefaultPosition, wxDefaultSize, 0 );
	m_Item8 = new wxTextCtrl( this, -1, _T(""), wxDefaultPosition, wxSize(50,-1), 0 );
	m_Item9 = new wxBoxSizer( wxHORIZONTAL );
	m_Item10 = new wxButton( this, CM_CHANGE_CIT, _("Change"), wxDefaultPosition, wxDefaultSize, 0 );
	m_Item12 = new wxStaticBox( this, -1, _("Move") );
	m_Item11 = new wxStaticBoxSizer( m_Item12, wxVERTICAL );
	m_Item13 = new wxBoxSizer( wxHORIZONTAL );
	m_Item14 = new wxStaticText( this,  -1, _("From\t:"), wxDefaultPosition, wxSize(60,-1), 0 );
	m_Item15 = new wxTextCtrl( this,  -1, _T("0N 0W 0A"), wxDefaultPosition, wxDefaultSize);
	m_Item16 = new wxBoxSizer( wxHORIZONTAL );
	m_Item17 = new wxStaticText( this,  -1, _("To\t:"), wxDefaultPosition, wxSize(60,-1), 0 );
	m_Item18 = new wxTextCtrl( this,  -1, _T("0N 0W 0A"), wxDefaultPosition, wxDefaultSize);
	m_Item19 = new wxBoxSizer( wxHORIZONTAL );
	m_Item20 = new wxButton( this, CM_MOVE, _("Move"), wxDefaultPosition, wxDefaultSize, 0 );
	m_Item22 = new wxStaticBox( this, -1, _("Rotate") );
	m_Item21 = new wxStaticBoxSizer( m_Item22, wxVERTICAL );
	m_Item23 = new wxBoxSizer( wxHORIZONTAL );
	m_Item24 = new wxStaticText( this,  -1, _("Pivot point\t:"), wxDefaultPosition, wxSize(120,-1), 0 );
	m_Item25 = new wxTextCtrl( this,  -1, _T("0N 0W"), wxDefaultPosition, wxDefaultSize);
	m_Item26 = new wxBoxSizer( wxHORIZONTAL );
	m_Item27 = new wxStaticText( this,  -1, _("CCW Angle in degrees\t:"), wxDefaultPosition, wxSize(120,-1), 0 );
    m_Item28 = new wxSpinCtrl( this, -1, _T("0"), wxDefaultPosition, wxSize(80,-1),wxSP_ARROW_KEYS, -359, 359,0 );
    m_Item29 = new wxBoxSizer( wxHORIZONTAL );
	m_Item30 = new wxButton( this, CM_ROTATE, _("Rotate"), wxDefaultPosition, wxDefaultSize, 0 );

    m_Item3->Add( m_Item4, 0, wxALIGN_CENTER|wxALL, 2 );
    m_Item1->Add( m_Item3, 0, wxALIGN_CENTER|wxALL, 2 );
    m_Item5->Add( m_Item6, 0, wxALIGN_CENTER|wxALL, 2 );
	m_Item5->Add( m_Item7, 0, wxALIGN_CENTER|wxALL, 2 );
	m_Item5->Add( m_Item8, 0, wxALIGN_CENTER|wxALL, 2 );
	m_Item1->Add( m_Item5, 0, wxALIGN_CENTER|wxALL, 2 );
	m_Item9->Add( m_Item10, 0, wxALIGN_CENTER|wxALL, 2 );
	m_Item1->Add( m_Item9, 0, wxALIGN_CENTER|wxALL, 2 );
	m_Item0->Add( m_Item1, 0, wxGROW|wxALL, 2 );

    m_Item13->Add( m_Item14, 0, wxALIGN_LEFT|wxALL, 2 );
    m_Item13->Add( m_Item15, 0, wxALIGN_LEFT|wxALL, 2 );
    m_Item11->Add( m_Item13, 0, wxALIGN_CENTER|wxALL, 2 );
    m_Item16->Add( m_Item17, 0, wxALIGN_LEFT|wxALL, 2 );
    m_Item16->Add( m_Item18, 0, wxALIGN_LEFT|wxALL, 2 );
    m_Item11->Add( m_Item16, 0, wxALIGN_CENTER|wxALL, 2 );
    m_Item19->Add( m_Item20, 0, wxALIGN_CENTER|wxALL, 2 );
    m_Item11->Add( m_Item19, 0, wxALIGN_CENTER|wxALL, 2 );
	m_Item0->Add( m_Item11, 0, wxGROW|wxALL, 5 );

    m_Item23->Add( m_Item24, 0, wxALIGN_LEFT|wxALL, 2 );
    m_Item23->Add( m_Item25, 0, wxALIGN_LEFT|wxALL, 2 );
    m_Item21->Add( m_Item23, 0, wxALIGN_CENTER|wxALL, 2 );
    m_Item26->Add( m_Item27, 0, wxALIGN_LEFT|wxALL, 2 );
    m_Item26->Add( m_Item28, 0, wxALIGN_LEFT|wxALL, 2 );
    m_Item21->Add( m_Item26, 0, wxALIGN_CENTER|wxALL, 2 );
    m_Item29->Add( m_Item30, 0, wxALIGN_CENTER|wxALL, 2 );
    m_Item21->Add( m_Item29, 0, wxALIGN_CENTER|wxALL, 2 );
	m_Item0->Add( m_Item21, 0, wxGROW|wxALL, 5 );

	SetAutoLayout ( TRUE );
	SetSizer( m_Item0 );
	m_Item0->Fit(this);
	m_Item0->SetSizeHints(this);
}

//------------------------------------------------------------------------------

CModify::~CModify ()
{

}

//------------------------------------------------------------------------------

void CModify::OnChange (wxCommandEvent& WXUNUSED(pEvent))
{
	long num;
	wxString s;
	int Cit1;
	int Cit2;
	s=m_Item6->GetValue();
	s.ToLong (&num);
	Cit1=(int) num;
	s=m_Item8->GetValue();
	s.ToLong (&num);
	Cit2=(int) num;
	m_Cell->ChgeCitSel(Cit1,Cit2);
	MAJ ();
}

//------------------------------------------------------------------------------

void CModify::MAJ ()
{
	m_Cell->GetCitSel(m_Item4);
}

//------------------------------------------------------------------------------

void CModify::OnMove (wxCommandEvent& WXUNUSED(pEvent))
{
	double x1,y1,a1,x2,y2,a2;
	int x,y,a;
	wxString s1,s2;
	s1=m_Item15->GetValue();
	s2=m_Item18->GetValue();
	AwToCoord (x1,y1,a1,s1);
	AwToCoord (x2,y2,a2,s2);
	x1*=1000;
	x2*=1000;
	y1*=1000;
	y2*=1000;
	a1*=100;
	a2*=100;
	x=(int)(x2-x1);
	y=(int)(y2-y1);
	a=(int)(a2-a1);
	m_Cell->MoveSel(x,y,a);
	if (Map) Map->Refresh ();
}

//------------------------------------------------------------------------------

void CModify::OnRotate (wxCommandEvent& WXUNUSED(pEvent))
{
	double x1,y1,a1;
	int x,y,alpha;
	wxString s;
	s=m_Item25->GetValue();
	alpha=m_Item28->GetValue();
	AwToCoord (x1,y1,a1,s);
	x1*=1000;
	y1*=1000;
	x=(int)(x1);
	y=(int)(y1);
	m_Cell->RotateSel(x,y,alpha);
	if (Map) Map->Refresh ();
}
