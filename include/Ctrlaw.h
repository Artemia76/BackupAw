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

#include <aw.h>

#include "CBot.h"

enum
{
	HEARTBEAT=11000
};

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
	virtual bool					Event (AW_EVENT_ATTRIBUTE id, CBot* Bot)=0;
	virtual bool					CallBack (AW_CALLBACK id, int rc, CBot* Bot)=0;
};

//-----------------------------------------------------------------------------
// SingleTon Aw controller

class CCtrlAw : public wxEvtHandler
{
	public:
static		CCtrlAw*				Create ();
			CBot*					GetBot (unsigned int num=0);
			int						Init(bool flag, size_t NbBot=1); // initialize AW DLL
			CBot*					GetBotInst(void* Instance);
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

// AW Events
static		void	    			On_Admin_Worlds_Delete	();
static		void	    			On_Admin_Worlds_Info	();
static		void	    			On_Avatar_Add			();
static		void	    			On_Avatar_Change		();
static		void	    			On_Avatar_Delete		();
static		void	    			On_Avatar_Click			();
static		void	    			On_Cell_Begin			();
static		void	    			On_Cell_End				();
static		void	    			On_Cell_Object			();
static		void	    			On_Chat					();
static		void	    			On_Console_Message		();
static		void	    			On_Object_Add			();
static		void	    			On_Object_Click			();
static		void	    			On_Object_Delete		();
static		void	    			On_Object_select		();
static		void	    			On_Teleport				();
static		void	    			On_Universe_Attributes	();
static		void	    			On_Url					();
static		void	    			On_World_Attributes		();
static		void	    			On_World_Disconnect		();
static		void	    			On_World_Info			();
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
			void					EventDispatch			(AW_EVENT_ATTRIBUTE id, CBot* Bot);
			void					CallBackDispatch		(AW_CALLBACK id, int rc, CBot* Bot);
friend class CAwListenner;
	protected:
			void					AddListenner			(CAwListenner* pListenner);
			void					DelListenner			(CAwListenner* pListenner);
// Controller HeartBea
			void					On_HeartBeat			(wxTimerEvent & event);

			wxDECLARE_EVENT_TABLE();
};

#endif
