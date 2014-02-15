// *****************************************************************************
// *                                                                           *
// *                        BACKUPAW : MapCanvas.h                             *
// *                  The Grid Canvas to display project                       *
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

#ifndef MAPCANVAS_H
#define MAPCANVAS_H

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif
#include <wx/wxprec.h>

#include "CtrlLog.h"
#include "CtrlLog.h"
#include "CtrlCell.h"
#include "CFilter.h"
#include "COutils.h"

class CMapCanvas: public wxWindow, public COutils
{
	private:
		wxFrame*	owner;
		CCtrlCell*	CtrlCell;
		CCtrlLog*	Logger;
		int			Tampon [200][200];
		int			Sel [200][200];
		wxCoord		NbCellx;
    	wxCoord		NbCelly;
        wxCoord		MCellx;
        wxCoord		MCelly;
        wxCoord		xbar;
        wxCoord		ybar;
        wxCoord		xori;
        wxCoord		yori;
        bool		CatchGrid;
        bool		SelectGrid;
        long		MouseX;
        long		MouseY;
        int			AOrigX;
        int			AOrigY;
        int			A2OrigX;
        int			A2OrigY;
        int			Larg;
        int			Haut;
        wxColour	GetLevel (size_t Indice=0, size_t Sel=0);
	public:
    				CMapCanvas( wxFrame *parent);
		void		DrawDefault(wxDC& dc);
		int			OrigX;
		int			OrigY;
		bool		BlockScroll;
		bool		BlockSelect;
    	wxCoord		Cell;
    	wxCoord		CellPtX;
    	wxCoord		CellPtY;
    	size_t		NbObjMax;
    	CFilter*	Filter;
    	bool		MapChange;
	protected:
		void		OnPaint (wxPaintEvent& event);
		void		OnSize (wxSizeEvent& event);
		void		OnMouseMove (wxMouseEvent& event);
		void		OnMClickDown (wxMouseEvent& event);
		void		OnMClickUp (wxMouseEvent& event);
		void		OnLClickDown (wxMouseEvent& event);
		void		OnLClickUp (wxMouseEvent& event);
		void		OnEnter (wxMouseEvent& event);
		DECLARE_EVENT_TABLE()
};

#endif
