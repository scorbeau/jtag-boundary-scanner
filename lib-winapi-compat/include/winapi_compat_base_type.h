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
* @file   winapi_compat_base_type.h
* @brief  Define compatible WinAPI type for Linux.
* @author Sébastien CORBEAU <seb.corbeau@gmail.com>
*/
#ifndef WINAPI_COMPAT_BASE_TYPE_H__
#define WINAPI_COMPAT_BASE_TYPE_H__

#include <stdbool.h>

typedef char		CHAR;
typedef bool		BOOL;
typedef unsigned short	WORD;
typedef unsigned long	DWORD;

typedef char*		PSTR, *LPSTR;
typedef const char*	LPCSTR;

typedef void*		HMODULE;
typedef void*		HANDLE;
typedef void*		FARPROC;

#define INVALID_HANDLE_VALUE	NULL

#define MAX_PATH		260

#endif /* WINAPI_COMPAT_BASE_TYPE_H__ */

