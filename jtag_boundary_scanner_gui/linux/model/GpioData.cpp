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
* @file   GpioData.cpp
* @brief  Implements class GpioData model.
* @author Sébastien CORBEAU <sebastien.corbeau@viveris.fr>
*/
#include "GpioData.h"

#include <jtag_core.h>

GpioData::GpioData(std::string p_name,
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

std::string GpioData::getName(void)
{
    return m_name;
}

bool GpioData::isGpioUsable(void)
{
    return m_type ? true : false;
}

bool GpioData::isInputGpio(void)
{
    return m_type&JTAG_CORE_PIN_IS_INPUT ? true : false;
}

bool GpioData::isOutputGpio(void)
{
    return m_type&JTAG_CORE_PIN_IS_OUTPUT ? true : false;
}

bool GpioData::isTristateGpio(void)
{
    return m_type&JTAG_CORE_PIN_IS_TRISTATES ? true : false;
}

bool GpioData::getInputState(void)
{
    return m_inputState;
}

bool GpioData::getOutputEnableState(void)
{
    return m_outputEnableState;
}

void GpioData::setOutputEnableState(bool p_state)
{
    m_outputEnableState = p_state;
}

bool GpioData::getOutputState(void)
{
    return m_outputState;
}

void GpioData::setOutputState(bool p_state)
{
    m_outputState = p_state;
}

bool GpioData::getToggleState(void)
{
    return m_toggleState;
}

void GpioData::setToggleState(bool p_state)
{
    m_toggleState = p_state;
}

