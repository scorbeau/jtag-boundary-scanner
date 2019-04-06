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
* @file   CpuData.h
* @brief  Define class CpuData model.
* @author Sébastien CORBEAU <sebastien.corbeau@viveris.fr>
*/
#ifndef MODEL_CPU_DATA_H__
#define MODEL_CPU_DATA_H__

#include <string>
#include <vector>

#include "PinData.h"

class CpuData
{
public:
	CpuData(unsigned long p_cpuId = 0, int p_cpuJtagIndex = -1);
	~CpuData();

	void updateCpuId(unsigned long p_cpuId);
	unsigned long getCpuId(void) const;

	int getCpuJtagIndex(void) const;

	void updateCpuName(std::string p_name);
	std::string getCpuName(void) const;

	void addBsdlFile(std::string p_bsdlFile);
	size_t getNbBsdlFiles(void) const;
	std::string getBsdlFile(size_t p_index) const;
	void setBsdlFileIndex(size_t p_index);
	size_t getBsdlFileIndex(void);

	void addPin(std::string p_name, size_t p_index, int p_type = 0);
	size_t getNbUsablePins(void) const;
	size_t getNbUnusablePins(void) const;
	size_t getNbPins(void) const;

	const PinData* getUsablePin(size_t p_index) const;
	const PinData* getUnusablePin(size_t p_index) const;
	const PinData* getChainPin(size_t p_index) const;

	void setOutputEnableState(size_t p_gpioIndex, bool p_state);
	void setOutputState(size_t p_gpioIndex, bool p_state);
	void setToggleState(size_t p_gpioIndex, bool p_state);
	void updateInputState(size_t p_gpioIndex, bool p_state);

private:
	unsigned long m_cpuId;
	int m_cpuJtagIndex;
	std::string m_name;

	size_t m_currentBsdlIdx;

	std::vector<std::string> m_bsdlFiles;
	std::vector<PinData*> m_usablePins;
	std::vector<PinData*> m_unusablePins;
	std::vector<PinData*> m_chainPins;
};

#endif /*  MODEL_CPU_DATA_H__ */

