// *****************************************************************************
// *                                                                           *
// *                        BACKUPAW : Ctrlaw.cpp                              *
// *                        Controller For AW Sdk                              *
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
// *   Last Modification : 14/04/2014                                          *
// *   Revision          : B                                                   *
// *                                                                           *
// *****************************************************************************

#include "Ctrlaw.h"


CAwListenner::CAwListenner()
{
    CtrlAw = CCtrlAw::Create();
    CtrlAw->AddListenner(this);
}

CAwListenner::~CAwListenner()
{
    CtrlAw->DelListenner(this);
}

wxBEGIN_EVENT_TABLE(CCtrlAw, wxEvtHandler)
    EVT_TIMER(HEARTBEAT, CCtrlAw::On_HeartBeat)
wxEND_EVENT_TABLE()

//------------------------------------------------------------------------------
// SingleTon Private pointer

CCtrlAw* CCtrlAw::m_PtrCCtrlAw = nullptr;

//------------------------------------------------------------------------------
// Creator
CCtrlAw* CCtrlAw::Create()
{
    if (!m_PtrCCtrlAw)
    {
        m_PtrCCtrlAw = new CCtrlAw();
    }
    return m_PtrCCtrlAw;
}

//------------------------------------------------------------------------------
// Singleton killer

void CCtrlAw::Kill()
{
    if (m_PtrCCtrlAw != nullptr) delete m_PtrCCtrlAw;
    m_PtrCCtrlAw = nullptr;
}

//------------------------------------------------------------------------------
// Private Constructor

CCtrlAw::CCtrlAw()
{
    m_AwInit = false;
    m_Config = wxConfigBase::Get();
    m_Heart = new wxTimer(this, HEARTBEAT);
}

//------------------------------------------------------------------------------
// Private Destructor

CCtrlAw::~CCtrlAw()
{
}

//------------------------------------------------------------------------------
// SDK Initialization and Bots instance creation
// bool flag = TRUE : Initialization
//           = FALSE : Close SDK

int CCtrlAw::Init(bool pFlag, size_t pNbBot)
{
    int rc;
    if (pNbBot < 1) pNbBot = 1;
    if ((pFlag) && (!m_AwInit))
    {
#ifndef VP_BUILD
        if (rc = aw_init(AW_BUILD))
#else
        if (rc = vp_init())
#endif // VP_BUILD
        {
            wxLogMessage(_("Unable to init the SDK, Reason :") + CBot::GetRCString(rc));
            return rc;
        }
        else
        {
            wxLogMessage(_("SDK Initialized"));
        }
        // Install AW Events
#ifndef VP_BUILD
        aw_event_set(AW_EVENT_WORLD_DISCONNECT, CCtrlAw::On_World_Disconnect);
        aw_event_set(AW_EVENT_UNIVERSE_DISCONNECT, CCtrlAw::On_Universe_Disconnect);
        aw_event_set(AW_EVENT_CELL_BEGIN, CCtrlAw::On_Cell_Begin);
        aw_event_set(AW_EVENT_CELL_OBJECT, CCtrlAw::On_Cell_Object);
        aw_event_set(AW_EVENT_OBJECT_ADD, CCtrlAw::On_Object_Add);
        aw_event_set(AW_EVENT_OBJECT_DELETE, CCtrlAw::On_Object_Delete);
        // Installe AW Callbacks
        aw_callback_set(AW_CALLBACK_LOGIN, CCtrlAw::On_Login);
        aw_callback_set(AW_CALLBACK_ENTER, CCtrlAw::On_Enter);
        aw_callback_set(AW_CALLBACK_QUERY, CCtrlAw::On_Query);
        aw_callback_set(AW_CALLBACK_OBJECT_RESULT, CCtrlAw::On_Object);
#endif // VP_BUILD
        m_AwInit = true;
        for (size_t i = 0; i < pNbBot; i++)
        {
            m_Bot.push_back(new CBot());
            m_Bot.back()->Charge();
            if (m_Bot.back()->CGConAuto)
            {
                m_Bot.back()->Global = true;
                if (m_Bot.back()->CGRecoEna)
                {
                    m_Bot.back()->CGRecoCnt = 0;
                    m_Bot.back()->CGRetente = m_Bot.back()->CGRecoDelay;
                    m_Bot.back()->ModeReco = true;
                }
                m_Bot.back()->Connect();
            }
        }
        m_Heart->Start(200);
        return 0;
    }
    else if ((!pFlag) && (m_AwInit))
    {
        m_Heart->Stop();
        for (wxVector<CBot*>::iterator i = m_Bot.begin(); i < m_Bot.end(); i++)
        {
#ifndef VP_BUILD
            if ((*i)->SetInstance())
            {
                (*i)->Connection(false);
            }
#else
            (*i)->Connection(false);
#endif // VP_BUILD
            (*i)->Sauve();
            delete (*i);
        }
        m_Bot.clear();
        m_AwInit = false;
#ifndef VP_BUILD
        aw_term();
#endif
        wxLogMessage(_("SDK Stopped."));
        return 0;
    }
    return 1000;
}

