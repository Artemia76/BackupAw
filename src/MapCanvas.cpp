// *****************************************************************************
// *                                                                           *
// *                       BACKUPAW : MapCanvas.cpp                            *
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
// *   Last Modification :                                                     *
// *   Revision          : A                                                   *
// *                                                                           *
// *****************************************************************************

#include "MapCanvas.h"
#include <math.h>
#include "wx/dcbuffer.h"

wxBEGIN_EVENT_TABLE(CMapCanvas, wxWindow)
    EVT_PAINT		(CMapCanvas::OnPaint)
    EVT_SIZE		(CMapCanvas::OnSize)
    EVT_MOTION		(CMapCanvas::OnMouseMove)
    EVT_MIDDLE_DOWN	(CMapCanvas::OnMClickDown)
    EVT_MIDDLE_UP	(CMapCanvas::OnMClickUp)
    EVT_RIGHT_DOWN	(CMapCanvas::OnMClickDown)
    EVT_RIGHT_UP	(CMapCanvas::OnMClickUp)
    EVT_LEFT_DOWN	(CMapCanvas::OnLClickDown)
    EVT_LEFT_UP		(CMapCanvas::OnLClickUp)
	EVT_ENTER_WINDOW(CMapCanvas::OnEnter)
	EVT_LEAVE_WINDOW(CMapCanvas::OnLeave)
	EVT_MOUSEWHEEL	(CMapCanvas::OnWheel)
wxEND_EVENT_TABLE()

//-----------------------------------------------------------------------------

CMapCanvas::CMapCanvas(wxFrame* pParent): wxWindow
	(
		pParent,
		wxID_ANY,
		wxDefaultPosition,
		wxDefaultSize,
        wxSUNKEN_BORDER | wxTAB_TRAVERSAL | wxCLIP_CHILDREN
	)
{
	m_Owner = pParent;
    Cell = 8;
    m_NbCellx = 0;
    m_NbCelly = 0;
	CellPtX = 0;
	CellPtY = 0;
    m_MCellx=0;
    m_MCelly=0;
    m_XBar=0;
    m_YBar=0;
    m_XOri=0;
    m_YOri=0;
	m_A2OrigX=0;
	m_A2OrigY=0;
	NbObjMax=40;
	m_CatchGrid=false;
	m_SelectGrid=false;
    GetSize (&m_Larg, &m_Haut);
    Filter=0;
    m_CtrlCell = CCtrlCell::Create();
	m_BackupCtrl = CBackupCtrl::Create();
	m_BackupCtrl->Map=this;
    //SetHelpText("essai aide");
	MapChange=false;
}

//-----------------------------------------------------------------------------

