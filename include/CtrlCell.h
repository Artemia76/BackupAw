// *****************************************************************************
// *                                                                           *
// *                         BACKUPAW : CtrlCell.h                             *
// *      Contain the project and provide method For backup,transform,...      *
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
// *   Creation          : 29/07/2006                                          *
// *   Last Modification :                                                     *
// *   Revision          : A                                                   *
// *                                                                           *
// *****************************************************************************

#ifndef CTRLCELL_H
#define CTRLCELL_H

#ifndef  WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/wxprec.h>

#include "AwObject.h"
#include "CtrlLog.h"

typedef enum
{
	EXACT_MATCH,
	CONTAINS,
} CellFilter;

typedef enum
{
	CELL_OK,
	CELL_NOT_EXIST,
	CELL_OBJ_NOT_FOUND,
	CELL_OBJ_NOT_EXIST,
	CELL_OBJ_ALREADY_EXIST,
	CELL_BAD_COORD,
	CELL_CIT_NOT_FOUND,
	CELL_INDEX_TOO_BIG,
	CELL_BAD_OBJ_NUM,
	CELL_BAD_FILENAME,
	CELL_BAD_POINTER
} CellRes;

typedef unsigned int uint;

class CCtrlCell
{
	public:
static	CCtrlCell*			Create ();
static	void				Kill ();
		void				DelGrid ();
		void				DelSel ();
		CellRes				AddObj (CObject Obj);
		CellRes				GetObj (CObject& Obj, size_t index=0);
		CellRes				GetObjSel (CObject& Obj, size_t index=0);
		size_t				GetNbObj (int x, int y);
		size_t				GetNbObj ();
		size_t				GetNbSel ();
		CellRes				Update (int* Buffer, int XMax,int YMax,int w, int h);
		CellRes				UpdateSel (int* Buffer, int XMax,int YMax,int w, int h);
		CellRes				DelObj (size_t index=0);
		CellRes				DelObjSel (size_t index=0);
		CellRes				ChangeObj (const CObject& Obj,size_t index=0);
		CellRes				FindObjNum (size_t& index, int ObjNum=0);
		CellRes				SortObj ();
		CellRes				LoadSel ();
		CellRes				SaveSel ();
		CellRes				ChgeCitSel (int CitSrc, int CitDest);
		CellRes				GetCitSel (wxTextCtrl* TxtZone=0);
		CellRes				MoveSel (int x=0, int y=0, int a=0);
		CellRes				RotateSel (int x=0, int y=0, int alpha=0);
		bool				CitFilt;
		bool				CitExcl;
		wxString			CitList;
		bool				ModelFilt;
		bool				ModelExcl;
		wxString			ModelName;
		bool				DescrFilt;
		bool				DescrMatch;
		bool				DescrExcl;
		wxString			DescrName;
		bool				ActionFilt;
		bool				ActionMatch;
		bool				ActionExcl;
		wxString			ActionName;
		bool				RegioFilt;
		bool				RegioExcl;
		int					RegioN;
		int					RegioW;
		int					RegioS;
		int					RegioE;
		wxString			FileName;
		int					RelX;
		int					RelZ;

	private:

static	CCtrlCell*			PtCCtrlCell;

							CCtrlCell ();
							~CCtrlCell ();
		AObject				Cell;
		AObject				Selection;
		CCtrlLog*			Logger;
};

#endif
