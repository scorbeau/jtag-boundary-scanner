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
* @file   Tabs.h
* @brief  Declare tabs index.
* @author Sébastien CORBEAU <seb.corbeau@gmail.com>
*/
#ifndef GUI_TABSMENU_H_
#define GUI_TABSMENU_H_

#include <FL/Fl.H>
#include <FL/Fl_Tabs.H>

#include <gui/TabsModel.h>

class TabsMenu : public Fl_Tabs
{
public:
	TabsMenu(int p_x, int p_y, int p_w, int p_h);
	~TabsMenu();

	void resize(int p_x, int p_y, int p_w, int p_h);
	void addTabs(TabsModel *tabs);
	void deleteTabs(const char* name);

	static const int TABS_MENU_HEIGHT = 12;
	static const int TABS_MENU_BOARDER = 10;
};

#endif /* GUI_TABSMENU_H_ */
