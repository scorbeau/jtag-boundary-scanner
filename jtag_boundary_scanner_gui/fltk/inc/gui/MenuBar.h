/*
 * Jtag Boundary Scanner
 * Copyright (c) 2019 Viveris Technologies
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
* @file   MenuBar.h
* @brief  Declare MenuBar of main windows.
* @author Sébastien CORBEAU <sebastien.corbeau@viveris.fr>
*/
#ifndef GUI_MENUBAR_H_
#define GUI_MENUBAR_H_

#include <FL/Fl.H>
#include <FL/Fl_Menu_Bar.H>

class MenuBar : public Fl_Menu_Bar
{
public:
	MenuBar(int p_width);
	~MenuBar();

	void resize(int x, int y, int w, int h);

	static const int MENU_BAR_HEIGHT = 25;
};

#endif /* GUI_MENUBAR_H_ */