#ifndef VP_BUILD
//------------------------------------------------------------------------------
// Cell Begin to be downloaded

void CCtrlAw::On_Cell_Begin(void)
{
    CBot* Robot = m_PtrCCtrlAw->GetBotInst(aw_instance());
    m_PtrCCtrlAw->EventDispatch(AW_EVENT_CELL_BEGIN, Robot);
}
#endif // VP_BUILD

//------------------------------------------------------------------------------
#ifdef VP_BUILD
void CCtrlAw::On_Cell_End(VPInstance pInstance)
{
    CBot* Robot = m_PtrCCtrlAw->GetBotInst(pInstance);
    m_PtrCCtrlAw->EventDispatch(VP_EVENT_CELL_END, Robot);
}
#endif // VP_BUILD

//------------------------------------------------------------------------------
#ifndef VP_BUILD
void CCtrlAw::On_Cell_Object(void)
{
    CBot* Robot = m_PtrCCtrlAw->GetBotInst(aw_instance());
    m_PtrCCtrlAw->EventDispatch(AW_EVENT_CELL_OBJECT, Robot);
}
#endif // VP_BUILD

//------------------------------------------------------------------------------
#ifndef VP_BUILD
void CCtrlAw::On_Object_Add(void)
{
    CBot* Robot = m_PtrCCtrlAw->GetBotInst(aw_instance());
    m_PtrCCtrlAw->EventDispatch(AW_EVENT_OBJECT_ADD, Robot);
}
#endif // VP_BUILD

//------------------------------------------------------------------------------
#ifdef VP_BUILD
void CCtrlAw::On_Object(VPInstance pInstance)
{
    CBot* Robot = m_PtrCCtrlAw->GetBotInst(pInstance);
    m_PtrCCtrlAw->EventDispatch(VP_EVENT_OBJECT, Robot);
}
#endif // VP_BUILD


//------------------------------------------------------------------------------
#ifdef VP_BUILD
void CCtrlAw::On_Object_Change(VPInstance pInstance)
{
    CBot* Robot = m_PtrCCtrlAw->GetBotInst(pInstance);
    m_PtrCCtrlAw->EventDispatch(VP_EVENT_OBJECT_CHANGE, Robot);
}
#endif // VP_BUILD

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
#ifndef VP_BUILD
void CCtrlAw::On_Object_Delete(void)
{
    CBot* Robot = m_PtrCCtrlAw->GetBotInst(aw_instance());
    m_PtrCCtrlAw->EventDispatch(AW_EVENT_OBJECT_DELETE, Robot);
}
#else
void CCtrlAw::On_Object_Delete(VPInstance pInstance)
{
    CBot* Robot = m_PtrCCtrlAw->GetBotInst(pInstance);
    m_PtrCCtrlAw->EventDispatch(VP_EVENT_OBJECT_DELETE, Robot);
}
#endif // VP_BUILD

