// *****************************************************************************
// *                                                                           *
// *                         BACKUPAW : CModify.h                              *
// *                        The Modifier Options Tab                           *
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
// *   Creation          : 12/08/2006                                          *
// *   Last Modification : 20/04/2014                                          *
// *   Revision          : B                                                   *
// *                                                                           *
// *****************************************************************************

#ifndef MODIFY_H
#define MODIFY_H

#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
	#include "wx/wx.h"
#endif

#include "wx/spinctrl.h"

#include "CtrlCell.h"
#include "COutils.h"

enum
{
	CM_CHANGE_CIT = wxID_HIGHEST,
	CM_MOVE,
	CM_ROTATE
};


class CModify : public wxPanel , public COutils
{
public:
							CModify (wxWindow* Parent);
							~CModify ();
		wxWindow*			Map;
		void				MAJ ();
private:
		CCtrlCell*			Cell;
		wxWindow*			Owner;
		wxBoxSizer*			item0;

		wxStaticBox*		item2;
		wxStaticBoxSizer*	item1;
		wxBoxSizer*			item3;
		wxTextCtrl*			item4;
		wxBoxSizer*			item5;
		wxTextCtrl*			item6;
		wxStaticText*		item7;
		wxTextCtrl*			item8;
		wxBoxSizer*			item9;
		wxButton*			item10;

		wxStaticBox*		item12;
		wxStaticBoxSizer*	item11;
		wxBoxSizer*			item13;
		wxStaticText*		item14;
		wxTextCtrl*			item15;
		wxBoxSizer*			item16;
		wxStaticText*		item17;
		wxTextCtrl*			item18;
		wxBoxSizer*			item19;
		wxButton*			item20;

		wxStaticBox*		item22;
		wxStaticBoxSizer*	item21;
		wxBoxSizer*			item23;
		wxStaticText*		item24;
		wxTextCtrl*			item25;
		wxBoxSizer*			item26;
		wxStaticText*		item27;
		wxSpinCtrl*			item28;
		wxBoxSizer*			item29;
		wxButton*			item30;

protected:
		void				OnChange (wxCommandEvent& event);
		void				OnMove (wxCommandEvent& event);
		void				OnRotate (wxCommandEvent& event);

		wxDECLARE_EVENT_TABLE();
};

#endif
