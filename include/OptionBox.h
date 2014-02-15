// *****************************************************************************
// *                                                                           *
// *                        BACKUPAW : OptionBox.h                             *
// *             Dialog Box for editing AW connexion parameters                *
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
// *   Creation          : 28/07/2006                                          *
// *   Last Modification :                                                     *
// *   Revision          : A                                                   *
// *                                                                           *
// *****************************************************************************

#ifndef OPTDIAL_H
#define OPTDIAL_H


#ifndef  WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/wxprec.h>
#include <wx/fileconf.h>
#include <wx/spinctrl.h>

#include "CBot.h"

class COptDial : public wxDialog
{
	private:
		CBot*			Bot;
		wxFileConfig*	pConfig;
		wxBoxSizer*		item0;
		wxBoxSizer*		item1;
		wxStaticText*	item2;
		wxTextCtrl*		item3;
		wxStaticText*	item4;
		wxTextCtrl*		item5;
		wxBoxSizer*		item6;
		wxStaticText*	item7;
		wxTextCtrl*		item8;
		wxStaticText*	item9;
		wxSpinCtrl*		item10;
		wxBoxSizer*		item11;
		wxStaticText*	item12;
		wxTextCtrl*		item13;
		wxStaticText*	item14;
		wxTextCtrl*		item15;
		wxBoxSizer*		item16;
		wxButton*		item17;
		wxButton*		item18;
		wxCheckBox*		item19;
		wxBoxSizer*		item20;
		wxStaticText*	item21;
		wxSpinCtrl*		item22;
		wxStaticText*	item23;
		wxSpinCtrl*		item24;
	public:
						COptDial
						(
							wxWindow *parent,
							CBot* Robot,
							wxFileConfig* fConfig,
							const wxString &title,
							const wxPoint &pos = wxDefaultPosition,
							const wxSize &size = wxDefaultSize,
							long style = wxDEFAULT_DIALOG_STYLE
						);
						~COptDial ();
virtual	bool			Validate();

	protected:
		void			OnOk(wxCommandEvent & event);
		DECLARE_EVENT_TABLE()
};

#endif
