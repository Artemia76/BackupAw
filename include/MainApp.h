// *****************************************************************************
// *                                                                           *
// *                         BACKUPAW : MainApp.h                              *
// *                        Main Application class                             *
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
// *                             APPLICATION CLASS                             *
// *                                                                           *
// *****************************************************************************
// *                                                                           *
// *   CopyRight 2006-2008 Neophile                                            *
// *   Creation          : 28/07/2006                                          *
// *   Last Modification : 20/04/2014                                          *
// *   Revision          : C                                                   *
// *                                                                           *
// *****************************************************************************

#ifndef MAINAPP_H
#define MAINAPP_H

#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "wx/intl.h"
#include "wx/fileconf.h"

#define NB_MAX_LNG 3
// language data
static const wxLanguage langIds[] =
{
    wxLANGUAGE_ENGLISH,
    wxLANGUAGE_FRENCH,
    wxLANGUAGE_ITALIAN
};

// note that it makes no sense to translate these strings, they are
// shown before we set the locale anyhow
const wxString langNames[] =
{
    _T("English"),
    _T("French"),
    _T("Italian")
};

wxCOMPILE_TIME_ASSERT( WXSIZEOF(langNames) == WXSIZEOF(langIds),
                       LangArraysMismatch );

class CMainApp : public wxApp
{
	private:
		wxFileConfig*		pConfig;
	public:
		virtual bool		OnInit ();
		virtual int			OnExit();
	protected:
		wxLocale			m_locale;
};

wxDECLARE_APP (CMainApp);

#endif
