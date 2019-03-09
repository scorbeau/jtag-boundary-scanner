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
* @file   ProcessorData.cpp
* @brief  Implements class ProcessorData model.
* @author Sébastien CORBEAU <sebastien.corbeau@viveris.fr>
*/
#include "ProcessorData.h"

ProcessorData::ProcessorData()
{
    m_name = "Unknown";
    m_nbUsableGpios = 0;
    m_jtagid = -1;
}

ProcessorData::ProcessorData(std::string p_name, unsigned long p_cpuid,
                             int p_jtagid)
{
    m_name = p_name;
    m_cpuid = p_cpuid;
    m_jtagid = p_jtagid;
    m_nbUsableGpios = 0;
}

ProcessorData::~ProcessorData()
{
    m_nbUsableGpios = 0;
    while(!m_gpios.empty()) {
        GpioData *gpio = m_gpios.back();
        m_gpios.pop_back();
        delete gpio;
    }
}

std::string ProcessorData::getProcessorName(void)
{
    return m_name;
}

unsigned long ProcessorData::getProcessorId(void)
{
    return m_cpuid;
}

int ProcessorData::getJtagId(void)
{
    return m_jtagid;
}

void ProcessorData::addGpio(std::string p_name,
                            int  p_type,
                            bool p_inputState,
                            bool p_outputEnableState,
                            bool p_outputState,
                            bool p_toggleState)
{
    // Create gpio
    GpioData *gpio = new GpioData(p_name,
                                  p_type,
                                  p_inputState,
                                  p_outputEnableState,
                                  p_outputState,
                                  p_toggleState);
    // Incrment if gpio is usable
    if(gpio->isGpioUsable())
        m_nbUsableGpios++;

    // Add gpio to processor
    m_gpios.push_back(gpio);
}

GpioData* ProcessorData::getGpioData(size_t index)
{
    if(index < m_gpios.size())
        return m_gpios[index];

    return NULL;
}

size_t ProcessorData::getNbPins(void)
{
    return m_gpios.size();
}

size_t ProcessorData::getNbUsableGpio(void)
{
    return m_nbUsableGpios;
}

