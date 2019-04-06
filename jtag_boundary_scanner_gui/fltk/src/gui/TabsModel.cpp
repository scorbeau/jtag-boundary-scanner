/*
 * Jtag Boundary Scanner
 * Copyright (c) 2019 S. Corbeau
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
* @file   TabsModel.cpp
* @brief  Implement tab model.
* @author Sébastien CORBEAU <seb.corbeau@gmail.com>
*/

#include <gui/TabsModel.h>

TabsModel::TabsModel(int p_x,
					 int p_y,
					 int p_w,
					 int p_h,
					 const char* p_label,
					 bool p_isCpuTab)
		: Fl_Group(p_x, p_y, p_w, p_h, p_label)
{
	m_isCpu = p_isCpuTab;
}

TabsModel::~TabsModel()
{
}

bool TabsModel::isCpuTab()
{
	return m_isCpu;
}

