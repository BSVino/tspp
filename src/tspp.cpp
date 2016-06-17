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

#include <extdll.h>			// always

#include <api_info.h>		// api_info_t, etc
#include <sdk_util.h>		// REG_SVR_COMMAND, etc
#include <meta_api.h>		// Plugin_info, etc
#include <ctype.h>
#include <com_model.h>

#include "tspp.h"
#include "ts.h"

extern enginefuncs_t g_engfuncs;

unsigned int weaponsbits;	//Bitmask for weapons currently UNrestricted.
char restmessage[100];	//Message sent when player buys a restricted weapon.
int restrictcode = RESTRICT_NONE;

hack_t players[MAX_CLIENTS];

cvar_t cvar_tspp_version =	{"tspp_version", VVERSION, FCVAR_SERVER | FCVAR_SPONLY};
cvar_t cvar_tspp_debug   =	{"tspp_debug",	 "0"     , FCVAR_UNLOGGED | FCVAR_SPONLY};
cvar_t cvar_tspp_passwd  =	{"tspp_passwd",	 ""      , FCVAR_UNLOGGED | FCVAR_SPONLY | FCVAR_PROTECTED};
cvar_t cvar_tspp_mflash  =	{"tspp_mflash",	 "0"     , FCVAR_SERVER   | FCVAR_SPONLY};
cvar_t cvar_tspp_knall   =	{"tspp_knall",	 "1"     , FCVAR_UNLOGGED | FCVAR_SPONLY};
cvar_t cvar_tspp_desperado =    {"tspp_desperado", "0"   , FCVAR_SERVER   | FCVAR_SPONLY};
cvar_t cvar_tspp_forcespec =    {"tspp_forcespec", "0"   , FCVAR_SERVER   | FCVAR_SPONLY};

/*
 * Got this from hullu, http://hullu.xtragaming.com/
 */
hudtextparms_t defaultHUD = {
        0, //x
        0, //y
        1, //effect
        0,0,0,0,//color1
        0,0,0,0,//color2
        0.2,//FadeinTime
        0.1,//FadeoutTime
        5.0,//HoldTime
        0,//fxTime
        3 //Channel
};

const char* wnamearray[] = {
        "fu",
        "g18",
        "?",
        "uzi",
        "m3",
        "m4a1",
        "mp5sd",
        "mp5k",
        "berettas",
        "mk23",
        "akim-mk23",
        "usas",
        "deagle",
        "ak47",
        "5-7",
        "aug",
        "akim-uzis",
        "tmp",
        "barrett",
        "pdw",
        "spas",
        "colts",
        "g20",
        "mac10",
        "nade",
        "knife"
};

/* http://www2.ics.hawaii.edu/~esb/2001fall.ics451/strcasestr.html
 * case-independent string matching, similar to strstr but
 * matching */
const char * UTIL_strcasestr(const char* haystack, const char* needle) {
  int i;
  int nlength = strlen (needle);
  int hlength = strlen (haystack);

  if (nlength > hlength) return NULL;
  if (hlength <= 0) return NULL;
  if (nlength <= 0) return haystack;
  /* hlength and nlength > 0, nlength <= hlength */
  for (i = 0; i <= (hlength - nlength); i++) {
    if (strncasecmp (haystack + i, needle, nlength) == 0) {
      return haystack + i;
    }
  }
  /* substring not found */
  return NULL;
}

void UTIL_PlayerLookAt( edict_t *pPlayer, 
edict_t 
*pTarget ) {

	float xdis = pPlayer->v.origin.x - pTarget->v.origin.x;
	float ydis = pPlayer->v.origin.y - pTarget->v.origin.y;
	pPlayer->v.v_angle.y = atan( xdis/ydis );

}

/*Got this from AdminMod too.*/
char* UTIL_VarArgs( char *format, ... ) {
  va_list         argptr;
  static char             acString[1024];

  va_start (argptr, format);
  vsnprintf (acString, sizeof(acString), format,argptr);
  va_end (argptr);

  return acString;
}

/*Made this one myself*/
char* UTIL_lcase(char* format) {

       for (int i = 0; i < strlen(format); i++) {
           *(format+i) = LOWER(*(format+i));
       }

       return format;

}

