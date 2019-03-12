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
* @file   I2cPage.cpp
* @brief  Implement class I2cPage to display I2C bus menu.
* @author Sébastien CORBEAU <sebastien.corbeCau@viveris.fr>
*/
#include "gui/I2cPage.h"

#include "gui/MainEventId.h"

I2cPage::I2cPage(wxWindow *parent)
        : MainPage(parent, wxID_ANY, false)
{
    wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *cbox;
    wxArrayString arrItems;
    wxFlexGridSizer *fgs = new wxFlexGridSizer(4, 3, 9, 9);
    wxFlexGridSizer *fgs2;

    m_processorCombo = new wxComboBox(this, EVT_I2c_Combo_Proc, "", 
                wxPoint(-1, -1), wxSize(-1, -1), arrItems, wxCB_READONLY);
    m_processorCombo->SetSelection(0);
    m_sdaCombo = new wxComboBox(this, wxID_ANY, "", wxPoint(-1, -1),
                wxSize(-1, -1), arrItems, wxCB_READONLY);
    m_sdaCombo->SetSelection(0);
    m_sclCombo = new wxComboBox(this, wxID_ANY, "", wxPoint(-1, -1),
                wxSize(-1, -1), arrItems, wxCB_READONLY);
    m_sclCombo->SetSelection(0);

    m_10bitAddrChkBox = new wxCheckBox(this, wxID_ANY, "10-bit address");

    m_autoscanBtn = new wxButton(this, EVT_I2c_Btn_Autoscan, "&Autoscan");
    m_writeBtn = new wxButton(this, EVT_I2c_Btn_Write, "&Write");
    m_readBtn = new wxButton(this, EVT_I2c_Btn_Read, "&Read");

    m_slaveTxtCtrl = new wxTextCtrl(this, wxID_ANY, "");
    m_writeTxtCtrl = new wxTextCtrl(this, wxID_ANY, "", wxPoint(-1, -1),
                wxSize(-1, 90), wxTE_MULTILINE);
    m_readTxtCtrl = new wxTextCtrl(this, wxID_ANY, "", wxPoint(-1, -1),
                wxSize(-1, 90), wxTE_MULTILINE);
    m_readSzTxtCtrl = new wxTextCtrl(this, wxID_ANY, "10");

    // First line
    fgs->Add(new wxStaticText(this, wxID_ANY, "Processor :"));
    fgs->Add(m_processorCombo, 1, wxEXPAND);
    fgs->Add(new wxStaticText(this, wxID_ANY, ""), 1, wxEXPAND);

    // Second line
    fgs->Add(new wxStaticText(this, wxID_ANY, ""));
    fgs2 = new wxFlexGridSizer(2, 4, 9, 9);
    fgs2->Add(new wxStaticText(this, wxID_ANY, "SDA Pin :"));
    fgs2->Add(m_sdaCombo, 1, wxEXPAND);
    fgs2->Add(new wxStaticText(this, wxID_ANY, "SCL Pin :"));
    fgs2->Add(m_sclCombo, 1, wxEXPAND);
    fgs2->Add(new wxStaticText(this, wxID_ANY, "Address (0x..):"));
    fgs2->Add(m_slaveTxtCtrl, 1, wxEXPAND);
    fgs2->Add(m_10bitAddrChkBox);
    fgs2->Add(new wxStaticText(this, wxID_ANY, ""));
    fgs2->AddGrowableCol(1, 1);
    fgs2->AddGrowableCol(3, 1);
    fgs->Add(fgs2, 1, wxEXPAND);
    fgs->Add(m_autoscanBtn);

    // Third line
    fgs->Add(new wxStaticText(this, wxID_ANY, "Data to Write :"));
    fgs->Add(m_writeTxtCtrl, 1, wxEXPAND);
    fgs->Add(m_writeBtn);

    // Fourth line
    fgs->Add(new wxStaticText(this, wxID_ANY, "Data read :"));
    fgs->Add(m_readTxtCtrl, 1, wxEXPAND);
    cbox = new wxBoxSizer(wxVERTICAL);
    cbox->Add(new wxStaticText(this, wxID_ANY, "Read size :"),
            wxSizerFlags().Border(wxDOWN, 9));
    cbox->Add(m_readSzTxtCtrl, wxSizerFlags().Border(wxDOWN, 9));
    cbox->Add(m_readBtn);
    fgs->Add(cbox);

    fgs->AddGrowableCol(1, 1);

    hbox->Add(fgs, 1, wxALL | wxEXPAND, 15);
    SetSizer(hbox);

    FitInside();
    SetScrollRate(5, 5);
}

void I2cPage::setConnectMode(void)
{
    m_processorCombo->Enable(true);
    m_sdaCombo->Enable(true);
    m_sclCombo->Enable(true);
    m_10bitAddrChkBox->Enable(true);
    m_autoscanBtn->Enable(true);
    m_writeBtn->Enable(true);
    m_readBtn->Enable(true);
    m_slaveTxtCtrl->Enable(true);
    m_writeTxtCtrl->Enable(true);
    m_readTxtCtrl->Enable(true);
    m_readSzTxtCtrl->Enable(true);
}

void I2cPage::setDisconnectMode(void)
{
    m_processorCombo->Enable(false);
    m_sdaCombo->Enable(false);
    m_sclCombo->Enable(false);
    m_10bitAddrChkBox->Enable(false);
    m_autoscanBtn->Enable(false);
    m_writeBtn->Enable(false);
    m_readBtn->Enable(false);
    m_slaveTxtCtrl->Enable(false);
    m_writeTxtCtrl->Enable(false);
    m_readTxtCtrl->Enable(false);
    m_readSzTxtCtrl->Enable(false);
}

