// *****************************************************************************
// *                                                                           *
// *                         BACKUPAW : ToolBook.h                             *
// *      Tab Book for implement Build, Delete ,modifier and filter tabs       *
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

#ifndef TOOLBOOK_H
#define TOOLBOOK_H

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif
#include <wx/notebook.h>

#include "CFilter.h"
#include "CDelete.h"
#include "CBuild.h"
#include "CModify.h"

enum
{
	TB_PAGE_CHANGE=17500
};

class CToolBook: public wxScrolledWindow
{
	private:
		wxWindow*	owner;
		wxBoxSizer*	SizerPrin;
		wxNotebook* Tools;
		void		OnPageChange (wxNotebookEvent& event);
		DECLARE_EVENT_TABLE()
	public:
		CFilter*	Filter;
		CDelete*	Delete;
		CBuild*		Build;
		CModify*	Modify;
   					CToolBook( wxWindow *parent );
};

#endif
