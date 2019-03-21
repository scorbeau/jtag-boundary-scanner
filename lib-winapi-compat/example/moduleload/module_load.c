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
* @file   module_load.c
* @brief  Implement a module to load interface.
* @author Sébastien CORBEAU <seb.corbeau@gmail.com>
*/
#include <stdio.h>
#if defined(WIN32) || defined(_WIN32)
	#include <windows.h>
#elif defined(__linux__)
	#include <winapi_compat.h>
#else
	#error "This programs only runs on Windows or Linux"
#endif

#include "module_load.h"

void module_print_message(void)
{
	printf("Helloworld from %s\n", __FUNCTION__);
}

int module_add_2_number(int a, int b)
{
	return a + b;
}

