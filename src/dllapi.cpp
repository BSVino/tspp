/********************************************************************************
 * TS Plus Plus - Server administration utility for The Specialists mod         *
 * Copyright (C) 2003 Jorge "Vino" Rodriguez                                    *
 *                                                                              *
 * This library is free software; you can redistribute it and/or                *
 * modify it under the terms of the GNU Lesser General Public                   *
 * License as published by the Free Software Foundation; either                 *
 * version 2.1 of the License, or (at your option) any later version.           *
 *                                                                              *
 * This library is distributed in the hope that it will be useful,              *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of               *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU            *
 * Lesser General Public License for more details.                              *
 *                                                                              *
 * You should have received a copy of the GNU Lesser General Public             *
 * License along with this library; if not, write to the Free Software          *
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA    *
 *                                                                              *
 * email: jorge12185@hotmail.com                                                *
 * web: http://funkyandfresh.ath.cx                                             *
 * AIM: Skizomaniac                                                             *
 ********************************************************************************/

#include <extdll.h>
#include <sdk_util.h>
#include <cbase.h>
#include <player.h>
#include <pm_defs.h>
#include <com_model.h>
#include <in_buttons.h>

#include <dllapi.h>
#include <meta_api.h>
#include "tspp.h"
#include "ts.h"

extern hudtextparms_t defaultHUD;
extern int weaponsbits;
extern int restrictcode;
extern char restmessage[];
extern const char* wnamearray[];
extern hack_t players[];

void ServerActivate( edict_t *pEdictList, int edictCount, int clientMax )
{
	SERVER_COMMAND ("exec addons/tsplusplus/tspp.cfg\n");
	RETURN_META(MRES_IGNORED);
}

void GameInit( void )
{
	//I know, I know, its stupid, but TS doesn't automatically execute autoexec.cfg.
	SERVER_COMMAND ("exec autoexec.cfg\n");
	RETURN_META(MRES_IGNORED);
}

int Spawn( edict_t *pent )
{
//	LOG_MESSAGE( PLID, "Spawn: %s", STRING(pent->v.netname));

	RETURN_META_VALUE(MRES_IGNORED, 0);
}

void Think( edict_t *pent )
{
//	LOG_CONSOLE( PLID, "Think: %s", STRING(pent->v.netname));

	RETURN_META(MRES_IGNORED);
}

void PM_Move( struct playermove_s *ppmove, qboolean server )
{

	RETURN_META(MRES_IGNORED);
}

void CmdStart( const edict_t *player, const struct usercmd_s *cmd, unsigned int random_seed )
{
	/*
	 * If the player is holding the forward key down, cmd->forwardmove is positive. If backwards is down its 
         * negative. If right, then cmd->sidemove is positive, left negative. If up, cmd->upmove positive, if
	 * down negative.
         *
         * cmd->buttons tells of which buttons are held down, in_buttons.h
         */

	RETURN_META(MRES_IGNORED);
}

void ServerDeactivate( void ) 
{
	RETURN_META(MRES_IGNORED);
}

void PlayerPreThink( edict_t *pEntity ) 
{
//	hack_t hackedict = GETHACKEDICT(pEntity);

/*	if (DEBUG) LOG_CONSOLE(PLID, "pre: %d", GETCURRENTWEAPON(hackedict));

	//Player must be alive!
	if (pEntity->v.deadflag == 0) {	
	    //Returns true if the player has a restricted weapon out
	    if (!((1<<GETCURRENTWEAPON(hackedict)) & weaponsbits)) {
	        if (pEntity->v.button & IN_ATTACK) {

		    tspp_csay(hackedict.pEdict, "You cannot use this restricted weapon!");
        	    pEntity->v.button &= ~IN_ATTACK; //'Release' the attack button.

	        }
	    }
	}
*/
       //If you happen to be a spectator, you are not allowed to spawn!
       if (!strcmp(PLAYER_TEAM(pEntity), "spectator")) {

           if (pEntity->v.button & IN_ATTACK) {

               tspp_csay(pEntity, "You cannot spawn - you are a spectator!\nSit back, relax, and enjoy the show.");
               pEntity->v.button &= ~IN_ATTACK;

           }

       }

	RETURN_META(MRES_IGNORED);
}

void PlayerPostThink( edict_t *pEntity )
{
	//hack_t pHack = players[ppmove->player_index];

/*
	if (pEntity->v.deadflag == DEAD_SPECTATOR) {

	    if (pEntity->v.dmg_inflictor) {

		if (strstr(STRING(pEntity->v.netname), "Bud")) {

		    if (pEntity->v.dmg_inflictor->v.owner) {
			SET_VIEW(pEntity, pEntity->v.dmg_inflictor->v.owner);
		    } else {
			SET_VIEW(pEntity, pEntity->v.dmg_inflictor);
		    }
		}

	    }

	} else {

	    SET_VIEW(pEntity, pEntity);

	}
*/
	RETURN_META(MRES_IGNORED);
}

