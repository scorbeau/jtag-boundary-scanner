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
#include "configuration.h"

SystemData::SystemData()
{
	m_refreshTime = DEFAULT_REFRESH_VAL;
	m_scanMode = DEFAULT_SCAN_MODE;

	m_mutex = new pthread_mutex_t[1];
	pthread_mutex_init(m_mutex, NULL);
}

SystemData::~SystemData()
{
	cleanProbe();
	cleanCpu();
	pthread_mutex_destroy(m_mutex);
	delete m_mutex;
}

const CpuData* SystemData::getCpu(size_t p_index) const
{
	if(p_index < m_cpu.size())
		return m_cpu[p_index];
	return NULL;
}

const ProbeData* SystemData::getProbe(size_t p_index) const
{
	if(p_index < m_probe.size())
		return m_probe[p_index];

	return NULL;
}

void SystemData::addProbe(ProbeData *probe)
{
	m_probe.push_back(probe);
}

void SystemData::cleanProbe(void)
{
	while(!m_probe.empty()) {
		ProbeData *probe = m_probe.back();
		m_probe.pop_back();
		delete probe;
	}
}

size_t SystemData::getNbProbe(void) const
{
	return m_probe.size();
}

void SystemData::addCpu(CpuData* cpu)
{
	m_cpu.push_back(cpu);
}

void SystemData::cleanCpu(void)
{
	while(!m_cpu.empty()) {
		CpuData *cpu = m_cpu.back();
		m_cpu.pop_back();
		delete cpu;
	}
}

size_t SystemData::getNbCpu(void) const
{
	return m_cpu.size();
}

void SystemData::updateCpuName(size_t p_index, std::string p_name)
{
	if(p_index < m_cpu.size())
		m_cpu[p_index]->updateCpuName(p_name);
}

void SystemData::addCpuBsdlFile(size_t p_index, std::string p_path)
{
	if(p_index < m_cpu.size())
		m_cpu[p_index]->addBsdlFile(p_path);
}

void SystemData::addCpuPin(size_t p_cpuIndex,
		       std::string p_name,
		       int p_pinIndex,
		       int p_type)
{
	if(p_cpuIndex < m_cpu.size())
		m_cpu[p_cpuIndex]->addPin(p_name, p_pinIndex, p_type);
}

void SystemData::setOutputEnableState(size_t p_cpuIndex,
			  size_t p_gpioIndex,
			  bool p_state)
{
	if(p_cpuIndex < m_cpu.size())
		m_cpu[p_cpuIndex]->setOutputEnableState(p_gpioIndex, p_state);
}

void SystemData::setOutputState(size_t p_cpuIndex,
		    size_t p_gpioIndex,
		    bool p_state)
{
	if(p_cpuIndex < m_cpu.size())
		m_cpu[p_cpuIndex]->setOutputState(p_gpioIndex, p_state);
}

void SystemData::setToggleState(size_t p_cpuIndex,
		    size_t p_gpioIndex,
		    bool p_state)
{
	if(p_cpuIndex < m_cpu.size())
		m_cpu[p_cpuIndex]->setToggleState(p_gpioIndex, p_state);
}

void SystemData::updateInputState(size_t p_cpuIndex,
								  size_t p_gpioIndex,
								  bool p_state)
{
	if(p_cpuIndex < m_cpu.size())
		m_cpu[p_cpuIndex]->updateInputState(p_gpioIndex, p_state);
}

int SystemData::getRefreshTime(void) const
{
	int ret = -1;
	pthread_mutex_lock(m_mutex);
	ret = m_refreshTime;
	pthread_mutex_unlock(m_mutex);
	return ret;
}

void SystemData::setRefreshTime(int p_refreshTime)
{
	if(p_refreshTime < 0)
		return;
	printf("Refresh time %d\n", p_refreshTime);
	pthread_mutex_lock(m_mutex);
	m_refreshTime = p_refreshTime;
	pthread_mutex_unlock(m_mutex);
}

int SystemData::getScanMode(void) const
{
	int ret = -1;
	pthread_mutex_lock(m_mutex);
	ret = m_scanMode;
	pthread_mutex_unlock(m_mutex);

	return ret;
}

void SystemData::setScanMode(int p_scanMode)
{
	if(p_scanMode != JTAG_CORE_EXTEST_SCANMODE &&
			p_scanMode != JTAG_CORE_SAMPLE_SCANMODE)
		return;
	printf("Scan mode %d\n", p_scanMode);
	pthread_mutex_lock(m_mutex);
	m_scanMode = p_scanMode;
	pthread_mutex_unlock(m_mutex);
}
