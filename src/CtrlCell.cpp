// *****************************************************************************
// *                                                                           *
// *                         BACKUPAW : CtrlCell.cpp                           *
// *       Contain the project and provide method For backup,transform,...     *
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
// *   CopyRight 2006-2007 Neophile                                            *
// *   Creation          : 30/07/2006                                          *
// *   Last Modification : 07/10/2007                                          *
// *   Revision          : B                                                   *
// *                                                                           *
// *****************************************************************************

#include "CtrlCell.h"
#include <wx/fileconf.h>

//------------------------------------------------------------------------------
// Class CCtrlCell

CCtrlCell* CCtrlCell::PtCCtrlCell = 0;

CCtrlCell* CCtrlCell::Create()
{
	if (!CCtrlCell::PtCCtrlCell) CCtrlCell::PtCCtrlCell = new CCtrlCell ();
	return CCtrlCell::PtCCtrlCell;
}

//------------------------------------------------------------------------------

void CCtrlCell::Kill()
{
	delete CCtrlCell::PtCCtrlCell;
	CCtrlCell::PtCCtrlCell=0;
}

//------------------------------------------------------------------------------

CCtrlCell::CCtrlCell ()
{
	CitFilt=false;
	CitExcl=false;
	CitList=_T("");
	ModelFilt=false;
	ModelExcl=false;
	ModelName=_T("");
	DescrFilt=false;
	DescrMatch=false;
	DescrExcl=false;
	DescrName=_T("");
	ActionFilt=false;
	ActionMatch=false;
	ActionExcl=false;
	ActionName=_T("");
	RegioFilt=false;
	RegioExcl=false;
	RegioN=0;
	RegioW=0;
	RegioS=0;
	RegioE=0;
	Logger=CCtrlLog::Create ();
	FileName=_T("");
	RelX=0;
	RelZ=0;
}

//------------------------------------------------------------------------------

CCtrlCell::~CCtrlCell ()
{
}

//------------------------------------------------------------------------------

void CCtrlCell::DelGrid ()
{
	Cell.Clear();
}

//------------------------------------------------------------------------------

void CCtrlCell::DelSel ()
{
	Selection.Clear();
}

//------------------------------------------------------------------------------

CellRes CCtrlCell::AddObj (CObject Obj)
{
	for (uint i=0; i < Cell.Count (); i++)
	{
		if ((Obj.Number==Cell[i].Number)&&(Obj.X==Cell[i].X)&&(Obj.Y==Cell[i].Y)) return CELL_OBJ_ALREADY_EXIST;
	}
	Cell.Add (Obj);
	return CELL_OK;
}

//------------------------------------------------------------------------------

CellRes	CCtrlCell::GetObj (CObject& Obj, size_t index)
{
	if (index >= Cell.Count()) return CELL_INDEX_TOO_BIG;
	Obj = Cell [index];
	return CELL_OK;
}

//------------------------------------------------------------------------------

CellRes	CCtrlCell::GetObjSel (CObject& Obj, size_t index)
{
	if (index >= Selection.Count()) return CELL_INDEX_TOO_BIG;
	Obj = Selection [index];
	return CELL_OK;
}

//------------------------------------------------------------------------------

size_t CCtrlCell::GetNbObj (int x, int y)
{
	size_t cnt=0;
	double X,Y;
	for (size_t i=0; i < Cell.Count(); i++)
	{
		X=Cell[i].X/1000;
		Y=Cell[i].Z/1000;
		if (((int) (floor (X)) == x ) && ((int) (floor (Y)) == y)) cnt++;
	}
	return cnt;
}

//------------------------------------------------------------------------------

size_t CCtrlCell::GetNbObj ()
{
	return Cell.Count ();
}

//------------------------------------------------------------------------------

size_t CCtrlCell::GetNbSel ()
{
	return Selection.Count ();
}

//------------------------------------------------------------------------------

CellRes	CCtrlCell::DelObj ( size_t index)
{
	if (index >= Cell.Count()) return CELL_INDEX_TOO_BIG;
	Cell.RemoveAt (index);
	return CELL_OK;
}

//------------------------------------------------------------------------------

CellRes	CCtrlCell::DelObjSel ( size_t index)
{
	if (index >= Selection.Count()) return CELL_INDEX_TOO_BIG;
	Selection.RemoveAt (index);
	return CELL_OK;
}

//------------------------------------------------------------------------------

CellRes CCtrlCell::ChangeObj (const CObject& Obj,size_t index)
{
	if (index >= Cell.Count()) return CELL_INDEX_TOO_BIG;
	Cell[index]=Obj;
	return CELL_OK;
}

//------------------------------------------------------------------------------

CellRes CCtrlCell::FindObjNum (size_t& index, int ObjNum)
{
	for (uint i=0; i<Cell.Count() ; i++)
	{
		if (Cell[i].Number==ObjNum)
		{
			index=i;
			return CELL_OK;
		}
	}
	return CELL_OBJ_NOT_FOUND;
}

//------------------------------------------------------------------------------