int UTIL_GetHackByID( const char* id ) {

       edict_t* pEdict;

       //This is a player by server player offset (players since first connect)
       if (id[0] == '#') {

           int userID = atoi(id+1);
           edict_t * pEdict;

           for (int i = 1; i < gpGlobals->maxClients; i++) {

               pEdict = g_engfuncs.pfnPEntityOfEntIndex(i);

               if (userID == g_engfuncs.pfnGetPlayerUserId( pEdict )) {

                   return (i-1);

               }

           }

       } else if (id[0] >= '0' && id[0] <= '9') {

            //Search for a wonid match
            for (int i = 1; i < gpGlobals->maxClients; i++) {

                pEdict = g_engfuncs.pfnPEntityOfEntIndex(i);

                //Test current player for a match.
                if (!strcmp(g_engfuncs.pfnGetPlayerAuthId(pEdict), id)) {

                    return (i-1);

                }

            }

       } else {

           //This is a player name.
            for (int i = 1; i < gpGlobals->maxClients; i++) {

                pEdict = g_engfuncs.pfnPEntityOfEntIndex(i);

                //Test current player for a match.
                if (UTIL_strcasestr(STRING(pEdict->v.netname), id)) {

                    return (i-1);

                }

            }

       }

       //-1 means no player was found!
       return -1;

}

inline unsigned short UTIL_FixedUnsigned16( float value, float scale )
{
	int output;

	output = (int)(value * scale);
	if ( output < 0 )
		output = 0;
	else if ( output > 0xFFFF )
		output = 0xFFFF;

	return (unsigned short)output;
}


inline short UTIL_FixedSigned16( float value, float scale )
{
	int output;

	output = (int)(value * scale);

	if ( output > 32767 )
		output = 32767;
	else if ( output < -32768 )
		output = -32768;

	return (short)output;
}


inline unsigned char UTIL_FixedUnsigned8( float value, float scale )
{
	int output = (int)(value*scale);
	
	if( output > 255 ) 
		output = 255;
	else if( output < 0 ) 
		output = 0;
	
	return (unsigned char)output;
}

void tspp_init(void)
{

    LOG_MESSAGE (PLID, "%s %s", Plugin_info.name, Plugin_info.version);
    LOG_MESSAGE (PLID, "Author: %s", Plugin_info.author);

    CVAR_REGISTER (&cvar_tspp_version);
    CVAR_REGISTER (&cvar_tspp_debug);
    CVAR_REGISTER (&cvar_tspp_passwd);
    CVAR_REGISTER (&cvar_tspp_mflash);
    CVAR_REGISTER (&cvar_tspp_knall);
    CVAR_REGISTER (&cvar_tspp_desperado);
    CVAR_REGISTER (&cvar_tspp_forcespec);

    REG_SVR_COMMAND ("tspp_restrict", cmd_tspp_restrict);
    REG_SVR_COMMAND ("tspp_unrestrict", cmd_tspp_restrict);

    //Enable all weapons by default
    weaponsbits = TS_WEAPON_KUNG_FU_BIT | TS_WEAPON_GLOCK_18_BIT
		| TS_WEAPON_WHATISTHIS_BIT | TS_WEAPON_MINI_UZI_BIT
		| TS_WEAPON_BENELLI_M3_BIT | TS_WEAPON_M4A1_BIT
		| TS_WEAPON_MP5SD_BIT | TS_WEAPON_MP5K_BIT
		| TS_WEAPON_AKIMBO_BERETTAS_BIT | TS_WEAPON_SOCOM_MK23_BIT
		| TS_WEAPON_AKIMBO_MK23_BIT | TS_WEAPON_USAS_12_BIT
		| TS_WEAPON_DESERT_EAGLE_BIT | TS_WEAPON_AK47_BIT
		| TS_WEAPON_FIVE_SEVEN_BIT | TS_WEAPON_STEYR_AUG_BIT
		| TS_WEAPON_AKIMBO_MINI_UZIS_BIT | TS_WEAPON_STEYR_TMP_BIT
		| TS_WEAPON_BARRET_M82A1_BIT | TS_WEAPON_H_K_PDW_BIT
		| TS_WEAPON_SPAS_12_BIT | TS_WEAPON_GOLDEN_COLTS_BIT
		| TS_WEAPON_GLOCK_20_BIT | TS_WEAPON_MAC_10_BIT
		| TS_WEAPON_M61_FRAG_GRENADE_BIT | TS_WEAPON_KNIFE_BIT;

    SERVER_COMMAND ("exec addons/tsplusplus/tspp.cfg\n");

}

