// *****************************************************************************
// *                                                                           *
// *                         BACKUPAW : CCoord.h                               *
// *                        The Coord System Tab                               *
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
// *   CopyRight 2012 Neophile                                                 *
// *   Creation          : 25/05/2012                                          *
// *   Last Modification :                                                     *
// *   Revision          : A                                                   *
// *                                                                           *
// *****************************************************************************

#ifndef COORD_H
#define COORD_H

#ifndef  WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/wxprec.h>
#include <wx/spinctrl.h>

#include "CtrlCell.h"
#include "MapCanvas.h"
#include "COutils.h"
#include "CtrlAw.h"

enum
{
	CC_COORD_X = 16300
};

class CCoord : public wxPanel , public COutils
{
	public:
							CCoord (wxWindow* Parent);
							~CCoord ();
		CMapCanvas*			Map;
		void				MAJ ();
	private:
		CCtrlCell*			Cell;
		wxWindow*			Owner;
		wxBoxSizer*			item0;
		wxBoxSizer*			item1;
		wxStaticText*		item2;
		wxTextCtrl*			item3;
		wxBoxSizer*			item4;
		wxStaticText*		item5;
		wxTextCtrl*			item6;
		CBot*				Bot;
		CCtrlAw*			CtrlAw;
		bool				EnaRelative;

		void				OnChkRelative (wxCommandEvent& event);

		DECLARE_EVENT_TABLE()
};

#endif
