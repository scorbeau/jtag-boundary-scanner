/*
 * Compat WinAPI for Linux
 * Copyright (c) 2008 - 2019 S. Corbeau
 *
 * Compate WinAPI for Linux is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 3.0 of the License, or (at your option) any later version.
 *
 * Compate WinAPI for Linux is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License version 3 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Compate WinAPI for Linuxs; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

/**
* @file   winapi_compat_module.c
* @brief  Implement compatible WinAPI module loading for Linux.
* @author Sébastien CORBEAU <seb.corbeau@gmail.com>
*/
#include <dlfcn.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <winapi_compat_error.h>
#include <winapi_compat_module.h>

HMODULE LoadLibrary(LPCSTR lpLibFileName)
{
	HMODULE ret = NULL;
	if(!lpLibFileName) {
		SetLastError(ERROR_INVALID_PARAMETER);
		return NULL;
	}

	SetLastError(ERROR_SUCCESS);

	dlerror();
	ret =  dlopen(lpLibFileName, RTLD_NOW);

	//TODO: Check return and SetLastError

	return ret;
}

BOOL FreeLibrary(HMODULE hLibModule)
{
	if(!hLibModule) {
	SetLastError(ERROR_INVALID_PARAMETER);
		return false;
	}

	SetLastError(ERROR_SUCCESS);
	dlerror();
	if(0 != dlclose(hLibModule)) {
		//TODO: SetLastError ?
		return false;
	}

	return true;
}

FARPROC GetProcAddress(HMODULE hModule, LPCSTR lpProcName)
{
	FARPROC ret = NULL;
	if(!hModule || !lpProcName) {
		SetLastError(ERROR_INVALID_PARAMETER);
		return NULL;
	}

	SetLastError(ERROR_SUCCESS);
	dlerror();
	ret = dlsym(hModule, lpProcName);
	//TODO: Check error and return last error

	return ret;
}

DWORD GetModuleFileName(HMODULE hModule, LPSTR lpFilename, DWORD nSize)
{
	DWORD ret = 0;

	if(hModule != NULL) {
		SetLastError(ERROR_NOT_SUPPORTED);
		return 0;
	}

	if(!lpFilename || (nSize <= 0)) {
		SetLastError(ERROR_INVALID_PARAMETER);
		return 0;
	}

	if(-1 == (ret = readlink("/proc/self/exe", lpFilename, nSize))) {
		if(errno == ENAMETOOLONG) {
			SetLastError(ERROR_INSUFFICIENT_BUFFER);
			lpFilename[nSize-1] = '\0';
			ret = nSize;
		} else {
			//TODO: Add last error code
			ret = 0;
		}
	} else {
		SetLastError(ERROR_SUCCESS);
	}

	return ret;
}