void CMapCanvas::DrawDefault(wxDC& dc)
{
	wxString dec;
	CObject Obj;
    m_NbCellx = m_Larg /Cell;
	m_NbCelly = m_Haut /Cell;
	dc.SetPen(wxPen(wxColour (127,127,127),0, wxPENSTYLE_SOLID ));
	m_MCellx = static_cast<wxCoord>(floor (static_cast<double>(m_NbCellx)/2));
	m_MCelly = static_cast<wxCoord>(floor (static_cast<double>(m_NbCelly)/2));
	m_XOri = m_BackupCtrl->OrigX + (Cell/2);
	m_YOri = m_BackupCtrl->OrigY + (Cell/2);
	m_XBar = m_MCellx - (((static_cast<int>(floor (static_cast<double>(m_XOri) / Cell))) *Cell)+3- m_BackupCtrl->OrigX);
	m_YBar = m_MCelly - (((static_cast<int>(floor (static_cast<double>(m_YOri) / Cell))) *Cell)+3- m_BackupCtrl->OrigY);
	while ( m_XBar >= Cell) m_XBar-=Cell;
	while ( m_YBar >= Cell) m_YBar-=Cell;
	memset (m_Tampon, 0, sizeof (m_Tampon));
	memset (m_Sel, false , sizeof (m_Sel));
	m_CtrlCell->Update (&m_Tampon[0][0], m_BackupCtrl->OrigX+ m_MCellx, m_BackupCtrl->OrigY+ m_MCelly, m_NbCellx, m_NbCelly);
	m_CtrlCell->UpdateSel (&m_Sel[0][0], m_BackupCtrl->OrigX+ m_MCellx, m_BackupCtrl->OrigY+ m_MCelly, m_NbCellx, m_NbCelly);
	for (int i=0; i< m_NbCellx; i++)
	{
		for (int j=0; j< m_NbCelly; j++)
		{
			dc.SetBrush(wxBrush(GetLevel(m_Tampon[i][j], m_Sel[i][j]), wxBRUSHSTYLE_SOLID));
			dc.DrawRectangle (i*Cell,j*Cell,Cell, Cell);
		}
	}
	dc.SetPen(wxPen(*wxBLUE, 0, wxPENSTYLE_SOLID));
	while (m_XBar < m_NbCellx)
	{
		dc.DrawLine ( m_XBar*Cell, 0 , m_XBar*Cell , m_NbCelly*Cell);
		m_XBar +=8;
	}
	while (m_YBar < m_NbCelly)
	{
		dc.DrawLine ( 0 , m_YBar*Cell , m_NbCellx*Cell , m_YBar*Cell);
		m_YBar +=8;
	}
	if (Filter)
	{
		if (Filter->m_Item43->GetValue())
		{
			wxCoord x1,y1,x2,y2;
			x1=(m_MCellx-(m_CtrlCell->RegioW- m_BackupCtrl->OrigX))*Cell;
			y1=(m_MCelly-(m_CtrlCell->RegioN- m_BackupCtrl->OrigY))*Cell;
			x2=((m_MCellx-(m_CtrlCell->RegioE- m_BackupCtrl->OrigX))*Cell)+Cell+1;
			y2=((m_MCelly-(m_CtrlCell->RegioS- m_BackupCtrl->OrigY))*Cell)+Cell+1;
			if (x1<0) x1=0;
			else if (x1>= m_Larg) x1= m_Larg-1;
			if (x2<0) x2=0;
			else if (x2>= m_Larg) x2= m_Larg-1;
			if (y1<0) y1=0;
			else if (y1>= m_Haut) y1= m_Haut-1;
			if (y2<0) y2=0;
			else if (y2>= m_Haut) y2= m_Haut-1;
			dc.SetPen(wxPen(wxColour (255,0,0),2, wxPENSTYLE_SOLID));
			dc.SetBrush(wxBrush(wxColour(0,0,0), wxBRUSHSTYLE_TRANSPARENT));
			dc.DrawRectangle ( x1 , y1 , x2 - x1, y2 - y1);
		}
	}
	//If Grid Catched by mouse, draw the scan zone
	if (m_CatchGrid || m_BackupCtrl->IsScanning())
	{
		wxCoord x1,y1,x2,y2,DemiScanUp,DemiScanDn;
		DemiScanDn=static_cast<wxCoord>(floor (static_cast<double>(m_BackupCtrl->GetScanSize())/2.0));
		DemiScanUp= m_BackupCtrl->GetScanSize() - DemiScanDn;
		x1=(m_MCellx-DemiScanUp+1)*Cell;
		y1=(m_MCelly-DemiScanUp+1)*Cell;
		x2=(m_MCellx+DemiScanDn+1)*Cell;
		y2=(m_MCelly+DemiScanDn+1)*Cell;
		if (x1<0) x1=0;
		else if (x1>= m_Larg) x1= m_Larg-1;
		if (x2<0) x2=0;
		else if (x2>= m_Larg) x2= m_Larg-1;
		if (y1<0) y1=0;
		else if (y1>= m_Haut) y1= m_Haut-1;
		if (y2<0) y2=0;
		else if (y2>= m_Haut) y2= m_Haut-1;
		dc.SetPen(wxPen(wxColour (0,255,0),2, wxPENSTYLE_SOLID));
		dc.SetBrush(wxBrush(wxColour(0,0,0), wxBRUSHSTYLE_TRANSPARENT));
		dc.DrawRectangle ( x1 , y1 , x2 - x1, y2 - y1);
	}
}

