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
#include <stdlib.h>
#include <string.h>
#include "controller/SystemController.h"

#if defined(WIN32) || defined(_WIN32)
	#include <windows.h>
#elif defined(__linux__)
	#include <winapi_compat.h>
#else
	#error "This programs only runs on Windows or Linux"
#endif

SystemController::SystemController()
{
	m_jtagCore = NULL;
	m_systemData = new SystemData();
}

SystemController::~SystemController()
{
	if(m_jtagCore)
		jtagcore_deinit(m_jtagCore);

	delete m_systemData;
}

const SystemData* SystemController::getSystemData(void) const
{
	return m_systemData;
}

int SystemController::initJtagCore(void)
{
	if(!m_jtagCore)
		m_jtagCore = jtagcore_init();

	return m_jtagCore ? 0 : -1;
}

int SystemController::refreshProbeList(void)
{
	int nbDriver = 0;
	int nbProbe = 0;
	char buffer[512];
	int err = 0;

	m_systemData->cleanProbe();

	nbDriver = jtagcore_get_number_of_probes_drv(m_jtagCore);
	//printf("Number of probe driver %d\n", nbDriver);
	for(int i=0; i<nbDriver; i++) {
		nbProbe = jtagcore_get_number_of_probes(m_jtagCore, i);
		//printf("Number of probe %d\n", nbProbe);
		for(int j=0; j<nbProbe; j++) {
			err = jtagcore_get_probe_name(m_jtagCore,
						      PROBE_ID(i, j),
						      buffer);
#if 0
			printf("Drv[%d]/Probe[%d] : Name=%s err=%d\n",
				i,
				j,
				buffer,
				err);
#endif
			if(!err) {
				m_systemData->addProbe(new ProbeData(
							std::string(buffer),
							i,
							j));
			}
		}
	}

	return err;
}

int SystemController::scanProcessor(size_t p_probeId)
{
	int err = 0;
	int i;
	int nbCpu = 0;
	unsigned long chipId;

	m_systemData->cleanCpu();

	err = jtagcore_select_and_open_probe(m_jtagCore, (int)p_probeId);
	//printf("Open probe return %d\n", err);
	if(!err) {
		err = jtagcore_scan_and_init_chain(m_jtagCore);
		//printf("jtagcore_scan_and_init_chain error %d\n", err);
	}

	if(!err) {
		nbCpu = jtagcore_get_number_of_devices(m_jtagCore);
		//printf("Nb CPU detected %d\n", nbCpu);
		if(nbCpu <= 0) {
			err = -1;
		} else {
			for(i=0; i < nbCpu; i++) {
				chipId = jtagcore_get_dev_id(m_jtagCore, i);
				if(chipId) {
					CpuData *cpu = new CpuData(chipId, i);
					m_systemData->addCpu(cpu);
				}
			}
		}
	}

	if(!err) {
		searchBsdlFiles();
	}

	return err;
}

int SystemController::searchBsdlFiles(void)
{
	HANDLE hFind = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATAA fileData = { 0 };
	char filename[MAX_PATH + 1];
	char currentPath[MAX_PATH +1];
	DWORD size;

	size = GetModuleFileName(NULL, currentPath, sizeof(currentPath));
	if(((size == sizeof(currentPath)) && 
	    (ERROR_INSUFFICIENT_BUFFER == GetLastError())) ||
	    (0 == size)) {
		// Failed to get current path
		return -1;
	}

	while(size && currentPath[size]!='/')
		size--;
	currentPath[size] = '\0';
	strncat(currentPath,"/bsdl_files/", sizeof(currentPath));
	//printf("BSDL path %s\n", currentPath);

	// Scan and check files in the folder.
	hFind = FindFirstFile(currentPath, &fileData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do {
			//printf("Element found %s\n", fileData.cFileName);

			strncpy(filename, currentPath, sizeof(filename) -1);
			strncat(filename,
				fileData.cFileName,
				sizeof(filename) -1);
			//TODO: Check file name is OK (lstat ?)

			if(!(fileData.dwFileAttributes &
			     FILE_ATTRIBUTE_DIRECTORY)) {
				checkAddBsdlFiles(filename);
			}

		}while(FindNextFile(hFind, &fileData));

		FindClose(hFind);
	} else {
		//printf("No file found in %s\n", currentPath);
		return -1;
	}

	return 0;
}

