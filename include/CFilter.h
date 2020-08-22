// *****************************************************************************
// *                                                                           *
// *                          BACKUPAW : CFilter.h                             *
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

#ifndef FILTER_H
#define FILTER_H

#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
#include "wx/wx.h"
#endif


#include "CtrlCell.h"
#include "COutils.h"

enum
{
    CF_UPDATE = wxID_HIGHEST
};

class CFilter : public wxPanel, public COutils
{

    friend class CMapCanvas;
public:
    wxWindow* Map;

    CFilter(wxWindow* pParent);
    ~CFilter();
private:
    CCtrlCell* m_Cell;
    wxWindow* m_Owner;
    wxBoxSizer* m_Item0;
    wxStaticBox* m_Item2;
    wxStaticBoxSizer* m_Item1;
    wxBoxSizer* m_Item3;
    wxBoxSizer* m_Item4;
    wxCheckBox* m_Item5;
    wxBoxSizer* m_Item6;
    wxCheckBox* m_Item7;
    wxBoxSizer* m_Item8;
    wxTextCtrl* m_Item9;
    wxStaticBox* m_Item11;
    wxStaticBoxSizer* m_Item10;
    wxBoxSizer* m_Item12;
    wxBoxSizer* m_Item13;
    wxCheckBox* m_Item14;
    wxBoxSizer* m_Item15;
    wxCheckBox* m_Item16;
    wxBoxSizer* m_Item17;
    wxTextCtrl* m_Item18;
    wxStaticBox* m_Item20;
    wxStaticBoxSizer* m_Item19;
    wxBoxSizer* m_Item21;
    wxBoxSizer* m_Item22;
    wxCheckBox* m_Item23;
    wxBoxSizer* m_Item24;
    wxCheckBox* m_Item25;
    wxCheckBox* m_Item26;
    wxBoxSizer* m_Item27;
    wxTextCtrl* m_Item28;
    wxStaticBoxSizer* m_Item29;
    wxStaticBox* m_Item30;
    wxBoxSizer* m_Item31;
    wxBoxSizer* m_Item32;
    wxCheckBox* m_Item33;
    wxBoxSizer* m_Item34;
    wxCheckBox* m_Item35;
    wxCheckBox* m_Item36;
    wxBoxSizer* m_Item37;
    wxTextCtrl* m_Item38;
    wxStaticBox* m_Item40;
    wxStaticBoxSizer* m_Item39;
    wxBoxSizer* m_Item41;
    wxBoxSizer* m_Item42;
    wxCheckBox* m_Item43;
    wxBoxSizer* m_Item44;
    wxCheckBox* m_Item45;
    wxBoxSizer* m_Item46;
    wxBoxSizer* m_Item47;
    wxStaticText* m_Item48;
    wxTextCtrl* m_Item49;
    wxBoxSizer* m_Item50;
    wxStaticText* m_Item51;
    wxTextCtrl* m_Item52;
    wxBoxSizer* m_Item53;
    wxButton* m_Item54;

    void OnUpdate(wxCommandEvent& pEvent);

    wxDECLARE_EVENT_TABLE();
};

#endif
