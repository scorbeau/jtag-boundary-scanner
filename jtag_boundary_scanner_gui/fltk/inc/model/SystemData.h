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
* @file   SystemData.h
* @brief  Define class SystemData model.
* @author Sébastien CORBEAU <sebastien.corbeau@viveris.fr>
*/
#ifndef MODEL_SYSTEM_DATA_H__
#define MODEL_SYSTEM_DATA_H__

#include <string>
#include <vector>

#include "ProbeData.h"
#include "CpuData.h"

class SystemData
{
public:
	SystemData();
	~SystemData();

	const CpuData* getCpu(size_t p_index) const;
	const ProbeData* getProbe(size_t p_index) const;

	// Probe update methods
	void addProbe(ProbeData* probe);
	void cleanProbe(void);
	size_t getNbProbe(void) const;

	// CPU update methods
	void addCpu(CpuData* cpu);
	void cleanCpu(void);
	size_t getNbCpu(void) const;
	void updateCpuName(size_t p_index, std::string p_name);

	void addCpuPin(size_t p_cpuIndex,
		       std::string p_name,
		       int p_pinIndex,
		       int p_type);

	void setOutputEnableState(size_t p_cpuIndex,
				  size_t p_gpioIndex,
				  bool p_state);

	void setOutputState(size_t p_cpuIndex,
			    size_t p_gpioIndex,
			    bool p_state);

	void setToggleState(size_t p_cpuIndex,
			    size_t p_gpioIndex,
			    bool p_state);

	void updateInputState(size_t p_cpuIndex,
						  size_t p_gpioIndex,
						  bool p_state);

	void addCpuBsdlFile(size_t p_index, std::string p_path);
private:
	std::vector<ProbeData*> m_probe;
	std::vector<CpuData*>   m_cpu;
};

#endif /*  MODEL_SYSTEM_DATA_H__ */