void PlayerPostThink_Post( edict_t *pEntity ) 
{

            //LOG_CONSOLE(PLID, "Dead: %s %d", STRING(pEntity->v.netname), pEntity->v.deadflag);

	RETURN_META(MRES_IGNORED);
}

void StartFrame( void ) {
	RETURN_META(MRES_IGNORED);
}

void StartFrame_Post( void )
{
	RETURN_META(MRES_IGNORED);
}

void PlayerConnect(edict_t *pEntity, const char *pszName, const char *pszAddress)
{
	RETURN_META(MRES_IGNORED);
}

qboolean ClientConnect_Post(edict_t *pEntity, const char *pszName, const char *pszAddress, char szRejectReason[ 128 ] ) {

       CLIENT_PRINTF( pEntity, print_console, "---------------------------------------------------------------\n\n" );
       CLIENT_PRINTF( pEntity, print_console, UTIL_VarArgs("This server is running TS++ %s!\n", VVERSION) );

       char restbuf[200];
       *restbuf = '\0';
       char unrestbuf[200];
       *unrestbuf = '\0';

       if (restrictcode == RESTRICT_ALL) {
           CLIENT_PRINTF( pEntity, print_console, "All weapons are currently restricted! FU FIGHT!\n");
       }

       if (restrictcode == RESTRICT_PISTOLS) {
           CLIENT_PRINTF( pEntity, print_console, "Weapons are currently restricted to pistols only.\n");
       }

       if (restrictcode == RESTRICT_SHOTGUNS) {
           CLIENT_PRINTF( pEntity, print_console, "Weapons are currently restricted to shotguns only.\n");
       }

       if (restrictcode == RESTRICT_RIFLES) {
           CLIENT_PRINTF( pEntity, print_console, "Weapons are currently restricted to rifles only.\n");
       }

       if (restrictcode == RESTRICT_SMGS) {
           CLIENT_PRINTF( pEntity, print_console, "Weapons are currently restricted to SMGs only.\n");
       }

       if (restrictcode == RESTRICT_KNIVES) {
           CLIENT_PRINTF( pEntity, print_console, "Weapons are currently restricted to knives only.\n");
       }

       if (restrictcode == RESTRICT_CUSTOM) {

           CLIENT_PRINTF( pEntity, print_console, "Custom weapon restrictions are currently in effect:\n");
            for (int i = 0; i < TS_MAXWEAPONS; i++) {

               //Dont list kung fu or "?"
               if (i == 0 || i == 2) {
                   continue;
               }

               if (weaponsbits & (1<<i)) {
                   sprintf(unrestbuf + strlen(unrestbuf), "%s ", wnamearray[i]);
               } else {
                   sprintf(restbuf + strlen(restbuf), "%s ", wnamearray[i]);
               }
           }

           CLIENT_PRINTF( pEntity, print_console, UTIL_VarArgs("Restricted weapons: %s\n", restbuf));
           CLIENT_PRINTF( pEntity, print_console, UTIL_VarArgs("Unrestricted weapons: %s\n", unrestbuf));
       }

       if (DESPERADO) {

           CLIENT_PRINTF( pEntity, print_console, "Desperado mode is on! You will not be allowed to buy ammo.\n");

       }

       if (DEBUG || DEBUG2) {

           CLIENT_PRINTF( pEntity, print_console, "Plugin is in debug mode.\n");

       }

       CLIENT_PRINTF( pEntity, print_console, "\n---------------------------------------------------------------\n" );

       if (FORCESPEC) {
           CLIENT_COMMAND( pEntity, "model spectator" );
           RETURN_META_VALUE(MRES_HANDLED, TRUE);
       }

        RETURN_META_VALUE(MRES_IGNORED, TRUE);
 }

BOOL 
ClientConnect( edict_t *pEntity, const char *pszName, const char 
*pszAddress, char szRejectReason[ 128 ]  )
{
	RETURN_META_VALUE(MRES_IGNORED, TRUE);
}

void ClientPutInServer( edict_t *pEntity ) 
{

	if (!strcmp( restmessage, "You have bought a restricted weapon!" )) {
            tspp_csay(pEntity, "Weapon restrictions are on!");
	} else {
	    tspp_csay(pEntity, restmessage);
	}

	int i = g_engfuncs.pfnIndexOfEdict(pEntity)-1;

	players[i].taken	= true;
	players[i].pEdict	= pEntity;
	players[i].fperson	= false;
	players[i].weapons	= 0;
	players[i].plrid	= i;

	RETURN_META(MRES_IGNORED);
}

void ClientDisconnect( edict_t *pEntity ) 
{
	int i = g_engfuncs.pfnIndexOfEdict(pEntity)-1;
	players[i].taken = false;
	
	RETURN_META(MRES_IGNORED);
}

