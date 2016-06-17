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

#include <dllapi.h>
#include <h_export.h>
#include <meta_api.h>

#include "tspp.h"
#include "vers_plugin.h"

extern META_FUNCTIONS gMetaFunctionTable;

#ifdef _WIN32
//! Required DLL entry point
// necessary for win9x ?
BOOL WINAPI DllMain(
   HINSTANCE hinstDLL,
   DWORD fdwReason,
   LPVOID lpvReserved)
{
	if      (fdwReason == DLL_PROCESS_ATTACH)
    {
    }
	else if (fdwReason == DLL_PROCESS_DETACH)
    {
    }
	return TRUE;
}
#endif

//! Holds engine functionality callbacks
enginefuncs_t g_engfuncs;
globalvars_t  *gpGlobals;

// Receive engine function table from engine.
// This appears to be the _first_ DLL routine called by the engine, so we
// do some setup operations here.

void WINAPI GiveFnptrsToDll
( enginefuncs_t* pengfuncsFromEngine, globalvars_t *pGlobals )
{
	memcpy(&g_engfuncs, pengfuncsFromEngine, sizeof(enginefuncs_t));
	gpGlobals = pGlobals;
	// NOTE!  Have to call logging function _after_ copying into g_engfuncs, so
	// that g_engfuncs.pfnAlertMessage() can be resolved properly, heh. :)
	ALERT( at_logged,"[%s] dev: called: GiveFnptrsToDll\n", Plugin_info.logtag);
}

// Description of plugin.
// (V* info from vers_plugin.h)
plugin_info_t Plugin_info = {
	META_INTERFACE_VERSION, // ifvers
	VNAME,						// name
	VVERSION,					// version
	VDATE,						// date
	VAUTHOR,					// author
	VURL,						// url
	VLOGTAG,					// logtag
	PT_CHANGELEVEL,					// loadable
	PT_CHANGELEVEL					// unloadable
};

// Global variables from metamod.  These variable names are referenced by
// various macros.
meta_globals_t *gpMetaGlobals;		// metamod globals
gamedll_funcs_t *gpGamedllFuncs;	// gameDLL function tables
mutil_funcs_t *gpMetaUtilFuncs;		// metamod utility functions

// Metamod requesting info about this plugin
//  ifvers			(given) interface_version metamod is using
//  pPlugInfo		(requested) struct with info about plugin
//  pMetaUtilFuncs	(given) table of utility functions provided by metamod

C_DLLEXPORT int Meta_Query
(char *ifvers, plugin_info_t **pPlugInfo, mutil_funcs_t *pMetaUtilFuncs) 
{
	if ((int) CVAR_GET_FLOAT("developer") != 0)
		ALERT( at_logged,"[%s] dev: called: Meta_Query; version=%s, ours=%s\n", 
				Plugin_info.logtag, ifvers, Plugin_info.ifvers);

	// Check for valid pMetaUtilFuncs before we continue.
	if(!pMetaUtilFuncs) {
		ALERT( at_logged,"[%s] ERROR: Meta_Query called with null pMetaUtilFuncs\n", Plugin_info.logtag);
		return(FALSE);
	}
	gpMetaUtilFuncs=pMetaUtilFuncs;

	// Give metamod our plugin_info struct.
	*pPlugInfo=&Plugin_info;

	// Check for interface version compatibility.
	if(!FStrEq(ifvers, Plugin_info.ifvers)) {
		int mmajor=0, mminor=0, pmajor=0, pminor=0;
		LOG_MESSAGE(PLID, "WARNING: meta-interface version mismatch; requested=%s ours=%s",
				Plugin_info.logtag, ifvers);
		// If plugin has later interface version, it's incompatible (update
		// metamod).
		sscanf(ifvers, "%d:%d", &mmajor, &mminor);
		sscanf(META_INTERFACE_VERSION, "%d:%d", &pmajor, &pminor);
		if(pmajor > mmajor || (pmajor==mmajor && pminor > mminor)) {
			LOG_ERROR(PLID, "metamod version is too old for this plugin; update metamod");
			return(FALSE);
		}
		// If plugin has older major interface version, it's incompatible
		// (update plugin).
		else if(pmajor < mmajor) {
			LOG_ERROR(PLID, "metamod version is incompatible with this plugin; please find a newer version of this plugin");
			return(FALSE);
		}
		// Minor interface is older, but this is guaranteed to be backwards
		// compatible, so we warn, but we still accept it.
		else if(pmajor==mmajor && pminor < mminor)
			LOG_MESSAGE(PLID, "WARNING: metamod version is newer than expected; consider finding a newer version of this plugin");
		else
			LOG_ERROR(PLID, "unexpected version comparison; metavers=%s, mmajor=%d, mminor=%d; plugvers=%s, pmajor=%d, pminor=%d", ifvers, mmajor, mminor, META_INTERFACE_VERSION, pmajor, pminor);
	}
	return(TRUE);
}

// Metamod attaching plugin to the server.
//  now				(given) current phase, ie during map, during changelevel, or at startup
//  pFunctionTable	(requested) table of function tables this plugin catches
//  pMGlobals		(given) global vars from metamod
//  pGamedllFuncs	(given) copy of function tables from game dll

C_DLLEXPORT int Meta_Attach
(PLUG_LOADTIME now, META_FUNCTIONS *pFunctionTable, meta_globals_t *pMGlobals, gamedll_funcs_t *pGamedllFuncs)
{
	if(now > Plugin_info.loadable) {
		LOG_ERROR(PLID, "Can't load plugin right now");
		return(FALSE);
	}
	if(!pMGlobals) {
		LOG_ERROR(PLID, "Meta_Attach called with null pMGlobals");
		return(FALSE);
	}
	gpMetaGlobals=pMGlobals;
	if(!pFunctionTable) {
		LOG_ERROR(PLID, "Meta_Attach called with null pFunctionTable");
		return(FALSE);
	}
	memcpy(pFunctionTable, &gMetaFunctionTable, sizeof(META_FUNCTIONS));
	gpGamedllFuncs=pGamedllFuncs;
	// Let's go.
        tspp_init();

	return(TRUE);
}

// Metamod detaching plugin from the server.
// now		(given) current phase, ie during map, etc
// reason	(given) why detaching (refresh, console unload, forced unload, etc)

C_DLLEXPORT int Meta_Detach
(PLUG_LOADTIME now, PL_UNLOAD_REASON reason) 
{
	if(now > Plugin_info.unloadable && reason != PNL_CMD_FORCED) {
		LOG_ERROR(PLID, "Can't unload plugin right now");
		return(FALSE);
	}
	return(TRUE);
}
