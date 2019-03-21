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

#include "ProbeData.h"
#include "CpuData.h"

class SystemData
{
public:
    SystemData();

    ~SystemData();

    int getNbCpu(void);
    int getNbProbe(void);

    ProbeData* getProbe(size_t index);
    CpuData* getCpu(size_t index);

    void addProbe(std::string p_name);
    size_t setProbeConnected(size_t index);
    size_t setProbeDisconnected(void);
    size_t getConnectedProbe(void);
    bool isProbeConnected(void);
    void cleanProbe(void);

    int addCpu(std::string p_name, unsigned long p_cpuid, int p_jtagid);
    int addPin(size_t p_cpuIndex,
               std::string p_name,
               int  p_type,
               bool p_inputState = false,
               bool p_outputEnableState = false,
               bool p_outputState = false,
               bool p_toggleState = false);
    int addCpu(CpuData *p_cpu);
    void cleanCpu(void);

private:
    std::vector<ProbeData*> m_probe;
    std::vector<CpuData*>   m_cpu;

    bool m_isConnected;
    size_t m_probeConnectedIndex;
};


#endif /*  MODEL_SYSTEM_DATA_H__ */