void cmd_tspp_restrict( void ) {

    if (CMD_ARGC() < 2) {
	LOG_CONSOLE(PLID, "Usage: tspp_restrict [weapon|\"list\"]");
	return;
    }

    qboolean restmode;
    const char* arrrrg = CMD_ARGV(0);

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

    if (!tspp_restrict( restmode, CMD_ARGV(1))) {

	LOG_CONSOLE(PLID, "Weapon \"%s\" does not exist!", CMD_ARGV(1));

    }

}

/*
 * restmode - true for restrict, false for unrestrict.
 */
int tspp_restrict(qboolean restmode, const char* rweapon) {

    if (!strcmp(rweapon, "list")) {

	tspp_displayrestrictions();

	return TRUE;

    }

    if (!strcmp(rweapon, "all")) {

        if (!restmode) {

            //Unrestrict all!
            weaponsbits = ~0;
            restrictcode = RESTRICT_NONE;
    	    tspp_announce("All weapons are now unrestricted.\n");

        } else {

	    strcpy(restmessage, "All weapons are restricted! FU FIGHT!");

            //Restrict all! Kung fu fight!
            weaponsbits = 0;
            restrictcode = RESTRICT_ALL;
    	    tspp_announce("All weapons have been restricted. FU FIGHT!\n");

        }

	tspp_displayrestrictions();
	return TRUE;

    }

    //Look for weapons to restrict.
    for (int i = 0; i < TS_MAXWEAPONS; i++) {
	
        //Skip kung fu and "?"
 	if (i == 0 || i == 2) {
            continue;
        }

	strcpy(restmessage, "You have bought a restricted weapon!");

	if (!strcmp(rweapon, wnamearray[i])) {

	    if (!restmode) {

		//Unrestrict!
                restrictcode = RESTRICT_CUSTOM;
		weaponsbits |= (1<<i);	//That should set the bit for this weapon
		char rstmsg[100];
		strcpy( rstmsg, "Weapon \"" );
		strcat( rstmsg, wnamearray[i] );
		strcat( rstmsg, "\" has been unrestricted." );
    		tspp_announce(rstmsg);
		
	    } else {

		//Restrict!
                restrictcode = RESTRICT_CUSTOM;
		weaponsbits &= ~(1<<i);	//That should clear the bit for this weapon
		char rstmsg[100];
		strcpy( rstmsg, "Weapon \"" );
		strcat( rstmsg, wnamearray[i] );
		strcat( rstmsg, "\" has been restricted." );
    		tspp_announce(rstmsg);

	    }

	    tspp_displayrestrictions();
	    return TRUE;

	}

    }

    //No weapons to restrict? Maybe we can restrict a group.
    if (!strcmp(rweapon, "pistols")) {

	strcpy(restmessage, "You have bought a restricted weapon!");

        if (!restmode) {

            //Unrestrict pistols.
            restrictcode = RESTRICT_CUSTOM;
            weaponsbits |= TS_WEAPON_PISTOLS_BIT;       //That should set the bits for pistols
	    tspp_announce("Pistols are now unrestricted.");

        } else {

            //Restrict pistols :-(
            restrictcode = RESTRICT_CUSTOM;
            weaponsbits &= ~TS_WEAPON_PISTOLS_BIT;      //That should clear the bits for pistols
	    tspp_announce("Pistols are now restricted.");

        }

    } else if (!strcmp(rweapon, "shotguns")) {

	strcpy(restmessage, "You have bought a restricted weapon!");

        if (!restmode) {

            //Unrestrict shotguns.
            restrictcode = RESTRICT_CUSTOM;
            weaponsbits |= TS_WEAPON_SHOTGUNS_BIT;       //That should set the bits for shotguns
	    tspp_announce("Shotguns are now unrestricted.");

        } else {

            //Restrict shotguns :-(
            restrictcode = RESTRICT_CUSTOM;
            weaponsbits &= ~TS_WEAPON_SHOTGUNS_BIT;      //That should clear the bits for shotguns
	    tspp_announce("Shotguns are now restricted.");

        }

    } else if (!strcmp(rweapon, "smgs")) {

	strcpy(restmessage, "You have bought a restricted weapon!");

        if (!restmode) {

            //Unrestrict smgs.
            restrictcode = RESTRICT_CUSTOM;
            weaponsbits |= TS_WEAPON_SMGS_BIT;       //That should set the bits for smgs
	    tspp_announce("SMG's are now unrestricted.");

        } else {

            //Restrict smgs O.o
            restrictcode = RESTRICT_CUSTOM;
            weaponsbits &= ~TS_WEAPON_SMGS_BIT;      //That should clear the bits for smgs
	    tspp_announce("SMG's are now restricted.");

        }

    } else if (!strcmp(rweapon, "rifles")) {

	strcpy(restmessage, "You have bought a restricted weapon!");

        if (!restmode) {

            //Unrestrict rifles.
            restrictcode = RESTRICT_CUSTOM;
            weaponsbits |= TS_WEAPON_RIFLES_BIT;       //That should set the bits for rifles
	    tspp_announce("Rifles are now unrestricted.");

        } else {

            //Restrict rifles :-)
            restrictcode = RESTRICT_CUSTOM;
            weaponsbits &= ~TS_WEAPON_RIFLES_BIT;      //That should clear the bits for rifles
	    tspp_announce("Rifles are now restricted.");

        }

    } else

    //What? No groups either? How about other cool stuff you can do:
    if (!strcmp(rweapon, "pistolsonly")) {

	strcpy(restmessage, "Pistols only!");

        restrictcode = RESTRICT_PISTOLS;
        weaponsbits = TS_WEAPON_PISTOLS_BIT;	//Unrestrict pistols
	tspp_announce("New restriction: Pistols only!");

	if (KNALL) {
	    weaponsbits |= TS_WEAPON_KNIFENADE_BIT;
	}

    } else if (!strcmp(rweapon, "knivesonly")) {

        strcpy(restmessage, "Knives only!");

        restrictcode = RESTRICT_KNIVES;
        weaponsbits = TS_WEAPON_KNIFE_BIT;     //Unrestrict knives
	tspp_announce("New restriction: Knives only!");

	//I know, I know...
	if (KNALL) {
	    weaponsbits |= TS_WEAPON_KNIFENADE_BIT;
	}

    } else if (!strcmp(rweapon, "shotgunsonly")) {

        strcpy(restmessage, "Shotguns only!");

        restrictcode = RESTRICT_SHOTGUNS;
        weaponsbits = TS_WEAPON_SHOTGUNS_BIT;  //Unrestrict shotguns
	tspp_announce("New restriction: Shotguns only!");

	if (KNALL) {
	    weaponsbits |= TS_WEAPON_KNIFENADE_BIT;
	}

    } else if (!strcmp(rweapon, "smgsonly")) {

        strcpy(restmessage, "SMG's only!");

        restrictcode = RESTRICT_SMGS;
        weaponsbits = TS_WEAPON_SMGS_BIT;      //Unrestrict SMGs
	tspp_announce("New restriction: SMG's only!");

	if (KNALL) {
	    weaponsbits |= TS_WEAPON_KNIFENADE_BIT;
	}

    } else if (!strcmp(rweapon, "riflesonly")) {

        strcpy(restmessage, "Rifles only!");

        restrictcode = RESTRICT_RIFLES;
        weaponsbits = TS_WEAPON_RIFLES_BIT;    //Unrestrict rifles
	tspp_announce("New restriction: Rifles only!");

	if (KNALL) {
	    weaponsbits |= TS_WEAPON_KNIFENADE_BIT;
	}

    } else {

	return FALSE;

    }

    tspp_displayrestrictions();
    return TRUE;

}

