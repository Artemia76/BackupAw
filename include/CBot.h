// *****************************************************************************
// *                                                                           *
// *                            BACKUPAW : CBot.h                              *
// *                      Represent An ActiveWorld Bot                         *
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
// *   CopyRight 2005-2007 Neophile                                            *
// *   Creation          : 15/05/2005                                          *
// *   Last Modification : 20/04/2014                                          *
// *   Revision          : B                                                   *
// *                                                                           *
// *****************************************************************************

#ifndef CBOT_H
#define CBOT_H

#ifdef VP_BUILD
	#include <VP.h>
#else
	#include <Aw.h>
#endif // VP_BUILD

#ifndef  WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/wxprec.h>
#include <wx/config.h>

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
        bool                NeedEvent;
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

		void				Connection	(bool);	// Connection/Deconnection de l'univers
		void				Enter		();	// Entrer/Sortir du monde
		void				Connect		();
		void				Deconnect	();
virtual	void				Update		();
		void				Login_CB	(int rc);
		void				Enter_CB	(int rc);
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

static	wxString			GetRCString			(int); // Traduction littérale du reason code

	protected:
							CBot ();		// Constructeur
							~CBot();		// Destructeur
		wxTimer*			CGRecoTimer;


		void				OnCGRecoEvent	(wxTimerEvent  & event);

		// Table d'Evenements
		wxDECLARE_EVENT_TABLE();
	private:

		wxConfigBase*		pConfig;

		bool				PerteUniv;
		bool				PerteMonde;
		bool				DemCon;
		bool				ConEC;
		bool				EntEC;
		bool				On_Universe;		// Etat de la connection univers
		bool				On_World;			// Etat de la connection au monde
		bool				DemDeco;
		bool				Visible;			// Etat de la visibilité
		CPassPriv*			PassPriv;
#ifdef VP_BUILD
		VPInstance			Instance;
#else
		void*				Instance;
#endif // VP_BUILD
};

#endif

