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
* @file   MainFrame.h
* @brief  Define class MainFrame application.
* @author Sébastien CORBEAU <sebastien.corbeau@viveris.fr>
*/
#ifndef GUI_MAIN_FRAME_H__
#define GUI_MAIN_FRAME_H__

#include "wxWidgetsInc.h"

#include "SystemController.h"
#include "model/PinData.h"

class MainFrame: public wxFrame
{
public:
    MainFrame(SystemController *p_controller);

    virtual ~MainFrame();

    int GetCpuCheckboxEventIdBase(void);

    void ConnectOutputProcessor(int p_eventId);
    void ConnectOutputEnableProcessor(int p_eventId);
    void ConnectToggleProcessor(int p_eventId);
    SystemData* getDataModel(void);
protected:
    // Menu event manager
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnLoadBsdl(wxCommandEvent& event);

    // Probe panel event manager
    void OnRefreshProbe(wxCommandEvent& event);
    void OnConnectProbe(wxCommandEvent& event);

    // I2C Panel event manager
    void OnAutoscanI2c(wxCommandEvent& event);
    void OnWriteI2c(wxCommandEvent& event);
    void OnReadI2c(wxCommandEvent& event);
    void OnProcessorI2c(wxCommandEvent& event);

    // SPI Panel event manager
    void OnWriteSpi(wxCommandEvent& event);
    void OnProcessorSpi(wxCommandEvent& event);

    // MDIO Panel event manager
    void OnAutoscanMdio(wxCommandEvent& event);
    void OnWriteMdio(wxCommandEvent& event);
    void OnReadMdio(wxCommandEvent& event);
    void OnProcessorMdio(wxCommandEvent& event);

    // Processor Panel
    void OnOutputProcessor(wxCommandEvent& event);
    void OnOutputEnableProcessor(wxCommandEvent& event);
    void OnToggleProcessor(wxCommandEvent& event);
private:
    SystemController *m_controller;

    wxMenu *m_menu;
    wxPanel *m_panel;
    wxNotebook *m_notebook;

    int m_checkboxCpuEvtBaseId;

    void connectProbe(void);
    void disconnectProbe(void);
    // TODO: Update for gpio
    PinData* getPinFromChkBoxEvt(int checkEvtId);

    wxDECLARE_EVENT_TABLE();
};

#endif /* GUI_MAIN_FRAME_H__ */

