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

CpuData::CpuData(unsigned long p_cpuId, int p_cpuJtagIndex)
{
	m_name = "Unknown";
	m_cpuId = p_cpuId;
	m_cpuJtagIndex = p_cpuJtagIndex;
	m_currentBsdlIdx = (size_t)-1;
}

CpuData::~CpuData()
{
    while(!m_usablePins.empty()) {
        PinData *pin = m_usablePins.back();
        m_usablePins.pop_back();
        delete pin;
    }

    while(!m_unusablePins.empty())
    {
        PinData *pin = m_unusablePins.back();
        m_unusablePins.pop_back();
        delete pin;
    }
}

void CpuData::updateCpuId(unsigned long p_cpuId)
{
	m_cpuId = p_cpuId;
}

unsigned long CpuData::getCpuId(void) const
{
	return m_cpuId;
}

void CpuData::updateCpuName(std::string p_name)
{
	m_name = p_name;
}

std::string CpuData::getCpuName(void) const
{
	return m_name;
}

int CpuData::getCpuJtagIndex(void) const
{
	return m_cpuJtagIndex;
}

void CpuData::addBsdlFile(std::string p_bsdlFile)
{
	m_bsdlFiles.push_back(p_bsdlFile);
}

size_t CpuData::getNbBsdlFiles(void) const
{
	return m_bsdlFiles.size();
}

std::string CpuData::getBsdlFile(size_t p_index) const
{
	if(p_index < m_bsdlFiles.size())
		return m_bsdlFiles[p_index];

	return "";
}

void CpuData::setBsdlFileIndex(size_t p_index)
{
	m_currentBsdlIdx = p_index;
}

size_t CpuData::getBsdlFileIndex(void)
{
	return m_currentBsdlIdx;
}

void CpuData::addPin(std::string p_name, size_t p_index, int p_type)
{
	PinData *pin = new PinData(p_name, p_index, p_type);

	m_chainPins.push_back(pin);

	if(pin->isPinUsable()) {
		m_usablePins.push_back(pin);
	} else {
		m_unusablePins.push_back(pin);
	}
}

size_t CpuData::getNbUsablePins(void) const
{
	return m_usablePins.size();
}

size_t CpuData::getNbUnusablePins(void) const
{
	return m_unusablePins.size();
}

size_t CpuData::getNbPins(void) const
{
	return m_chainPins.size();
}

const PinData* CpuData::getUsablePin(size_t p_index) const
{
	if(p_index < m_usablePins.size())
		return m_usablePins[p_index];
	return NULL;
}

const PinData* CpuData::getUnusablePin(size_t p_index) const
{
	if(p_index < m_unusablePins.size())
		return m_unusablePins[p_index];
	return NULL;
}

const PinData* CpuData::getChainPin(size_t p_index) const
{
	if(p_index < m_chainPins.size())
		return m_chainPins[p_index];
	return NULL;
}

void CpuData::setOutputEnableState(size_t p_gpioIndex, bool p_state)
{
	if(p_gpioIndex < m_chainPins.size()) {
		if(m_chainPins[p_gpioIndex]->isTristate())
			m_chainPins[p_gpioIndex]->setOutputEnableState(p_state);
	}
}

void CpuData::setOutputState(size_t p_gpioIndex, bool p_state)
{
	if(p_gpioIndex < m_chainPins.size()) {
		if(m_chainPins[p_gpioIndex]->isOutput())
			m_chainPins[p_gpioIndex]->setOutputState(p_state);
	}
}

void CpuData::setToggleState(size_t p_gpioIndex, bool p_state)
{
	if(p_gpioIndex < m_chainPins.size()) {
		if(m_chainPins[p_gpioIndex]->isOutput())
			m_chainPins[p_gpioIndex]->setToggleState(p_state);
	}
}

void CpuData::updateInputState(size_t p_gpioIndex, bool p_state){
	if(p_gpioIndex < m_chainPins.size()) {
		if(m_chainPins[p_gpioIndex]->isInput())
			m_chainPins[p_gpioIndex]->updateInputState(p_state);
	}
}
