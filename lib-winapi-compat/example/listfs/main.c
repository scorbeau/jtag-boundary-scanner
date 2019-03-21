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
* @brief  Test compatible WinAPI list current dir.
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
	HANDLE hFind = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATAA findFileData = { 0 };
	int err = 0;

	if(argc < 2) {
		printf("Usage : \n %s <directory>\n", argv[0]);
		return 1;
	}

	hFind = FindFirstFile(argv[1], &findFileData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		printf("File contains in \"%s\" :\n", argv[1]);
		do
		{
			printf("\t- \"%s/%s\" ",
			       argv[1],
			       findFileData.cFileName);
			if(!(findFileData.dwFileAttributes &
			     FILE_ATTRIBUTE_DIRECTORY)) {
				printf("is regular file.\n");
			} else {
				printf("is directory.\n");
			}
		}while(FindNextFile(hFind, &findFileData));

		if(!FindClose(hFind)) {
			printf("Failed to close handle error %ld\n",
			       GetLastError());
			err = 1;
		} else {
			err = 0;
		}
	} else {
		printf("Failed to get informations of %s error %ld\n",
		       argv[1], GetLastError());
		err = 1;
	}

	return err;
}

