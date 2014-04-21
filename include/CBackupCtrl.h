// *****************************************************************************
// *                                                                           *
// *                       BACKUPAW : CBackupCtrl.h                            *
// *                  The Grid Canvas to display project                       *
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
// *   CopyRight 2014 Neophile                                                 *
// *   Creation          : 21/04/2014                                          *
// *   Last Modification :                                                     *
// *   Revision          : A                                                   *
// *                                                                           *
// *****************************************************************************

#ifndef BACKUPCTRL_H
#define BACKUPCTRL_H

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif
#include <wx/wxprec.h>
#include <wx/config.h>

#include "CtrlAw.h"
#include "CtrlCell.h"

enum
{
	OBJ_TIME = wxID_HIGHEST
};

class CBackupCtrl: public wxEvtHandler, public COutils, public CAwListenner
{
public:
static	CBackupCtrl*	Create ();
static	void			Kill ();
		void			Scan		();
		bool			IsScanning	();
		bool			IsSurvey	();
		void			Reset ();
		void			StartDelete	();
		void			StartBuild	();

		bool			CTBuild;
		bool			Deleting;
		bool			Building;
		bool			BlockScroll;
		bool			BlockSelect;
		int				OrigX;
		int				OrigY;
		wxWindow*		Map;

private:
static	CBackupCtrl*	PtCBackupCtrl;
	
						CBackupCtrl();
						~CBackupCtrl();
		void			Query_CB	(int rc, CBot* Bot);
		void			Object_CB	(int rc, CBot* Bot);
		void			Cell_Begin	(CBot* Bot);
		void			Cell_Object (CBot* Bot);
		void			Object_Delete (CBot* Bot);

		wxTimer*		ObjectTimer;
		wxConfigBase*	pConfig;
		CCtrlCell*		Cell;
		int			CellX;
		int			CellZ;

protected:
		bool			Scanning;
		bool			Survey;
		size_t			DelEC;
		size_t			BuildEC;
		int				sequence[5][5];

		bool			Event (AW_EVENT_ATTRIBUTE id, CBot* Bot);
		bool			CallBack (AW_CALLBACK id, int rc, CBot* Bot);

		void			OnObjTimer		(wxTimerEvent  & event);
		wxDECLARE_EVENT_TABLE();
};

#endif