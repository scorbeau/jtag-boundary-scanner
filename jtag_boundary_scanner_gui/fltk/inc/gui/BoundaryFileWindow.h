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
* @file   BoundaryFileWindow.h
* @brief  Declare Boundary file selector window.
* @author Sébastien CORBEAU <sebastien.corbeau@viveris.fr>
*/
#ifndef GUI_BOUNDARYFILEWINDOW_H_
#define GUI_BOUNDARYFILEWINDOW_H_

#include <string>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Input.H>

#include "model/CpuData.h"

class BoundaryFileWindow : public Fl_Window
{
public:
	BoundaryFileWindow(const char *p_applName, const CpuData* p_cpu);
	~BoundaryFileWindow();

	void setCancelRequest(bool cancel = true);
	bool isCancelRequest(void);

	void selectInstallBsdlChoice(bool selectInstallBsdl = true);

	void setSelectedBsdlPath(const char* path);

	bool isInstalledBsdl(void);
	int getInstalledBsdlIndex(void);

	std::string getBsdlPath(void);
private:
	bool m_cancelRequest;

	Fl_Choice *m_bsdlChoice;
	Fl_Input  *m_bsdlInput;
	Fl_Button *m_selectFileBtn;
};

#endif /* GUI_BOUNDARYFILEWINDOW_H_ */
