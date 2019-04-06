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
* @file   VirtualTabs.h
* @brief  Declare TODO.
* @author Sébastien CORBEAU <seb.corbeau@gmail.com>
*/
#ifndef GUI_TABSMODEL_H_
#define GUI_TABSMODEL_H_

#include <FL/Fl_Group.H>
#include <FL/Fl_Scroll.H>

class TabsModel : public Fl_Group {
public:
	TabsModel(int p_x,
			  int p_y,
			  int p_w,
			  int p_h,
			  const char* p_label=0,
			  bool p_isCpuTab = false);
	~TabsModel();
	bool isCpuTab();

	virtual void refresh(void) = 0;

	static const int SCROLL_BORDER = 10;
private:
	bool m_isCpu;
};



#endif /* GUI_TABSMODEL_H_ */
