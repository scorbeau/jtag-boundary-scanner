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
* @file   CpuTab.h
* @brief  Declare Cpu tab GUI class.
* @author Sébastien CORBEAU <seb.corbeau@gmail.com>
*/
#ifndef GUI_CPUTAB_H_
#define GUI_CPUTAB_H_

#include <vector>

#include <model/SystemData.h>
#include <gui/MainWindow.h>
#include <gui/CpuPinCheckBox.h>

class CpuTab : public TabsModel
{
public:
	CpuTab(MainWindow *p_win,
		   size_t p_cpuIndex,
		   int p_x,
		   int p_y,
		   int p_w,
		   int p_h,
		   const char *p_label = 0);
	~CpuTab();
	void refresh(void);
	int getCpuIndex(void);
	const CpuPinCheckBox* getPinCheckBoxes(size_t p_index) const;
private:
	const SystemData *m_systemData;
	std::vector<CpuPinCheckBox*> m_cpuPinCheckBoxes;
	size_t m_cpuIndex;
};

#endif /* GUI_CPUTAB_H_ */
