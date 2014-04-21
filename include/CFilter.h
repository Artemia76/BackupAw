// *****************************************************************************
// *                                                                           *
// *                          BACKUPAW : CFilter.h                             *
// *                         The Filter Options Tab                            *
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
// *   Creation          : 05/08/2006                                          *
// *   Last Modification : 20/04/2014                                          *
// *   Revision          : B                                                   *
// *                                                                           *
// *****************************************************************************

#ifndef FILTER_H
#define FILTER_H

#ifndef  WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/wxprec.h>
#include "CtrlCell.h"
#include "COutils.h"

enum
{
	CF_UPDATE = wxID_HIGHEST
};

class CFilter : public wxPanel , public COutils
{
public:
							CFilter (wxWindow* Parent);
							~CFilter ();
		wxWindow*			Map;
		CCtrlCell*			Cell;
		wxWindow*			Owner;
		wxBoxSizer*			item0;
		wxStaticBox*		item2;
		wxStaticBoxSizer*	item1;
		wxBoxSizer*			item3;
		wxBoxSizer*			item4;
		wxCheckBox*			item5;
		wxBoxSizer*			item6;
		wxCheckBox*			item7;
		wxBoxSizer*			item8;
		wxTextCtrl*			item9;
		wxStaticBox*		item11;
		wxStaticBoxSizer*	item10;
		wxBoxSizer*			item12;
		wxBoxSizer*			item13;
		wxCheckBox*			item14;
		wxBoxSizer*			item15;
		wxCheckBox*			item16;
		wxBoxSizer*			item17;
		wxTextCtrl*			item18;
		wxStaticBox*		item20;
		wxStaticBoxSizer*	item19;
		wxBoxSizer*			item21;
		wxBoxSizer*			item22;
		wxCheckBox*			item23;
		wxBoxSizer*			item24;
		wxCheckBox*			item25;
		wxCheckBox*			item26;
		wxBoxSizer*			item27;
		wxTextCtrl*			item28;
		wxStaticBoxSizer*	item29;
		wxStaticBox*		item30;
		wxBoxSizer*			item31;
		wxBoxSizer*			item32;
		wxCheckBox*			item33;
		wxBoxSizer*			item34;
		wxCheckBox*			item35;
		wxCheckBox*			item36;
		wxBoxSizer*			item37;
		wxTextCtrl*			item38;
		wxStaticBox*		item40;
		wxStaticBoxSizer*	item39;
		wxBoxSizer*			item41;
		wxBoxSizer*			item42;
		wxCheckBox*			item43;
		wxBoxSizer*			item44;
		wxCheckBox*			item45;
		wxBoxSizer*			item46;
		wxBoxSizer*			item47;
		wxStaticText*		item48;
		wxTextCtrl*			item49;
		wxBoxSizer*			item50;
		wxStaticText*		item51;
		wxTextCtrl*			item52;
		wxBoxSizer*			item53;
		wxButton*			item54;
		void				OnUpdate (wxCommandEvent& event);
		wxDECLARE_EVENT_TABLE();
};

#endif