void ClientUserInfoChanged( edict_t *pEntity, char *infobuffer ) 
{

        int indexOfEdict = g_engfuncs.pfnIndexOfEdict(pEntity)-1;

        //This should take care of the mother fuckers who go "model Gordon" and then show up as the enemy in your
        //crosshair. It converts the model to all-lowercase.
        g_engfuncs.pfnSetClientKeyValue(indexOfEdict, infobuffer, "model",
                UTIL_lcase(g_engfuncs.pfnInfoKeyValue(infobuffer, "model")) );
	
	RETURN_META(MRES_IGNORED);

}

void ClientCommand( edict_t *pEntity )
{

	hack_t hackedict = GETHACKEDICT(pEntity);

	//LOG_CONSOLE(PLID, "pid: %d", g_engfuncs.pfnIndexOfEdict(pEntity)-1);

	//Client sent the thirdperson command!
	if (!strcmp(CMD_ARGV(0), "thirdperson")) {

	    //Now is our chance to spring into action!
	    if (GETINFIRST(hackedict)) {
		GETINFIRST(hackedict) = false;
	    } else {
		GETINFIRST(hackedict) = true;
	    }

	}

	//Client sent teh command to switch to a weapon.
	if (strstr(CMD_ARGV(0), "weapon_")) {

	    const char errstr[] = "This weapon is restricted!";
            const char* cmdbuf = CMD_ARGV(0)+7;	//Place the pointer at the part up to the weapon number

	//Before I made this I had a little case of 'case' errors (hehe)
	//For weapons that number above nine, they have two digits, and
	//So are handled inside the big 'switch's case '1'. Looks like this:
	//switch {
	//case '1':
	//  switch {
	//  case '1':	//This is actually weapon 11.
	//  case '2':	//Weapon 12
	//  }
	//case '2':
	//  switch {
	//  case '\0':	//Weapon 2 (trailing '\0')
	//  case '2':	//Weapon 22
	//  }
	//}
	    switch(cmdbuf[0]) {

	    case '0':
		//It's allways okay to switch to fu.
		break;

	    case '1':

		switch(cmdbuf[1]) {
		case '\0':

		    if (!(weaponsbits & TS_WEAPON_GLOCK_18_BIT)) {
		        tspp_csay(pEntity, errstr);
		    }
		    break;

	        case '0':
		    if (!(weaponsbits & TS_WEAPON_AKIMBO_MK23_BIT)) {
		        tspp_csay(pEntity, errstr);
		    }
 		    break;

	        case '1':
		    if (!(weaponsbits & TS_WEAPON_USAS_12_BIT)) {
		        tspp_csay(pEntity, errstr);
		    }
 		    break;

	        case '2':
		    if (!(weaponsbits & TS_WEAPON_DESERT_EAGLE_BIT)) {
		        tspp_csay(pEntity, errstr);
		    }
 		    break;

	        case '3':
		    if (!(weaponsbits & TS_WEAPON_AK47_BIT)) {
		        tspp_csay(pEntity, errstr);
		    }
 		    break;

	        case '4':
		    if (!(weaponsbits & TS_WEAPON_FIVE_SEVEN_BIT)) {
		        tspp_csay(pEntity, errstr);
		    }
 		    break;

	        case '5':
		    if (!(weaponsbits & TS_WEAPON_STEYR_AUG_BIT)) {
		        tspp_csay(pEntity, errstr);
		    }
 		    break;

	        case '6':
		    if (!(weaponsbits & TS_WEAPON_AKIMBO_MINI_UZIS_BIT)) {
		        tspp_csay(pEntity, errstr);
		    }
 		    break;

	        case '7':
		    if (!(weaponsbits & TS_WEAPON_STEYR_TMP_BIT)) {
		        tspp_csay(pEntity, errstr);
		    }
 		    break;

	        case '8':
		    if (!(weaponsbits & TS_WEAPON_BARRET_M82A1_BIT)) {
		        tspp_csay(pEntity, errstr);
		    }
 		    break;

	        case '9':
		    if (!(weaponsbits & TS_WEAPON_H_K_PDW_BIT)) {
		        tspp_csay(pEntity, errstr);
		    }
 		    break;

		default:
		    //Somethin's screwy here...
		    break;

		}
		break;

	    case '2':
		switch (cmdbuf[1]) {
		case '\0':
		    //This weapon don't exist!! Bunk, I tell you!
		    break;

	        case '0':
		    if (!(weaponsbits & TS_WEAPON_SPAS_12_BIT)) {
		        tspp_csay(pEntity, errstr);
		    }
 		    break;

	        case '1':
		    if (!(weaponsbits & TS_WEAPON_GOLDEN_COLTS_BIT)) {
		        tspp_csay(pEntity, errstr);
		    }
 		    break;

	        case '2':
		    if (!(weaponsbits & TS_WEAPON_GLOCK_20_BIT)) {
		        tspp_csay(pEntity, errstr);
		    }
 		    break;

	        case '3':
		    if (!(weaponsbits & TS_WEAPON_MAC_10_BIT)) {
		        tspp_csay(pEntity, errstr);
		    }
 		    break;

	        case '4':
		    if (!(weaponsbits & TS_WEAPON_M61_FRAG_GRENADE_BIT)) {
		        tspp_csay(pEntity, errstr);
		    }
 		    break;

	        case '5':
	            if (!(weaponsbits & TS_WEAPON_KNIFE_BIT)) {
		        tspp_csay(pEntity, errstr);
		    }
 		    break;

		default:
		    //Somethin's screwy here...
		    break;

		}
		break;

	    case '3':
		if (!(weaponsbits & TS_WEAPON_MINI_UZI_BIT)) {
		    tspp_csay(pEntity, errstr);
		}
 		break;

	    case '4':
		if (!(weaponsbits & TS_WEAPON_BENELLI_M3_BIT)) {
		    tspp_csay(pEntity, errstr);
		}
 		break;

	    case '5':
		if (!(weaponsbits & TS_WEAPON_M4A1_BIT)) {
		    tspp_csay(pEntity, errstr);
		}
 		break;

	    case '6':
		if (!(weaponsbits & TS_WEAPON_MP5SD_BIT)) {
		    tspp_csay(pEntity, errstr);
		}
 		break;

	    case '7':
		if (!(weaponsbits & TS_WEAPON_MP5K_BIT)) {
		    tspp_csay(pEntity, errstr);
		}
 		break;

	    case '8':
		if (!(weaponsbits & TS_WEAPON_AKIMBO_BERETTAS_BIT)) {
		    tspp_csay(pEntity, errstr);
		}
 		break;

	    case '9':
		if (!(weaponsbits & TS_WEAPON_SOCOM_MK23_BIT)) {
		    tspp_csay(pEntity, errstr);
		}
 		break;

	    default:
		//Somethin's screwy here...
		break;

	    }

	    RETURN_META(MRES_IGNORED);

	}

	//Client sent a command to buy a weapon! Time to RESTRICT MOTHER FUCKERS!
	if (strstr(CMD_ARGV(0), "takew_")) {

            const char* cmdbuf = CMD_ARGV(0)+6;	//Place the pointer at the part up to the weapon number

	//Before I made this I had a little case of 'case' errors (hehe)
	//For weapons that number above nine, they have two digits, and
	//So are handled inside the big 'switch's case '1'. Looks like this:
	//switch {
	//case '1':
	//  switch {
	//  case '1':	//This is actually weapon 11.
	//  case '2':	//Weapon 12
	//  }
	//case '2':
	//  switch {
	//  case '_':	//Weapon 2 (trailing '_')
	//  case '2':	//Weapon 22
	//  }
	//}
	    switch(cmdbuf[0]) {

	    case '0':
		//WTF?!? He bought kung fu?!?
		break;

	    case '1':

		switch(cmdbuf[1]) {
		case '_':

		    if (!(weaponsbits & TS_WEAPON_GLOCK_18_BIT)) {
		        tspp_csay(pEntity, restmessage);
		        RETURN_META(MRES_SUPERCEDE);
		    } else {
			GETCURRENTWEAPON(hackedict) = TS_WEAPON_GLOCK_18;
			GETAVAILWEAPONS(hackedict) &= TS_WEAPON_GLOCK_18_BIT;
		    }
		    break;

	        case '0':
		    if (!(weaponsbits & TS_WEAPON_AKIMBO_MK23_BIT)) {
		        tspp_csay(pEntity, restmessage);
		        RETURN_META(MRES_SUPERCEDE);
		    } else {
                        GETCURRENTWEAPON(hackedict) = TS_WEAPON_AKIMBO_MK23;
                        GETAVAILWEAPONS(hackedict) &= TS_WEAPON_AKIMBO_MK23_BIT;
                    }
		    break;

	        case '1':
		    if (!(weaponsbits & TS_WEAPON_USAS_12_BIT)) {
		        tspp_csay(pEntity, restmessage);
		        RETURN_META(MRES_SUPERCEDE);
		    } else {
                        GETCURRENTWEAPON(hackedict) = TS_WEAPON_USAS_12;
                        GETAVAILWEAPONS(hackedict) &= TS_WEAPON_USAS_12_BIT;
                    }
		    break;

	        case '2':
		    if (!(weaponsbits & TS_WEAPON_DESERT_EAGLE_BIT)) {
		        tspp_csay(pEntity, restmessage);
		        RETURN_META(MRES_SUPERCEDE);
		    } else {
                        GETCURRENTWEAPON(hackedict) = TS_WEAPON_DESERT_EAGLE;
                        GETAVAILWEAPONS(hackedict) &= TS_WEAPON_DESERT_EAGLE_BIT;
                    }
		    break;

	        case '3':
		    if (!(weaponsbits & TS_WEAPON_AK47_BIT)) {
		        tspp_csay(pEntity, restmessage);
		        RETURN_META(MRES_SUPERCEDE);
		    } else {
                        GETCURRENTWEAPON(hackedict) = TS_WEAPON_AK47;
                        GETAVAILWEAPONS(hackedict) &= TS_WEAPON_AK47_BIT;
                    }
		    break;

	        case '4':
		    if (!(weaponsbits & TS_WEAPON_FIVE_SEVEN_BIT)) {
		        tspp_csay(pEntity, restmessage);
		        RETURN_META(MRES_SUPERCEDE);
		    } else {
                        GETCURRENTWEAPON(hackedict) = TS_WEAPON_FIVE_SEVEN;
                        GETAVAILWEAPONS(hackedict) &= TS_WEAPON_FIVE_SEVEN_BIT;
                    }
		    break;

	        case '5':
		    if (!(weaponsbits & TS_WEAPON_STEYR_AUG_BIT)) {
		        tspp_csay(pEntity, restmessage);
		        RETURN_META(MRES_SUPERCEDE);
		    } else {
                        GETCURRENTWEAPON(hackedict) = TS_WEAPON_STEYR_AUG;
                        GETAVAILWEAPONS(hackedict) &= TS_WEAPON_STEYR_AUG_BIT;
                    }
		    break;

	        case '6':
		    if (!(weaponsbits & TS_WEAPON_AKIMBO_MINI_UZIS_BIT)) {
		        tspp_csay(pEntity, restmessage);
		        RETURN_META(MRES_SUPERCEDE);
		    } else {
                        GETCURRENTWEAPON(hackedict) = TS_WEAPON_AKIMBO_MINI_UZIS;
                        GETAVAILWEAPONS(hackedict) &= TS_WEAPON_AKIMBO_MINI_UZIS_BIT;
                    }
		    break;

	        case '7':
		    if (!(weaponsbits & TS_WEAPON_STEYR_TMP_BIT)) {
		        tspp_csay(pEntity, restmessage);
		        RETURN_META(MRES_SUPERCEDE);
		    } else {
                        GETCURRENTWEAPON(hackedict) = TS_WEAPON_STEYR_TMP;
                        GETAVAILWEAPONS(hackedict) &= TS_WEAPON_STEYR_TMP_BIT;
                    }
		    break;

	        case '8':
		    if (!(weaponsbits & TS_WEAPON_BARRET_M82A1_BIT)) {
		        tspp_csay(pEntity, restmessage);
		        RETURN_META(MRES_SUPERCEDE);
		    } else {
                        GETCURRENTWEAPON(hackedict) = TS_WEAPON_BARRET_M82A1;
                        GETAVAILWEAPONS(hackedict) &= TS_WEAPON_BARRET_M82A1_BIT;
                    }
		    break;

	        case '9':
		    if (!(weaponsbits & TS_WEAPON_H_K_PDW_BIT)) {
		        tspp_csay(pEntity, restmessage);
		        RETURN_META(MRES_SUPERCEDE);
		    } else {
                        GETCURRENTWEAPON(hackedict) = TS_WEAPON_H_K_PDW;
                        GETAVAILWEAPONS(hackedict) &= TS_WEAPON_H_K_PDW_BIT;
                    }
		    break;

		default:
		    //Somethin's screwy here...
		    RETURN_META(MRES_IGNORED);

		}
		break;

	    case '2':
		switch (cmdbuf[1]) {
		case '_':
		    //WTF?!? He bought nothing!
		    break;

	        case '0':
		    if (!(weaponsbits & TS_WEAPON_SPAS_12_BIT)) {
		        tspp_csay(pEntity, restmessage);
		        RETURN_META(MRES_SUPERCEDE);
		    } else {
                        GETCURRENTWEAPON(hackedict) = TS_WEAPON_SPAS_12;
                        GETAVAILWEAPONS(hackedict) &= TS_WEAPON_SPAS_12_BIT;
                    }
		    break;

	        case '1':
		    if (!(weaponsbits & TS_WEAPON_GOLDEN_COLTS_BIT)) {
		        tspp_csay(pEntity, restmessage);
		        RETURN_META(MRES_SUPERCEDE);
		    } else {
                        GETCURRENTWEAPON(hackedict) = TS_WEAPON_GOLDEN_COLTS;
                        GETAVAILWEAPONS(hackedict) &= TS_WEAPON_GOLDEN_COLTS_BIT;
                    }
		    break;

	        case '2':
		    if (!(weaponsbits & TS_WEAPON_GLOCK_20_BIT)) {
		        tspp_csay(pEntity, restmessage);
		        RETURN_META(MRES_SUPERCEDE);
		    } else {
                        GETCURRENTWEAPON(hackedict) = TS_WEAPON_GLOCK_20;
                        GETAVAILWEAPONS(hackedict) &= TS_WEAPON_GLOCK_20_BIT;
                    }
		    break;

	        case '3':
		    if (!(weaponsbits & TS_WEAPON_MAC_10_BIT)) {
		        tspp_csay(pEntity, restmessage);
		        RETURN_META(MRES_SUPERCEDE);
		    } else {
                        GETCURRENTWEAPON(hackedict) = TS_WEAPON_MAC_10;
                        GETAVAILWEAPONS(hackedict) &= TS_WEAPON_MAC_10_BIT;
                    }
		    break;

	        case '4':
		    if (!(weaponsbits & TS_WEAPON_M61_FRAG_GRENADE_BIT)) {
		        tspp_csay(pEntity, restmessage);
		        RETURN_META(MRES_SUPERCEDE);
		    } else {
                        GETCURRENTWEAPON(hackedict) = TS_WEAPON_M61_FRAG_GRENADE;
                        GETAVAILWEAPONS(hackedict) &= TS_WEAPON_M61_FRAG_GRENADE_BIT;
                    }
		    break;

	        case '5':
	            if (!(weaponsbits & TS_WEAPON_KNIFE_BIT)) {
		        tspp_csay(pEntity, restmessage);
		        RETURN_META(MRES_SUPERCEDE);
		    } else {
                        GETCURRENTWEAPON(hackedict) = TS_WEAPON_KNIFE;
                        GETAVAILWEAPONS(hackedict) &= TS_WEAPON_KNIFE_BIT;
                    }
		    break;

		default:
		    //Somethin's screwy here...
		    RETURN_META(MRES_IGNORED);

		}
		break;

	    case '3':
		if (!(weaponsbits & TS_WEAPON_MINI_UZI_BIT)) {
		    tspp_csay(pEntity, restmessage);
		    RETURN_META(MRES_SUPERCEDE);
		} else {
                    GETCURRENTWEAPON(hackedict) = TS_WEAPON_MINI_UZI;
                    GETAVAILWEAPONS(hackedict) &= TS_WEAPON_MINI_UZI_BIT;
                }
		break;

	    case '4':
		if (!(weaponsbits & TS_WEAPON_BENELLI_M3_BIT)) {
		    tspp_csay(pEntity, restmessage);
		    RETURN_META(MRES_SUPERCEDE);
		} else {
                    GETCURRENTWEAPON(hackedict) = TS_WEAPON_BENELLI_M3;
                    GETAVAILWEAPONS(hackedict) &= TS_WEAPON_BENELLI_M3_BIT;
                }
		break;

	    case '5':
		if (!(weaponsbits & TS_WEAPON_M4A1_BIT)) {
		    tspp_csay(pEntity, restmessage);
		    RETURN_META(MRES_SUPERCEDE);
		} else {
                    GETCURRENTWEAPON(hackedict) = TS_WEAPON_M4A1;
                    GETAVAILWEAPONS(hackedict) &= TS_WEAPON_M4A1_BIT;
                }
		break;

	    case '6':
		if (!(weaponsbits & TS_WEAPON_MP5SD_BIT)) {
		    tspp_csay(pEntity, restmessage);
		    RETURN_META(MRES_SUPERCEDE);
		} else {
                    GETCURRENTWEAPON(hackedict) = TS_WEAPON_MP5SD;
                    GETAVAILWEAPONS(hackedict) &= TS_WEAPON_MP5SD_BIT;
                }
		break;

	    case '7':
		if (!(weaponsbits & TS_WEAPON_MP5K_BIT)) {
		    tspp_csay(pEntity, restmessage);
		    RETURN_META(MRES_SUPERCEDE);
		} else {
                    GETCURRENTWEAPON(hackedict) = TS_WEAPON_MP5K;
                    GETAVAILWEAPONS(hackedict) &= TS_WEAPON_MP5K_BIT;
                }
		break;

	    case '8':
		if (!(weaponsbits & TS_WEAPON_AKIMBO_BERETTAS_BIT)) {
		    tspp_csay(pEntity, restmessage);
		    RETURN_META(MRES_SUPERCEDE);
		} else {
                    GETCURRENTWEAPON(hackedict) = TS_WEAPON_AKIMBO_BERETTAS;
                    GETAVAILWEAPONS(hackedict) &= TS_WEAPON_AKIMBO_BERETTAS_BIT;
                }
		break;

	    case '9':
		if (!(weaponsbits & TS_WEAPON_SOCOM_MK23_BIT)) {
		    tspp_csay(pEntity, restmessage);
		    RETURN_META(MRES_SUPERCEDE);
		} else {
                    GETCURRENTWEAPON(hackedict) = TS_WEAPON_SOCOM_MK23;
                    GETAVAILWEAPONS(hackedict) &= TS_WEAPON_SOCOM_MK23_BIT;
                }
		break;

	    default:
		//Somethin's screwy here...
		RETURN_META(MRES_IGNORED);

	    }

        }

        if (DESPERADO && strstr(CMD_ARGV(0), "takea_")) {
            RETURN_META(MRES_SUPERCEDE);
        }

        if (!strcmp(CMD_ARGV(0), "tspp_restrict") || !strcmp(CMD_ARGV(0), "tspp_unrestrict")) {

	    qboolean restmode;
	    const char* arrrrg = CMD_ARGV(0);   //I'm a pirate! :-P

	    //Restrict or unrestrict?
	    //tspp_restrict
	    //tspp_unrestrict <--has 'un' and thats what im testing for
	    if (arrrrg[5]=='u') {

	        //Unrestrict!
	        restmode = false;

	    } else {

	        //Restrict!
	        restmode = true;

	    }

	    if (CMD_ARGC() > 1 && !strcmp(CMD_ARGV(1), "list")) {

		char restbuf[200];
		strcpy(restbuf, "Restricted weapons: ");
    		char unrestbuf[200];
		strcpy(unrestbuf, "Unrestricted weapons: ");

    		for (int i = 0; i < TS_MAXWEAPONS; i++) {

    		    //Dont list kung fu or "?"
    		    if (i == 0 || i == 2) {
    		        continue;
    		    }

    		    if (weaponsbits & (1<<i)) {
    		        sprintf(unrestbuf + strlen(unrestbuf), "%s ", wnamearray[i]);
    		    } else {
    		        sprintf(restbuf + strlen(restbuf), "%s ", wnamearray[i]);
    		    }

    		}
	        CLIENT_PRINTF(pEntity, print_console, strcat(restbuf, "\n"));
	        CLIENT_PRINTF(pEntity, print_console, strcat(unrestbuf, "\n"));
    		RETURN_META(MRES_SUPERCEDE);


	    } else {

		if (CMD_ARGC() < 3) {
		    CLIENT_PRINTF(pEntity, print_console, "Password incorrect!\n");
    		    RETURN_META(MRES_SUPERCEDE);
		}

    		if (strcmp(CMD_ARGV(2), PASSWD)) {
		    CLIENT_PRINTF(pEntity, print_console, "Password incorrect!\n");
    		    LOG_MESSAGE(PLID, "Incorrect password attempt from %s\n", STRING(pEntity->v.netname));
    		    RETURN_META(MRES_SUPERCEDE);
    		}

 		if (!tspp_restrict( restmode, CMD_ARGV(1) )) {

        	    CLIENT_PRINTF(pEntity, print_console, "That weapon does not exist!");

		} else {

		    LOG_MESSAGE(PLID, "Weapon restriction \"%s\" made by \"%s<%s>\"",
			CMD_ARGV(1), 
			STRING(pEntity->v.netname),
			GETPLAYERAUTHID(pEntity));

		}

    		RETURN_META(MRES_SUPERCEDE);

	    }

	}

/*        if (!strcmp(CMD_ARGV(0), "tspp_team")) {

            if (CMD_ARGC() < 4) {
                CLIENT_PRINTF(pEntity, print_console, "Password incorrect!\n");
                RETURN_META(MRES_SUPERCEDE);
            }

            if (strcmp(CMD_ARGV(3), PASSWD)) {
                CLIENT_PRINTF(pEntity, print_console, "Password incorrect!\n");
                LOG_MESSAGE(PLID, "Incorrect password attempt from %s\n", STRING(pEntity->v.netname));
                RETURN_META(MRES_SUPERCEDE);
            }

            edict_t *pVictim;

            int hackindex = UTIL_GetHackByID(CMD_ARGV(1));
            if (hackindex == -1) {
                CLIENT_PRINTF(pEntity, print_console, "Can't find that dude.\n");
                RETURN_META(MRES_SUPERCEDE);
            }
            hackedict = &players[hackindex];

            pVictim = hackedict->pEdict;

            tspp_csay(pVictim, "Admin has switched your team.");
            CLIENT_COMMAND(pVictim, "model %s\n", CMD_ARGV(2));
            LOG_MESSAGE( PLID, "%s switched %s to team %s.", STRING(pEntity->v.netname), STRING(pVictim->v.netname), CMD_ARGV(2));

            RETURN_META(MRES_SUPERCEDE);
        }*/

        if (!strcmp(CMD_ARGV(0), "tspp_god")) {

	    if (CMD_ARGC() < 2) {
		CLIENT_PRINTF(pEntity, print_console, "Password incorrect!\n");
                RETURN_META(MRES_SUPERCEDE);
 	    }

            if (strcmp(CMD_ARGV(1), PASSWD)) {
                CLIENT_PRINTF(pEntity, print_console, "Password incorrect!\n");
                LOG_MESSAGE(PLID, "Incorrect password attempt from %s\n", STRING(pEntity->v.netname));
                RETURN_META(MRES_SUPERCEDE);
            }

            char message[100];
            strcpy (message, STRING(pEntity->v.netname));

	    //Thanks to Admin Mod for showing me how to do this!
	    if (pEntity->v.takedamage == DAMAGE_NO) {
		
		//God mode is on, take it off.
		pEntity->v.solid = SOLID_SLIDEBOX;
		pEntity->v.takedamage = DAMAGE_AIM;
		tspp_csay(pEntity, "God mode is now off!");
                tspp_announce( strcat(message, " has become mortal once again!\n") );
                LOG_MESSAGE( PLID, "\"%s<%s>\" turned god mode off for himself.",
		    STRING(pEntity->v.netname),
		    GETPLAYERAUTHID(pEntity)
		    );

	    } else {

		//God mode is off, turn it on.
 		pEntity->v.solid = SOLID_NOT;
		pEntity->v.takedamage = DAMAGE_NO;
		tspp_csay(pEntity, "God mode is now on!");
                tspp_announce( strcat(message, " has turned himself into a GOD!\n") );
                LOG_MESSAGE( PLID, "\"%s<%s>\" turned god mode on for himself.",
		    STRING(pEntity->v.netname),
		    GETPLAYERAUTHID(pEntity)
		    );

	    }
 	    RETURN_META(MRES_SUPERCEDE);

	}

	RETURN_META(MRES_IGNORED);
}

