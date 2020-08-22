// *****************************************************************************
// *                                                                           *
// *                         BACKUPAW : CPasspriv.cpp                          *
// *                Password Encryption for storage in INI file                *
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
// *   CopyRight 2005 Neophile                                                 *
// *   Creation          : 22/04/2005                                          *
// *   Last Modification :                                                     *
// *   Revision          : A                                                   *
// *                                                                           *
// *****************************************************************************

#include "Cpasspriv.h"
#include <math.h>


//------------------------------------------------------------------------------

CPassPriv* CPassPriv::m_PtrCPassPriv = nullptr;

//------------------------------------------------------------------------------

CPassPriv* CPassPriv::Create()
{
	if (!m_PtrCPassPriv) m_PtrCPassPriv = new CPassPriv;
	return m_PtrCPassPriv;
}

//------------------------------------------------------------------------------

void CPassPriv::Kill()
{
	if (m_PtrCPassPriv)
	{
		delete m_PtrCPassPriv;
		m_PtrCPassPriv =nullptr;
	}
}

//------------------------------------------------------------------------------

CPassPriv::CPassPriv()
{
	m_Serial=0x4BAF1FBA; //To Do : Find a better method to generate key like serial or MAC on each OS
	m_Masque[0]= 0x000000FF;
	m_Masque[1]= 0x0000FF00;
	m_Masque[2]= 0x00FF0000;
	m_Masque[3]= 0xFF000000;
	m_Decalage[0]= 0;
	m_Decalage[1]= 8;
	m_Decalage[2]= 16;
	m_Decalage[3]= 24;
}

//------------------------------------------------------------------------------

CPassPriv::~CPassPriv()
{
}

//------------------------------------------------------------------------------
// Crypt

wxString CPassPriv::Code(wxString pMotDePasse)
{
	char buff[3];
	size_t Long= pMotDePasse.Len();
	wxString Resultat;
	int j=0;
	unsigned int temp;
	for (size_t i=0; i<Long; i++)
	{
		temp= pMotDePasse[i];
		temp=temp^((m_Serial& m_Masque[j])>> m_Decalage[j]);
		sprintf(buff,"%02X",temp);
		Resultat << (wxChar) buff[0];
		Resultat << (wxChar) buff[1];
		j++;
		if (j>3) j=0;
	}
	return Resultat;
}

//------------------------------------------------------------------------------
// Uncrypt

wxString CPassPriv::Decode(wxString pMotDePasse)
{
	char buff[3];
	int j=0;
	unsigned int temp;
	wxString Resultat;
	size_t Long= pMotDePasse.Len();
	for (size_t i=0; i<(Long/2); i++)
	{
		buff[0]= pMotDePasse[i*2];
		buff[1]= pMotDePasse[(i*2)+1];
		buff[2]='\0';
		temp=HexToDec(buff);
		Resultat << (wxChar)(temp^((m_Serial&m_Masque[j])>>m_Decalage[j]));
		j++;
		if (j>3) j=0;
	}
	return Resultat;
}


