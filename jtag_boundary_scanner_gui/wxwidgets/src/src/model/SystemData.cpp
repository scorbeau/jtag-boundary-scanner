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
* @file   SystemData.cpp
* @brief  Implement class SystemData model.
* @author Sébastien CORBEAU <sebastien.corbeau@viveris.fr>
*/
#include "model/SystemData.h"

SystemData::SystemData()
{
    m_isConnected = false;
    m_probeConnectedIndex = (size_t) -1;
}

SystemData::~SystemData()
{
    cleanProbe();
    cleanCpu();
}

int SystemData::getNbCpu(void)
{
    return m_cpu.size();
}

int SystemData::getNbProbe(void)
{
    return m_probe.size();
}

ProbeData* SystemData::getProbe(size_t index)
{
    if(index < m_probe.size())
        return m_probe[index];

    return NULL;
}

CpuData* SystemData::getCpu(size_t index)
{
    if(index < m_cpu.size())
        return m_cpu[index];

    return NULL;
}

void SystemData::cleanProbe(void)
{
    while(!m_probe.empty())
    {
        ProbeData *probe = m_probe.back();
        m_probe.pop_back();
        delete probe;
    }
}

void SystemData::addProbe(std::string p_name)
{
    ProbeData *probe = new ProbeData(p_name);
    m_probe.push_back(probe);
}

size_t SystemData::setProbeConnected(size_t index)
{
    if(index >= m_probe.size() || m_isConnected)
        return (size_t)-1;

    m_isConnected = true;
    m_probeConnectedIndex = index;

    return index;
}

size_t SystemData::setProbeDisconnected(void)
{
    size_t index = (size_t) -1;
    if(!m_isConnected)
        return (size_t) -1;

    index = m_probeConnectedIndex;
    m_probeConnectedIndex = (size_t) -1;
    m_isConnected = false;

    return index;
}

size_t SystemData::getConnectedProbe(void)
{
    if(m_isConnected)
        return m_probeConnectedIndex;

    return (size_t) -1;
}

bool SystemData::isProbeConnected(void)
{
    return m_isConnected;
}


int SystemData::addCpu(std::string p_name, unsigned long p_cpuid, int p_jtagid)
{
    CpuData *cpu = new CpuData(p_name, p_cpuid, p_jtagid);
    m_cpu.push_back(cpu);

    // Return index of CPU
    return m_cpu.size() -1;
}

int SystemData::addPin(size_t p_cpuIndex,
                       std::string p_name,
                       int  p_type,
                       bool p_inputState,
                       bool p_outputEnableState,
                       bool p_outputState,
                       bool p_toggleState)
{
    CpuData *cpu = NULL;
    // Cpu not in list
    if(p_cpuIndex >= m_cpu.size())
        return -1;

    cpu = m_cpu[p_cpuIndex];
    cpu->addPin(p_name,
                p_type,
                p_inputState,
                p_outputEnableState,
                p_outputState,
                p_toggleState);

    return 0;
}

int SystemData::addCpu(CpuData *p_cpu)
{
    m_cpu.push_back(p_cpu);

    // Return index of CPU
    return m_cpu.size() -1;
}

void SystemData::cleanCpu(void)
{
    while(!m_cpu.empty())
    {
        CpuData *cpu = m_cpu.back();
        m_cpu.pop_back();
        delete cpu;
    }
}

