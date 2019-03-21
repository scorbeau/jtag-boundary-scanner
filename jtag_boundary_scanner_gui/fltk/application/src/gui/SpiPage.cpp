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
* @file   SpiPage.h
* @brief  Implement class SpiPage to display SPI bus menu.
* @author Sébastien CORBEAU <sebastien.corbeCau@viveris.fr>
*/
#include "gui/SpiPage.h"

#include "gui/MainEventId.h"

SpiPage::SpiPage(wxWindow *parent)
        : MainPage(parent, wxID_ANY, false)
{
    wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
    wxArrayString arrItems;
    wxFlexGridSizer *fgs = new wxFlexGridSizer(4, 3, 9, 9);
    wxFlexGridSizer *fgs2;
    wxFlexGridSizer *fgs3;

    m_processorCombo = new wxComboBox(this, EVT_Spi_Combo_Proc, "", 
                wxPoint(-1, -1), wxSize(-1, -1), arrItems, wxCB_READONLY);
    m_processorCombo->SetSelection(0);
    m_mosiCombo = new wxComboBox(this, wxID_ANY, "", wxPoint(-1, -1),
                wxSize(-1, -1), arrItems, wxCB_READONLY);
    m_misoCombo = new wxComboBox(this, wxID_ANY, "", wxPoint(-1, -1),
                wxSize(-1, -1), arrItems, wxCB_READONLY);
    m_csCombo = new wxComboBox(this, wxID_ANY, "", wxPoint(-1, -1),
                wxSize(-1, -1), arrItems, wxCB_READONLY);
    m_clkCombo = new wxComboBox(this, wxID_ANY, "", wxPoint(-1, -1),
                wxSize(-1, -1), arrItems, wxCB_READONLY);

    m_cpolChkBox = new wxCheckBox(this, wxID_ANY, "CPOL");
    m_cphaChkBox = new wxCheckBox(this, wxID_ANY, "CPHA");
    m_csActiveHiChkBox = new wxCheckBox(this, wxID_ANY, "CS active high");
    m_clkIdleHiChkBox = new wxCheckBox(this, wxID_ANY, "Clock idle high");
    m_lsbFirstChkBox = new wxCheckBox(this, wxID_ANY, "Data LSB first");

    m_writeTxtCtrl = new wxTextCtrl(this, wxID_ANY, "", wxPoint(-1, -1),
                wxSize(-1, 90), wxTE_MULTILINE);
    m_readTxtCtrl = new wxTextCtrl(this, wxID_ANY, "", wxPoint(-1, -1),
                wxSize(-1, 90), wxTE_MULTILINE);

    m_writeBtn = new wxButton(this, EVT_Spi_Btn_Write, "&Write");

    // First line
    fgs->Add(new wxStaticText(this, wxID_ANY, "Processor :"));
    fgs->Add(m_processorCombo, 1, wxEXPAND);
    fgs->Add(new wxStaticText(this, wxID_ANY, ""));

    // Second line
    fgs->Add(new wxStaticText(this, wxID_ANY, ""));
    fgs2 = new wxFlexGridSizer(4, 2, 9, 9);

    fgs3 = new wxFlexGridSizer(2, 2, 9, 9);
    fgs3->Add(new wxStaticText(this, wxID_ANY, "MOSI Pin :"));
    fgs3->Add(m_mosiCombo, 1, wxEXPAND);
    fgs3->Add(new wxStaticText(this, wxID_ANY, "CS Pin :"));
    fgs3->Add(m_csCombo, 1, wxEXPAND);
    fgs3->AddGrowableCol(1, 1);
    fgs2->Add(fgs3, 1, wxEXPAND);

    fgs3 = new wxFlexGridSizer(2, 2, 9, 9);
    fgs3->Add(new wxStaticText(this, wxID_ANY, "MISO Pin :"));
    fgs3->Add(m_misoCombo, 1, wxEXPAND);
    fgs3->Add(new wxStaticText(this, wxID_ANY, "CLK Pin :"));
    fgs3->Add(m_clkCombo, 1, wxEXPAND);
    fgs3->AddGrowableCol(1, 1);
    fgs2->Add(fgs3, 1, wxEXPAND);

    fgs2->Add(m_cpolChkBox, 1, wxEXPAND);
    fgs2->Add(m_cphaChkBox, 1, wxEXPAND);
    fgs2->Add(m_csActiveHiChkBox, 1, wxEXPAND);
    fgs2->Add(m_clkIdleHiChkBox, 1, wxEXPAND);
    fgs2->Add(m_lsbFirstChkBox, 1, wxEXPAND);
    fgs2->Add(new wxStaticText(this, wxID_ANY, ""));
    fgs->Add(fgs2, 1, wxEXPAND);
    fgs->Add(new wxStaticText(this, wxID_ANY, ""));

    // Third line
    fgs->Add(new wxStaticText(this, wxID_ANY, "Data to write"));
    fgs->Add(m_writeTxtCtrl, 1, wxEXPAND);
    fgs->Add(m_writeBtn);

    // Fourth line
    fgs->Add(new wxStaticText(this, wxID_ANY, "Data read"));
    fgs->Add(m_readTxtCtrl, 1, wxEXPAND);
    fgs->Add(new wxStaticText(this, wxID_ANY, ""));

    fgs->AddGrowableCol(1, 1);

    hbox->Add(fgs, 1, wxALL | wxEXPAND, 15);
    SetSizer(hbox);

    FitInside();
    SetScrollRate(5, 5);
}

void SpiPage::setConnectMode(void)
{
    m_processorCombo->Enable(true);
    m_mosiCombo->Enable(true);
    m_misoCombo->Enable(true);
    m_csCombo->Enable(true);
    m_clkCombo->Enable(true);
    m_cpolChkBox->Enable(true);
    m_cphaChkBox->Enable(true);
    m_csActiveHiChkBox->Enable(true);
    m_clkIdleHiChkBox->Enable(true);
    m_lsbFirstChkBox->Enable(true);
    m_writeTxtCtrl->Enable(true);
    m_readTxtCtrl->Enable(true);
    m_writeBtn->Enable(true);
}

void SpiPage::setDisconnectMode(void)
{
    m_processorCombo->Enable(false);
    m_mosiCombo->Enable(false);
    m_misoCombo->Enable(false);
    m_csCombo->Enable(false);
    m_clkCombo->Enable(false);
    m_cpolChkBox->Enable(false);
    m_cphaChkBox->Enable(false);
    m_csActiveHiChkBox->Enable(false);
    m_clkIdleHiChkBox->Enable(false);
    m_lsbFirstChkBox->Enable(false);
    m_writeTxtCtrl->Enable(false);
    m_readTxtCtrl->Enable(false);
    m_writeBtn->Enable(false);
}


