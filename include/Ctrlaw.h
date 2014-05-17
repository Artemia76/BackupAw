// *****************************************************************************
// *                                                                           *
// *                          BACKUPAW : Ctrlaw.h                              *
// *                         Controller For AW Sdk                             *
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
// *   CopyRight 2005 Neophile                                                 *
// *   Creation          : 22/04/2005                                          *
// *   Last Modification :                                                     *
// *   Revision          : A                                                   *
// *                                                                           *
// *****************************************************************************

#ifndef CTRLAW_H
#define CTRLAW_H


#ifndef  WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/wxprec.h>
#include <wx/config.h>
#include <wx/vector.h>

#ifndef VP_BUILD
    #include <Aw.h>
#else
    #include <VP.h>
#endif // VP_BUILD

#include "CBot.h"

enum
{
	HEARTBEAT=11000
};

class CCtrlAw;

//-----------------------------------------------------------------------------
// Abstract Class to get Aw events and callbacks on external

class CAwListenner
{
	friend class CCtrlAw;
public:
									CAwListenner ();
									~CAwListenner ();
protected:
			CCtrlAw*				CtrlAw;
#ifndef VP_BUILD
	virtual bool					Event (AW_EVENT_ATTRIBUTE id, CBot* Bot)=0;
	virtual bool					CallBack (AW_CALLBACK id, int rc, CBot* Bot)=0;
#else
    virtual bool					Event (vp_event_t id, CBot* Bot)=0;
	virtual bool					CallBack (vp_callback_t id, int rc, int Handle, CBot* Bot)=0;
#endif // VP_BUILD
};

//-----------------------------------------------------------------------------
// SingleTon Aw controller

class CCtrlAw : public wxEvtHandler
{
	public:
static		CCtrlAw*				Create ();
			CBot*					GetBot (unsigned int num=0);
			int						Init(bool flag, size_t NbBot=1); // initialize AW DLL
#ifndef VP_BUILD
			CBot*					GetBotInst(void* Instance);
#else
            CBot*                   GetBotInst(VPInstance Instance);
#endif // VP_BUILD

static		void					Kill();

	private:

									CCtrlAw ();
									~CCtrlAw ();
static		CCtrlAw*				PtCCtrlAw; //SingleTon Pointer

			wxVector<CBot*>			Bot;
			wxVector<CAwListenner*>	Listenners;
			wxConfigBase*			pConfig;
			bool					AwInit;
			wxTimer*				Heart;
#ifndef VP_BUILD
// AW Events
static		void	    			On_Cell_Begin			();
static		void	    			On_Cell_Object			();
static		void	    			On_Object_Add			();
static		void	    			On_Object_Delete		();
static		void	    			On_World_Disconnect		();
static		void	    			On_Terrain_Begin		();
static		void	    			On_Terrain_Changed		();
static		void					On_Terrain_Data			();
static		void					On_Terrain_End			();
static		void					On_Universe_Disconnect	();

// AW Callbacks

static		void					On_Login				(int rc);
static		void					On_Enter				(int rc);
static		void					On_Query				(int rc);
static		void					On_Object				(int rc);

#else
// VP Events

static      void                    On_World_Disconnect (VPInstance Instance);
static      void                    On_Universe_Disconnect (VPInstance Instance);
static      void                    On_Cell_End (VPInstance Instance);
static      void                    On_Object (VPInstance Instance);
static      void                    On_Object_Change (VPInstance Instance);
static      void                    On_Object_Delete (VPInstance Instance);

// VP Callback

static      void                    On_Object_Add_CB        (VPInstance Instance, int rc, int ID);
static      void                    On_Object_Delete_CB   (VPInstance Instance, int rc, int ID);

#endif // VP_BUILD

#ifndef VP_BUILD
			void					EventDispatch			(AW_EVENT_ATTRIBUTE id, CBot* Bot);
			void					CallBackDispatch		(AW_CALLBACK id, int rc, CBot* Bot);
#else
			void					EventDispatch			(vp_event_t id, CBot* Bot);
			void					CallBackDispatch		(vp_callback_t id, int rc, int Handle, CBot* Bot);
#endif // VP_BUILD

friend class CAwListenner;
	protected:
			void					AddListenner			(CAwListenner* pListenner);
			void					DelListenner			(CAwListenner* pListenner);
// Controller HeartBea
			void					On_HeartBeat			(wxTimerEvent & event);

			wxDECLARE_EVENT_TABLE();
};

#endif
