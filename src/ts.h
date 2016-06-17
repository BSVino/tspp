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

#ifndef TS_H
#define TS_H

#define TS_WEAPON_KUNG_FU		0
#define TS_WEAPON_GLOCK_18		1
#define TS_WEAPON_WHATISTHIS		2
#define TS_WEAPON_MINI_UZI		3
#define TS_WEAPON_BENELLI_M3		4
#define TS_WEAPON_M4A1			5
#define TS_WEAPON_MP5SD			6
#define TS_WEAPON_MP5K			7
#define TS_WEAPON_AKIMBO_BERETTAS	8
#define TS_WEAPON_SOCOM_MK23		9
#define TS_WEAPON_AKIMBO_MK23		10
#define TS_WEAPON_USAS_12		11
#define TS_WEAPON_DESERT_EAGLE		12
#define TS_WEAPON_AK47			13
#define TS_WEAPON_FIVE_SEVEN		14
#define TS_WEAPON_STEYR_AUG		15
#define TS_WEAPON_AKIMBO_MINI_UZIS	16
#define TS_WEAPON_STEYR_TMP		17
#define TS_WEAPON_BARRET_M82A1		18
#define TS_WEAPON_H_K_PDW		19
#define TS_WEAPON_SPAS_12		20
#define TS_WEAPON_GOLDEN_COLTS		21
#define TS_WEAPON_GLOCK_20		22
#define TS_WEAPON_MAC_10		23
#define TS_WEAPON_M61_FRAG_GRENADE	24
#define TS_WEAPON_KNIFE			25

#define TS_WEAPON_KUNG_FU_BIT		(1<<0)
#define TS_WEAPON_GLOCK_18_BIT      	(1<<1)
#define TS_WEAPON_WHATISTHIS_BIT	(1<<2)
#define TS_WEAPON_MINI_UZI_BIT		(1<<3)
#define TS_WEAPON_BENELLI_M3_BIT	(1<<4)
#define TS_WEAPON_M4A1_BIT		(1<<5)
#define TS_WEAPON_MP5SD_BIT		(1<<6)
#define TS_WEAPON_MP5K_BIT		(1<<7)
#define TS_WEAPON_AKIMBO_BERETTAS_BIT	(1<<8)
#define TS_WEAPON_SOCOM_MK23_BIT	(1<<9)
#define TS_WEAPON_AKIMBO_MK23_BIT	(1<<10)
#define TS_WEAPON_USAS_12_BIT		(1<<11)
#define TS_WEAPON_DESERT_EAGLE_BIT	(1<<12)
#define TS_WEAPON_AK47_BIT		(1<<13)
#define TS_WEAPON_FIVE_SEVEN_BIT	(1<<14)
#define TS_WEAPON_STEYR_AUG_BIT		(1<<15)
#define TS_WEAPON_AKIMBO_MINI_UZIS_BIT	(1<<16)
#define TS_WEAPON_STEYR_TMP_BIT		(1<<17)
#define TS_WEAPON_BARRET_M82A1_BIT	(1<<18)
#define TS_WEAPON_H_K_PDW_BIT		(1<<19)
#define TS_WEAPON_SPAS_12_BIT		(1<<20)
#define TS_WEAPON_GOLDEN_COLTS_BIT	(1<<21)
#define TS_WEAPON_GLOCK_20_BIT		(1<<22)
#define TS_WEAPON_MAC_10_BIT		(1<<23)
#define TS_WEAPON_M61_FRAG_GRENADE_BIT	(1<<24)
#define TS_WEAPON_KNIFE_BIT		(1<<25)

#define TS_WEAPON_PISTOLS_BIT 		( TS_WEAPON_GLOCK_18_BIT | TS_WEAPON_AKIMBO_BERETTAS_BIT \
			        	| TS_WEAPON_SOCOM_MK23_BIT | TS_WEAPON_AKIMBO_MK23_BIT \
        				| TS_WEAPON_DESERT_EAGLE_BIT | TS_WEAPON_FIVE_SEVEN_BIT \
				        | TS_WEAPON_GOLDEN_COLTS_BIT | TS_WEAPON_GLOCK_20_BIT )
#define TS_WEAPON_SHOTGUNS_BIT		( TS_WEAPON_BENELLI_M3_BIT | TS_WEAPON_USAS_12_BIT | TS_WEAPON_SPAS_12_BIT )
#define TS_WEAPON_SMGS_BIT		( TS_WEAPON_MINI_UZI_BIT | TS_WEAPON_MP5SD_BIT \
					| TS_WEAPON_MP5K_BIT | TS_WEAPON_AKIMBO_MINI_UZIS_BIT \
					| TS_WEAPON_STEYR_TMP_BIT | TS_WEAPON_H_K_PDW_BIT \
					| TS_WEAPON_MAC_10_BIT )