//------------------------------------------------------------------------------
#ifndef VP_BUILD
void CCtrlAw::On_World_Disconnect(void)
{
    CBot* Robot = m_PtrCCtrlAw->GetBotInst(aw_instance());
    Robot->m_PerteMonde = true;
    m_PtrCCtrlAw->EventDispatch(AW_EVENT_WORLD_DISCONNECT, Robot);
}
#else
void CCtrlAw::On_World_Disconnect(VPInstance pInstance)
{
    CBot* Robot = m_PtrCCtrlAw->GetBotInst(pInstance);
    Robot->m_PerteMonde = true;
    m_PtrCCtrlAw->EventDispatch(VP_EVENT_WORLD_DISCONNECT, Robot);
}
#endif // VP_BUILD

//------------------------------------------------------------------------------
#ifndef VP_BUILD
void CCtrlAw::On_Universe_Disconnect(void)
{
    CBot* Robot = m_PtrCCtrlAw->GetBotInst(aw_instance());
    Robot->m_PerteUniv = true;
    m_PtrCCtrlAw->EventDispatch(AW_EVENT_UNIVERSE_DISCONNECT, Robot);
}
#else

void CCtrlAw::On_Universe_Disconnect(VPInstance pInstance)
{
    CBot* Robot = m_PtrCCtrlAw->GetBotInst(pInstance);
    Robot->m_PerteUniv = true;
    m_PtrCCtrlAw->EventDispatch(VP_EVENT_UNIVERSE_DISCONNECT, Robot);
}
#endif // VP_BUILD
//------------------------------------------------------------------------------
// Callbacks Events
#ifndef VP_BUILD
void CCtrlAw::On_Login(int pRC)
{
    CBot* Robot = m_PtrCCtrlAw->GetBotInst(aw_instance());
    Robot->Login_CB(pRC);
    m_PtrCCtrlAw->CallBackDispatch(AW_CALLBACK_LOGIN, pRC, Robot);
}

//------------------------------------------------------------------------------

void CCtrlAw::On_Enter(int pRC)
{
    CBot* Robot = m_PtrCCtrlAw->GetBotInst(aw_instance());
    Robot->Enter_CB(pRC);
    m_PtrCCtrlAw->CallBackDispatch(AW_CALLBACK_ENTER, pRC, Robot);
}

//------------------------------------------------------------------------------

void CCtrlAw::On_Query(int pRC)
{
    m_PtrCCtrlAw->CallBackDispatch(AW_CALLBACK_QUERY, pRC, m_PtrCCtrlAw->GetBotInst(aw_instance()));
}

//------------------------------------------------------------------------------

void CCtrlAw::On_Object(int pRC)
{
    m_PtrCCtrlAw->CallBackDispatch(AW_CALLBACK_OBJECT_RESULT, pRC, m_PtrCCtrlAw->GetBotInst(aw_instance()));
}
#else

//------------------------------------------------------------------------------

void CCtrlAw::On_Object_Add_CB(VPInstance pInstance, int pRC, int pHandle)
{
    CBot* Robot = m_PtrCCtrlAw->GetBotInst(pInstance);
    m_PtrCCtrlAw->CallBackDispatch(VP_CALLBACK_OBJECT_ADD, pRC, pHandle, Robot);
}

//------------------------------------------------------------------------------

void CCtrlAw::On_Object_Load_CB(VPInstance pInstance, int pRC, int pHandle)
{
    CBot* Robot = m_PtrCCtrlAw->GetBotInst(pInstance);
    m_PtrCCtrlAw->CallBackDispatch(VP_CALLBACK_OBJECT_LOAD, pRC, pHandle, Robot);
}

//------------------------------------------------------------------------------

void CCtrlAw::On_Object_Delete_CB(VPInstance pInstance, int pRC, int pHandle)
{
    CBot* Robot = m_PtrCCtrlAw->GetBotInst(pInstance);
    m_PtrCCtrlAw->CallBackDispatch(VP_CALLBACK_OBJECT_DELETE, pRC, pHandle, Robot);
}

//------------------------------------------------------------------------------

