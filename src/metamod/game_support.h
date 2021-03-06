// vi: set ts=4 sw=4 :
// vim: set tw=75 :

// game_support.h - structures for supporting different HL mod "games"

/*
 * Copyright (c) 2001-2003 Will Day <willday@hpgx.net>
 *
 *    This file is part of Metamod.
 *
 *    Metamod is free software; you can redistribute it and/or modify it
 *    under the terms of the GNU General Public License as published by the
 *    Free Software Foundation; either version 2 of the License, or (at
 *    your option) any later version.
 *
 *    Metamod is distributed in the hope that it will be useful, but
 *    WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with Metamod; if not, write to the Free Software Foundation,
 *    Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *    In addition, as a special exception, the author gives permission to
 *    link the code of this program with the Half-Life Game Engine ("HL
 *    Engine") and Modified Game Libraries ("MODs") developed by Valve,
 *    L.L.C ("Valve").  You must obey the GNU General Public License in all
 *    respects for all of the code used other than the HL Engine and MODs
 *    from Valve.  If you modify this file, you may extend this exception
 *    to your version of the file, but you are not obligated to do so.  If
 *    you do not wish to do so, delete this exception statement from your
 *    version.
 *
 */

#ifndef GAME_SUPPORT_H
#define GAME_SUPPORT_H

#include "types_meta.h"		// mBOOL
#include "metamod.h"		// gamedll_t

// Information we have about each game/mod DLL.
typedef struct game_modinfo_s {
	char *name;			// name (the game dir)
	char *linux_so;		// filename of linux shared lib
	char *win_dll;		// filename of win32 dll
	char *desc;			// our long-name description
} game_modinfo_t;

typedef game_modinfo_t game_modlist_t[];

mBOOL lookup_game(gamedll_t *gamedll);

#endif /* GAME_SUPPORT_H */
