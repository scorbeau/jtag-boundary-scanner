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
* @brief  Test compatible WinAPI load module.
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

#define MODULE_NAME	"./libmodule-load.so"
#define PRINT_FCT_NAME	"module_print_message"
#define ADD_FCT_NAME	"module_add_2_number"

typedef void(*PRINTF_FCT)(void);
typedef int(*ADD_FCT)(int, int);

int main(int argc, char *argv[])
{
	int err = 0;
	HMODULE module = NULL;
	PRINTF_FCT printFct = NULL;
	ADD_FCT addFct = NULL;

	(void) argc;
	(void) argv;

	if(NULL == (module = LoadLibrary(MODULE_NAME))) {
		printf("Failed load module %s error %ld\n",
		       MODULE_NAME, GetLastError());
		err = 1;
	} else if(NULL == (printFct = GetProcAddress(module, PRINT_FCT_NAME))) {
		printf("Failed load function %s error %ld\n",
		PRINT_FCT_NAME, GetLastError());
		err = 1; 
	} else if(NULL == (addFct = GetProcAddress(module, ADD_FCT_NAME))) {
		printf("Failed load function %s error %ld\n",
		ADD_FCT_NAME, GetLastError());
		err = 1;
	} else {
		printf("Module and function loading !\n");
		printFct();
		printf("addFct(1, 2) = %d\n", addFct(1, 2));
	}

	if(NULL != module) {
		if(!FreeLibrary(module)) {
			printf("Failed to unload %s error %ld\n", MODULE_NAME,
			GetLastError());
			err = 1;
		} else {
			printf("Module free\n");
		}
	}

	return err;
}