void CCtrlAw::On_Login_CB(VPInstance pInstance, int pRC, int pHandle)
{
    CBot* Robot = m_PtrCCtrlAw->GetBotInst(pInstance);
    Robot->Login_CB(pRC);
    m_PtrCCtrlAw->CallBackDispatch(VP_CALLBACK_LOGIN, pRC, pHandle, Robot);
}

//------------------------------------------------------------------------------

void CCtrlAw::On_Enter_CB(VPInstance pInstance, int pRC, int pHandle)
{
    CBot* Robot = m_PtrCCtrlAw->GetBotInst(pInstance);
    Robot->Enter_CB(pRC);
    m_PtrCCtrlAw->CallBackDispatch(VP_CALLBACK_LOGIN, pRC, pHandle, Robot);
}

#endif



//------------------------------------------------------------------------------

CBot* CCtrlAw::GetBot(unsigned int pNum)
{
    if ((pNum >= m_Bot.size()) || (!m_AwInit)) return 0;
    return m_Bot[pNum];
}

//------------------------------------------------------------------------------
#ifndef VP_BUILD
CBot* CCtrlAw::GetBotInst(void* pInstance)
#else
CBot* CCtrlAw::GetBotInst(VPInstance pInstance)
#endif
{
    for (wxVector<CBot*>::iterator i = m_Bot.begin(); i < m_Bot.end(); i++)
    {
        if ((*i)->GetInstance() == pInstance)
        {
            return (*i);
        }
    }
    return 0;
}

//------------------------------------------------------------------------------
// Controller HeartBeat for SDK update

void CCtrlAw::On_HeartBeat(wxTimerEvent& WXUNUSED(pEvent))
{
#ifndef VP_BUILD
    aw_wait(0);
#endif
    for (wxVector<CBot*>::iterator i = m_Bot.begin(); i < m_Bot.end(); i++)
    {
#ifndef VP_BUILD
        (*i)->SetInstance();
#else
        if ((*i)->GetInstance()) vp_wait((*i)->GetInstance(), 0);
#endif // VP_BUILD
        (*i)->Update();
    }
}

//------------------------------------------------------------------------------
// Add a listenner to list

void CCtrlAw::AddListenner(CAwListenner* pListenner)
{
    if (pListenner)
    {
        m_Listenners.push_back(pListenner);
    }
}

//------------------------------------------------------------------------------
// Del a listenner from list

void CCtrlAw::DelListenner(CAwListenner* pListenner)
{
    if (pListenner)
    {
        for (wxVector<CAwListenner*>::iterator i = m_Listenners.begin(); i != m_Listenners.end();)
        {
            if (*i == pListenner)
            {
                i = m_Listenners.erase(i);
                break;
            }
            else ++i;
        }
    }
}

//------------------------------------------------------------------------------
// Dispatch Event to suscribers
#ifndef VP_BUILD
void CCtrlAw::EventDispatch(AW_EVENT_ATTRIBUTE pID, CBot* pBot)
#else
void CCtrlAw::EventDispatch(vp_event_t pID, CBot* pBot)
#endif // VP_BUILD
{
    for (wxVector<CAwListenner*>::iterator i = m_Listenners.begin(); i != m_Listenners.end(); i++)
    {
        (*i)->Event(pID, pBot);
    }
}

//------------------------------------------------------------------------------
// Dispatch CallBacks to suscribers
#ifndef VP_BUILD
void CCtrlAw::CallBackDispatch(AW_CALLBACK pID, int pRC, CBot* pBot)
#else
void CCtrlAw::CallBackDispatch(vp_callback_t pID, int pRC, int pHandle, CBot* pBot)
#endif
{
    for (wxVector<CAwListenner*>::iterator i = m_Listenners.begin(); i != m_Listenners.end(); i++)
    {
#ifndef VP_BUILD
        (*i)->CallBack(pID, pRC, pBot);
#else
        (*i)->CallBack(pID, pRC, pHandle, pBot);
#endif // VP_BUILD
    }
}
