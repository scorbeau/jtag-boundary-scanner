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
* @file   CpuTabCheckBox.h
* @brief  Declare class to store Fl_Check_Button of each pins.
* @author Sébastien CORBEAU <sebastien.corbeau@viveris.fr>
*/
#ifndef GUI_CPUPINCHECKBOX_H_
#define GUI_CPUPINCHECKBOX_H_

#include <FL/Fl.H>
#include <FL/Fl_Check_Button.H>

class CpuPinCheckBox {
public:
	CpuPinCheckBox(Fl_Check_Button *p_output,
			Fl_Check_Button *p_outEnable,
			Fl_Check_Button *p_input,
			Fl_Check_Button *p_toggle);

	int getOutputState(void) const;
	int getOutputEnableState(void) const;
	int getInputState(void) const;
	int getToggleState(void) const;

	void setOutputState(int p_state);
	void setOutputEnableState(int p_state);
	void setInputState(int p_state);

	void toggleOutputState(void);
private:
	Fl_Check_Button *m_output;
	Fl_Check_Button *m_outputEnable;
	Fl_Check_Button *m_input;
	Fl_Check_Button *m_toggle;
};

#endif /* GUI_CPUPINCHECKBOX_H_ */
