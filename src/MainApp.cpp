// *****************************************************************************
// *                                                                           *
// *                        BACKUPAW : MainApp.cpp                             *
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
// *   Last Modification : 08/03/2008                                          *
// *   Revision          : B                                                   *
// *                                                                           *
// *****************************************************************************

#include "MainApp.h"
#include "MainFrame.h"
#include "Global.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>

IMPLEMENT_APP(CMainApp)

bool CMainApp::OnInit ()
{
	long lng=-1;
	ConfPath = wxStandardPaths::Get().GetUserLocalDataDir() + wxFileName::GetPathSeparator();
	wxFileName ConfFile = ConfPath + _T("backupaw.ini");
	if (!ConfFile.DirExists()) ConfFile.Mkdir(0777, wxPATH_MKDIR_FULL);
	pConfig = new wxFileConfig
		(
			_T("BackupAw"),
			wxEmptyString,
			ConfFile.GetLongPath (),
			wxEmptyString,
			wxCONFIG_USE_LOCAL_FILE
		);
	wxConfigBase::Set(pConfig);
	pConfig->Read (_T("misc/language"),&lng,-1);
	if ((lng < 0) || (lng >= NB_MAX_LNG))
    {
        lng = wxGetSingleChoiceIndex
              (
                _T("Please choose language:"),
                _T("Language"),
                WXSIZEOF(langNames),
                langNames
              );
    }
	if (( lng >= 0 ) || (lng < NB_MAX_LNG))
    {
        // don't use wxLOCALE_LOAD_DEFAULT flag so that Init() doesn't return
        // false just because it failed to load wxstd catalog
        if ( !m_locale.Init(langIds[lng]) )
        {
            wxLogError(_T("This language is not supported by the system."));
            return false;
        }
        pConfig->Write (_T("misc/language"),lng);
        pConfig->Flush ();
    }
    else return false;

    // normally this wouldn't be necessary as the catalog files would be found
    // in the default locations, but when the program is not installed the
    // catalogs are in the build directory where we wouldn't find them by
    // default
    wxLocale::AddCatalogLookupPathPrefix(_T("./lng/"));

    // Initialize the catalogs we'll be using
    m_locale.AddCatalog(_T("backupaw"));

    // this catalog is installed in standard location on Linux systems and
    // shows that you may make use of the standard message catalogs as well
    //
    // if it's not installed on your system, it is just silently ignored
#ifdef __LINUX__
    {
        wxLogNull noLog;
        m_locale.AddCatalog(_T("fileutils"));
    }
#endif
	CMainFrame* MainFrame = new CMainFrame (m_locale);
	MainFrame->Show (true);
    SetTopWindow(MainFrame);
	return true;
}

int CMainApp::OnExit()
{
    return 0;
}
