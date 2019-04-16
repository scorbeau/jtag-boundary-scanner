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
* @file   AboutWindow.h
* @brief  Declare class to manage About window.
* @author Sébastien CORBEAU <sebastien.corbeau@viveris.fr>
*/
#ifndef GUI_ABOUTWINDOW_H_
#define GUI_ABOUTWINDOW_H_

#include <FL/Fl.H>
#include <FL/Fl_Window.H>

class AboutWindow : public Fl_Window
{
public:
	AboutWindow(const char *p_applName);
	~AboutWindow();
};

#endif /* GUI_ABOUTWINDOW_H_ */
