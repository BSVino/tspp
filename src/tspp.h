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

#ifndef TSPP_H
#define TSPP_H

#include <time.h>			// time()
#include <enginecallback.h>		// ALERT()
#include <sdk_util.h>			// UTIL_VarArgs()
#include <api_info.h>
#include "vers_plugin.h"

// Parts of body for hits
#define HITGROUP_GENERIC	0 // none
#define HITGROUP_HEAD		1
#define HITGROUP_CHEST		2
#define HITGROUP_STOMACH	3
#define HITGROUP_LEFTARM	4
#define HITGROUP_RIGHTARM	5
#define HITGROUP_LEFTLEG	6
#define HITGROUP_RIGHTLEG	7

#define MAX_HUD_TEXT_LENGTH 256

//cvars
#define PASSWD         (CVAR_GET_POINTER("tspp_passwd")->string)
#define DEBUG          !strcmp(CVAR_GET_POINTER("tspp_debug")->string, "1")
#define DEBUG2         !strcmp(CVAR_GET_POINTER("tspp_debug")->string, "2")
#define MFLASH         !strcmp(CVAR_GET_POINTER("tspp_mflash")->string, "1")
#define KNALL          !strcmp(CVAR_GET_POINTER("tspp_knall")->string, "1")
#define DESPERADO      !strcmp(CVAR_GET_POINTER("tspp_desperado")->string, "1")
#define FORCESPEC      !strcmp(CVAR_GET_POINTER("tspp_forcespec")->string, "1")        //Force people onto specator team

//'hack' refers to the plugin's hold on a player
#define GETHACKEDICT(edict)	(players[g_engfuncs.pfnIndexOfEdict(edict)-1])	//Get the hack edict from the real one.
#define GETREALEDICT(hack)	((hack).pEdict)		//Get the REAL (not the hack) edict for this player.
#define GETHACKTAKEN(hack)	((hack).taken)		//Is this hack taken already by a player?
#define GETINFIRST(hack)	((hack).fperson)	//Is the player in first person mode?
#define GETCURRENTWEAPON(hack)	((hack).curweapon)	//The TS_WEAPON_* the player has currently out.
#define GETAVAILWEAPONS(hack)	((hack).weapons)	//Bitmask TS_WEAPON_*_BIT this player has bought.

//Other macros which are useful to me
#define PLAYER_TEAM(edict)     g_engfuncs.pfnInfoKeyValue(g_engfuncs.pfnGetInfoKeyBuffer(edict),"model")
#define LOWER(c)               (((c)>='A'  && (c) <= 'Z') ? ((c)+('a'-'A')) : (c))     //From circlemud!

//These are used by the weapon restriction code to keep track of what weapons are restricted.
#define RESTRICT_NONE          0
#define RESTRICT_ALL           1
#define RESTRICT_PISTOLS       2
#define RESTRICT_SHOTGUNS      3
#define RESTRICT_SMGS          4
#define RESTRICT_RIFLES        5
#define RESTRICT_KNIVES        6
#define RESTRICT_CUSTOM        7

void			UTIL_PlayerLookAt( edict_t *pPlayer, edict_t *pTarget );
char*			UTIL_lcase(char* format);
inline unsigned short	UTIL_FixedUnsigned16( float value, float scale );
inline unsigned char	UTIL_FixedUnsigned8( float value, float scale );
inline short		UTIL_FixedSigned16( float value, float scale );

void tspp_init(void);
void tspp_csay(edict_t* pEdict, const char *szMsg);
void tspp_cmessage(edict_t *pEntity, const hudtextparms_t &textparms, const char *pMessage);
void tspp_displayrestrictions( void );
int  tspp_restrict( qboolean restmode, const char* rweapon );
void tspp_announce( const char* pMessage );

void cmd_tspp_restrict( void );


//Heres a bunch of structs I might use!

typedef struct hack_s
{
	qboolean taken;
	int plrid;
	edict_t *pEdict;
	qboolean fperson;
	int curweapon;
	int weapons;
} hack_t;

/*
void Client_DeathMsg(void*);
void Client_Damage(void*);
void Client_CurWeapon(void*);
void Client_TextMsg(void*);
void Client_TeamInfo(void*);
void Client_ResetHUD_End(void*);
void Client_SendAudio(void*);
void Client_TeamScore(void*);
void Client_Money(void*);
void Client_WeaponList(void*);
void Client_Battery(void*);
void Client_ShowMenu(void*);
void Client_intermission_End(void*);
void Client_AmmoX(void*);
void Client_Health(void*);
void EmitSound(edict_t *entity, int channel, const char *sample, float volume, float attenuation, int fFlags, int pitch);
void SetModel(edict_t *e, const char *m);
void StartFrame( void );
*/

#endif // TSPP_H
