// *****************************************************************************
// *                                                                           *
// *                         BACKUPAW : CDelete.h                              *
// *                        The Deletion Option Tab                            *
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
// *   Creation          : 09/08/2006                                          *
// *   Last Modification :                                                     *
// *   Revision          : A                                                   *
// *                                                                           *
// *****************************************************************************

#ifndef CDELETE_H
#define CDELETE_H

#ifndef  WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/wxprec.h>
#include "CtrlCell.h"
#include "MapCanvas.h"
#include "CBot.h"

enum
{
	CD_DELETE = 15250
};

class CDelete : public wxPanel
{
	public:
							CDelete (wxWindow* Parent);
							~CDelete ();
		CMapCanvas*			Map;
		CBot*				Bot;
	private:
		CCtrlCell*			Cell;
		wxWindow*			Owner;
		wxBoxSizer*			item0;
		wxStaticText*		item1;
		wxButton*			item2;

		void				OnDelete (wxCommandEvent& event);
		DECLARE_EVENT_TABLE()
};

#endif
