// *****************************************************************************
// *                                                                           *
// *                         BACKUPAW : CtrlCell.cpp                           *
// *       Contain the project and provide method For backup,transform,...     *
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
// *   CopyRight 2006-2007 Neophile                                            *
// *   Creation          : 30/07/2006                                          *
// *   Last Modification : 20/04/2014                                          *
// *   Revision          : C                                                   *
// *                                                                           *
// *****************************************************************************

#include "CtrlCell.h"

//------------------------------------------------------------------------------
// Class CCtrlCell

CCtrlCell* CCtrlCell::m_PtrCCtrlCell = 0;

CCtrlCell* CCtrlCell::Create()
{
	if (!CCtrlCell::m_PtrCCtrlCell) CCtrlCell::m_PtrCCtrlCell = new CCtrlCell ();
	return CCtrlCell::m_PtrCCtrlCell;
}

//------------------------------------------------------------------------------

void CCtrlCell::Kill()
{
	delete CCtrlCell::m_PtrCCtrlCell;
	CCtrlCell::m_PtrCCtrlCell =0;
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
}

//------------------------------------------------------------------------------

CCtrlCell::~CCtrlCell ()
{
}

//------------------------------------------------------------------------------

void CCtrlCell::DelGrid ()
{
	m_Cell.clear();
}

//------------------------------------------------------------------------------

void CCtrlCell::DelSel ()
{
	m_Selection.clear();
}

//------------------------------------------------------------------------------

CellRes CCtrlCell::AddObj (CObject pObj)
{
	for (vector<CObject>::iterator i = m_Cell.begin(); i < m_Cell.end (); i++)
	{
#ifndef VP_BUILD
		if ((pObj.Number==i->Number)&&(pObj.X==i->X)&&(pObj.Y==i->Y)) return CELL_OBJ_ALREADY_EXIST;
#else
        if (pObj.Number==i->Number)
        {
            UpdateObj(pObj,i - m_Cell.begin());
            return CELL_OK;
        }
#endif // VP_BUILD
	}
	m_Cell.push_back(pObj);
	return CELL_OK;

}

//------------------------------------------------------------------------------

CellRes	CCtrlCell::GetObj (CObject& pObj, size_t index)
{
	if (index >= GetNbSel()) return CELL_INDEX_TOO_BIG;
	pObj = m_Cell[index];
	return CELL_OK;
}

//------------------------------------------------------------------------------

CellRes CCtrlCell::UpdateObj (CObject pObj, size_t index)
{
	if (index >= GetNbObj()) return CELL_INDEX_TOO_BIG;
	m_Cell[index] = pObj;
	return CELL_OK;
}

//------------------------------------------------------------------------------

CellRes	CCtrlCell::GetObjSel (CObject& pObj, size_t index)
{
	if (index >= GetNbSel()) return CELL_INDEX_TOO_BIG;
	pObj = m_Selection [index];
	return CELL_OK;
}

//------------------------------------------------------------------------------

unsigned int CCtrlCell::GetNbObj (int x, int y)
{
	unsigned int cnt=0;
	double X,Y;
	for (vector<CObject>::iterator i = m_Cell.begin(); i < m_Cell.end (); i++)
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
	return (m_Cell.end()-m_Cell.begin());
}

//------------------------------------------------------------------------------

unsigned int CCtrlCell::GetNbSel ()
{
	return (m_Selection.end()-m_Selection.begin());
}

//------------------------------------------------------------------------------

CellRes	CCtrlCell::DelObj ( size_t index)
{
	if (index >= GetNbObj()) return CELL_INDEX_TOO_BIG;
	m_Cell.erase (m_Cell.begin() + index);
	return CELL_OK;
}

//------------------------------------------------------------------------------

CellRes	CCtrlCell::DelObjSel ( size_t index)
{
	if (index >= GetNbSel ()) return CELL_INDEX_TOO_BIG;
	m_Selection.erase (m_Selection.begin() + index);
	return CELL_OK;
}

//------------------------------------------------------------------------------

CellRes CCtrlCell::ChangeObj (const CObject& pObj,size_t index)
{
	if (index >= GetNbObj()) return CELL_INDEX_TOO_BIG;
	m_Cell[index]= pObj;
	return CELL_OK;
}

//------------------------------------------------------------------------------

CellRes CCtrlCell::FindObjNum (size_t& index, int ObjNum)
{
	for (vector<CObject>::iterator i = m_Cell.begin(); i < m_Cell.end (); i++)
	{
		if (i->Number==ObjNum)
		{
			index=i-m_Cell.begin();
			return CELL_OK;
		}
	}
	return CELL_OBJ_NOT_FOUND;
}

