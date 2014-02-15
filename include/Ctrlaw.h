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

#include "CtrlLog.h"
#include "CBot.h"
#include "MapCanvas.h"

enum
{
	HEARTBEAT=11000
};

class CCtrlAw : public wxEvtHandler
{
	private:

static		CCtrlAw*		PtCCtrlAw; //SingleTon Pointer
			CCtrlLog*		Logger;
			CBot*			Bot; // Tab Bot Instance
			CMapCanvas*		Map;
			bool			AwInit;
            wxFileConfig*	pConfig;
			wxTimer*		Heart;

                            CCtrlAw
                            (
                                wxFileConfig* fConfig
                                , CMapCanvas* Carte
                            );
                            ~CCtrlAw                ();
// AW Events
static		void	    	On_Admin_Worlds_Delete	();
static		void	    	On_Admin_Worlds_Info	();
static		void	    	On_Avatar_Add			();
static		void	    	On_Avatar_Change		();
static		void	    	On_Avatar_Delete		();
static		void	    	On_Avatar_Click			();
static		void	    	On_Cell_Begin			();
static		void	    	On_Cell_End				();
static		void	    	On_Cell_Object			();
static		void	    	On_Chat					();
static		void	    	On_Console_Message		();
static		void	    	On_Object_Add			();
static		void	    	On_Object_Click			();
static		void	    	On_Object_Delete		();
static		void	    	On_Object_select		();
static		void	    	On_Teleport				();
static		void	    	On_Universe_Attributes	();
static		void	    	On_Url					();
static		void	    	On_World_Attributes		();
static		void	    	On_World_Disconnect		();
static		void	    	On_World_Info			();
static		void	    	On_Terrain_Begin		();
static		void	    	On_Terrain_Changed		();
static		void		    On_Terrain_Data			();
static		void		    On_Terrain_End			();
static		void		    On_Universe_Disconnect	();

// AW Callbacks

static		void		    On_Login				(int rc);
static		void		    On_Enter				(int rc);
static		void		    On_Query				(int rc);
static		void		    On_Object				(int rc);

// Controller HeartBeat
			void		    On_HeartBeat			(wxTimerEvent & event);
	public:

	static	CCtrlAw*		Create ( wxFileConfig* fConfig, CMapCanvas* Carte);
	static	CCtrlAw*		Get		(); //Get SingleTon Pointer
			CBot*			GetBot (); //Get Bot Pointer
			int				Init(bool); //Init or Close controller

static		void			Kill();

	DECLARE_EVENT_TABLE()
};

#endif