#define TS_WEAPON_RIFLES_BIT		( TS_WEAPON_M4A1_BIT | TS_WEAPON_AK47_BIT | TS_WEAPON_STEYR_AUG_BIT )
#define TS_WEAPON_KNIFENADE_BIT		( TS_WEAPON_M61_FRAG_GRENADE_BIT | TS_WEAPON_KNIFE_BIT)

#define TS_MAXWEAPONS			26

//Don't look at me, these abbreviations are used in game :-P
#define TS_ACC_SIL			(1<<0)	//Silencer
#define TS_ACC_LAS			(1<<1)	//Laser
#define TS_ACC_FLA			(1<<2)	//Flashlight
#define TS_ACC_SCO			(1<<3)	//Scope
#define TS_ACC_ALL			( TS_ACC_SIL|TS_ACC_LAS|TS_ACC_FLA|TS_ACC_SCO )

#define TS_AMMO_FU		0	//FU!
#define TS_AMMO_9_19MM		1	//glock18 mp5k berettas uzis mp5sd tmp
#define TS_AMMO_45_ACP		2	//Glock socom mac10
#define TS_AMMO_SHELLS		3	//All three shotguns
#define TS_AMMO_5_56_NATO	4	//m4a1 and aug
#define TS_AMMO_50_AE		5	//deagle
#define TS_AMMO_7_62_NATO	6	//ak47
#define TS_AMMO_5_7x28		7	//5-7 and pdw
#define TS_AMMO_50_BMG		8	//barret
#define TS_AMMO_10MM_AUTO	9	//glock 20
#define TS_AMMO_NADE		10	//NADE! ***
#define TS_AMMO_KNIFE		11	//KNIFE! ***
//*** - These are not used by the actual game, but i shoved them in so I could use them in
// my handy array that gives you max ammo hold for weapons. This, of course, applies not at
// all to kung fu, which is just...there. :-/

#define TS_FIRE_PUMP		(1<<0)
#define TS_FIRE_SEMI		(1<<1)
#define TS_FIRE_BURST		(1<<2)
#define TS_FIRE_AUTO		(1<<3)

#define TS_STAT_AMMOTYPE	0
#define TS_STAT_CLIP		1
#define TS_STAT_ACCESSORIES	2
#define TS_STAT_FIREMODES	3

//These bitmasks (yes, they are bitmasks!) are used for the pEntity->v.iuser4
//I dont know why Morpheo chose such strange values. 
#define TS_STUNT_CROUCHED	(1<<0)			//Player is stunt-crouched, getting up from a stunt or doing a crouch roll.
#define TS_STUNT		(1<<2)			//This is or'ed into every stunt.
#define TS_STUNT_EXT1		(1<<3)			//This is allways OR'ed into TS_STUNT_AIRWHEEL_LOW (I dont know what else it's used for. I'll rename it when I figure that out.)
#define TS_STUNT_DIVE		(1<<4)			//Player is currently in the air in a dive. This, too is allways OR'ed into TS_STUNT_AIRWHEEL_LOW.
#define TS_STUNT_PRONE		(1<<5)			//Player has landed, and is prone on the floor.
#define TS_WEARING_STEALTH	(1<<9)			//Player is wearing stealth shoes. (Wtf? Doesnt this have somewhere better to be?)
#define TS_AIRWHEEL_HIGH	(1<<10)			//Player is in the air for a high airwheel
#define TS_AIRWHEEL_LOW		(1<<11)			//Player is in the air for an airwheel (medium or low.) (Also has TS_STUNT_EXT1 and TS_STUNT_DIVE OR'ed in.)
//I suppose this arrangement kinda makes sense. If you want to know if the user is 'prone' in the air (and not 
//'crouched' like in a high airwheel) then you can (iuser4 & TS_STUNT_DIVE). That returns false if the player is doing a 
//high dive, which lands you on your feet (not prone.)
//Note that TS_STUNT is OR'ed into all the TS_STUNT's, but NOT the TS_AIRWHEELS. If the player is crouched from ANY 
//stunt, then TS_STUNT is in there, even if it was an airwheel. However, TS_STUNT is not in during the actual airwheel.
//TS_WEARING_STEALTH is kinda random in there, but its useful to know if the player is wearing stealth boots.

//These bitmasks are used for pEntity->v.deadflag
//As it appears, 2 and 3 are not used.
#define DEAD		(1<<0)			//The player is dead. If DEAD_SPECTATOR is not set, his camera is still in his body.
#define DEAD_SPECTATOR	(1<<1)			//The player's camera has left his body, he is now free to roam (or chase cam.)
//1 is just like pEntity->v.deadflag, except that the DEAD flag is not set until the camera leaves the player's body (useless...)

//So, just to make your life easier...
#define stuntpos iuser4
#define slowvalue fuser1

//About the other user variables:
//fuser1 seems to be the globalslow value for the player..
//None of the vuser or euser variables seem to be used.

