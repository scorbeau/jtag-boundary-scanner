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
* @file   main.c
* @brief  Test compatible WinAPI get CurrentDirectory.
* @author Sébastien CORBEAU <seb.corbeau@gmail.com>
*/
#include <stdio.h>
#include <stdlib.h>

#if defined(WIN32) || defined(_WIN32)
	#include <windows.h>
#elif defined(__linux__)
	#include <winapi_compat.h>
#else
	#error "This programs only runs on Windows or Linux"
#endif

#define PATH_SIZE	256

int main(int argc, char *argv[])
{
	DWORD dwRet;
	CHAR  filename[PATH_SIZE];
	int err = 0;

	(void)argc;
	(void)argv;

	dwRet = GetModuleFileName(NULL, filename, sizeof(filename));
	if(!dwRet) {
		printf("Failed to get current path err: %ld\n", GetLastError());
		err = 1;
	} else if((dwRet == sizeof(filename)) && 
		  (GetLastError() == ERROR_INSUFFICIENT_BUFFER)) {
		printf("Buffer size is too short\n");
		err = 1;
	} else {
		printf("Current path: %s Size: %ld\n", filename, dwRet);
		err = 0;
	}

	return err;
}