const char *GetGameDescription(void) {

        RETURN_META_VALUE(MRES_SUPERCEDE, "TS Beta 1.5");

}

DLL_FUNCTIONS gFunctionTable_Post;
C_DLLEXPORT int GetEntityAPI2_Post( DLL_FUNCTIONS *pFunctionTable, int *interfaceVersion ) {
        gFunctionTable_Post.pfnPlayerPostThink = PlayerPostThink_Post;
        gFunctionTable_Post.pfnStartFrame = StartFrame_Post;
        gFunctionTable_Post.pfnClientConnect = ClientConnect_Post;
 	memcpy( pFunctionTable, &gFunctionTable_Post, sizeof( DLL_FUNCTIONS ) );
	return(TRUE);
}

DLL_FUNCTIONS gFunctionTable;
C_DLLEXPORT int GetEntityAPI2( DLL_FUNCTIONS *pFunctionTable, int *interfaceVersion ){
	gFunctionTable.pfnGameInit = GameInit;
	gFunctionTable.pfnSpawn = Spawn;
	gFunctionTable.pfnThink = Think;
	gFunctionTable.pfnPM_Move = PM_Move;
	gFunctionTable.pfnCmdStart = CmdStart;
	gFunctionTable.pfnServerActivate = ServerActivate;
	gFunctionTable.pfnClientConnect = ClientConnect;
	gFunctionTable.pfnClientUserInfoChanged = ClientUserInfoChanged;
	gFunctionTable.pfnClientDisconnect = ClientDisconnect;
	gFunctionTable.pfnClientCommand = ClientCommand;
	gFunctionTable.pfnPlayerPreThink = PlayerPreThink;
	gFunctionTable.pfnPlayerPostThink = PlayerPostThink;
	gFunctionTable.pfnClientPutInServer = ClientPutInServer;
	gFunctionTable.pfnServerDeactivate = ServerDeactivate;
	gFunctionTable.pfnStartFrame = StartFrame;
        gFunctionTable.pfnGetGameDescription = GetGameDescription;

	memcpy( pFunctionTable, &gFunctionTable, sizeof( DLL_FUNCTIONS ) );
	return(TRUE);
}

