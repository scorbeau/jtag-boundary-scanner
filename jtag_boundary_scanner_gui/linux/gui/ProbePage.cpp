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
#include "ProbePage.h"

#include "MainEventId.h"

ProbePage::ProbePage(wxWindow *parent)
        : MainPage(parent, wxID_ANY, false)
{
    wxBoxSizer* colSizer;
    wxBoxSizer* rowSizer;
    wxSizerFlags flagsBorder = wxSizerFlags().Border().Centre();
    const int border = 4;

    // TODO: get list of probe
    wxArrayString arrItems;
    arrItems.Add("Probe 1");
    arrItems.Add("Probe 2");
    arrItems.Add("Probe 3");
    arrItems.Add("Probe 4");
    arrItems.Add("Probe 5");
    arrItems.Add("Probe 6");

    colSizer = new wxBoxSizer( wxVERTICAL );

    rowSizer = new wxBoxSizer( wxHORIZONTAL );

    rowSizer->Add(new wxStaticText(this, wxID_ANY, "Select available probe :"),
                   wxSizerFlags().Border(wxRIGHT, border));
    colSizer->Add(rowSizer, 0, wxEXPAND|wxALL, 5);

    rowSizer = new wxBoxSizer( wxHORIZONTAL );
    m_probeCombo = new wxComboBox(this, wxID_ANY, wxEmptyString, wxDefaultPosition,
                        wxDefaultSize, arrItems, wxCB_SORT);
    rowSizer->Add(m_probeCombo, wxSizerFlags().Border(wxRIGHT, border));
    //m_probeCombo->SetValue("Probe 1");
    m_probeCombo->SetSelection(0);

    m_probeDetect = new wxStaticText(this, wxID_ANY, "");
    rowSizer->Add(m_probeDetect, wxSizerFlags().Border(wxRIGHT, border));

    colSizer->Add(rowSizer, 0, wxEXPAND|wxALL, 5);

    rowSizer = new wxBoxSizer( wxHORIZONTAL );
    m_probeRefreshBtn = new wxButton(this, EVT_Probe_Btn_Refresh, "&Refresh");
    rowSizer->Add(m_probeRefreshBtn, flagsBorder);
    m_probeConnectBtn = new wxButton(this, EVT_Probe_Btn_Connect, "&Connect");
    rowSizer->Add(m_probeConnectBtn, flagsBorder);
    colSizer->Add(rowSizer, 0, wxEXPAND|wxALL, 5);

    SetSizer(colSizer);

    if(arrItems.IsEmpty()) {
        m_probeDetect->SetLabel("Not probe found !");
        m_probeConnectBtn->Enable(false);
    }

    FitInside();
    SetScrollRate(5, 5);
}

void ProbePage::setConnectMode(void)
{
    m_probeConnectBtn->SetLabel("Disconnect");
    m_probeRefreshBtn->Enable(false);
    m_probeCombo->Enable(false);
    /* TODO: Add processor panel ? */
}

void ProbePage::setDisconnectMode(void)
{
    m_probeConnectBtn->SetLabel("Connect");
    m_probeRefreshBtn->Enable(true);
    m_probeCombo->Enable(true);
    /* TODO: Remove processor panel ? */
}

void ProbePage::refreshProbeList(wxArrayString p_arrItems)
{
    
}

