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
* @file   TestTab.cpp
* @brief  Implement TODO.
* @author Sébastien CORBEAU <sebastien.corbeau@viveris.fr>
*/
#include <stdio.h>

#include <FL/Fl_Scroll.H>
#include <FL/Fl_Button.H>

#include <gui/TestTab.h>
#include <gui/MainWindow.h>

TestTab::TestTab(int p_x, int p_y, int p_w, int p_h, const char *p_label)
		: TabsModel(p_x, p_y, p_w, p_h, p_label, false)
{
	Fl_Scroll *scroll = new Fl_Scroll(p_x+TabsModel::SCROLL_BORDER,
									  p_y+TabsModel::SCROLL_BORDER,
									  p_w-(2*TabsModel::SCROLL_BORDER),
									  p_h-(2*TabsModel::SCROLL_BORDER));
	new Fl_Button(60, 90,200,25,"But 1 Tab Seb");
	new Fl_Button(60, 120,200,25,"But 2 Tab Seb");
	scroll->end();
}

TestTab::~TestTab()
{

}

void TestTab::refresh(void)
{

}
