// *****************************************************************************
// *                                                                           *
// *                        BACKUPAW : MainFrame.h                             *
// *                           Main Frame class                                *
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
// *   CopyRight 2006-2007 Neophile                                            *
// *   Creation          : 28/07/2006                                          *
// *   Last Modification : 07/10/2007                                          *
// *   Revision          : B                                                   *
// *                                                                           *
// *****************************************************************************

#ifndef MAINFRAME_H
#define MAINFRAME_H

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <wx/wxprec.h>
#include <wx/fileconf.h>
#include <wx/toolbar.h>

#include "MapCanvas.h"
#include "ToolBook.h"
#include "CtrlLog.h"
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
	MF_UPDATE
};

class CMainFrame : public wxFrame, public COutils
{
	private:
		DECLARE_EVENT_TABLE()
		wxTextCtrl*				LogZone;
		wxBoxSizer* 			SizerPrin;
		wxBoxSizer* 			SizerSec;
		CCtrlLog*				Logger;
		CMapCanvas*				MapCanvas;
		CToolBook*				Tools;
		wxFileConfig* 			pConfig;
		wxToolBar*				ToolBar;
        wxTimer*                TUpdate;
		bool					AConnect;
		CCtrlAw*				CtrlAw;
		CBot*					Bot;
		CCtrlCell*				Cell;
		int						CntEarth;
		int						ACntEarth;
		int						Cnt;
		bool					CntSens;
		wxLocale&				m_locale;
	public:
								CMainFrame (wxLocale& locale,wxFileConfig* fConfig);
		virtual					~CMainFrame ();
	protected:

		void				OnNew (wxCommandEvent& event);
		void				OnLoad (wxCommandEvent& event);
		void				OnSave (wxCommandEvent& event);
		void				OnSaveAs (wxCommandEvent& event);
		void				OnAwCon (wxCommandEvent& event);
		void				OnAwSetup (wxCommandEvent& event);
		void				OnScan (wxCommandEvent& event);
		void				OnSetOri (wxCommandEvent& event);
		void				OnExit (wxCommandEvent& event);
		void				OnHelp (wxCommandEvent& event);
		void				OnForum (wxCommandEvent& event);
		void				OnAbout (wxCommandEvent& event);
		void                OnTUpdate (wxTimerEvent& event);
		void				OnZoomOut (wxCommandEvent& event);
		void				OnZoomIn (wxCommandEvent& event);
		void				OnSetRelative (wxCommandEvent& event);
};

#endif