CellRes CCtrlCell::SortObj ()
{
	Selection.Clear();
	bool FM,FD,FA,FC,FR;
	double x,y;
	int X,Z;
	wxString s;
	for (uint i=0; i<Cell.Count(); i++)
	{
		FC=false;
		FM=false;
		FD=false;
		FA=false;
		FR=false;
		x=Cell[i].X;
		y=Cell[i].Z;
		X=(int)floor(x/1000);
		Z=(int)floor(y/1000);
		if (CitFilt)
		{
			s.Printf(_T("%d"),Cell[i].Owner);
			if (CitList==s) FC=true;
			if (CitExcl) FC=!FC;
		}

		if (ModelFilt)
		{
			if (Cell[i].Model==ModelName) FM=true;
			if (ModelExcl) FM=!FM;
		}
		if (DescrFilt)
		{
			if (DescrMatch) FD=Cell[i].Description==DescrName;
			else FD=Cell[i].Description.Contains(DescrName);
			if (DescrExcl) FD=!FD;
		}
		if (ActionFilt)
		{
			if (ActionMatch) FA=Cell[i].Action==ActionName;
			else FA=Cell[i].Action.Contains(ActionName);
			if (ActionExcl) FA=!FA;
		}
		if (RegioFilt)
		{
			if
				(
					(X<=RegioW) &&
					(X>=RegioE) &&
					(Z<=RegioN) &&
					(Z>=RegioS)
				)
				FR=true;
			if (RegioExcl) FR=!FR;
		}
		if (FC || FM || FD || FA || FR)
		{
			if
				(
					((!CitFilt) || FC) &&
					((!ModelFilt) || FM) &&
					((!DescrFilt) || FD) &&
					((!ActionFilt) || FA) &&
					((!RegioFilt) || FR)
				)
			{
				Selection.Add (Cell[i]);
			}
		}
	}
	return CELL_OK;
}

//------------------------------------------------------------------------------

CellRes	CCtrlCell::Update (int* Buffer, int XMax,int YMax,int w, int h)
{
	int X,Z;
	int* Pt=0;
	double x,y;
	for (uint i=0; i < Cell.Count(); i++)
	{
		x=Cell[i].X;
		y=Cell[i].Z;
		X=(int)floor(x/1000);
		Z=(int)floor(y/1000);
		if ( (X <= XMax) && (X > (XMax-w)) && (Z <=YMax) && (Z > (YMax-h)))
		{
			Pt=(Buffer+ (((XMax-X)*200) + (YMax-Z)));
			(*Pt)=(*Pt) +1;
		}
	}
	return CELL_OK;
}

//------------------------------------------------------------------------------

CellRes	CCtrlCell::UpdateSel (int* Buffer, int XMax,int YMax,int w, int h)
{
	int X,Z;
	int* Pt=0;
	double x,y;
	for (uint i=0; i < Selection.Count(); i++)
	{
		x=Selection[i].X;
		y=Selection[i].Z;
		X=(int)floor(x/1000);
		Z=(int)floor(y/1000);
		if ( (X <= XMax) && (X > (XMax-w)) && (Z <=YMax) && (Z > (YMax-h)))
		{
			Pt=(Buffer+ (((XMax-X)*200) + (YMax-Z)));
			(*Pt)=(*Pt) +1;
		}
	}
	return CELL_OK;
}

//------------------------------------------------------------------------------

CellRes CCtrlCell::LoadSel ()
{
	wxString s;
	int NbObj;
	CObject Obj;
	if (FileName==_T("")) return CELL_BAD_FILENAME;
	wxFileConfig* pConfig = new wxFileConfig(_T(""), _T(""), FileName);
	wxConfigBase::Set(pConfig);
	Selection.Clear ();
	pConfig->Read(_T("General/NbObj"), &NbObj, 0);
	for (int i=0; i < NbObj; i++)
	{
		s.Printf (_T("Objet%d/"),i);
		pConfig->Read(s+_T("Number"),&Obj.Number,0);
		pConfig->Read(s+_T("Owner"),&Obj.Owner,0);
		pConfig->Read(s+_T("BTime"),&Obj.BuildTime,0);
		pConfig->Read(s+_T("X"),&Obj.X,0);
		pConfig->Read(s+_T("Y"),&Obj.Y,0);
		pConfig->Read(s+_T("Z"),&Obj.Z,0);
		pConfig->Read(s+_T("Yaw"),&Obj.Yaw,0);
		pConfig->Read(s+_T("Tilt"),&Obj.Tilt,0);
		pConfig->Read(s+_T("Roll"),&Obj.Roll,0);
		pConfig->Read(s+_T("Model"),&Obj.Model,_T(""));
		pConfig->Read(s+_T("Descr"),&Obj.Description,_T(""));
		pConfig->Read(s+_T("Action"),&Obj.Action,_T(""));
		#if AW_BUILD>41
        pConfig->Read(s+_T("ID"),&Obj.ID,0);
		pConfig->Read(s+_T("Type"),&Obj.Obj_Type,0);
		if (Obj.Obj_Type>1)
		{
			pConfig->Read(s+_T("Data"),&Obj.DataV4,_T(""));
		}
		#endif
		Selection.Add (Obj);
	}
	return CELL_OK;
}

