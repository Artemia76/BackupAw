// *****************************************************************************
// *                                                                           *
// *                        BACKUPAW : MainFrame.h                             *
// *                           Main Frame class                                *
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
// *   CopyRight 2006-2007 Neophile                                            *
// *   Creation          : 28/07/2006                                          *
// *   Last Modification : 20/04/2014                                          *
// *   Revision          : C                                                   *
// *                                                                           *
// *****************************************************************************

#ifndef MAINFRAME_H
#define MAINFRAME_H

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/config.h"
#include "wx/toolbar.h"
#include "wx/timer.h"

#ifndef VP_BUILD
#include "CBackupCtrl.h"
#else
#include "CBackupVP.h"
#endif // VP_BUILD

#include "MapCanvas.h"
#include "ToolBook.h"
#include "Ctrlaw.h"
#include "CBot.h"
#include "OptionBox.h"
#include "CtrlCell.h"
#include "COutils.h"

enum MF_COMMANDS
{
    MF_MENU_NEW = wxID_HIGHEST,
    MF_MENU_OPEN,
    MF_MENU_SAVE,
    MF_MENU_SAVE_AS,
    MF_MENU_EXIT,
    MF_MENU_AWCON,
    MF_MENU_AWSETUP,
    MF_MENU_SCAN,
    MF_MENU_SETORI,
    MF_MENU_HELP,
    MF_MENU_FORUM,
    MF_MENU_ABOUT,
    MF_MENU_ZOOM_OUT,
    MF_MENU_ZOOM_IN,
    MF_MENU_SET_REL,
    MF_MENU_SET_SCAN_SIZE,
    MF_UPDATE
};

class CMainFrame : public wxFrame, public COutils
{
public:
    CMainFrame();
    virtual	~CMainFrame();

private:
    wxTextCtrl* m_LogZone;
    wxBoxSizer* m_SizerPrin;
    wxBoxSizer* m_SizerSec;
    CMapCanvas* m_MapCanvas;
    CToolBook* m_Tools;
    wxConfigBase* m_Config;
    wxToolBar* m_ToolBar;
    wxTimer* m_TUpdate;
    bool m_AConnect;
    CCtrlAw* m_CtrlAw;
    CBackupCtrl* m_BackupCtrl;
    CBot* m_Bot;
    CCtrlCell* m_Cell;
    int m_CntEarth;
    int m_ACntEarth;
    int m_Cnt;
    bool m_CntSens;

protected:

    void				OnNew(wxCommandEvent& pEvent);
    void				OnLoad(wxCommandEvent& pEvent);
    void				OnSave(wxCommandEvent& pEvent);
    void				OnSaveAs(wxCommandEvent& pEvent);
    void				OnUniverseCon(wxCommandEvent& pEvent);
    void				OnUniverseSetup(wxCommandEvent& pEvent);
    void				OnScan(wxCommandEvent& pEvent);
    void				OnSetOri(wxCommandEvent& pEvent);
    void				OnExit(wxCommandEvent& pEvent);
    void				OnHelp(wxCommandEvent& pEvent);
    void				OnForum(wxCommandEvent& pEvent);
    void				OnAbout(wxCommandEvent& pEvent);
    void                OnTUpdate(wxTimerEvent& pEvent);
    void				OnZoomOut(wxCommandEvent& pEvent);
    void				OnZoomIn(wxCommandEvent& pEvent);
    void				OnSetRelative(wxCommandEvent& pEvent);
    void				OnSetScanSize(wxCommandEvent& pEvent);
    void				OnCloseWindow(wxCloseEvent& pEvent);

    wxDECLARE_EVENT_TABLE();
};

#endif