//------------------------------------------------------------------------------

CellRes CCtrlCell::SortObj ()
{
	m_Selection.clear();
	bool FM,FD,FA,FC,FR;
	double x,y;
	int X,Z;
	wxString s;
	for (vector<CObject>::iterator i = m_Cell.begin(); i < m_Cell.end (); i++)
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
				m_Selection.push_back (*i);
			}
		}
	}
	return CELL_OK;
}

//------------------------------------------------------------------------------

CellRes	CCtrlCell::Update (int* pBuffer, int pXMax,int pYMax,int pWidth, int pHeigh)
{
	int X,Z;
	int* Pt=0;
	double x,y;
	for (vector<CObject>::iterator i = m_Cell.begin(); i < m_Cell.end (); i++)
	{
		x=i->X;
		y=i->Z;
		X=(int)floor(x/1000);
		Z=(int)floor(y/1000);
		if ( (X <= pXMax) && (X > (pXMax- pWidth)) && (Z <=pYMax) && (Z > (pYMax- pHeigh)))
		{
			Pt=pBuffer+ ((pXMax-X)*200) + (pYMax-Z);
			(*Pt)=(*Pt) +1;
		}
	}
	return CELL_OK;
}

//------------------------------------------------------------------------------

CellRes	CCtrlCell::UpdateSel (int* pBuffer, int pXMax,int pYMax,int pWidth, int pHeigh)
{
	int X,Z;
	int* Pt=0;
	double x,y;
	for (vector<CObject>::iterator i = m_Selection.begin(); i < m_Selection.end (); i++)
	{
		x=i->X;
		y=i->Z;
		X=(int)floor(x/1000);
		Z=(int)floor(y/1000);
		if ( (X <= pXMax) && (X > (pXMax- pWidth)) && (Z <=pYMax) && (Z > (pYMax- pHeigh)))
		{
			Pt=(pBuffer+ (((pXMax-X)*200) + (pYMax-Z)));
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
	wxFileConfig* Config = new wxFileConfig(_T(""), _T(""), FileName.GetFullPath());
	m_Selection.clear ();
	Config->Read(_T("General/NbObj"), &NbObj, 0);
	Config->Read(_T("General/RelX"), &RelX, 0);
	Config->Read(_T("General/RelZ"), &RelZ, 0);
	Config->Read(_T("General/RelY"), &RelY, 0);
	Config->Read(_T("General/RelYAW"), &RelYaw, 0);

	for (int i=0; i < NbObj; i++)
	{
		s=wxString::Format(_T("Objet%i/"),i);
		Config->Read(s+_T("Number"),&Obj.Number,0);
		Config->Read(s+_T("Owner"),&Obj.Owner,0);
		Config->Read(s+_T("BTime"),&Obj.BuildTime,0);
		Config->Read(s+_T("X"),&Obj.X,0.0);
		Config->Read(s+_T("Y"),&Obj.Y,0.0);
		Config->Read(s+_T("Z"),&Obj.Z,0.0);
		Config->Read(s+_T("Yaw"),&Obj.Yaw,0.0);
		Config->Read(s+_T("Tilt"),&Obj.Tilt,0.0);
		Config->Read(s+_T("Roll"),&Obj.Roll,0.0);
		Config->Read(s+_T("RotX"),&Obj.RotX,0.0);
		Config->Read(s+_T("RotY"),&Obj.RotY,0.0);
		Config->Read(s+_T("RotZ"),&Obj.RotZ,0.0);
		Config->Read(s+_T("RotR"),&Obj.RotR,0.0);
		Config->Read(s+_T("Model"),&Obj.Model,_T(""));
		Config->Read(s+_T("Descr"),&Obj.Description,_T(""));
		Config->Read(s+_T("Action"),&Obj.Action,_T(""));
#if AW_BUILD>41 || VP_BUILD
#ifdef AW_BUILD
		Config->Read(s+_T("ID"),&Obj.ID,0);
#endif
		Config->Read(s+_T("Type"),&Obj.Type,0);
		if (Obj.Type>1)
		{
			Config->Read(s+_T("Data"),&Obj.Data,_T(""));
		}
#endif
		m_Selection.push_back (Obj);
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
	wxFileConfig* Config = new wxFileConfig(_T(""), _T(""), FileName.GetFullPath());
	m_Cell.clear ();
	Config->Read(_T("General/NbObj"), &NbObj, 0);
	for (int i=0; i < NbObj; i++)
	{
		s=wxString::Format(_T("Objet%i/"),i);
		Config->Read(s+_T("Number"),&Obj.Number,0);
		Config->Read(s+_T("Owner"),&Obj.Owner,0);
		Config->Read(s+_T("BTime"),&Obj.BuildTime,0);
		Config->Read(s+_T("X"),&Obj.X,0.0);
		Config->Read(s+_T("Y"),&Obj.Y,0.0);
		Config->Read(s+_T("Z"),&Obj.Z,0.0);
		Config->Read(s+_T("Yaw"),&Obj.Yaw,0.0);
		Config->Read(s+_T("Tilt"),&Obj.Tilt,0.0);
		Config->Read(s+_T("Roll"),&Obj.Roll,0.0);
		Config->Read(s+_T("RotX"),&Obj.RotX,0.0);
		Config->Read(s+_T("RotY"),&Obj.RotY,0.0);
		Config->Read(s+_T("RotZ"),&Obj.RotZ,0.0);
		Config->Read(s+_T("RotR"),&Obj.RotR,0.0);
		Config->Read(s+_T("Model"),&Obj.Model,_T(""));
		Config->Read(s+_T("Descr"),&Obj.Description,_T(""));
		Config->Read(s+_T("Action"),&Obj.Action,_T(""));
#if AW_BUILD>41 || VP_BUILD
#ifdef AW_BUILD
		Config->Read(s+_T("ID"),&Obj.ID,0);
#endif
		Config->Read(s+_T("Type"),&Obj.Type,0);
		if (Obj.Type>1)
		{
			Config->Read(s+_T("Data"),&Obj.Data,_T(""));
		}
#endif
		m_Cell.push_back(Obj);
	}
	delete Config;
	return CELL_OK;
}

//------------------------------------------------------------------------------

CellRes CCtrlCell::SaveSel ()
{
	wxString s;
	int NbObj=0;
	CObject Obj;
	if (FileName==_T("")) return CELL_BAD_FILENAME;
	wxFileConfig* Config = new wxFileConfig(_T(""), _T("") , FileName.GetFullPath());
	NbObj=GetNbSel();
	Config->DeleteAll ();
	Config->Write(_T("General/NbObj"), NbObj);
	Config->Write(_T("General/RelX"), RelX);
	Config->Write(_T("General/RelZ"), RelZ);
	Config->Write(_T("General/RelY"), RelY);
	Config->Write(_T("General/RelYAW"), RelYaw);
	for (vector<CObject>::iterator i = m_Selection.begin(); i < m_Selection.end (); i++)
	{
		s=wxString::Format(_T("Objet%i/"),(unsigned int)(i-m_Selection.begin()));
		Config->Write(s+_T("Number"),i->Number);
		Config->Write(s+_T("Owner"),i->Owner);
		Config->Write(s+_T("BTime"),i->BuildTime);
		Config->Write(s+_T("X"),(i->X - RelX));
		Config->Write(s+_T("Y"),(i->Y - RelY));
		Config->Write(s+_T("Z"),(i->Z - RelZ));
		Config->Write(s+_T("Yaw"),i->Yaw);
		Config->Write(s+_T("Tilt"),i->Tilt);
		Config->Write(s+_T("Roll"),i->Roll);
		Config->Write(s+_T("RotX"),i->RotX);
		Config->Write(s+_T("RotY"),i->RotY);
		Config->Write(s+_T("RotZ"),i->RotZ);
		Config->Write(s+_T("RotR"),i->RotR);
		Config->Write(s+_T("Model"),i->Model);
		Config->Write(s+_T("Descr"),i->Description);
		Config->Write(s+_T("Action"),i->Action);
#if AW_BUILD>41 || VP_BUILD
#ifndef VP_BUILD
        Config->Write(s+_T("ID"),i->ID);
#endif // VP_BUILD
		if (i->Type>1)
		{
			Config->Write(s+_T("Type"),i->Type);
			Config->Write(s+_T("Data"),i->Data);
		}
#endif
	}
	Config->Flush();
	return CELL_OK;
}

//------------------------------------------------------------------------------

CellRes CCtrlCell::SaveGrid ()
{
	wxString s;
	CObject Obj;
	if (FileName==_T("")) return CELL_BAD_FILENAME;
	wxFileConfig* Config = new wxFileConfig(_T(""), _T("") , FileName.GetFullPath());
	Config->DeleteAll ();
	Config->Write(_T("General/NbObj"), GetNbObj());
	Config->Write(_T("General/RelX"), RelX);
	Config->Write(_T("General/RelZ"), RelZ);
	Config->Write(_T("General/RelY"), RelY);
	Config->Write(_T("General/RelYAW"), RelYaw);
	for (vector<CObject>::iterator i = m_Cell.begin(); i < m_Cell.end (); i++)
	{
		s=wxString::Format(_T("Objet%i/"),(unsigned int)(i-m_Cell.begin()));
		Config->Write(s+_T("Number"),i->Number);
		Config->Write(s+_T("Owner"),i->Owner);
		Config->Write(s+_T("BTime"),i->BuildTime);
		Config->Write(s+_T("X"),i->X);
		Config->Write(s+_T("Y"),i->Y);
		Config->Write(s+_T("Z"),i->Z);
		Config->Write(s+_T("Yaw"),i->Yaw);
		Config->Write(s+_T("Tilt"),i->Tilt);
		Config->Write(s+_T("Roll"),i->Roll);
		Config->Write(s+_T("RotX"),i->RotX);
		Config->Write(s+_T("RotY"),i->RotY);
		Config->Write(s+_T("RotZ"),i->RotZ);
		Config->Write(s+_T("RotR"),i->RotR);
		Config->Write(s+_T("Model"),i->Model);
		Config->Write(s+_T("Descr"),i->Description);
		Config->Write(s+_T("Action"),i->Action);
#if AW_BUILD>41 || VP_BUILD
#ifdef AW_BUILD
        Config->Write(s+_T("ID"),i->ID);
#endif // AW_BUILD
		if (i->Type>1)
		{
			Config->Write(s+_T("Type"),i->Type);
			Config->Write(s+_T("Data"),i->Data);
		}
#endif
	}
	Config->Flush();
	delete Config;
	return CELL_OK;
}


//------------------------------------------------------------------------------

CellRes CCtrlCell::ChgeCitSel (int pCitSrc, int pCitDest)
{
	CellRes Result=CELL_CIT_NOT_FOUND;
	for (vector<CObject>::iterator i = m_Selection.begin(); i < m_Selection.end (); i++)
	{
		if ((i->Owner == pCitSrc) || (pCitSrc<0))
		{
			if (i->Owner != pCitDest) i->Owner =pCitDest;
			Result=CELL_OK;
		}
	}
	return Result;
}

//------------------------------------------------------------------------------

CellRes CCtrlCell::GetCitSel (wxTextCtrl* pTxtZone)
{
	if (pTxtZone ==0) return CELL_BAD_POINTER;
	pTxtZone->Clear ();
	wxArrayString Liste;
	wxString s;
	int rc;
	long Lon;
	int Nombre;
	for (vector<CObject>::iterator i = m_Selection.begin(); i < m_Selection.end (); i++)
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
			for (vector<CObject>::iterator j = m_Selection.begin(); j < m_Selection.end (); j++)
			{
				if (j->Owner==rc) Nombre ++;
			}
			s.Printf(_T("%d"),Nombre);
			pTxtZone->AppendText (Liste [i]+_T("\t:")+s+_(" Object(s)\n"));
		}
	}
	else
	{
		pTxtZone->AppendText (_("No Objects in Project."));
	}
	return CELL_OK;
}

//------------------------------------------------------------------------------

CellRes CCtrlCell::MoveSel (int pX, int pY, int pAlpha)
{
	for (vector<CObject>::iterator i = m_Selection.begin(); i < m_Selection.end (); i++)
	{
		i->X+=pX;
		i->Z+=pY;
		i->Y+=pAlpha;
	}
	return CELL_OK;
}

//------------------------------------------------------------------------------

CellRes CCtrlCell::RotateSel (int pX, int pY, int pAlpha)
{
	double XO,YO,XA,YA,ALPHA,BETA,R;
    XO= static_cast<double>(pX);
    YO=static_cast<double>(pY);
    wxString s;
    ALPHA=(double)(pAlpha*(M_PI/180.0));
	for (vector<CObject>::iterator i = m_Selection.begin(); i < m_Selection.end (); i++)
	{
		XA=(double)i->Z;
		YA=(double)i->X;
		R=sqrt( pow((XA-XO),2)+pow((YA-YO),2));
		BETA= atan2 ((YA-YO),(XA-XO));
		i->Yaw-=(pAlpha*10);
		i->Z = (int)(YO+(R * cos(BETA-ALPHA)));
		i->X = (int)(XO+(R * sin(BETA-ALPHA)));
		i->RotR=0;
		i->RotX=0;
		i->RotY=0;
		i->RotZ=0;
	}
	return CELL_OK;
}
