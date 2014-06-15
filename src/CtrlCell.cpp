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
// *   Last Modification : 20/04/2014                                          *
// *   Revision          : C                                                   *
// *                                                                           *
// *****************************************************************************

#include "CtrlCell.h"

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
	FileName=_T("");
	RelX=0;
	RelZ=0;
	RelY=0;
	//Selection.reserve (100000);
	//Cell.reserve (100000);
}

//------------------------------------------------------------------------------

CCtrlCell::~CCtrlCell ()
{
}

//------------------------------------------------------------------------------

void CCtrlCell::DelGrid ()
{
	Cell.clear();
}

//------------------------------------------------------------------------------

void CCtrlCell::DelSel ()
{
	Selection.clear();
}

//------------------------------------------------------------------------------

CellRes CCtrlCell::AddObj (CObject Obj)
{
	for (vector<CObject>::iterator i = Cell.begin(); i < Cell.end (); i++)
	{
#ifndef VP_BUILD
		if ((Obj.Number==i->Number)&&(Obj.X==i->X)&&(Obj.Y==i->Y)) return CELL_OBJ_ALREADY_EXIST;
#else
        if (Obj.Number==i->Number)
        {
            UpdateObj(Obj,i - Cell.begin());
            return CELL_OK;
        }
#endif // VP_BUILD
	}
	Cell.push_back(Obj);
	return CELL_OK;

}

//------------------------------------------------------------------------------

CellRes	CCtrlCell::GetObj (CObject& Obj, size_t index)
{
	if (index >= GetNbSel()) return CELL_INDEX_TOO_BIG;
	Obj = Cell [index];
	return CELL_OK;
}

//------------------------------------------------------------------------------

CellRes CCtrlCell::UpdateObj (CObject Obj, size_t index)
{
	if (index >= GetNbObj()) return CELL_INDEX_TOO_BIG;
	Cell [index] = Obj;
	return CELL_OK;
}

//------------------------------------------------------------------------------

CellRes	CCtrlCell::GetObjSel (CObject& Obj, size_t index)
{
	if (index >= GetNbSel()) return CELL_INDEX_TOO_BIG;
	Obj = Selection [index];
	return CELL_OK;
}

//------------------------------------------------------------------------------

unsigned int CCtrlCell::GetNbObj (int x, int y)
{
	unsigned int cnt=0;
	double X,Y;
	for (vector<CObject>::iterator i = Cell.begin(); i < Cell.end (); i++)
	{
		X=i->X/1000;
		Y=i->Z/1000;
		if (((int) (floor (X)) == x ) && ((int) (floor (Y)) == y)) cnt++;
	}
	return cnt;
}

//------------------------------------------------------------------------------

unsigned int CCtrlCell::GetNbObj ()
{
	return (Cell.end()-Cell.begin());
}

//------------------------------------------------------------------------------

unsigned int CCtrlCell::GetNbSel ()
{
	return (Selection.end()-Selection.begin());
}

//------------------------------------------------------------------------------

CellRes	CCtrlCell::DelObj ( size_t index)
{
	if (index >= GetNbObj()) return CELL_INDEX_TOO_BIG;
	Cell.erase (Cell.begin() + index);
	return CELL_OK;
}

//------------------------------------------------------------------------------

CellRes	CCtrlCell::DelObjSel ( size_t index)
{
	if (index >= GetNbSel ()) return CELL_INDEX_TOO_BIG;
	Selection.erase (Selection.begin() + index);
	return CELL_OK;
}

//------------------------------------------------------------------------------

CellRes CCtrlCell::ChangeObj (const CObject& Obj,size_t index)
{
	if (index >= GetNbObj()) return CELL_INDEX_TOO_BIG;
	Cell[index]=Obj;
	return CELL_OK;
}

//------------------------------------------------------------------------------

CellRes CCtrlCell::FindObjNum (size_t& index, int ObjNum)
{
	for (vector<CObject>::iterator i = Cell.begin(); i < Cell.end (); i++)
	{
		if (i->Number==ObjNum)
		{
			index=i-Cell.begin();
			return CELL_OK;
		}
	}
	return CELL_OBJ_NOT_FOUND;
}

//------------------------------------------------------------------------------

