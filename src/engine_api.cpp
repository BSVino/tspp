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

#include <stdio.h>
#include <stdarg.h>

#include <extdll.h>

#include "engine_api.h"
#include "meta_api.h"

int	mState;

#ifdef DEBUG_OPTION
static FILE*fp;
#endif

void MessageBegin(int msg_dest, int msg_type, const float *pOrigin, edict_t *ed) {
	RETURN_META(MRES_IGNORED);
}

void MessageEnd(void) {
	RETURN_META(MRES_IGNORED);
}

void WriteByte(int iValue) {
	RETURN_META(MRES_IGNORED);
}
void WriteChar(int iValue) {
	RETURN_META(MRES_IGNORED);
}
void WriteShort(int iValue) {
	RETURN_META(MRES_IGNORED);
}
void WriteLong(int iValue) {
	RETURN_META(MRES_IGNORED);
}
void WriteAngle(float flValue) {
	RETURN_META(MRES_IGNORED);
}
void WriteCoord(float flValue) {
	RETURN_META(MRES_IGNORED);
}
void WriteString(const char *sz) {
	RETURN_META(MRES_IGNORED);
}
void WriteEntity(int iValue) {
	RETURN_META(MRES_IGNORED);
}

void TraceLine(const float *v1, const float *v2, int fNoMonsters, edict_t *pentToSkip, TraceResult *ptr) {
	RETURN_META(MRES_IGNORED);
}

enginefuncs_t meta_engfuncs;
C_DLLEXPORT int GetEngineFunctions(enginefuncs_t *pengfuncsFromEngine, int *interfaceVersion ) {
	meta_engfuncs.pfnMessageBegin = MessageBegin;
	meta_engfuncs.pfnMessageEnd = MessageEnd;
	meta_engfuncs.pfnWriteByte = WriteByte;
	meta_engfuncs.pfnWriteChar = WriteChar;
	meta_engfuncs.pfnWriteShort = WriteShort;
	meta_engfuncs.pfnWriteLong = WriteLong;
	meta_engfuncs.pfnWriteAngle = WriteAngle;
	meta_engfuncs.pfnWriteCoord = WriteCoord;
	meta_engfuncs.pfnWriteString = WriteString;
	meta_engfuncs.pfnWriteEntity =  WriteEntity;
	meta_engfuncs.pfnTraceLine = TraceLine;

	memcpy(pengfuncsFromEngine, &meta_engfuncs, sizeof(enginefuncs_t));
	return TRUE;
}
