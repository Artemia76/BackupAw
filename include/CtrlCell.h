// *****************************************************************************
// *                                                                           *
// *                         BACKUPAW : CtrlCell.h                             *
// *      Contain the project and provide method For backup,transform,...      *
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
// *   Creation          : 29/07/2006                                          *
// *   Last Modification : 20/04/2014                                          *
// *   Revision          : B                                                   *
// *                                                                           *
// *****************************************************************************

#ifndef CTRLCELL_H
#define CTRLCELL_H

#include <vector>

#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/filename.h"
#include "wx/fileconf.h"

#include "AwObject.h"

using namespace std;

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
    CELL_BAD_POINTER,
    CELL_MEMORY_FULL
} CellRes;

typedef unsigned int uint;

class CCtrlCell
{
public:
    static	CCtrlCell* Create();
    static	void				Kill();
    void				DelGrid();
    void				DelSel();
    CellRes				AddObj(CObject pObj);
    CellRes				AddObjSel(CObject pObj);
    CellRes				GetObj(CObject& pObj, size_t pIndex = 0);
    CellRes				UpdateObj(CObject pObj, size_t pIndex = 0);
    CellRes				GetObjSel(CObject& pObj, size_t pIndex = 0);
    CellRes				UpdateObjSel(CObject pObj, size_t pIndex = 0);
    unsigned int		GetNbObj(int pX, int pY);
    unsigned int		GetNbObj();
    unsigned int		GetNbSel();
    CellRes				Update(int* pBuffer, int pXMax, int pYMax, int pWidth, int pHeigh);
    CellRes				UpdateSel(int* pBuffer, int pXMax, int pYMax, int pWidth, int pHeigh);
    CellRes				DelObj(size_t pIndex = 0);
    CellRes				DelObjSel(size_t pIndex = 0);
    CellRes				ChangeObj(const CObject& pObj, size_t pIndex = 0);
    CellRes				FindObjNum(size_t& pIndex, int pObjNum = 0);
    CellRes				SortObj();
    CellRes				LoadSel();
    CellRes				LoadGrid();
    CellRes				SaveSel();
    CellRes				SaveGrid();
    CellRes				ChgeCitSel(int pCitSrc, int pCitDest);
    CellRes				GetCitSel(wxTextCtrl* pTxtZone = 0);
    CellRes				MoveSel(int pX = 0, int pY = 0, int pAlpha = 0);
    CellRes				RotateSel(int pX = 0, int pY = 0, int pAlpha = 0);
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
    wxFileName			FileName;
    double				RelX;
    double				RelZ;
    double				RelY;
    double				RelYaw;

private:

    static	CCtrlCell* m_PtrCCtrlCell;

    CCtrlCell();
    ~CCtrlCell();
    vector<CObject>		m_Cell;
    vector<CObject>		m_Selection;
};

#endif
