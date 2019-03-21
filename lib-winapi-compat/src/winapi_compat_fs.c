/*
 * Compate WinAPI for Linux
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
* @file   winapi_compat_fs.c
* @brief  Implement compatible filesystem functions from WinAPI for Linux.
* @author Sébastien CORBEAU <seb.corbeau@gmail.com>
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h> 
#include <unistd.h>

#include <dirent.h>

#include <winapi_compat.h>

struct file_handle_t
{
	size_t		size;
	uint32_t	magic;
	DIR		*pdir;
	char		currentPath[MAX_PATH];
};

static int getFileStat(const char* path,
		       const char* filename,
		       LPWIN32_FIND_DATAA lpFindFileData);

HANDLE FindFirstFile(LPCSTR lpFileName, LPWIN32_FIND_DATAA lpFindFileData)
{
	struct file_handle_t *handle = NULL;
	struct dirent *ep;
	struct stat stats;
	char filePath[MAX_PATH*2];

	if(!lpFileName || !lpFindFileData) {
		SetLastError(ERROR_INVALID_PARAMETER);
		return INVALID_HANDLE_VALUE;
	}

	memset(lpFindFileData, 0, sizeof(*lpFindFileData));

	if(NULL == (handle = malloc(sizeof(*handle)))) {
		SetLastError(ERROR_NOT_ENOUGH_MEMORY);
		return INVALID_HANDLE_VALUE;
	} else {
		handle->size = sizeof(*handle);
		handle->magic = HANDLE_COMPAT_FS_MAGIC;
		handle->pdir = NULL;

		if(-1 == lstat(lpFileName, &stats)) {
			SetLastError(ERROR_FILE_NOT_FOUND);
			goto exit_error;
		} else if(!S_ISDIR(stats.st_mode)) {
			SetLastError(ERROR_FILE_NOT_FOUND);
			goto exit_error;
		} else if(NULL == (handle->pdir = opendir(lpFileName))) {
			SetLastError(ERROR_FILE_NOT_FOUND);
			goto exit_error;
		} else {
			//TODO Check error
			strncpy(handle->currentPath,
			lpFileName,
			sizeof(handle->currentPath));

			ep = readdir(handle->pdir);
			if(ep) {
				if(getFileStat(handle->currentPath,
					       ep->d_name,
					       lpFindFileData)) {
					//TODO: Set error code
					goto exit_error;
				}
				snprintf(filePath,
					 sizeof(filePath),
					 "%s",
					 ep->d_name);
				SetLastError(ERROR_SUCCESS);
			} else {
				SetLastError(ERROR_NO_MORE_FILES);
				goto exit_error;
			}
		}
	}

	return handle;
exit_error:
	if(handle) {
		if(handle->pdir)
			(void) closedir(handle->pdir);
		free(handle);
	}
	return INVALID_HANDLE_VALUE;
}

BOOL FindNextFile(HANDLE hFindFile, LPWIN32_FIND_DATAA lpFindFileData)
{
	struct file_handle_t *handle = (struct file_handle_t *) hFindFile;
	struct dirent *ep;
	BOOL ret = false;

	if(!handle ||
	   (sizeof(*handle) != handle->size) ||
	   (HANDLE_COMPAT_FS_MAGIC != handle->magic)) {
		SetLastError(ERROR_INVALID_PARAMETER);
		return false;
	}

	ep = readdir(handle->pdir);
	if(ep) {
		if(getFileStat(handle->currentPath, ep->d_name, lpFindFileData)) {
			//TODO: Set error code
			ret = false;
		} else {
			SetLastError(ERROR_SUCCESS);
			ret = true;
		}
	} else {
		ret = false;
		SetLastError(ERROR_NO_MORE_FILES);
	}

	return ret;
}

BOOL FindClose(HANDLE hFindFile)
{
	BOOL ret = false;
	struct file_handle_t *handle = (struct file_handle_t *)hFindFile;

	if(!handle ||
	  (sizeof(*handle) != handle->size) ||
	  (HANDLE_COMPAT_FS_MAGIC != handle->magic)) {
		SetLastError(ERROR_INVALID_PARAMETER);
		return false;
	}

	SetLastError(ERROR_SUCCESS);
	if(handle->pdir)
		(void) closedir(handle->pdir);
	free(handle);
	ret = true;

	return ret;
}

static int getFileStat(const char* path,
		       const char* filename,
		       LPWIN32_FIND_DATAA lpFindFileData)
{
	char filePath[MAX_PATH*2];
	struct stat stats;
	int err;

	snprintf(filePath, sizeof(filePath)-1, "%s/%s", path, filename);

	if(0 == (err = lstat(filePath, &stats))) {
		if(S_ISDIR(stats.st_mode)) {
			lpFindFileData->dwFileAttributes =
					FILE_ATTRIBUTE_DIRECTORY;
			if(0 == (stats.st_mode&(S_IWUSR|S_IWGRP|S_IWOTH))) {
				lpFindFileData->dwFileAttributes |=
						FILE_ATTRIBUTE_READONLY;
			}
		} else if(S_ISREG(stats.st_mode)) {
			if(0 == (stats.st_mode&(S_IWUSR|S_IWGRP|S_IWOTH))) {
				lpFindFileData->dwFileAttributes =
						FILE_ATTRIBUTE_READONLY;
			} else {
				lpFindFileData->dwFileAttributes =
						FILE_ATTRIBUTE_NORMAL;
			}
		} else {
			lpFindFileData->dwFileAttributes = 0;
		}

		lpFindFileData->nFileSizeHigh = stats.st_size >> 4;
		lpFindFileData->nFileSizeLow = stats.st_size & 0xFFFFFFFF;

		strncpy(lpFindFileData->cFileName, filename, MAX_PATH-1);
	}

	return err;
}

