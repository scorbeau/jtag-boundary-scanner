/*
 * JTAG Boundary Scanner
 * Copyright (c) 2008 - 2019 Viveris Technologies
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
 * along with JTAG Boundary Scanners; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

/**
* @file   PinData.h
* @brief  Define class PinData model.
* @author Sébastien CORBEAU <sebastien.corbeau@viveris.fr>
*/
#ifndef MODEL_PIN_DATA_H__
#define MODEL_PIN_DATA_H__

#include <string>
#include <vector>

class PinData
{
public:
	PinData(std::string p_name, size_t p_chainIndex, int p_type = 0);

	std::string getName(void) const;

	size_t getPinJtagChainIndex(void) const;

	bool isPinUsable(void) const;

	bool isInput(void) const;
	bool isOutput(void) const;
	bool isTristate(void) const;

	bool getInputState(void) const;
	void updateInputState(bool p_state);

	bool getOutputEnableState(void) const;
	void setOutputEnableState(bool p_state);

	bool getOutputState(void) const;
	void setOutputState(bool p_state);

	bool getToggleState(void) const;
	void setToggleState(bool p_state);
private:
	std::string m_name;
	int  m_type;

	size_t m_chainIndex;

	bool m_inputState;
	bool m_outputEnableState;
	bool m_outputState;
	bool m_toggleState;
};
#endif /*  MODEL_PIN_DATA_H__ */

