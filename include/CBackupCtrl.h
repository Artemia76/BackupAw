// *****************************************************************************
// *                                                                           *
// *                       BACKUPAW : CBackupCtrl.h                            *
// *                  The Grid Canvas to display project                       *
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
// *   CopyRight 2014 Neophile                                                 *
// *   Creation          : 21/04/2014                                          *
// *   Last Modification :                                                     *
// *   Revision          : A                                                   *
// *                                                                           *
// *****************************************************************************

#ifndef VP_BUILD

#ifndef BACKUPCTRL_H
#define BACKUPCTRL_H

#ifndef VP_BUILD

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif
#include <wx/wxprec.h>
#include <wx/config.h>
#include <wx/hashmap.h>

#include "Ctrlaw.h"
#include "CtrlCell.h"

enum
{
    OBJ_TIME = wxID_HIGHEST
};

WX_DECLARE_STRING_HASH_MAP(bool, hmCellMap);
WX_DECLARE_HASH_MAP(int, CObject, wxIntegerHash, wxIntegerEqual, hmObjectCB);

class CBackupCtrl : public wxEvtHandler, public COutils, public CAwListenner
{
public:
    bool			CTBuild;
    bool			Deleting;
    bool			Building;
    bool			BlockScroll;
    bool			BlockSelect;
    int				OrigX;
    int				OrigY;
    wxWindow*       Map;

    static CBackupCtrl* Create();
    static void     Kill();
    void			Scan();
    bool			IsScanning();
    bool			IsSurvey();
    void			Reset();
    void			StartDelete();
    void			StartBuild();
    int				GetScanSize();
    void			SetScanSize(int pSize);

private:
    static CBackupCtrl* m_PtrCBackupCtrl;
    int				m_ScanSize;
    wxTimer*        m_ObjectTimer;
    wxConfigBase*   m_Config;
    CCtrlCell*      m_Cell;
    hmCellMap		m_CellMap;
    hmObjectCB		m_ObjectMap;
    int				m_CellX;
    int				m_CellZ;

    CBackupCtrl();
    ~CBackupCtrl();
    void			Query_CB(int pRC, CBot* pBot);
    void			Object_CB(int pRC, CBot* pBot);
    void			Cell_Begin(CBot* pBot);
    void			Cell_Object(CBot* pBot);
    void			Object_Delete(CBot* pBot);

protected:
    bool			m_Scanning;
    bool			m_Survey;
    size_t			m_DelEC;
    size_t			m_BuildEC;
    int				m_Sequence[5][5];

    bool			Event(AW_EVENT_ATTRIBUTE pID, CBot* pBot);
    bool			CallBack(AW_CALLBACK pID, int pRC, CBot* pBot);

    void			OnObjTimer(wxTimerEvent& pEvent);
    wxDECLARE_EVENT_TABLE();
};

#endif
#endif
#endif