//-----------------------------------------------------------------------------

void CMapCanvas::OnPaint (wxPaintEvent& pEvent)
{
	wxBitmap tmpbmp(m_Larg, m_Haut);
	wxMemoryDC tmpdc;
	tmpdc.SelectObject(tmpbmp);
    DrawDefault (tmpdc);
	tmpdc.SelectObject(wxNullBitmap);
    wxPaintDC dc(this);
	dc.DrawBitmap(tmpbmp,0, 0, false);
	pEvent.Skip();
}

//-----------------------------------------------------------------------------

void CMapCanvas::OnSize (wxSizeEvent& WXUNUSED(pEvent))
{
    GetSize (&m_Larg, &m_Haut);
	Refresh ();
}

//-----------------------------------------------------------------------------

void CMapCanvas::OnMouseMove(wxMouseEvent & pEvent)
{
    wxClientDC dc(this);
    wxPoint pos = pEvent.GetPosition();
    long x = dc.DeviceToLogicalX( pos.x );
    long y = dc.DeviceToLogicalY( pos.y );
    if (m_BackupCtrl->BlockScroll) m_CatchGrid=false;
    if (m_CatchGrid)
    {
		m_BackupCtrl->OrigX = m_AOrigX+((x- m_MouseX)/Cell);
		m_BackupCtrl->OrigY = m_AOrigY+((y- m_MouseY)/Cell);
		if ((m_BackupCtrl->OrigX != m_A2OrigX) || (m_BackupCtrl->OrigY != m_A2OrigY))
		{
			Refresh ();
    		m_A2OrigX = m_BackupCtrl->OrigX;
    		m_A2OrigY = m_BackupCtrl->OrigY;
		}
	}
	if
	(
		(x >=0 ) && ( x <(m_NbCellx * Cell)) &&
		(y >=0 ) && ( y <(m_NbCelly * Cell))
	)
	{
		CellPtX = m_MCellx- static_cast<wxCoord>(floor (static_cast<double>(x / Cell)))+ m_BackupCtrl->OrigX;
		CellPtY = m_MCelly- static_cast<wxCoord>(floor (static_cast<double>(y / Cell)))+ m_BackupCtrl->OrigY;
	}
	wxString Position,Numb;
	Position=CoordToAw(CellPtX*1000,CellPtY*1000);
	int NbTamp=m_Tampon [m_BackupCtrl->OrigX+m_MCellx-CellPtX][(m_BackupCtrl->OrigY+m_MCelly)-CellPtY];
	int NbSel=m_Sel [m_BackupCtrl->OrigX+m_MCellx-CellPtX][(m_BackupCtrl->OrigY+m_MCelly)-CellPtY];
	if (m_Sel) Numb.Printf (_(":Nb of Obj=%d in cell"), NbSel);
	else Numb.Printf (_(":Nb of Obj=%d"), NbTamp);
	m_Owner->SetStatusText ( Position + Numb, 2);
	if (m_SelectGrid && Filter && (!m_BackupCtrl->BlockSelect))
	{
		int x1,x2,y1,y2;
		if (m_AOrigX < CellPtX)
		{
			x1=CellPtX;
			x2=m_AOrigX;
		}
		else
		{
			x2=CellPtX;
			x1=m_AOrigX;
		}
		if (m_AOrigY < CellPtY)
		{
			y1=CellPtY;
			y2=m_AOrigY;
		}
		else
		{
			y2=CellPtY;
			y1=m_AOrigY;
		}
		Filter->m_Item49->SetValue (CoordToAw(x1*1000,y1*1000));
		Filter->m_Item52->SetValue (CoordToAw(x2*1000,y2*1000));
		wxCommandEvent event =0;
		Filter->OnUpdate (event);
	}
	pEvent.Skip();
}

//-----------------------------------------------------------------------------