void tspp_displayrestrictions( void ) {

    tspp_announce("Type tspp_restrict list in your console to view the current restriction.\n");

    char restbuf[200];
    *restbuf = '\0';
    char unrestbuf[200];
    *unrestbuf = '\0';

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

	LOG_CONSOLE(PLID, "Restricted weapons: %s", restbuf);
	LOG_CONSOLE(PLID, "Unrestricted weapons: %s", unrestbuf);
	LOG_CONSOLE(PLID, "Current rest. message: %s", restmessage);

        return;


}

/*
 * Announces in the chat window to all players in the server.
 */
void tspp_announce(const char *pMessage)
{

        MESSAGE_BEGIN( MSG_ALL, 76, NULL, (edict_t*)NULL );
        WRITE_BYTE( 1 );
        WRITE_STRING( UTIL_VarArgs("TSPP - %s", pMessage) );
        MESSAGE_END( );

}

/*
 * Big think letters in the middle of the screen.
 * I got this code from Hullu http://hullu.xtragaming.com/
 */
void tspp_cmessage(edict_t *pEntity, const hudtextparms_t &textparms, const char *pMessage)
{
	if(!pEntity || !pMessage || !*pMessage) return;
	
	MESSAGE_BEGIN( MSG_ONE, SVC_TEMPENTITY, NULL, pEntity );
		WRITE_BYTE( TE_TEXTMESSAGE );
		WRITE_BYTE( textparms.channel & 0xFF );

		WRITE_SHORT( UTIL_FixedSigned16( textparms.x, 1<<13 ) );
		WRITE_SHORT( UTIL_FixedSigned16( textparms.y, 1<<13 ) );
		WRITE_BYTE( UTIL_FixedUnsigned8( textparms.effect, 1 ) );

		WRITE_BYTE( UTIL_FixedUnsigned8( textparms.r1, 1 ) );
		WRITE_BYTE( UTIL_FixedUnsigned8( textparms.g1, 1 ) );
		WRITE_BYTE( UTIL_FixedUnsigned8( textparms.b1, 1 ) );
		WRITE_BYTE( UTIL_FixedUnsigned8( textparms.a1, 1 ) );

		WRITE_BYTE( UTIL_FixedUnsigned8( textparms.r2, 1 ) );
		WRITE_BYTE( UTIL_FixedUnsigned8( textparms.g2, 1 ) );
		WRITE_BYTE( UTIL_FixedUnsigned8( textparms.b2, 1 ) );
		WRITE_BYTE( UTIL_FixedUnsigned8( textparms.a2, 1 ) );

		WRITE_SHORT( UTIL_FixedUnsigned16( textparms.fadeinTime, 1<<8 ) );
		WRITE_SHORT( UTIL_FixedUnsigned16( textparms.fadeoutTime, 1<<8 ) );
		WRITE_SHORT( UTIL_FixedUnsigned16( textparms.holdTime, 1<<8 ) );

		if ( textparms.effect == 2 )
			WRITE_SHORT( UTIL_FixedUnsigned16( textparms.fxTime, 1<<8 ) );
		
		char sendMessage[MAX_HUD_TEXT_LENGTH];
		
		strncpy(sendMessage, pMessage, MAX_HUD_TEXT_LENGTH);
		
		sendMessage[MAX_HUD_TEXT_LENGTH-1] = 0;
		
		//There is some chars that aren't shows right way .. only two of these can be fixed :/
		for(int i = 0, slen = strlen(sendMessage); i < slen; i++)
		{
			switch( sendMessage[i] )
			{
				case ';':
					sendMessage[i] = 60;
				break;
			
				case '<':
					sendMessage[i] = 127;
				break;
			
				case '=':
				case '>':
				case '\\':
				case '^':
					//No fix for these yet :(
				break;
			}
		}
		
		WRITE_STRING( sendMessage );

	MESSAGE_END();
}

void tspp_csay(edict_t* pEdict, const char *szMsg) {

    g_engfuncs.pfnClientPrintf( pEdict, print_center, szMsg);

}
