// *****************************************************************************
// *                                                                           *
// *                         BACKUPAW : CtrlLog.h                              *
// *              Controller for logging message and SDK errors                *
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
// *   CopyRight 2005 Neophile                                                 *
// *   Creation          : 29/04/2005                                          *
// *   Last Modification :                                                     *
// *   Revision          : A                                                   *
// *                                                                           *
// *****************************************************************************

#ifndef CTRLLOG_H
#define CTRLLOG_H


#ifndef  WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/wxprec.h>
#include <wx/datetime.h>

class CCtrlLog
{
    private:
static	CCtrlLog*	PtCtrlLog;
        			CCtrlLog	(wxTextCtrl*);
        			~CCtrlLog	();
        wxWindow*	Parent;
        bool		Init;
        wxDateTime	Horloge;
		wxTextCtrl*	FenLog;

	public:
static	CCtrlLog*	Create(wxTextCtrl* LogZone=0);
static	void		Kill();
        int			Log 	(wxString Message=_T(""),wxColour Coul=_T("BLACK"), bool date = false, int Reason=0);
        wxString	RC		(int); // Traduction littérale du reason code
        void		SetLogZone (wxTextCtrl* LogZone=0);
};

#endif

