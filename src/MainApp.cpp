// *****************************************************************************
// *                                                                           *
// *                        BACKUPAW : MainApp.cpp                             *
// *                        Main Application class                             *
// *                                                                           *
// *****************************************************************************
// * This file is part of BackupAw project.                                    *
// * BackupAw is free software; you can redistribute it and/or modify          *
// * it under the terms of BSD Revision 3 License :                            *
// *                                                                           *
// * Copyright 2020 Neophile                                                   *
// *                                                                           *
// * Redistributionand use in source and binary forms, with or without         *
// * modification, are permitted provided that the following conditions are    *
// * met :                                                                     *
// *                                                                           *
// * 1. Redistributions of source code must retain the above copyright notice, *
// * this list of conditionsand the following disclaimer.                      *
// *                                                                           *
// * 2. Redistributions in binary form must reproduce the above copyright      *
// * notice, this list of conditionsand the following disclaimer in the        *
// * documentation and /or other materials provided with the distribution.     *
// *                                                                           *
// * 3. Neither the name of the copyright holder nor the names of its          *
// * contributors may be used to endorse or promote products derived from this *
// * software without specific prior written permission.                       *
// *                                                                           *
// * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS       *
// * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED *
// * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A           *
// * PARTICULAR PURPOSE ARE DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDER  *
// * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,  *
// * EXEMPLARY, OR CONSEQUENTIAL DAMAGES(INCLUDING, BUT NOT LIMITED TO,        *
// * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR        *
// * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF    *
// * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT                 *
// * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF  *
// * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.         *
// *                                                                           *
// * BackupAW is distributed in the hope that it will be useful,               *
// * but WITHOUT ANY WARRANTY; without even the implied warranty of            *
// * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
// *                                                                           *
// * BackupAW use third part library copyrighted by ActiveWorlds Inc.          *
// * For more details please read attached AW_SDK_License_(aw.dll).txt         *
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

#include "wx/stdpaths.h"
#include "wx/filename.h"

IMPLEMENT_APP(CMainApp)

bool CMainApp::OnInit ()
{
	long lng=-1;
	ConfPath = wxStandardPaths::Get().GetUserLocalDataDir() + wxFileName::GetPathSeparator();
	wxFileName ConfFile = ConfPath + AppName.Lower() + _T(".ini");
	if (!ConfFile.DirExists()) ConfFile.Mkdir(0777, wxPATH_MKDIR_FULL);
	m_Config = new wxFileConfig
		(
			AppName,
			wxEmptyString,
			ConfFile.GetLongPath (),
			wxEmptyString,
			wxCONFIG_USE_LOCAL_FILE
		);
	wxConfigBase::Set(m_Config);
    m_Config->Read (_T("misc/language"),&lng,-1);
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
        m_Config->Write (_T("misc/language"),lng);
        m_Config->Flush ();
    }
    else return false;

    // normally this wouldn't be necessary as the catalog files would be found
    // in the default locations, but when the program is not installed the
    // catalogs are in the build directory where we wouldn't find them by
    // default
#ifdef __WXMAC__
    wxFileName fname(wxTheApp->argv[0]);
    wxString path= fname.GetPath();
    wxLocale::AddCatalogLookupPathPrefix(path + _T("/../Resources/lng/"));
#else
    wxLocale::AddCatalogLookupPathPrefix(_T("./lng/"));
#endif
    // Initialize the catalogs we'll be using
    m_locale.AddCatalog(_T("backup"));

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
	CMainFrame* MainFrame = new CMainFrame ();
	MainFrame->Show (true);
    SetTopWindow(MainFrame);
	return true;
}

int CMainApp::OnExit()
{
    return 0;
}
