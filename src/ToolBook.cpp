// *****************************************************************************
// *                                                                           *
// *                        BACKUPAW : ToolBook.cpp                            *
// *      Tab Book for implement Build, Delete ,modifier and filter tabs       *
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

#include "ToolBook.h"

wxBEGIN_EVENT_TABLE(CToolBook, wxScrolledWindow)
    EVT_NOTEBOOK_PAGE_CHANGED(TB_PAGE_CHANGE, CToolBook::OnPageChange)
wxEND_EVENT_TABLE()

CToolBook::CToolBook(wxWindow* pParent) : wxScrolledWindow
(
    pParent,
    wxID_ANY,
    wxPoint(0, 0),
    wxDefaultSize,
    wxSUNKEN_BORDER | wxTAB_TRAVERSAL
)
{

    m_Owner = pParent;
    SetScrollRate(8, 8);
    SetVirtualSize(800, 800);
    m_SizerPrin = new wxBoxSizer(wxVERTICAL);
    m_Tools = new wxNotebook
    (
        this,
        TB_PAGE_CHANGE,
        wxDefaultPosition,
        wxDefaultSize,
        wxNB_TOP
    );
    m_SizerPrin->Add(m_Tools, 1, wxEXPAND);
    Filter = new CFilter(m_Tools);
    Delete = new CDelete(m_Tools);
    Build = new CBuild(m_Tools);
    Modify = new CModify(m_Tools);

    m_Tools->AddPage(Filter, _("Filters"));
    m_Tools->AddPage(Modify, _("Modify"));
    m_Tools->AddPage(Build, _("Build"));
    m_Tools->AddPage(Delete, _("Delete"));
    m_Tools->SetSelection(0);
    SetSizer(m_SizerPrin);
}

void CToolBook::OnPageChange(wxNotebookEvent& pEvent)
{
    if (pEvent.GetSelection() == 1)
    {
        Modify->MAJ();
    }
}