// Must provide at least one of these..
META_FUNCTIONS gMetaFunctionTable = {
	NULL,					// pfnGetEntityAPI				HL SDK; called before game DLL
	NULL,					// pfnGetEntityAPI_Post			META; called after game DLL
	GetEntityAPI2,			// pfnGetEntityAPI2				HL SDK2; called before game DLL
	GetEntityAPI2_Post,		// GetEntityAPI2_Post,			// pfnGetEntityAPI2_Post		META; called after game DLL
	NULL,					// pfnGetNewDLLFunctions		HL SDK2; called before game DLL
	NULL,					// GetNewDLLFunctions_Post,	// pfnGetNewDLLFunctions_Post	META; called after game DLL
	GetEngineFunctions,		// pfnGetEngineFunctions		META; called before HL engine
	NULL	// pfnGetEngineFunctions_Post	META; called after HL engine
};


void Client_DeathMsg(void*)
{
}

void Client_Damage(void*)
{
}

void Client_CurWeapon(void*)
{
}

void Client_TextMsg(void*)
{
}

void Client_TeamInfo(void*)
{
}

void Client_ResetHUD_End(void*)
{
}

void Client_SendAudio(void*)
{
}

void Client_TeamScore(void*)
{
}

void Client_Money(void*)
{
}

void Client_WeaponList(void*)
{
}

void Client_Battery(void*)
{
}

void Client_ShowMenu(void*)
{
}

void Client_intermission_End(void*)
{
}

void Client_AmmoX(void*)
{
}

void Client_Health(void*)
{
}

void EmitSound(edict_t *entity, int channel, const char *sample, float volume, float attenuation, int fFlags, int pitch)
{
}

void SetModel(edict_t *e, const char *m)
{
}

