// *****************************************************************************
// *                                                                           *
// *                           BACKUPAW : About.h                              *
// *                              About Dialog                                 *
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

#ifndef ABOUTBOX_H
#define ABOUTBOX_H

#ifndef  WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/wxprec.h>
#include <wx/fileconf.h>

enum
{
	ID_SB_WXWINDOWS = 10400,
	ID_BTHOME
};


class AboutBox: public wxDialog
{
	public:
						AboutBox
						(
							wxWindow *parent,
							wxFileConfig* fConfig,
							const wxString &title,
							const wxPoint &pos = wxDefaultPosition,
							const wxSize &size = wxDefaultSize,
							long style = wxDEFAULT_DIALOG_STYLE
						);
						~AboutBox ();
	private:
		wxFileConfig*	pConfig;
		wxStaticText	*StaticText;
	protected:
		void			On_lien_site (wxCommandEvent & event);
		void			On_lien_wxwidget (wxCommandEvent & event);
		DECLARE_EVENT_TABLE()
};

#endif

