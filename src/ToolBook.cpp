// *****************************************************************************
// *                                                                           *
// *                        BACKUPAW : ToolBook.cpp                            *
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

#include "ToolBook.h"

BEGIN_EVENT_TABLE (CToolBook, wxScrolledWindow)
	EVT_NOTEBOOK_PAGE_CHANGED(TB_PAGE_CHANGE, CToolBook::OnPageChange)
END_EVENT_TABLE()

CToolBook::CToolBook(wxWindow* parent): wxScrolledWindow
	(
		parent,
		wxID_ANY,
		wxPoint (0,0),
		wxDefaultSize,
        wxSUNKEN_BORDER| wxTAB_TRAVERSAL
	)
{
	owner = parent;
	SetScrollRate( 8, 8 );
    SetVirtualSize( 800, 800 );
	SizerPrin = new wxBoxSizer(wxVERTICAL);
	Tools = new wxNotebook
		(
			this,
			TB_PAGE_CHANGE,
			wxDefaultPosition,
			wxDefaultSize,
			wxNB_TOP
		);
	SizerPrin->Add (Tools, 1, wxEXPAND);
	Filter = new CFilter (Tools);
	Delete = new CDelete (Tools);
	Build = new CBuild (Tools);
	Modify = new CModify (Tools);

	Tools->AddPage (Filter, _("Filters"));
	Tools->AddPage (Modify, _("Modify"));
	Tools->AddPage (Build, _("Build"));
	Tools->AddPage (Delete, _("Delete"));
	Tools->SetSelection(0);
	SetSizer(SizerPrin);
}

void CToolBook::OnPageChange (wxNotebookEvent& event)
{
	if (event.GetSelection() == 1)
	{
		Modify->MAJ();
	}
}

