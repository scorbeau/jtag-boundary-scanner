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
* @file   module_load.h
* @brief  Define a module to load interface.
* @author Sébastien CORBEAU <seb.corbeau@gmail.com>
*/

#ifndef MODULE_LOAD_H__
#define MODULE_LOAD_H__

#ifdef __cplusplus
extern "C"{
#endif

void module_print_message(void);
int module_add_2_number(int a, int b);

#ifdef __cplusplus
}
#endif

#endif /* MODULE_LOAD_H__ */

