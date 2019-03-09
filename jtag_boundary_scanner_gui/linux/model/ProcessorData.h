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
* @file   ProcessorData.h
* @brief  Define class ProcessorData model.
* @author Sébastien CORBEAU <sebastien.corbeau@viveris.fr>
*/
#ifndef MODEL_PROCESSOR_DATA_H__
#define MODEL_PROCESSOR_DATA_H__

#include <string>
#include <vector>

#include "GpioData.h"

class ProcessorData
{
public:
    ProcessorData();
    ProcessorData(std::string p_name, unsigned long p_cpuid, int p_jtagid);
    ~ProcessorData();

    std::string getProcessorName(void);

    unsigned long getProcessorId(void);
    int getJtagId(void);

    void addGpio(std::string p_name,
                 int  p_type = 0,
                 bool p_inputState = false,
                 bool p_outputEnableState = false,
                 bool p_outputState = false,
                 bool p_toggleState = false);

    GpioData* getGpioData(size_t index);

    size_t getNbPins(void);

    size_t getNbUsableGpio(void);
private:
    std::string m_name;
    std::vector<GpioData*> m_gpios;
    size_t m_nbUsableGpios;

    unsigned long m_cpuid;
    int m_jtagid;
};

#endif /*  MODEL_PROCESSOR_DATA_H__ */
