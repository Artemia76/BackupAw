// *****************************************************************************
// *                                                                           *
// *                            BACKUPAW : CBot.h                              *
// *                      Represent An ActiveWorld Bot                         *
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
// *   CopyRight 2005-2007 Neophile                                            *
// *   Creation          : 15/05/2005                                          *
// *   Last Modification : 20/04/2014                                          *
// *   Revision          : B                                                   *
// *                                                                           *
// *****************************************************************************

#ifndef CBOT_H
#define CBOT_H

#ifdef VP_BUILD
	#include "VPSDK/VP.h"
#else
	#include <Aw.h>
#endif // VP_BUILD

#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
	#include "wx/wx.h"
#endif

#include "wx/config.h"

#include "Cpasspriv.h"
#include "COutils.h"

enum
{
	CG_RECO=wxID_HIGHEST
};

class CBot : public wxEvtHandler, public COutils
{
	public:

	friend class CCtrlAw;

		bool				Global;			// Mode Global
		bool				CGConAuto;
		bool				CGRecoEna;
		int					CGRecoDelay;	// Temps de Reconnection sur AW
		int					CGRecoRetry;	// Nombres d'essais sur AW
#ifdef VP_BUILD
		wxString			UserName;		// Virtual Paradise User Name
#else
		int					Citoyen;		// Numéro du citoyen
#endif // VP_BUILD

		int					Port;			// Port de l'univers
		int					CGRecoCnt;			// Compteur de tentative de reconnections AW
		int					CGRetente;
		bool				ModeReco;

		wxString			Monde;			// Nom du Monde
		wxString			Nom;			// Nom du Bot
		wxString			PassWord;		// Mot de Passe Citoyen
		wxString			Univers;		// Adresse de l'univers

		void				Connection	(bool pFlag);	// Connection/Deconnection de l'univers
		void				Enter		();	// Entrer/Sortir du monde
		void				Connect		();
		void				Deconnect	();
virtual	void				Update		();
		void				Login_CB	(int pRC);
		void				Enter_CB	(int pRC);
		void				World_Attribute ();
		void				StartDelete	();
		void				StartBuild	();
		void				Tentative	();

		bool				IsOnUniverse();
		bool				IsOnWorld	();
virtual	void				Sauve		();
virtual	void				Charge		();
#ifndef VP_BUILD
		bool				SetInstance			();
		void*				GetInstance			();
#else
		VPInstance			GetInstance			();
#endif // VP_BUILD

static	wxString			GetRCString			(int pRC); // Traduction littérale du reason code

	protected:
							CBot ();		// Constructeur
							~CBot();		// Destructeur
		wxTimer*			m_CGRecoTimer;


		void				OnCGRecoEvent	(wxTimerEvent  & pEvent);

		// Table d'Evenements
		wxDECLARE_EVENT_TABLE();
	private:

		wxConfigBase*		m_Config;

		bool				m_PerteUniv;
		bool				m_PerteMonde;
		bool				m_DemCon;
		bool				m_ConEC;
		bool				m_EntEC;
		bool				m_On_Universe;		// Etat de la connection univers
		bool				m_On_World;			// Etat de la connection au monde
		bool				m_DemDeco;
		bool				m_Visible;			// Etat de la visibilité
		CPassPriv*			m_PassPriv;
#ifdef VP_BUILD
		VPInstance			m_Instance;
#else
		void*				m_Instance;
#endif // VP_BUILD
};

#endif

