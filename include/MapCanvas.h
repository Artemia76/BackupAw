// *****************************************************************************
// *                                                                           *
// *                        BACKUPAW : MapCanvas.h                             *
// *                  The Grid Canvas to display project                       *
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
// *   CopyRight 2006 Neophile                                                 *
// *   Creation          : 28/07/2006                                          *
// *   Last Modification : 20/04/2014                                          *
// *   Revision          : B                                                   *
// *                                                                           *
// *****************************************************************************

#ifndef MAPCANVAS_H
#define MAPCANVAS_H

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#ifndef VP_BUILD
    #include "CBackupCtrl.h"
#else
    #include "CBackupVP.h"
#endif // VP_BUILD

#include "CtrlCell.h"
#include "CFilter.h"
#include "COutils.h"

class CMapCanvas: public wxWindow, public COutils
{
	public:
    				CMapCanvas( wxFrame* pParent);
		void		DrawDefault(wxDC& pDC);
    	wxCoord		Cell;
    	wxCoord		CellPtX;
    	wxCoord		CellPtY;
    	size_t		NbObjMax;
    	CFilter*	Filter;
    	bool		MapChange;


		void		ZoomIn ();
		void		ZoomOut ();

	private:
		wxFrame*	m_Owner;
		CCtrlCell*	m_CtrlCell;
		CBackupCtrl* m_BackupCtrl;

		int			m_Tampon [200][200];
		int			m_Sel [200][200];
		wxCoord		m_NbCellx;
    	wxCoord		m_NbCelly;
        wxCoord		m_MCellx;
        wxCoord		m_MCelly;
        wxCoord		m_XBar;
        wxCoord		m_YBar;
        wxCoord		m_XOri;
        wxCoord		m_YOri;
        bool		m_CatchGrid;
        bool		m_SelectGrid;
        long		m_MouseX;
        long		m_MouseY;
        int			m_AOrigX;
        int			m_AOrigY;
        int			m_A2OrigX;
        int			m_A2OrigY;
        int			m_Larg;
        int			m_Haut;
        wxColour	GetLevel (size_t pIndice=0, size_t pSel=0);

	protected:

		void		OnPaint (wxPaintEvent& pEvent);
		void		OnSize (wxSizeEvent& pEvent);
		void		OnMouseMove (wxMouseEvent& pEvent);
		void		OnMClickDown (wxMouseEvent& pEvent);
		void		OnMClickUp (wxMouseEvent& pEvent);
		void		OnLClickDown (wxMouseEvent& pEvent);
		void		OnLClickUp (wxMouseEvent& pEvent);
		void		OnEnter (wxMouseEvent& pEvent);
		void		OnLeave (wxMouseEvent& pEvent);
		void		OnWheel (wxMouseEvent& pEvent);

		wxDECLARE_EVENT_TABLE();
};

#endif
