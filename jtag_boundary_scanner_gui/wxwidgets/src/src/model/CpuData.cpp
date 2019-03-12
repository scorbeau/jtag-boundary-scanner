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
* @file   CpuData.cpp
* @brief  Implements class CpuData model.
* @author Sébastien CORBEAU <sebastien.corbeau@viveris.fr>
*/
#include "model/CpuData.h"

CpuData::CpuData()
{
    m_name = "Unknown";
    m_jtagid = -1;
}

CpuData::CpuData(std::string p_name, unsigned long p_cpuid, int p_jtagid)
{
    m_name = p_name;
    m_cpuid = p_cpuid;
    m_jtagid = p_jtagid;
}

CpuData::~CpuData()
{
    while(!m_pins.empty()) {
        PinData *pin = m_pins.back();
        m_pins.pop_back();
        delete pin;
    }

    while(!m_unusablePins.empty())
    {
        PinData *pin = m_unusablePins.back();
        m_unusablePins.pop_back();
        delete pin;
    }
}

std::string CpuData::getCpuName(void)
{
    return m_name;
}

unsigned long CpuData::getCpuId(void)
{
    return m_cpuid;
}

int CpuData::getJtagId(void)
{
    return m_jtagid;
}

void CpuData::addPin(std::string p_name,
                     int  p_type,
                     bool p_inputState,
                     bool p_outputEnableState,
                     bool p_outputState,
                     bool p_toggleState)
{
    // Create gpio
    PinData *pin = new PinData(p_name,
                               p_type,
                               p_inputState,
                               p_outputEnableState,
                               p_outputState,
                               p_toggleState);
    // Incrment if gpio is usable
    if(pin->isPinUsable()) {
        // Add gpio to processor
        m_pins.push_back(pin);
    } else {
        m_unusablePins.push_back(pin);
    }
}

PinData* CpuData::getPinData(size_t index)
{
    if(index < m_pins.size())
        return m_pins[index];

    return NULL;
}

PinData* CpuData::getUnusablePinData(size_t index)
{
    if(index < m_unusablePins.size())
        return m_unusablePins[index];

    return NULL;
}

void CpuData::enablePinToggle(size_t index, bool toggle)
{
    if(index < m_pins.size())
        m_pins[index]->setToggleState(toggle);
}

void CpuData::setPinOutput(size_t index, bool state)
{
    if(index < m_pins.size())
        m_pins[index]->setOutputState(state);
}

void CpuData::setPinOutputEnable(size_t index, bool state)
{
    if(index < m_pins.size())
        m_pins[index]->setOutputEnableState(state);
}

bool CpuData::getPinToggle(size_t index)
{
    if(index < m_pins.size())
        return m_pins[index]->getInputState();

    return false;
}

size_t CpuData::getNbPins(void)
{
    return m_pins.size() + m_unusablePins.size();
}

size_t CpuData::getNbUsablePins(void)
{
    return m_pins.size();
}

