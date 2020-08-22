// *****************************************************************************
// *                                                                           *
// *                          BACKUPAW : Global.h                              *
// *                              Global Var                                   *
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
// *   CopyRight 2005-2007 Neophile                                            *
// *   Creation          : 08/11/2005                                          *
// *   Last Modification : 23/02/2014                                          *
// *   Revision          : C                                                   *
// *                                                                           *
// *****************************************************************************

#ifndef GLOBAL_H
#define GLOBAL_H

#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
	#include "wx/wx.h"
#endif

#include "wx/stdpaths.h"
#include "wx/filename.h"
#include "wx/version.h"

#ifndef VP_BUILD
#include <Aw.h>
static const int Major = 1;
static const int Minor = 6;
static const int Build = 1;
static const wxString Version = wxString::Format(_T("%i.%i.%i"),Major,Minor,Build);
static const wxString AppName = _T("BackupAW");
static const wxString AppRevision = AppName + Version;
#if AW_BUILD<77
static const wxString AppVersion = AppRevision + _T(" For AW 3.6");
#else
	#if AW_BUILD<85
		static const wxString AppVersion = AppRevision + _T(" For AW 4.1");
	#else
        #if AW_BUILD<93
            static const wxString AppVersion = AppRevision + _T(" For AW 4.2");
        #else
			#if AW_BUILD<100
				static const wxString AppVersion = AppRevision + _T(" For AW 5.1");
			#else
				static const wxString AppVersion = AppRevision + _T(" For AW 5.2 or 6.0");
			#endif
        #endif
	#endif
#endif
#else
    #include <VP.h>
	static const wxString AppName = _T("BackupVP");
	static const wxString AppRevision = AppName + _T(" V1.6.2");
    static const wxString AppVersion = AppRevision + _T(" For Virtual Paradise");
#endif // VP_BUILD

static const long LongFileMax = 500000;

static const  int NbLigneMax = 150;

static const  wxString AppLicence = AppVersion
+   _T("\nThis software is under BSD v3 licensed")
+	_T("\nBuild with ") + wxVERSION_STRING
#ifdef VP_BUILD
+   _T(" and VP SDK Version ") + wxString::Format(_T("%i"),VPSDK_VERSION)
#endif
+	_T("\n\nThird Part License Terms:\n")
#ifndef VP_BUILD
+	_T("BACKUPAW use the (c)Activeworlds SDK published for devellopers, then this software depend of the AW terms in the \"AW_SDK_License_(aw.dll).rtf\" file.")
#else
+	_T("BACKUPVP use the Virtual Paradise SDK (c) 2016 Edwin Rijkee. Use BackupVP at your own risk.")
#endif
;

static wxString BackupAW_Website = _T("https://sourceforge.net/projects/backupaw/");
static wxString BackupAW_Forum = _T("https://sourceforge.net/p/backupaw/discussion/?source=navbar");
static wxString BackupAW_Help = _T("https://sourceforge.net/p/backupaw/wiki/Home/");

static wxString ConfPath;

#endif
