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
// *   Last Modification : 07/10/2007                                          *
// *   Revision          : B                                                   *
// *                                                                           *
// *****************************************************************************

#ifndef CBOT_H
#define CBOT_H

#ifndef  WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/wxprec.h>
#include <wx/fileconf.h>

#include "CtrlLog.h"
#include "Cpasspriv.h"
#include "MapCanvas.h"
#include "CtrlCell.h"
#include "COutils.h"

enum
{
	CG_RECO=10300,
	OBJ_TIME
};

class CBot : public wxEvtHandler, public COutils
{
	protected:
// ---------------
// POINTEURS PRIVES
// ---------------

		CPassPriv*		PassPriv;
		wxTimer*		CGRecoTimer;
		wxTimer*		ObjectTimer;
		CCtrlCell*		Cell;
		void*			Instance;

// -----------------
// VARIABLES PRIVEES
// -----------------

// Booléen

		bool			On_Universe;		// Etat de la connection univers
		bool			On_World;			// Etat de la connection au monde
		bool			Visible;			// Etat de la visibilité
		bool			Scanning;
		bool			Survey;
		size_t			DelEC;
		size_t			BuildEC;

// Entiers

		int				sequence[5][5];
		int				CellX;
		int				CellZ;
		int				CellMax;
// Couleur

// ----------------
// METHODES PRIVEES
// ----------------

		void			OnCGRecoEvent	(wxTimerEvent  & event);
		void			OnObjTimer		(wxTimerEvent  & event);

	public:

// -----------------
// POINTEURS PUBLICS
// -----------------

		CCtrlLog*		Logger;		// Pointeur du Logger
		wxFileConfig*	pConfig;
		CMapCanvas*		Map;

// -----------------
// VARIABLES PUBLICS
// -----------------
		bool			Global;			// Mode Global
		bool			CGConAuto;
		bool			CGRecoEna;
		bool			PerteUniv;
		bool			PerteMonde;
		bool			DemCon;
		bool			ConEC;
		bool			EntEC;
		bool			DemDeco;
		bool			ModeReco;
		bool			CTBuild;
		bool			Deleting;
		bool			Building;

		int				CGRecoDelay;	// Temps de Reconnection sur AW
		int				CGRecoRetry;	// Nombres d'essais sur AW
		int				Citoyen;		// Numéro du citoyen
		int				Port;			// Port de l'univers
		int				CGRecoCnt;			// Compteur de tentative de reconnections AW
		int				CGRetente;

		wxString		Monde;			// Nom du Monde
		wxString		Nom;			// Nom du Bot
		wxString		PassWord;		// Mot de Passe Citoyen
		wxString		Univers;		// Adresse de l'univers

// ----------------
// METHODES PUBLICS
// ----------------

// Constructeur et Destructeur
						CBot ();
						~CBot();

// Entiers

		void			Connection	(bool);	// Connection/Deconnection de l'univers
		void			Enter		();	// Entrer/Sortir du monde
		void			Connect		();
		void			Deconnect	();
		void			Scan		();
		bool			IsScanning	();
		bool			IsSurvey	();
virtual	void			Update		();
		void			Login_CB	(int rc);
		void			Enter_CB	(int rc);
		void			Query_CB	(int rc);
		void			Object_CB	(int rc);
		void			Cell_Begin	();
		void			Cell_Object ();
		void			Object_Add	();
		void			Object_Delete ();
		void			World_Attribute ();
		void			StartDelete	();
		void			StartBuild	();
		void			Tentative	();

		bool			IsOnUniverse();
		bool			IsOnWorld	();
virtual	void			Sauve		();
virtual	void			Charge		();

// Tzble d'Evenements

		DECLARE_EVENT_TABLE()
};

#endif

