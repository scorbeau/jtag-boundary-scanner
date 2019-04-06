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
* @file   PinData.cpp
* @brief  Implements class PinData model.
* @author Sébastien CORBEAU <sebastien.corbeau@viveris.fr>
*/
#include "model/PinData.h"

#include <jtag_core.h>

PinData::PinData(std::string p_name, size_t p_chainIndex, int  p_type)
{
	m_name = p_name;
	m_chainIndex = p_chainIndex;
	m_type = p_type;

	m_inputState = false;
	m_outputEnableState = false;
	m_outputState = false;
	m_toggleState = false;
}

std::string PinData::getName(void) const
{
	return m_name;
}

size_t PinData::getPinJtagChainIndex(void) const
{
	return m_chainIndex;
}

bool PinData::isPinUsable(void) const
{
	return m_type ? true : false;
}

bool PinData::isInput(void) const
{
	return m_type&JTAG_CORE_PIN_IS_INPUT ? true : false;
}

bool PinData::isOutput(void) const
{
	return m_type&JTAG_CORE_PIN_IS_OUTPUT ? true : false;
}

bool PinData::isTristate(void) const
{
	return m_type&JTAG_CORE_PIN_IS_TRISTATES ? true : false;
}

bool PinData::getInputState(void) const
{
	return m_inputState;
}

void PinData::updateInputState(bool p_state)
{
	m_inputState = p_state;
}

bool PinData::getOutputEnableState(void) const
{
	return m_outputEnableState;
}

void PinData::setOutputEnableState(bool p_state)
{
	m_outputEnableState = p_state;
}

bool PinData::getOutputState(void) const
{
	return m_outputState;
}

void PinData::setOutputState(bool p_state)
{
	m_outputState = p_state;
}

bool PinData::getToggleState(void) const
{
	return m_toggleState;
}

void PinData::setToggleState(bool p_state)
{
	m_toggleState = p_state;
}