void CMapCanvas::OnMClickDown (wxMouseEvent& pEvent)
{
    wxClientDC dc(this);
    if (m_SelectGrid) return;
	if (m_BackupCtrl->BlockScroll) return;
    wxPoint pos = pEvent.GetPosition();
    m_MouseX = dc.DeviceToLogicalX( pos.x );
    m_MouseY = dc.DeviceToLogicalY( pos.y );
    m_AOrigX = m_BackupCtrl->OrigX;
    m_AOrigY = m_BackupCtrl->OrigY;
	m_CatchGrid = true;
	pEvent.Skip();
}

//-----------------------------------------------------------------------------

void CMapCanvas::OnLClickDown (wxMouseEvent& pEvent)
{
    wxClientDC dc(this);
    if (m_CatchGrid || m_BackupCtrl->BlockSelect) return;
    m_AOrigX = CellPtX;
	m_AOrigY = CellPtY;
	if (Filter)
	{
		Filter->m_Item43->SetValue (true);
		Filter->m_Item45->SetValue (false);
		Filter->m_Item49->SetValue (CoordToAw(CellPtX*1000,CellPtY*1000));
		Filter->m_Item52->SetValue (CoordToAw(CellPtX*1000,CellPtY*1000));
		wxCommandEvent event=0;
		Filter->OnUpdate (event);
	}
	m_SelectGrid = true;
	pEvent.Skip();
}

//-----------------------------------------------------------------------------

void CMapCanvas::OnMClickUp (wxMouseEvent& pEvent)
{
	m_CatchGrid = false;
	MapChange = true;
	pEvent.Skip();
}

//-----------------------------------------------------------------------------

void CMapCanvas::OnLClickUp (wxMouseEvent& pEvent)
{
	m_SelectGrid = false;
	pEvent.Skip();
}

//-----------------------------------------------------------------------------

void CMapCanvas::OnWheel (wxMouseEvent& pEvent)
{
	if (pEvent.GetWheelRotation() > 0) ZoomIn ();
	else ZoomOut ();
}

//-----------------------------------------------------------------------------

void CMapCanvas::OnEnter (wxMouseEvent& pEvent)
{
	this->SetFocus();
	if (m_CatchGrid && (!pEvent.MiddleIsDown ())) m_CatchGrid = false;
	if (m_SelectGrid && (!pEvent.LeftIsDown ())) m_SelectGrid = false;
	pEvent.Skip();
}

//-----------------------------------------------------------------------------

void CMapCanvas::OnLeave (wxMouseEvent& pEvent)
{
	m_Owner->SetFocus();
	pEvent.Skip();
}


//-----------------------------------------------------------------------------

wxColour CMapCanvas::GetLevel (size_t pIndice, size_t pSel)
{
	size_t Level;
	if (pSel >0) Level = (pSel *100 )/NbObjMax;
	else Level = (pIndice *100 )/NbObjMax;;
	int R,V,B;
	wxString text;
	if (Level==0)
	{
		R=255;
		V=255;
		B=255;
	}
	else if (Level < 20)
	{
		V=0;
		R=0;
		B=static_cast<int>(127+Level * 6.375);
	}
	else if (Level < 40)
	{
		V=0;
		R= static_cast<int>(Level * 12.75);
		B= static_cast<int>(255-(Level * 12.75));
	}
	else if (Level < 100)
	{
		V= static_cast<int>((Level-40) * 4.25);
		R=255;
		B=0;
	}
	else
	{
		V=255;
		R=255;
		B=0;
	}
	if (pSel)
	{
		R=255-R;
		V=255-V;
		B=255-B;
	}
	return wxColour (R,V,B);
}

//------------------------------------------------------------------------------

void	CMapCanvas::ZoomIn ()
{
	if (Cell < 16)
	{
		Cell++;
		Refresh();
	}
}

//------------------------------------------------------------------------------

void	CMapCanvas::ZoomOut ()
{
	if (Cell > 4)
	{
		Cell--;
		Refresh();
	}
}

