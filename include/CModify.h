// *****************************************************************************
// *                                                                           *
// *                         BACKUPAW : CModify.h                              *
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

#ifndef MODIFY_H
#define MODIFY_H

#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/spinctrl.h"

#include "CtrlCell.h"
#include "COutils.h"

enum
{
    CM_CHANGE_CIT = wxID_HIGHEST,
    CM_MOVE,
    CM_ROTATE
};


class CModify : public wxPanel, public COutils
{
public:
    CModify(wxWindow* pParent);
    ~CModify();
    wxWindow* Map;
    void MAJ();

private:
    CCtrlCell* m_Cell;
    wxWindow* m_Owner;
    wxBoxSizer* m_Item0;

    wxStaticBox* m_Item2;
    wxStaticBoxSizer* m_Item1;
    wxBoxSizer* m_Item3;
    wxTextCtrl* m_Item4;
    wxBoxSizer* m_Item5;
    wxTextCtrl* m_Item6;
    wxStaticText* m_Item7;
    wxTextCtrl* m_Item8;
    wxBoxSizer* m_Item9;
    wxButton* m_Item10;

    wxStaticBox* m_Item12;
    wxStaticBoxSizer* m_Item11;
    wxBoxSizer* m_Item13;
    wxStaticText* m_Item14;
    wxTextCtrl* m_Item15;
    wxBoxSizer* m_Item16;
    wxStaticText* m_Item17;
    wxTextCtrl* m_Item18;
    wxBoxSizer* m_Item19;
    wxButton* m_Item20;

    wxStaticBox* m_Item22;
    wxStaticBoxSizer* m_Item21;
    wxBoxSizer* m_Item23;
    wxStaticText* m_Item24;
    wxTextCtrl* m_Item25;
    wxBoxSizer* m_Item26;
    wxStaticText* m_Item27;
    wxSpinCtrl* m_Item28;
    wxBoxSizer* m_Item29;
    wxButton* m_Item30;

protected:
    void OnChange(wxCommandEvent& pEvent);
    void OnMove(wxCommandEvent& pEvent);
    void OnRotate(wxCommandEvent& pEvent);

    wxDECLARE_EVENT_TABLE();
};

#endif
