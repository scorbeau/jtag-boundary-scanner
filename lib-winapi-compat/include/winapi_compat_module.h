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
* @file   winapi_compat_module.h
* @brief  Define compatible WinAPI module loading for Linux.
* @author Sébastien CORBEAU <seb.corbeau@gmail.com>
*/
#ifndef WINAPI_COMPAT_MODULE_H__
#define WINAPI_COMPAT_MODULE_H__

#include <winapi_compat_base_type.h>

#ifdef __cplusplus
extern "C"{
#endif

HMODULE LoadLibrary(LPCSTR lpLibFileName);

BOOL FreeLibrary(HMODULE hLibModule);

FARPROC GetProcAddress(HMODULE hModule, LPCSTR lpProcName);

DWORD GetModuleFileName(HMODULE hModule, LPSTR lpFilename, DWORD nSize);

#ifdef __cplusplus
}
#endif

#endif /* WINAPI_COMPAT_MODULE_H__ */

