/*
 * Jtag Boundary Scanner
 * Copyright (c) 2019 Viveris Technologies
 *
 * JTAG Boundary Scanner is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 3.0 of the License, or (at your option) any later version.
 *
 * JTAG Boundary Scanner is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License version 3 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Compate WinAPI for Linuxs; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

/**
* @file   configuration.h
* @brief  Declare configuration value.
* @author Sébastien CORBEAU <sebastien.corbeau@viveris.fr>
*/
#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include "jtag_core.h"

#define NO_REFRESH_VAL		0
#define REFRESH_20MS_VAL	20
#define REFRESH_200MS_VAL	200
#define REFRESH_1S_VAL		1000

#define DEFAULT_REFRESH_VAL	NO_REFRESH_VAL
#define DEFAULT_SCAN_MODE	JTAG_CORE_SAMPLE_SCANMODE

#endif /* CONFIGURATION_H_ */
