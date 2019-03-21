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
    CpuData();
    CpuData(std::string p_name, unsigned long p_cpuid, int p_jtagid);
    ~CpuData();

    std::string getCpuName(void);

    unsigned long getCpuId(void);
    int getJtagId(void);

    void addPin(std::string p_name,
                int  p_type = 0,
                bool p_inputState = false,
                bool p_outputEnableState = false,
                bool p_outputState = false,
                bool p_toggleState = false);

    PinData* getPinData(size_t index);
    PinData* getUnusablePinData(size_t index);

    void enablePinToggle(size_t index, bool toggle = true);
    void setPinOutput(size_t index, bool state = true);
    void setPinOutputEnable(size_t index, bool state = true);
    bool getPinToggle(size_t index);

    size_t getNbPins(void);

    size_t getNbUsablePins(void);
private:
    std::string m_name;
    std::vector<PinData*> m_pins;
    std::vector<PinData*> m_unusablePins;

    unsigned long m_cpuid;
    int m_jtagid;
};

#endif /*  MODEL_CPU_DATA_H__ */

