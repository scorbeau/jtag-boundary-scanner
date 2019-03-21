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
* @file   winapi_compat_error.h
* @brief  Declare compatible error function WinAPI for Linux.
* @author Sébastien CORBEAU <seb.corbeau@gmail.com>
*/
#ifndef WINAPI_COMPAT_ERROR_H__
#define WINAPI_COMPAT_ERROR_H__

#include <winapi_compat_base_type.h>

enum {
	ERROR_SUCCESS = 0,
	ERROR_FILE_NOT_FOUND = 2,
	ERROR_NOT_ENOUGH_MEMORY = 8,
	ERROR_NO_MORE_FILES = 18,
	ERROR_NOT_SUPPORTED = 50,
	ERROR_INVALID_PARAMETER = 87,
	ERROR_INSUFFICIENT_BUFFER = 122,
};

#ifdef __cplusplus
extern "C"{
#endif

void SetLastError(DWORD dwErrCode);

DWORD GetLastError(void);

#ifdef __cplusplus
}
#endif

#endif /* WINAPI_COMPAT_ERROR_H__ */

