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
* @file   CpuTabCheckBox.cpp
* @brief  Implement class to store Fl_Check_Button of each pins.
* @author Sébastien CORBEAU <seb.corbeau@gmail.com>
*/

#include <gui/CpuPinCheckBox.h>

CpuPinCheckBox::CpuPinCheckBox(Fl_Check_Button *p_output,
			Fl_Check_Button *p_outputEnable,
			Fl_Check_Button *p_input,
			Fl_Check_Button *p_toggle)
{
	m_output = p_output;
	m_outputEnable = p_outputEnable;
	m_input = p_input;
	m_toggle = p_toggle;
}

int CpuPinCheckBox::getOutputState(void) const
{
	return (m_output) ? m_output->value() : -1;
}

int CpuPinCheckBox::getOutputEnableState(void) const
{
	return (m_outputEnable) ? m_outputEnable->value() : -1;
}

int CpuPinCheckBox::getInputState(void) const
{
	return (m_input) ? m_input->value() : -1;
}

int CpuPinCheckBox::getToggleState(void) const
{
	return (m_toggle) ? m_toggle->value() : -1;
}

void CpuPinCheckBox::setOutputState(int p_state)
{
	if(m_output) {
		if(p_state)
			m_output->set();
		else
			m_output->clear();
	}
}

void CpuPinCheckBox::setOutputEnableState(int p_state)
{
	if(m_outputEnable) {
		if(p_state)
			m_outputEnable->set();
		else
			m_outputEnable->clear();
	}
}

void CpuPinCheckBox::setInputState(int p_state)
{
	if(m_input) {
		if(p_state)
			m_input->set();
		else
			m_input->clear();
	}
}
