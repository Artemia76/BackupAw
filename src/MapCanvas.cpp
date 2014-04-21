// *****************************************************************************
// *                                                                           *
// *                       BACKUPAW : MapCanvas.cpp                            *
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

#include "MapCanvas.h"
#include <math.h>
#include <wx/dcbuffer.h>

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

CMapCanvas::CMapCanvas(wxFrame* parent): wxWindow
	(
		parent,
		wxID_ANY,
		wxDefaultPosition,
		wxDefaultSize,
        wxSUNKEN_BORDER | wxTAB_TRAVERSAL | wxCLIP_CHILDREN
	)
{
	owner = parent;
    Cell = 8;
    NbCellx = 0;
    NbCelly = 0;
	CellPtX = 0;
	CellPtY = 0;
    MCellx=0;
    MCelly=0;
    xbar=0;
    ybar=0;
    xori=0;
    yori=0;
	A2OrigX=0;
	A2OrigY=0;
	NbObjMax=40;
	CatchGrid=false;
	SelectGrid=false;
    GetSize (&Larg, &Haut);
    Filter=0;
    CtrlCell = CCtrlCell::Create();
	BackupCtrl = CBackupCtrl::Create();
	BackupCtrl->Map=this;
    //SetHelpText("essai aide");
	MapChange=false;
}

//-----------------------------------------------------------------------------

void CMapCanvas::DrawDefault(wxDC& dc)
{
	wxString dec;
	CObject Obj;
    NbCellx = Larg /Cell;
    NbCelly = Haut /Cell;
	dc.SetPen(wxPen(wxColour (127,127,127),0, wxSOLID ));
	MCellx = (wxCoord)floor ((double)NbCellx/2);
	MCelly = (wxCoord)floor ((double)NbCelly/2);
	xori = BackupCtrl->OrigX + (Cell/2);
	yori = BackupCtrl->OrigY + (Cell/2);
	xbar = (MCellx - ((((int)floor ((double)xori / Cell)) *Cell)+3-BackupCtrl->OrigX));
	ybar = (MCelly - ((((int)floor ((double)yori / Cell)) *Cell)+3-BackupCtrl->OrigY));
	while ( xbar >= Cell) xbar-=Cell;
	while ( ybar >= Cell) ybar-=Cell;
	memset (Tampon, 0, sizeof (Tampon));
	memset (Sel, false , sizeof (Sel));
	CtrlCell->Update (&Tampon[0][0],BackupCtrl->OrigX+MCellx, BackupCtrl->OrigY+MCelly, NbCellx, NbCelly);
	CtrlCell->UpdateSel (&Sel[0][0],BackupCtrl->OrigX+MCellx, BackupCtrl->OrigY+MCelly, NbCellx, NbCelly);
	for (int i=0; i<NbCellx; i++)
	{
		for (int j=0; j<NbCelly; j++)
		{
			dc.SetBrush(wxBrush(GetLevel(Tampon[i][j],Sel[i][j]),wxSOLID));
			dc.DrawRectangle (i*Cell,j*Cell,Cell, Cell);
		}
	}
	dc.SetPen(wxPen(*wxBLUE, 0, wxSOLID ));
	while (xbar < NbCellx)
	{
		dc.DrawLine ( xbar*Cell, 0 , xbar*Cell , NbCelly*Cell);
		xbar +=8;
	}
	while (ybar < NbCelly)
	{
		dc.DrawLine ( 0 , ybar*Cell , NbCellx*Cell , ybar*Cell);
		ybar +=8;
	}
	if (Filter)
	{
		if (Filter->item43->GetValue())
		{
			wxCoord x1,y1,x2,y2;
			x1=(MCellx-(CtrlCell->RegioW-BackupCtrl->OrigX))*Cell;
			y1=(MCelly-(CtrlCell->RegioN-BackupCtrl->OrigY))*Cell;
			x2=((MCellx-(CtrlCell->RegioE-BackupCtrl->OrigX))*Cell)+Cell+1;
			y2=((MCelly-(CtrlCell->RegioS-BackupCtrl->OrigY))*Cell)+Cell+1;
			if (x1<0) x1=0;
			else if (x1>=Larg) x1=Larg-1;
			if (x2<0) x2=0;
			else if (x2>=Larg) x2=Larg-1;
			if (y1<0) y1=0;
			else if (y1>=Haut) y1=Haut-1;
			if (y2<0) y2=0;
			else if (y2>=Haut) y2=Haut-1;
			dc.SetPen(wxPen(wxColour (255,0,0),2, wxSOLID ));
			dc.SetBrush(wxBrush(wxColour(0,0,0),wxTRANSPARENT));
			dc.DrawRectangle ( x1 , y1 , x2 - x1, y2 - y1);
		}
	}
}

//-----------------------------------------------------------------------------

void CMapCanvas::OnPaint (wxPaintEvent& event)
{
	wxBitmap tmpbmp(Larg, Haut);
	wxMemoryDC tmpdc;
	tmpdc.SelectObject(tmpbmp);
    DrawDefault (tmpdc);
	tmpdc.SelectObject(wxNullBitmap);
    wxPaintDC dc(this);
	dc.DrawBitmap(tmpbmp,0, 0, false);
	event.Skip();
}

//-----------------------------------------------------------------------------

void CMapCanvas::OnSize (wxSizeEvent& WXUNUSED(event))
{
    GetSize (&Larg, &Haut);
	Refresh ();
}

//-----------------------------------------------------------------------------