CellRes CCtrlCell::SortObj ()
{
	Selection.clear();
	bool FM,FD,FA,FC,FR;
	double x,y;
	int X,Z;
	wxString s;
	for (vector<CObject>::iterator i = Cell.begin(); i < Cell.end (); i++)
	{
		FC=false;
		FM=false;
		FD=false;
		FA=false;
		FR=false;
		x=i->X;
		y=i->Z;
		X=(int)floor(x/1000);
		Z=(int)floor(y/1000);
		if (CitFilt)
		{
			s.Printf(_T("%d"),i->Owner);
			if (CitList==s) FC=true;
			if (CitExcl) FC=!FC;
		}

		if (ModelFilt)
		{
			if (i->Model==ModelName) FM=true;
			if (ModelExcl) FM=!FM;
		}
		if (DescrFilt)
		{
			if (DescrMatch) FD=i->Description==DescrName;
			else FD=i->Description.Contains(DescrName);
			if (DescrExcl) FD=!FD;
		}
		if (ActionFilt)
		{
			if (ActionMatch) FA=i->Action==ActionName;
			else FA=i->Action.Contains(ActionName);
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
				Selection.push_back (*i);
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
	for (vector<CObject>::iterator i = Cell.begin(); i < Cell.end (); i++)
	{
		x=i->X;
		y=i->Z;
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
	for (vector<CObject>::iterator i = Selection.begin(); i < Selection.end (); i++)
	{
		x=i->X;
		y=i->Z;
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
	wxFileConfig* pConfig = new wxFileConfig(_T(""), _T(""), FileName.GetFullPath());
	Selection.clear ();
	pConfig->Read(_T("General/NbObj"), &NbObj, 0);
	pConfig->Read(_T("General/RelX"), &RelX, 0);
	pConfig->Read(_T("General/RelZ"), &RelZ, 0);
	pConfig->Read(_T("General/RelY"), &RelY, 0);
	pConfig->Read(_T("General/RelYAW"), &RelYaw, 0);

	for (int i=0; i < NbObj; i++)
	{
		s=wxString::Format(_T("Objet%i/"),i);
		pConfig->Read(s+_T("Number"),&Obj.Number,0);
		pConfig->Read(s+_T("Owner"),&Obj.Owner,0);
		pConfig->Read(s+_T("BTime"),&Obj.BuildTime,0);
		pConfig->Read(s+_T("X"),&Obj.X,0.0);
		pConfig->Read(s+_T("Y"),&Obj.Y,0.0);
		pConfig->Read(s+_T("Z"),&Obj.Z,0.0);
		pConfig->Read(s+_T("Yaw"),&Obj.Yaw,0.0);
		pConfig->Read(s+_T("Tilt"),&Obj.Tilt,0.0);
		pConfig->Read(s+_T("Roll"),&Obj.Roll,0.0);
		pConfig->Read(s+_T("RotX"),&Obj.RotX,0.0);
		pConfig->Read(s+_T("RotY"),&Obj.RotY,0.0);
		pConfig->Read(s+_T("RotZ"),&Obj.RotZ,0.0);
		pConfig->Read(s+_T("RotR"),&Obj.RotR,0.0);
		pConfig->Read(s+_T("Model"),&Obj.Model,_T(""));
		pConfig->Read(s+_T("Descr"),&Obj.Description,_T(""));
		pConfig->Read(s+_T("Action"),&Obj.Action,_T(""));
#if AW_BUILD>41 || VP_BUILD
#ifdef AW_BUILD
        pConfig->Read(s+_T("ID"),&Obj.ID,0);
#endif
		pConfig->Read(s+_T("Type"),&Obj.Type,0);
		if (Obj.Type>1)
		{
			pConfig->Read(s+_T("Data"),&Obj.Data,_T(""));
		}
#endif
		Selection.push_back (Obj);
	}
	return CELL_OK;
}

//------------------------------------------------------------------------------

CellRes CCtrlCell::LoadGrid ()
{
	wxString s;
	int NbObj;
	CObject Obj;
	if (FileName==_T("")) return CELL_BAD_FILENAME;
	wxFileConfig* pConfig = new wxFileConfig(_T(""), _T(""), FileName.GetFullPath());
	Cell.clear ();
	pConfig->Read(_T("General/NbObj"), &NbObj, 0);
	for (int i=0; i < NbObj; i++)
	{
		s=wxString::Format(_T("Objet%i/"),i);
		pConfig->Read(s+_T("Number"),&Obj.Number,0);
		pConfig->Read(s+_T("Owner"),&Obj.Owner,0);
		pConfig->Read(s+_T("BTime"),&Obj.BuildTime,0);
		pConfig->Read(s+_T("X"),&Obj.X,0.0);
		pConfig->Read(s+_T("Y"),&Obj.Y,0.0);
		pConfig->Read(s+_T("Z"),&Obj.Z,0.0);
		pConfig->Read(s+_T("Yaw"),&Obj.Yaw,0.0);
		pConfig->Read(s+_T("Tilt"),&Obj.Tilt,0.0);
		pConfig->Read(s+_T("Roll"),&Obj.Roll,0.0);
		pConfig->Read(s+_T("RotX"),&Obj.RotX,0.0);
		pConfig->Read(s+_T("RotY"),&Obj.RotY,0.0);
		pConfig->Read(s+_T("RotZ"),&Obj.RotZ,0.0);
		pConfig->Read(s+_T("RotR"),&Obj.RotR,0.0);
		pConfig->Read(s+_T("Model"),&Obj.Model,_T(""));
		pConfig->Read(s+_T("Descr"),&Obj.Description,_T(""));
		pConfig->Read(s+_T("Action"),&Obj.Action,_T(""));
#if AW_BUILD>41 || VP_BUILD
#ifdef AW_BUILD
        pConfig->Read(s+_T("ID"),&Obj.ID,0);
#endif
		pConfig->Read(s+_T("Type"),&Obj.Type,0);
		if (Obj.Type>1)
		{
			pConfig->Read(s+_T("Data"),&Obj.Data,_T(""));
		}
#endif
		Cell.push_back(Obj);
	}
	delete pConfig;
	return CELL_OK;
}

//------------------------------------------------------------------------------

CellRes CCtrlCell::SaveSel ()
{
	wxString s;
	int NbObj=0;
	CObject Obj;
	if (FileName==_T("")) return CELL_BAD_FILENAME;
	wxFileConfig* pConfig = new wxFileConfig(_T(""), _T("") , FileName.GetFullPath());
	NbObj=GetNbSel();
	pConfig->DeleteAll ();
	pConfig->Write(_T("General/NbObj"), NbObj);
	pConfig->Write(_T("General/RelX"), RelX);
	pConfig->Write(_T("General/RelZ"), RelZ);
	pConfig->Write(_T("General/RelY"), RelY);
	pConfig->Write(_T("General/RelYAW"), RelYaw);
	for (vector<CObject>::iterator i = Selection.begin(); i < Selection.end (); i++)
	{
		s=wxString::Format(_T("Objet%i/"),(unsigned int)(i-Selection.begin()));
		pConfig->Write(s+_T("Number"),i->Number);
		pConfig->Write(s+_T("Owner"),i->Owner);
		pConfig->Write(s+_T("BTime"),i->BuildTime);
		pConfig->Write(s+_T("X"),(i->X - RelX));
		pConfig->Write(s+_T("Y"),(i->Y - RelY));
		pConfig->Write(s+_T("Z"),(i->Z - RelZ));
		pConfig->Write(s+_T("Yaw"),i->Yaw);
		pConfig->Write(s+_T("Tilt"),i->Tilt);
		pConfig->Write(s+_T("Roll"),i->Roll);
		pConfig->Write(s+_T("RotX"),i->RotX);
		pConfig->Write(s+_T("RotY"),i->RotY);
		pConfig->Write(s+_T("RotZ"),i->RotZ);
		pConfig->Write(s+_T("RotR"),i->RotR);
		pConfig->Write(s+_T("Model"),i->Model);
		pConfig->Write(s+_T("Descr"),i->Description);
		pConfig->Write(s+_T("Action"),i->Action);
#if AW_BUILD>41 || VP_BUILD
#ifndef VP_BUILD
        pConfig->Write(s+_T("ID"),i->ID);
#endif // VP_BUILD
		if (i->Type>1)
		{
			pConfig->Write(s+_T("Type"),i->Type);
			pConfig->Write(s+_T("Data"),i->Data);
		}
#endif
	}
	pConfig->Flush();
	return CELL_OK;
}

//------------------------------------------------------------------------------

CellRes CCtrlCell::SaveGrid ()
{
	wxString s;
	CObject Obj;
	if (FileName==_T("")) return CELL_BAD_FILENAME;
	wxFileConfig* pConfig = new wxFileConfig(_T(""), _T("") , FileName.GetFullPath());
	pConfig->DeleteAll ();
	pConfig->Write(_T("General/NbObj"), GetNbObj());
	pConfig->Write(_T("General/RelX"), RelX);
	pConfig->Write(_T("General/RelZ"), RelZ);
	pConfig->Write(_T("General/RelY"), RelY);
	pConfig->Write(_T("General/RelYAW"), RelYaw);
	for (vector<CObject>::iterator i = Cell.begin(); i < Cell.end (); i++)
	{
		s=wxString::Format(_T("Objet%i/"),(unsigned int)(i-Cell.begin()));
		pConfig->Write(s+_T("Number"),i->Number);
		pConfig->Write(s+_T("Owner"),i->Owner);
		pConfig->Write(s+_T("BTime"),i->BuildTime);
		pConfig->Write(s+_T("X"),i->X);
		pConfig->Write(s+_T("Y"),i->Y);
		pConfig->Write(s+_T("Z"),i->Z);
		pConfig->Write(s+_T("Yaw"),i->Yaw);
		pConfig->Write(s+_T("Tilt"),i->Tilt);
		pConfig->Write(s+_T("Roll"),i->Roll);
		pConfig->Write(s+_T("RotX"),i->RotX);
		pConfig->Write(s+_T("RotY"),i->RotY);
		pConfig->Write(s+_T("RotZ"),i->RotZ);
		pConfig->Write(s+_T("RotR"),i->RotR);
		pConfig->Write(s+_T("Model"),i->Model);
		pConfig->Write(s+_T("Descr"),i->Description);
		pConfig->Write(s+_T("Action"),i->Action);
#if AW_BUILD>41 || VP_BUILD
#ifdef AW_BUILD
        pConfig->Write(s+_T("ID"),i->ID);
#endif // AW_BUILD
		if (i->Type>1)
		{
			pConfig->Write(s+_T("Type"),i->Type);
			pConfig->Write(s+_T("Data"),i->Data);
		}
#endif
	}
	pConfig->Flush();
	delete pConfig;
	return CELL_OK;
}


//------------------------------------------------------------------------------

CellRes CCtrlCell::ChgeCitSel (int CitSrc, int CitDest)
{
	CellRes Result=CELL_CIT_NOT_FOUND;
	for (vector<CObject>::iterator i = Selection.begin(); i < Selection.end (); i++)
	{
		if ((i->Owner == CitSrc) || (CitSrc<0))
		{
			if (i->Owner != CitDest) i->Owner =CitDest;
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
	for (vector<CObject>::iterator i = Selection.begin(); i < Selection.end (); i++)
	{
		s.Printf(_T("%d"), i->Owner);
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
			for (vector<CObject>::iterator j = Selection.begin(); j < Selection.end (); j++)
			{
				if (j->Owner==rc) Nombre ++;
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
	for (vector<CObject>::iterator i = Selection.begin(); i < Selection.end (); i++)
	{
		i->X+=x;
		i->Z+=y;
		i->Y+=a;
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
    ALPHA=(double)(alpha*(M_PI/180.0));
	for (vector<CObject>::iterator i = Selection.begin(); i < Selection.end (); i++)
	{
		XA=(double)i->Z;
		YA=(double)i->X;
		R=sqrt( pow((XA-XO),2)+pow((YA-YO),2));
		BETA= atan2 ((YA-YO),(XA-XO));
		i->Yaw-=(alpha*10);
		i->Z = (int)(XO+(R * cos(BETA-ALPHA)));
		i->X = (int)(YO+(R * sin(BETA-ALPHA)));
		i->RotR=0;
		i->RotX=0;
		i->RotY=0;
		i->RotZ=0;
	}
	return CELL_OK;
}