//------------------------------------------------------------------------------

CellRes CCtrlCell::SaveSel ()
{
	wxString s;
	int NbObj=0;
	CObject Obj;
	if (FileName==_T("")) return CELL_BAD_FILENAME;
	wxFileConfig* pConfig = new wxFileConfig(_T(""), _T("") , FileName);
	wxConfigBase::Set(pConfig);
	NbObj=Selection.Count();
	pConfig->DeleteAll ();
	pConfig->Write(_T("General/NbObj"), NbObj);
	for (int i=0; i < NbObj; i++)
	{
		Obj=Selection.Item (i);
		s.Printf (_T("Objet%d/"),i);
		pConfig->Write(s+_T("Number"),Obj.Number);
		pConfig->Write(s+_T("Owner"),Obj.Owner);
		pConfig->Write(s+_T("BTime"),Obj.BuildTime);
		pConfig->Write(s+_T("X"),(Obj.X - RelX));
		pConfig->Write(s+_T("Y"),Obj.Y);
		pConfig->Write(s+_T("Z"),(Obj.Z - RelZ));
		pConfig->Write(s+_T("Yaw"),Obj.Yaw);
		pConfig->Write(s+_T("Tilt"),Obj.Tilt);
		pConfig->Write(s+_T("Roll"),Obj.Roll);
		pConfig->Write(s+_T("Model"),Obj.Model);
		pConfig->Write(s+_T("Descr"),Obj.Description);
		pConfig->Write(s+_T("Action"),Obj.Action);
		#if AW_BUILD>41
        pConfig->Write(s+_T("ID"),Obj.ID);
		if (Obj.Obj_Type>1)
		{
			pConfig->Write(s+_T("Type"),Obj.Obj_Type);
			pConfig->Write(s+_T("Data"),Obj.DataV4);
		}
		#endif
	}
	pConfig->Flush();
	return CELL_OK;
}

//------------------------------------------------------------------------------

CellRes CCtrlCell::ChgeCitSel (int CitSrc, int CitDest)
{
	CellRes Result=CELL_CIT_NOT_FOUND;
	for (size_t i=0; i < Selection.Count (); i++)
	{
		if ((Selection[i].Owner == CitSrc) || (CitSrc<0))
		{
			if (Selection[i].Owner != CitDest) Selection[i].Owner =CitDest;
			Result=CELL_OK;
		}
	}
	return Result;
}

//------------------------------------------------------------------------------

CellRes CCtrlCell::GetCitSel (wxTextCtrl* TxtZone)
{
	if (TxtZone==0) return CELL_BAD_POINTER;
	TxtZone->Clear ();
	wxArrayString Liste;
	wxString s;
	int rc;
	long Lon;
	int Nombre;
	for (size_t i=0; i < Selection.Count (); i++)
	{
		s.Printf(_T("%d"), Selection[i].Owner);
		rc=Liste.Index (s, false);
		if (rc < 0)
		{
			Liste.Add (s);
		}
	}
	if (Liste.Count () > 0)
	{
		for (size_t i=0; i < Liste.Count (); i++)
		{
			Nombre=0;
			Liste[i].ToLong(&Lon);
			rc=(int)Lon;
			for (size_t j=0; j<Selection.Count (); j++)
			{
				if (Selection[j].Owner==rc) Nombre ++;
			}
			s.Printf(_T("%d"),Nombre);
			TxtZone->AppendText (Liste [i]+_T("\t:")+s+_(" Object(s)\n"));
		}
	}
	else
	{
		TxtZone->AppendText (_("No Objects in Project."));
	}
	return CELL_OK;
}

//------------------------------------------------------------------------------

CellRes CCtrlCell::MoveSel (int x, int y, int a)
{
	for (size_t i=0; i<Selection.Count (); i++)
	{
		Selection[i].X+=x;
		Selection[i].Z+=y;
		Selection[i].Y+=a;
	}
	return CELL_OK;
}

//------------------------------------------------------------------------------

CellRes CCtrlCell::RotateSel (int x, int y, int alpha)
{
    double XO,YO,XA,YA,ALPHA,BETA,R;
    XO=(double)y;
    YO=(double)x;
    wxString s;
    ALPHA=(double)(alpha*(3.1415/180));
	for (size_t i=0; i<Selection.Count (); i++)
	{
		XA=(double)Selection[i].Z;
		YA=(double)Selection[i].X;
		R=sqrt( pow((XA-XO),2)+pow((YA-YO),2));
		BETA= atan2 ((YA-YO),(XA-XO));
		/*if (i==0)
		{
		    s.Printf("Valeur du rayon : %f, XO=%f, Y0=%f,XA=%f,YA=%f,BETA=%f",R,XO,YO,XA,YA,BETA);
		    Logger->Log( s ,"BLACK");
		}*/
		Selection[i].Yaw-=(alpha*10);
		Selection[i].Z = (int)(XO+(R * cos(BETA-ALPHA)));
		Selection[i].X = (int)(YO+(R * sin(BETA-ALPHA)));
	}
	return CELL_OK;
}
