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
* @file   ProbeTab.h
* @brief  Declare Probe Tab GUI class.
* @author Sébastien CORBEAU <sebastien.corbeau@viveris.fr>
*/
#ifndef GUI_PROBETAB_H_
#define GUI_PROBETAB_H_

#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Choice.H>

#include "gui/TabsModel.h"
#include "gui/MainWindow.h"

#include "model/SystemData.h"

class ProbeTab : public TabsModel
{
public:
	ProbeTab(MainWindow *p_win,
			 int p_x,
			 int p_y,
			 int p_w,
			 int p_h,
			 const char *p_label = 0);
	~ProbeTab();
	void refresh(void);
	int getProbeIndex(void);
private:
	const SystemData *m_systemData;
	Fl_Button *m_connectBtn;
	Fl_Choice *m_probeChoice;
};

#endif /* GUI_PROBETAB_H_ */
