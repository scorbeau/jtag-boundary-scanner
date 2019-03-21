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
* @file   winapi_compat_fs.h
* @brief  Declare compatible filesystem functions from WinAPI for Linux.
* @author Sébastien CORBEAU <seb.corbeau@gmail.com>
*/
#ifndef WINAPI_COMPAT_FS_H__
#define WINAPI_COMPAT_FS_H__

#include <winapi_compat_base_type.h>

typedef struct _FILETIME {
	DWORD dwLowDateTime;
	DWORD dwHighDateTime;
} FILETIME, *PFILETIME, *LPFILETIME;

typedef struct _WIN32_FIND_DATAA {
	DWORD		dwFileAttributes;
	FILETIME	ftCreationTime;
	FILETIME	ftLastAccessTime;
	FILETIME	ftLastWriteTime;
	DWORD		nFileSizeHigh;
	DWORD		nFileSizeLow;
	DWORD		dwReserved0;
	DWORD		dwReserved1;
	CHAR		cFileName[MAX_PATH];
	CHAR		cAlternateFileName[14];
	DWORD		dwFileType;
	DWORD		dwCreatorType;
	WORD		wFinderFlags;
} WIN32_FIND_DATAA, *PWIN32_FIND_DATAA, *LPWIN32_FIND_DATAA;

/* dwFileAttributes code */
#define FILE_ATTRIBUTE_READONLY			(1<<0)
#define FILE_ATTRIBUTE_HIDDEN			(1<<1)
#define FILE_ATTRIBUTE_SYSTEM			(1<<2)
#define FILE_ATTRIBUTE_DIRECTORY		(1<<4)
#define FILE_ATTRIBUTE_ARCHIVE			(1<<5)
#define FILE_ATTRIBUTE_DEVICE			(1<<6)
#define FILE_ATTRIBUTE_NORMAL			(1<<7)
#define FILE_ATTRIBUTE_TEMPORARY		(1<<8)
#define FILE_ATTRIBUTE_SPARSE_FILE		(1<<9)
#define FILE_ATTRIBUTE_REPARSE_POINT		(1<<10)
#define FILE_ATTRIBUTE_COMPRESSED		(1<<11)
#define FILE_ATTRIBUTE_OFFLINE			(1<<12)
#define FILE_ATTRIBUTE_NOT_CONTENT_INDEXED	(1<<13)
#define FILE_ATTRIBUTE_ENCRYPTED		(1<<14)
#define FILE_ATTRIBUTE_INTEGRITY_STREAM		(1<<15)
#define FILE_ATTRIBUTE_VIRTUAL			(1<<16)
#define FILE_ATTRIBUTE_NO_SCRUB_DATA		(1<<17)
#define FILE_ATTRIBUTE_RECALL_ON_OPEN		(1<<18)
#define FILE_ATTRIBUTE_RECALL_ON_DATA_ACCESS	(1<<22)

#ifdef __cplusplus
extern "C"{
#endif

HANDLE FindFirstFile(LPCSTR lpFileName, LPWIN32_FIND_DATAA lpFindFileData);

BOOL FindNextFile(HANDLE hFindFile, LPWIN32_FIND_DATAA lpFindFileData);

BOOL FindClose(HANDLE hFindFile);

#ifdef __cplusplus
}
#endif

#endif /* WINAPI_COMPAT_FS_H__ */

