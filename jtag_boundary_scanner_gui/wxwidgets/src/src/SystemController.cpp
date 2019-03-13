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
* @file   SystemController.cpp
* @brief  Implement class SystemController model.
* @author Sébastien CORBEAU <sebastien.corbeau@viveris.fr>
*/
#include "SystemController.h"

#include "plateform.h"

SystemController::SystemController()
{
    printf("Construct %s\n", __func__);
    m_systemModel = new SystemData();

    m_jtagCore = jtagcore_init();
    if(!m_jtagCore) {
        printf("Failed to init jtagcore");
        exit(-1);
    }
}

SystemController::~SystemController()
{
    cleanProbe();
    cleanCpu();

    jtagcore_deinit(m_jtagCore);
}

int SystemController::getNbCpu(void)
{
    return m_systemModel->getNbCpu();
}

int SystemController::getNbProbe(void)
{
    return m_systemModel->getNbProbe();
}

ProbeData* SystemController::getProbe(size_t index)
{
    return m_systemModel->getProbe(index);
}

CpuData* SystemController::getCpu(size_t index)
{
    return m_systemModel->getCpu(index);
}

SystemData* SystemController::getSystemData(void)
{
    return m_systemModel;
}

void SystemController::cleanProbe(void)
{
    //TODO: Disconnect probe if needed
    m_systemModel->cleanProbe();
}

void SystemController::cleanCpu(void)
{
    //TODO: Disconnect probe if needed
    m_systemModel->cleanCpu();
}

void SystemController::refreshProbe(void)
{
    static int toto = 0;
    int ret = 0;
    //TODO: Get available probe
    m_systemModel->cleanProbe();
    if(toto++%2) {
        m_systemModel->addProbe("azerty");
        m_systemModel->addProbe("bazjjahz");
        m_systemModel->addProbe("aze");
        m_systemModel->addProbe("dddzjjahz");
    } else {
        
    }
    ret = jtagcore_get_number_of_probes_drv(m_jtagCore);
    printf("Number of probe driver %d\n", ret);
}

int SystemController::connectToProbe(size_t index)
{
    //TODO: Connect to probe
    return m_systemModel->setProbeConnected(index);
}

size_t SystemController::disconnectProbe(void)
{
    //TODO: Disconnect probe
    return m_systemModel->setProbeDisconnected();
}

size_t SystemController::getConnectedProbe(void)
{
    return m_systemModel->getConnectedProbe();
}

bool SystemController::isProbeConnected(void)
{
     return m_systemModel->isProbeConnected();
}

CpuData* SystemController::loadBsdlFile(std::string filename)
{
    CpuData *cpu = NULL;
    char buffer[256];
    int cpuId;
    int jtagIdx;
    int err;
    int nbPins = 0;
    int i, type;

    jtagIdx = jtagcore_loadbsdlfile(m_jtagCore, filename.c_str(), -1);
    //printf("JTAG index %d\n", jtagIdx);
    if(jtagIdx >= 0)
    {
        cpuId = jtagcore_get_bsdl_id(m_jtagCore, filename.c_str());
        err = jtagcore_get_dev_name(m_jtagCore,
                                    jtagIdx, 
                                    buffer,
                                    NULL);
        //printf("Processor name %s err %d\n", buffer, err);
        if(!err) {
            cpu = new CpuData(std::string(buffer), cpuId, jtagIdx);

            //printf("CpuId = %08X\n", cpuId);
            nbPins = jtagcore_get_number_of_pins(m_jtagCore, jtagIdx);
            // printf("Nb pins %d\n", nbPins);

            i = 0;
            while((i<nbPins) && (!err)) {
                err = jtagcore_get_pin_properties(m_jtagCore,
                                                  jtagIdx,
                                                  i,
                                                  buffer,
                                                  sizeof(buffer),
                                                  &type);
                if(!err) {
                    //printf("Name %s type %d\r\n", buffer, type);
                    cpu->addPin(std::string(buffer),
                                type,
                                false,
                                false,
                                false,
                                false);
                    i++;
                }
            }
            if(!err) {
                m_systemModel->addCpu(cpu);
            } else {
                delete cpu;
                cpu = NULL;
            }
        }
    } else {
        err = -1;
    }

    return err ? NULL : cpu;
}

