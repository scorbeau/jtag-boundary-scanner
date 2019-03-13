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
* @file   SystemController.h
* @brief  Define class SystemController.
* @author Sébastien CORBEAU <sebastien.corbeau@viveris.fr>
*/
#ifndef SYSTEM_CONTROLLER_H__
#define SYSTEM_CONTROLLER_H__

#include <string>
#include <vector>

#include <jtag_core.h>

#include "model/SystemData.h"

class SystemController
{
public:
    SystemController();
    ~SystemController();

    int getNbCpu(void);
    int getNbProbe(void);

    ProbeData* getProbe(size_t index);
    CpuData* getCpu(size_t index);
    SystemData* getSystemData(void);

    void cleanProbe(void);
    void cleanCpu(void);

    void refreshProbe(void);

    int connectToProbe(size_t index);
    size_t disconnectProbe(void);
    size_t getConnectedProbe(void);
    bool isProbeConnected(void);

    CpuData* loadBsdlFile(std::string filename);
private:
    SystemData *m_systemModel;
    jtag_core *m_jtagCore;
};

#endif /*  SYSTEM_CONTROLLER_H__ */