const int TS_weapon_stats[][4] = {
//ammotype 		accessories 		firemodes
{TS_AMMO_FU,	    0,	0,			0			}, //FU!
{TS_AMMO_9_19MM,    17,	TS_ACC_SIL|TS_ACC_LAS|TS_ACC_FLA,TS_FIRE_SEMI|TS_FIRE_AUTO}, //Glock-18
{TS_AMMO_FU, 	    0,	0,			0,				}, //What am I?
{TS_AMMO_9_19MM,    32,	TS_ACC_SIL,		TS_FIRE_AUTO|TS_FIRE_SEMI,	}, //Uzi
{TS_AMMO_SHELLS,    7,	TS_ACC_LAS|TS_ACC_FLA|TS_ACC_SCO,TS_FIRE_PUMP|TS_FIRE_SEMI}, //M3
{TS_AMMO_5_56_NATO, 30,	TS_ACC_ALL,		TS_FIRE_SEMI|TS_FIRE_BURST|TS_FIRE_AUTO}, //M4A1
{TS_AMMO_9_19MM,    30,	TS_ACC_ALL,		TS_FIRE_SEMI|TS_FIRE_BURST|TS_FIRE_AUTO}, //MP5SD NOTE:comes with a silencer, can't take it off!
{TS_AMMO_9_19MM,    30,	TS_ACC_ALL,		TS_FIRE_SEMI|TS_FIRE_BURST|TS_FIRE_AUTO}, //MP5K
{TS_AMMO_9_19MM,    30,	TS_ACC_SIL|TS_ACC_LAS|TS_ACC_FLA,TS_FIRE_SEMI,		}, //Berettas
{TS_AMMO_45_ACP,    12,	TS_ACC_SIL|TS_ACC_LAS|TS_ACC_FLA,TS_FIRE_SEMI,		}, //Socom MK23
{TS_AMMO_45_ACP,    24,	TS_ACC_SIL|TS_ACC_LAS|TS_ACC_FLA,TS_FIRE_SEMI,		}, //Akimbo Socom MK23
{TS_AMMO_SHELLS,    20,	TS_ACC_LAS|TS_ACC_FLA,	TS_FIRE_AUTO,			}, //USAS-12
{TS_AMMO_50_AE,	    7,	TS_ACC_SIL|TS_ACC_SCO|TS_ACC_LAS,TS_FIRE_SEMI,		}, //Desert Eagle
{TS_AMMO_7_62_NATO, 30,	TS_ACC_SCO,		TS_FIRE_SEMI|TS_FIRE_AUTO,	}, //AK47
{TS_AMMO_5_7x28,    20,	TS_ACC_SIL|TS_ACC_LAS|TS_ACC_FLA,TS_FIRE_SEMI,		}, //Five-Seven
{TS_AMMO_5_56_NATO, 30,	TS_ACC_SIL|TS_ACC_LAS|TS_ACC_SCO,TS_FIRE_SEMI|TS_FIRE_AUTO}, //Steyr AUG
{TS_AMMO_9_19MM,    64,	TS_ACC_SIL,		TS_FIRE_AUTO|TS_FIRE_SEMI,	}, //Akimbo Uzis
{TS_AMMO_9_19MM,    30,	TS_ACC_SIL|TS_ACC_LAS,	TS_FIRE_SEMI|TS_FIRE_AUTO,	}, //Steyr TMP
{TS_AMMO_50_BMG,    5,	TS_ACC_LAS,		TS_FIRE_SEMI,			}, //Barret M82A1
{TS_AMMO_5_7x28,    40,	TS_ACC_SIL|TS_ACC_LAS|TS_ACC_SCO,TS_FIRE_SEMI|TS_FIRE_AUTO}, //H&K-PDW
{TS_AMMO_SHELLS,    8,	TS_ACC_LAS|TS_ACC_FLA,	TS_FIRE_PUMP|TS_FIRE_SEMI,	}, //SPAS-12
{TS_AMMO_45_ACP,    16,	0,			TS_FIRE_SEMI,			}, //Golden Colts
{TS_AMMO_10MM_AUTO, 15,	TS_ACC_SIL|TS_ACC_LAS|TS_ACC_FLA,TS_FIRE_SEMI,		}, //Glock-20
{TS_AMMO_45_ACP,    32,	TS_ACC_SIL,		TS_FIRE_SEMI|TS_FIRE_AUTO,	}, //MAC-10
{TS_AMMO_NADE,	    1,	0,			TS_FIRE_SEMI,			}, //M81 Fragmentation Grenade
{TS_AMMO_KNIFE,	    1,	0,			TS_FIRE_SEMI,			}, //Knife
};

const int TS_ammo_stats[] = {
	0,	//FU!
	300,	//9x19mm
	200,	//.45 ACP
	100,	//Shells - One per clip, this is shotguns. Theyre all different.
	90,	//5.56 Nato
	70,	//.50 AE
	90,	//7.62 Nato
	200,	//5.7x28
	20,	//50 BMG
	100,	//10mm AUTO
	2,	//Nade
	10,	//Knife
};

#endif // TS_H
