// *****************************************************************************
// *                                                                           *
// *                          BACKUPAW : Ctrlaw.h                              *
// *                         Controller For AW Sdk                             *
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
// *   CopyRight 2005 Neophile                                                 *
// *   Creation          : 22/04/2005                                          *
// *   Last Modification :                                                     *
// *   Revision          : A                                                   *
// *                                                                           *
// *****************************************************************************

#ifndef CTRLAW_H
#define CTRLAW_H

#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
#include <wx/wx.h>
#endif

#include "wx/config.h"
#include "wx/vector.h"

#ifndef VP_BUILD
#include <Aw.h>
#else
#include "VPSDK/VP.h"
#endif // VP_BUILD

#include "CBot.h"

enum
{
    HEARTBEAT = 11000
};

class CCtrlAw;

//-----------------------------------------------------------------------------
// Abstract Class to get Aw events and callbacks on external

class CAwListenner
{
    friend class CCtrlAw;
public:
    CAwListenner();
    ~CAwListenner();
protected:
    CCtrlAw* CtrlAw;
#ifndef VP_BUILD
    virtual bool Event(AW_EVENT_ATTRIBUTE pID, CBot* pBot) = 0;
    virtual bool CallBack(AW_CALLBACK pID, int pRC, CBot* pBot) = 0;
#else
    virtual bool Event(vp_event_t pID, CBot* pBot) = 0;
    virtual bool CallBack(vp_callback_t pID, int pRC, int pHandle, CBot* pBot) = 0;
#endif // VP_BUILD
};

//-----------------------------------------------------------------------------
// SingleTon Aw controller

class CCtrlAw : public wxEvtHandler
{
public:
    static CCtrlAw* Create();
    CBot* GetBot(unsigned int pNum = 0);
    int Init(bool pFlag, size_t pNbBot = 1); // initialize AW DLL
#ifndef VP_BUILD
    CBot* GetBotInst(void* pInstance);
#else
    CBot* GetBotInst(VPInstance pInstance);
#endif // VP_BUILD

    static void Kill();

private:

    CCtrlAw();
    ~CCtrlAw();
    static CCtrlAw* m_PtrCCtrlAw; //SingleTon Pointer

    wxVector<CBot*> m_Bot;
    wxVector<CAwListenner*>	m_Listenners;
    wxConfigBase* m_Config;
    bool m_AwInit;
    wxTimer* m_Heart;

protected:
    friend class CAwListenner;
    friend class CBot;
#ifndef VP_BUILD
    // AW Events
    static void On_Cell_Begin();
    static void On_Cell_Object();
    static void	On_Object_Add();
    static void	On_Object_Delete();
    static void	On_World_Disconnect();
    static void	On_Terrain_Begin();
    static void	On_Terrain_Changed();
    static void	On_Terrain_Data();
    static void	On_Terrain_End();
    static void	On_Universe_Disconnect();

    // AW Callbacks

    static void On_Login(int pRC);
    static void	On_Enter(int pRC);
    static void	On_Query(int pRC);
    static void	On_Object(int pRC);

#else
    // VP Events

    static void On_World_Disconnect(VPInstance pInstance);
    static void On_Universe_Disconnect(VPInstance pInstance);
    static void On_Cell_End(VPInstance pInstance);
    static void On_Object(VPInstance pInstance);
    static void On_Object_Change(VPInstance pInstance);
    static void On_Object_Delete(VPInstance pInstance);

    // VP Callback

    static void On_Object_Add_CB(VPInstance pInstance, int pRC, int pID);
    static void On_Object_Load_CB(VPInstance pInstance, int pRC, int pID);
    static void On_Object_Delete_CB(VPInstance pInstance, int pRC, int pID);
    static void On_Login_CB(VPInstance pInstance, int pRC, int pID);
    static void On_Enter_CB(VPInstance pInstance, int pRC, int pID);
#endif // VP_BUILD

#ifndef VP_BUILD
    void EventDispatch(AW_EVENT_ATTRIBUTE pID, CBot* pBot);
    void CallBackDispatch(AW_CALLBACK pID, int pRC, CBot* pBot);
#else
    void EventDispatch(vp_event_t pID, CBot* pBot);
    void CallBackDispatch(vp_callback_t pID, int pRC, int pHandle, CBot* pBot);
#endif // VP_BUILD

    void AddListenner(CAwListenner* pListenner);
    void DelListenner(CAwListenner* pListenner);

    // Controller HeartBeat
    void On_HeartBeat(wxTimerEvent& pEvent);

    wxDECLARE_EVENT_TABLE();
};

#endif
