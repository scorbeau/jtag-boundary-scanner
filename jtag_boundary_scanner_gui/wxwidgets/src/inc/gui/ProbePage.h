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
* @file   ProbePage.h
* @brief  Declare class ProbesPage for panel application.
* @author Sébastien CORBEAU <sebastien.corbeau@viveris.fr>
*/
#ifndef GUI_PROBE_PAGE_H__
#define GUI_PROBE_PAGE_H__

#include "wxWidgetsInc.h"
#include "MainFrame.h"
#include "MainPage.h"

// and the panel taking up MyFrame client area
class ProbePage : public MainPage
{
public:
    ProbePage(wxWindow *parent, MainFrame *frame);

    void setConnectMode(void);
    void setDisconnectMode(void);
    void refreshProbeList(void);
    int getSelectedProbeIndex(void);
private:
    wxComboBox      *m_probeCombo;
    wxStaticText    *m_probeDetect;
    wxButton        *m_probeConnectBtn;
    wxButton        *m_probeRefreshBtn;
    
    SystemData      *m_model;
};

#endif /* GUI_PROBE_PAGE_H__ */

