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
* @file   ProbeData.cpp
* @brief  Define class ProbeData model.
* @author Sébastien CORBEAU <sebastien.corbeau@viveris.fr>
*/
#include <jtag_core.h>

#include "model/ProbeData.h"

ProbeData::ProbeData(std::string p_name, int p_driverId, int p_probeId)
{
	m_name = p_name;
	m_identifier = PROBE_ID(p_driverId, p_probeId);
}

ProbeData::~ProbeData()
{
}

std::string ProbeData::getName(void) const
{
	return m_name;
}

int ProbeData::getIdentifier(void) const
{
	return m_identifier;
}


