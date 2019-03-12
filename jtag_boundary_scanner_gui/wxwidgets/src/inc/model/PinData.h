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
* @file   PinData.h
* @brief  Define class PinData model.
* @author Sébastien CORBEAU <sebastien.corbeau@viveris.fr>
*/
#ifndef MODEL_PIN_DATA_H__
#define MODEL_PIN_DATA_H__

#include <string>
#include <vector>

class PinData
{
public:
    PinData(std::string p_name,
             int  p_type = 0,
             bool p_inputState = false,
             bool p_outputEnableState = false,
             bool p_outputState = false,
             bool p_toggleState = false);

    std::string getName(void);

    bool isPinUsable(void);

    bool isInputPin(void);
    bool isOutputPin(void);
    bool isTristatePin(void);

    bool getInputState(void);

    bool getOutputEnableState(void);
    void setOutputEnableState(bool p_state);

    bool getOutputState(void);
    void setOutputState(bool p_state);

    bool getToggleState(void);
    void setToggleState(bool p_state);
private:
    std::string m_name;
    int  m_type;
    bool m_inputState;
    bool m_outputEnableState;
    bool m_outputState;
    bool m_toggleState;
};
#endif /*  MODEL_PIN_DATA_H__ */

