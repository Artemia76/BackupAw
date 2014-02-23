// *****************************************************************************
// *                                                                           *
// *                          BACKUPAW : Global.h                              *
// *                              Global Var                                   *
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
// *   CopyRight 2005-2007 Neophile                                            *
// *   Creation          : 08/11/2005                                          *
// *   Last Modification : 23/02/2014                                          *
// *   Revision          : C                                                   *
// *                                                                           *
// *****************************************************************************

#ifndef GLOBAL_H
#define GLOBAL_H


#ifndef  WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/wxprec.h>
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/version.h> 
#include <aw.h>

static const wxString CGRevision = _T("BackupAw V1.5.2");

#if AW_BUILD<77
static const wxString CGVersion = CGRevision + _T(" For AW 3.6");
#else
	#if AW_BUILD<85
		static const wxString CGVersion = CGRevision + _T(" For AW 4.1");
	#else
        #if AW_BUILD<93
            static const wxString CGVersion = CGRevision + _T(" For AW 4.2");
        #else
			#if AW_BUILD<100
				static const wxString CGVersion = CGRevision + _T(" For AW 5.1");
			#else
				static const wxString CGVersion = CGRevision + _T(" For AW 5.2 or 6.0");
			#endif
        #endif
	#endif
#endif

static const long LongFileMax = 500000;

static const  int NbLigneMax = 150;

static const  wxString CGLicence = CGVersion
+   _T("\nThis software is under GPL v2")
+	_T("\nBuild with ") + wxVERSION_STRING
+	_T("\n\nThird Part License Terms:\n")
+	_T("BACKUPAW use the (c)Activeworlds SDK published for devellopers, then this software depend of the AW terms in the \"AW_SDK_License_(aw.dll).rtf\" file.")
;

static wxString BackupAW_Website = _T("https://sourceforge.net/projects/backupaw/");
static wxString BackupAW_Forum = _T("https://sourceforge.net/p/backupaw/discussion/?source=navbar");
static wxString BackupAW_Help = _T("https://sourceforge.net/p/backupaw/wiki/Home/");

static wxString ConfPath;

#endif
