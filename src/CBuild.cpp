// *****************************************************************************
// *                                                                           *
// *                         BACKUPAW : CBuild.cpp                             *
// *                          The Build Option Tab                             *
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
// *   Creation          : 10/08/2006                                          *
// *   Last Modification : 20/04/2014                                          *
// *   Revision          : B                                                   *
// *                                                                           *
// *****************************************************************************

#include "CBuild.h"

wxBEGIN_EVENT_TABLE (CBuild, wxPanel)
	EVT_CHECKBOX	( CB_CTBUILD, CBuild::OnChkCTBuild)
	EVT_BUTTON		( CB_BUILD, CBuild::OnBuild)
wxEND_EVENT_TABLE()

CBuild::CBuild(wxWindow* pParent) : wxPanel
	(
		pParent,
		-1,
		wxDefaultPosition,
		wxDefaultSize
	)
{
	m_Owner = pParent;
	BackupCtrl = CBackupCtrl::Create();
	m_Cell = CCtrlCell::Create();
	m_Item1 = new wxStaticText( this, -1, _("Warning This function can build object."), wxDefaultPosition, wxSize(-1,40),0 );
	m_Item2 = new wxButton (this, CB_BUILD, _("Build"), wxDefaultPosition, wxDefaultSize, 0);
	m_Item3 = new wxCheckBox (this, CB_CTBUILD, _("Build as a CareTaker (Use many citizen Nb)"),wxDefaultPosition, wxSize(-1,40), 0);
	m_Item3->SetValue (BackupCtrl->CTBuild);
	m_Item0 = new wxBoxSizer( wxVERTICAL );
	m_Item0->Add(m_Item1, 0, wxGROW, 5 );
	m_Item0->Add(m_Item3, 0, wxGROW, 5 );
	m_Item0->Add(m_Item2, 0, wxGROW, 5 );
	SetAutoLayout ( TRUE );
	SetSizer(m_Item0 );
	m_Item0->Fit(this);
	m_Item0->SetSizeHints(this);
}

//------------------------------------------------------------------------------

CBuild::~CBuild ()
{

}

//------------------------------------------------------------------------------

void CBuild::OnBuild (wxCommandEvent& WXUNUSED(pEvent))
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
		BackupCtrl->StartBuild	();
	}
}

//------------------------------------------------------------------------------

void CBuild::OnChkCTBuild (wxCommandEvent& WXUNUSED(pEvent))
{
	BackupCtrl->CTBuild=m_Item3->GetValue ();
	wxConfigBase* Config = wxConfigBase::Get();
	Config->Write(_T("Bot/BuildMode"), BackupCtrl->CTBuild);
}
