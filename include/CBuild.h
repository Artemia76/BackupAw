// *****************************************************************************
// *                                                                           *
// *                          BACKUPAW : CBuild.h                              *
// *                          The Build Option Tab                             *
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
// *   CopyRight 2006 Neophile                                                 *
// *   Creation          : 10/08/2006                                          *
// *   Last Modification : 20/04/2014                                          *
// *   Revision          : B                                                   *
// *                                                                           *
// *****************************************************************************

#ifndef CBUILD_H
#define CBUILD_H

#ifndef  WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/wxprec.h>
#include "CtrlCell.h"
#ifndef VPBUILD
    #include "CBackupCtrl.h"
#else
    #include "CBackupVP.h"
#endif // VPBUILD

enum
{
	CB_BUILD = wxID_HIGHEST,
	CB_CTBUILD
};

class CBuild : public wxPanel
{
	public:
							CBuild (wxWindow* Parent);
							~CBuild ();
		CBackupCtrl*		BackupCtrl;
	private:
		CCtrlCell*			Cell;
		wxWindow*			Owner;
		wxBoxSizer*			item0;
		wxStaticText*		item1;
		wxCheckBox*			item3;
		wxButton*			item2;
		CCtrlAw*			CtrlAw;

		void				OnBuild (wxCommandEvent& event);
		void				OnChkCTBuild (wxCommandEvent& event);
		wxDECLARE_EVENT_TABLE();
};

#endif