int SystemController::checkAddBsdlFiles(std::string p_bsdlPath)
{
	int ret = 0;
	unsigned long bsdlChipId = 0;
	size_t i;

	bsdlChipId = jtagcore_get_bsdl_id(m_jtagCore, p_bsdlPath.c_str());
#if 0
	printf("Bsdl id 0x%08lX read from %s\n", bsdlChipId,
	       p_bsdlPath.c_str());
#endif

	if(bsdlChipId)
	{
		for(i=0; i < m_systemData->getNbCpu(); i++) {
			const CpuData *cpu = m_systemData->getCpu(i);
			if(bsdlChipId == cpu->getCpuId()) {
				//printf("Found BSDL file for CPU[%ld]\n", i);
				m_systemData->addCpuBsdlFile(i, p_bsdlPath);
			}
		}
		ret = 0;
	} else {
		ret = -1;
	}

	return ret;
}

int SystemController::loadCpuBsdl(size_t p_cpuIndex, size_t p_bsdlIndex)
{
	const CpuData* cpu = m_systemData->getCpu(p_cpuIndex);

	if(!cpu)
		return -1;

	if(p_bsdlIndex >= cpu->getNbBsdlFiles())
		return -1;

	return loadBsdlFile(p_cpuIndex, p_bsdlIndex);
}

int SystemController::createCpuFromBsdl(std::string p_bsdlPath)
{
	int err = -1;
	unsigned long bsdlChipId = 0;
	char devName[512];

	bsdlChipId = jtagcore_get_bsdl_id(m_jtagCore, p_bsdlPath.c_str());
	if(bsdlChipId) {
		err = jtagcore_get_bsdl_dev_name(m_jtagCore,
						 p_bsdlPath.c_str(),
						 devName);
	}

	if(!err) {
		
	}
	return 0;
}

int SystemController::loadBsdlFile(size_t p_cpuIndex, size_t p_bsdlIndex)
{
	std::string filename;
	char buffer[512];
	int err;

	const CpuData *cpu = m_systemData->getCpu(p_cpuIndex);
	if(!cpu)
		return -1;

	filename = cpu->getBsdlFile(p_bsdlIndex);
	//printf("File name %s\n", filename.c_str());

	err = jtagcore_loadbsdlfile(m_jtagCore,
				    filename.c_str(),
				    cpu->getCpuJtagIndex());
	//printf("jtagcore_loadbsdlfile %d\n", err);
	if(err >= 0) {
		err = jtagcore_get_dev_name(m_jtagCore,
					cpu->getCpuJtagIndex(),
					buffer,
					NULL);
	}
	if(!err) {
		//printf("Processor name %s err %d\n", buffer, err);
		m_systemData->updateCpuName(p_cpuIndex, std::string(buffer));

		loadPinsFromBsdl(p_cpuIndex);
	}

	return err;
}

int SystemController::loadPinsFromBsdl(size_t p_index)
{
	char buffer[512];
	int nbPins = 0;
	int i, type;
	int err;

	const CpuData *cpu = m_systemData->getCpu(p_index);
	if(!cpu)
		return -1;

	nbPins = jtagcore_get_number_of_pins(m_jtagCore, 
					cpu->getCpuJtagIndex());
	//printf("Nb pins %d\n", nbPins);

	for(i=0; i<nbPins; i++) {
		err = jtagcore_get_pin_properties(m_jtagCore,
					cpu->getCpuJtagIndex(),
					i,
					buffer,
					sizeof(buffer),
					&type);
		if(!err) {
			//printf("Name %s type %d\r\n", buffer, type);
			m_systemData->addCpuPin(p_index,
						std::string(buffer),
						i,
						type);
		}
	}

	return 0;
}

