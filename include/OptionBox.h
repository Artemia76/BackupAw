// *****************************************************************************
// *                                                                           *
// *                        BACKUPAW : OptionBox.h                             *
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

#ifndef OPTDIAL_H
#define OPTDIAL_H

#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
#include "wx/wx.h"
#endif


#include "wx/fileconf.h"
#include "wx/spinctrl.h"

#include "CBot.h"

class COptDial : public wxDialog
{
private:
    CBot* m_Bot;
    wxConfigBase* m_Config;
    wxBoxSizer* m_Item0;
    wxBoxSizer* m_Item1;
    wxStaticText* m_Item2;
    wxTextCtrl* m_Item3;
    wxStaticText* m_Item4;
    wxTextCtrl* m_Item5;
    wxBoxSizer* m_Item6;
    wxStaticText* m_Item7;
    wxTextCtrl* m_Item8;
    wxStaticText* m_Item9;
    wxSpinCtrl* m_Item10;
    wxBoxSizer* m_Item11;
    wxStaticText* m_Item12;
    wxTextCtrl* m_Item13;
    wxStaticText* m_Item14;
    wxTextCtrl* m_Item15;
    wxBoxSizer* m_Item16;
    wxButton* m_Item17;
    wxButton* m_Item18;
    wxCheckBox* m_Item19;
    wxBoxSizer* m_Item20;
    wxStaticText* m_Item21;
    wxSpinCtrl* m_Item22;
    wxStaticText* m_Item23;
    wxSpinCtrl* m_Item24;
public:
    COptDial
    (
        wxWindow* pParent,
        CBot* pRobot,
        const wxString& pTitle,
        const wxPoint& pPos = wxDefaultPosition,
        const wxSize& pSize = wxDefaultSize,
        long pStyle = wxDEFAULT_DIALOG_STYLE
    );
    ~COptDial();
    virtual	bool			Validate();

protected:
    void			OnOk(wxCommandEvent& pEvent);
    wxDECLARE_EVENT_TABLE();
};

#endif
