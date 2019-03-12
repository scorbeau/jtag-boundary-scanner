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

PinData::PinData(std::string p_name,
                   int  p_type,
                   bool p_inputState,
                   bool p_outputEnableState,
                   bool p_outputState,
                   bool p_toggleState)
{
    m_name = p_name;
    m_type = p_type;
    m_inputState = p_inputState;
    m_outputEnableState = p_outputEnableState;
    m_outputState = p_outputState;
    m_toggleState = p_toggleState;
}

std::string PinData::getName(void)
{
    return m_name;
}

bool PinData::isPinUsable(void)
{
    return m_type ? true : false;
}

bool PinData::isInputPin(void)
{
    return m_type&JTAG_CORE_PIN_IS_INPUT ? true : false;
}

bool PinData::isOutputPin(void)
{
    return m_type&JTAG_CORE_PIN_IS_OUTPUT ? true : false;
}

bool PinData::isTristatePin(void)
{
    return m_type&JTAG_CORE_PIN_IS_TRISTATES ? true : false;
}

bool PinData::getInputState(void)
{
    return m_inputState;
}

bool PinData::getOutputEnableState(void)
{
    return m_outputEnableState;
}

void PinData::setOutputEnableState(bool p_state)
{
    m_outputEnableState = p_state;
}

bool PinData::getOutputState(void)
{
    return m_outputState;
}

void PinData::setOutputState(bool p_state)
{
    m_outputState = p_state;
}

bool PinData::getToggleState(void)
{
    return m_toggleState;
}

void PinData::setToggleState(bool p_state)
{
    m_toggleState = p_state;
}

