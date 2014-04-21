// *****************************************************************************
// *                                                                           *
// *                         BACKUPAW : CModify.cpp                            *
// *                        The Modifier Options Tab                           *
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

CModify::CModify(wxWindow* Parent) : wxPanel
	(
		Parent,
		-1,
		wxDefaultPosition,
		wxDefaultSize
	)
{
	Map=0;
	Owner = Parent;
	Cell = CCtrlCell::Create();
	item0 = new wxBoxSizer( wxVERTICAL );
	item2 = new wxStaticBox( this, -1, _("Citizen Modifier") );
	item1 = new wxStaticBoxSizer( item2, wxVERTICAL );
	item3 = new wxBoxSizer( wxHORIZONTAL );
	item4 = new wxTextCtrl( this,  -1, _T(""), wxDefaultPosition, wxSize (250,100), wxTE_MULTILINE|wxTE_READONLY );
	item5 = new wxBoxSizer( wxHORIZONTAL );
	item6 = new wxTextCtrl( this,  -1, _T(""), wxDefaultPosition, wxSize(50,-1), 0 );
	item7 = new wxStaticText( this,  -1, _("to"), wxDefaultPosition, wxDefaultSize, 0 );
	item8 = new wxTextCtrl( this, -1, _T(""), wxDefaultPosition, wxSize(50,-1), 0 );
	item9 = new wxBoxSizer( wxHORIZONTAL );
	item10 = new wxButton( this, CM_CHANGE_CIT, _("Change"), wxDefaultPosition, wxDefaultSize, 0 );
	item12 = new wxStaticBox( this, -1, _("Move") );
	item11 = new wxStaticBoxSizer( item12, wxVERTICAL );
	item13 = new wxBoxSizer( wxHORIZONTAL );
	item14 = new wxStaticText( this,  -1, _("From\t:"), wxDefaultPosition, wxSize(60,-1), 0 );
	item15 = new wxTextCtrl( this,  -1, _T("0N 0W 0A"), wxDefaultPosition, wxDefaultSize);
	item16 = new wxBoxSizer( wxHORIZONTAL );
	item17 = new wxStaticText( this,  -1, _("To\t:"), wxDefaultPosition, wxSize(60,-1), 0 );
	item18 = new wxTextCtrl( this,  -1, _T("0N 0W 0A"), wxDefaultPosition, wxDefaultSize);
	item19 = new wxBoxSizer( wxHORIZONTAL );
	item20 = new wxButton( this, CM_MOVE, _("Move"), wxDefaultPosition, wxDefaultSize, 0 );
	item22 = new wxStaticBox( this, -1, _("Rotate") );
	item21 = new wxStaticBoxSizer( item22, wxVERTICAL );
	item23 = new wxBoxSizer( wxHORIZONTAL );
	item24 = new wxStaticText( this,  -1, _("Pivot point\t:"), wxDefaultPosition, wxSize(120,-1), 0 );
	item25 = new wxTextCtrl( this,  -1, _T("0N 0W"), wxDefaultPosition, wxDefaultSize);
	item26 = new wxBoxSizer( wxHORIZONTAL );
	item27 = new wxStaticText( this,  -1, _("CCW Angle in degrees\t:"), wxDefaultPosition, wxSize(120,-1), 0 );
    item28 = new wxSpinCtrl( this, -1, _T("0"), wxDefaultPosition, wxSize(80,-1),wxSP_ARROW_KEYS, -359, 359,0 );
    item29 = new wxBoxSizer( wxHORIZONTAL );
	item30 = new wxButton( this, CM_ROTATE, _("Rotate"), wxDefaultPosition, wxDefaultSize, 0 );

    item3->Add( item4, 0, wxALIGN_CENTER|wxALL, 2 );
    item1->Add( item3, 0, wxALIGN_CENTER|wxALL, 2 );
    item5->Add( item6, 0, wxALIGN_CENTER|wxALL, 2 );
	item5->Add( item7, 0, wxALIGN_CENTER|wxALL, 2 );
	item5->Add( item8, 0, wxALIGN_CENTER|wxALL, 2 );
	item1->Add( item5, 0, wxALIGN_CENTER|wxALL, 2 );
	item9->Add( item10, 0, wxALIGN_CENTER|wxALL, 2 );
	item1->Add( item9, 0, wxALIGN_CENTER|wxALL, 2 );
	item0->Add( item1, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 2 );

    item13->Add( item14, 0, wxALIGN_LEFT|wxALL, 2 );
    item13->Add( item15, 0, wxALIGN_LEFT|wxALL, 2 );
    item11->Add( item13, 0, wxALIGN_CENTER|wxALL, 2 );
    item16->Add( item17, 0, wxALIGN_LEFT|wxALL, 2 );
    item16->Add( item18, 0, wxALIGN_LEFT|wxALL, 2 );
    item11->Add( item16, 0, wxALIGN_CENTER|wxALL, 2 );
    item19->Add( item20, 0, wxALIGN_CENTER|wxALL, 2 );
    item11->Add( item19, 0, wxALIGN_CENTER|wxALL, 2 );
	item0->Add( item11, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

    item23->Add( item24, 0, wxALIGN_LEFT|wxALL, 2 );
    item23->Add( item25, 0, wxALIGN_LEFT|wxALL, 2 );
    item21->Add( item23, 0, wxALIGN_CENTER|wxALL, 2 );
    item26->Add( item27, 0, wxALIGN_LEFT|wxALL, 2 );
    item26->Add( item28, 0, wxALIGN_LEFT|wxALL, 2 );
    item21->Add( item26, 0, wxALIGN_CENTER|wxALL, 2 );
    item29->Add( item30, 0, wxALIGN_CENTER|wxALL, 2 );
    item21->Add( item29, 0, wxALIGN_CENTER|wxALL, 2 );
	item0->Add( item21, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	SetAutoLayout ( TRUE );
	SetSizer( item0 );
	item0->Fit(this);
	item0->SetSizeHints(this);
}

//------------------------------------------------------------------------------

CModify::~CModify ()
{

}

//------------------------------------------------------------------------------

void CModify::OnChange (wxCommandEvent& WXUNUSED(event))
{
	long num;
	wxString s;
	int Cit1;
	int Cit2;
	s=item6->GetValue();
	s.ToLong (&num);
	Cit1=(int) num;
	s=item8->GetValue();
	s.ToLong (&num);
	Cit2=(int) num;
	Cell->ChgeCitSel(Cit1,Cit2);
	MAJ ();
}

//------------------------------------------------------------------------------

void CModify::MAJ ()
{
	Cell->GetCitSel(item4);
}

//------------------------------------------------------------------------------

void CModify::OnMove (wxCommandEvent& WXUNUSED(event))
{
	double x1,y1,a1,x2,y2,a2;
	int x,y,a;
	wxString s1,s2;
	s1=item15->GetValue();
	s2=item18->GetValue();
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
	Cell->MoveSel(x,y,a);
	if (Map) Map->Refresh ();
}

//------------------------------------------------------------------------------

void CModify::OnRotate (wxCommandEvent& WXUNUSED(event))
{
	double x1,y1,a1;
	int x,y,alpha;
	wxString s;
	s=item25->GetValue();
	alpha=item28->GetValue();
	AwToCoord (x1,y1,a1,s);
	x1*=1000;
	y1*=1000;
	x=(int)(x1);
	y=(int)(y1);
	Cell->RotateSel(x,y,alpha);
	if (Map) Map->Refresh ();
}