void CMapCanvas::OnMouseMove(wxMouseEvent &event)
{
    wxClientDC dc(this);
    wxPoint pos = event.GetPosition();
    long x = dc.DeviceToLogicalX( pos.x );
    long y = dc.DeviceToLogicalY( pos.y );
    if (BackupCtrl->BlockScroll) CatchGrid=false;
    if (CatchGrid)
    {
		BackupCtrl->OrigX = AOrigX+((x-MouseX)/Cell);
		BackupCtrl->OrigY = AOrigY+((y-MouseY)/Cell);
		if ((BackupCtrl->OrigX != A2OrigX) || (BackupCtrl->OrigY != A2OrigY))
		{
			Refresh ();
    		A2OrigX = BackupCtrl->OrigX;
    		A2OrigY = BackupCtrl->OrigY;
		}
	}
	if
	(
		(x >=0 ) && ( x <(NbCellx * Cell)) &&
		(y >=0 ) && ( y <(NbCelly * Cell))
	)
	{
		CellPtX = (MCellx-(wxCoord) floor ((double)(x / Cell)))+BackupCtrl->OrigX;
		CellPtY = (MCelly-(wxCoord) floor ((double)(y / Cell)))+BackupCtrl->OrigY;
	}
	wxString Position,Numb;
	Position=CoordToAw(CellPtX*1000,CellPtY*1000);
	int NbTamp=Tampon [(BackupCtrl->OrigX+MCellx)-CellPtX][(BackupCtrl->OrigY+MCelly)-CellPtY];
	int NbSel=Sel [(BackupCtrl->OrigX+MCellx)-CellPtX][(BackupCtrl->OrigY+MCelly)-CellPtY];
	if (Sel) Numb.Printf (_(":Nb of Obj=%d in project"), NbSel);
	else Numb.Printf (_(":Nb of Obj=%d"), NbTamp);
	owner->SetStatusText ( Position + Numb, 2);
	if (SelectGrid && Filter && (!BackupCtrl->BlockSelect))
	{
		int x1,x2,y1,y2;
		if (AOrigX < CellPtX)
		{
			x1=CellPtX;
			x2=AOrigX;
		}
		else
		{
			x2=CellPtX;
			x1=AOrigX;
		}
		if (AOrigY < CellPtY)
		{
			y1=CellPtY;
			y2=AOrigY;
		}
		else
		{
			y2=CellPtY;
			y1=AOrigY;
		}
		Filter->item49->SetValue (CoordToAw(x1*1000,y1*1000));
		Filter->item52->SetValue (CoordToAw(x2*1000,y2*1000));
		wxCommandEvent event=0;
		Filter->OnUpdate (event);
	}
	event.Skip();
}

//-----------------------------------------------------------------------------

void CMapCanvas::OnMClickDown (wxMouseEvent& event)
{
    wxClientDC dc(this);
    if (SelectGrid) return;
    wxPoint pos = event.GetPosition();
    MouseX = dc.DeviceToLogicalX( pos.x );
    MouseY = dc.DeviceToLogicalY( pos.y );
    AOrigX = BackupCtrl->OrigX;
    AOrigY = BackupCtrl->OrigY;
	CatchGrid = true;
	event.Skip();
}

//-----------------------------------------------------------------------------

void CMapCanvas::OnLClickDown (wxMouseEvent& event)
{
    wxClientDC dc(this);
    if (CatchGrid || BackupCtrl->BlockSelect) return;
    AOrigX = CellPtX;
	AOrigY = CellPtY;
	if (Filter)
	{
		Filter->item43->SetValue (true);
		Filter->item45->SetValue (false);
		Filter->item49->SetValue (CoordToAw(CellPtX*1000,CellPtY*1000));
		Filter->item52->SetValue (CoordToAw(CellPtX*1000,CellPtY*1000));
		wxCommandEvent event=0;
		Filter->OnUpdate (event);
	}
	SelectGrid = true;
	event.Skip();
}

//-----------------------------------------------------------------------------

void CMapCanvas::OnMClickUp (wxMouseEvent& event)
{
	CatchGrid = false;
	MapChange = true;
	event.Skip();
}

//-----------------------------------------------------------------------------

void CMapCanvas::OnLClickUp (wxMouseEvent& event)
{
	SelectGrid = false;
	event.Skip();
}

//-----------------------------------------------------------------------------

void CMapCanvas::OnWheel (wxMouseEvent& event)
{
	if (event.GetWheelRotation() > 0) ZoomIn ();
	else ZoomOut ();
}

//-----------------------------------------------------------------------------

void CMapCanvas::OnEnter (wxMouseEvent& event)
{
	this->SetFocus();
	if (CatchGrid && (!event.MiddleIsDown ())) CatchGrid = false;
	if (SelectGrid && (!event.LeftIsDown ())) SelectGrid = false;
	event.Skip();
}

//-----------------------------------------------------------------------------

void CMapCanvas::OnLeave (wxMouseEvent& event)
{
	owner->SetFocus();
	event.Skip();
}


//-----------------------------------------------------------------------------

wxColour CMapCanvas::GetLevel (size_t Indice, size_t Sel)
{
	size_t Level;
	if (Sel>0) Level = (Sel *100 )/NbObjMax;
	else Level = (Indice *100 )/NbObjMax;;
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
		B=(int)(127+Level * 6.375);
	}
	else if (Level < 40)
	{
		V=0;
		R=(int)(Level * 12.75);
		B=(int)(255-(Level * 12.75));
	}
	else if (Level < 100)
	{
		V=(int)((Level-40) * 4.25);
		R=255;
		B=0;
	}
	else
	{
		V=255;
		R=255;
		B=0;
	}
	if (Sel)
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

