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
* @file   MdioPage.h
* @brief  Implement class MdioPage to display MDIO bus menu.
* @author Sébastien CORBEAU <sebastien.corbeCau@viveris.fr>
*/
#include "gui/MdioPage.h"

#include "gui/MainEventId.h"

MdioPage::MdioPage(wxWindow *parent)
        : MainPage(parent, wxID_ANY, false)
{
    wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
    wxArrayString arrItems;
    wxFlexGridSizer *fgs = new wxFlexGridSizer(4, 3, 9, 9);
    wxFlexGridSizer *fgs2;

    m_processorCombo = new wxComboBox(this, EVT_Mdio_Combo_Proc, "", 
                wxPoint(-1, -1), wxSize(-1, -1), arrItems, wxCB_READONLY);
    m_processorCombo->SetSelection(0);
    m_mdioCombo = new wxComboBox(this, wxID_ANY, "", wxPoint(-1, -1),
                wxSize(-1, -1), arrItems, wxCB_READONLY);
    m_mdioCombo->SetSelection(0);
    m_mdcCombo = new wxComboBox(this, wxID_ANY, "", wxPoint(-1, -1),
                wxSize(-1, -1), arrItems, wxCB_READONLY);
    m_mdcCombo->SetSelection(0);

    m_autoscanBtn = new wxButton(this, EVT_Mdio_Btn_Autoscan, "&Autoscan");
    m_writeBtn = new wxButton(this, EVT_Mdio_Btn_Write, "&Write");
    m_readBtn = new wxButton(this, EVT_Mdio_Btn_Read, "&Read");

    m_addrTxtCtrl = new wxTextCtrl(this, wxID_ANY, "");
    m_regTxtCtrl = new wxTextCtrl(this, wxID_ANY, "");
    m_writeTxtCtrl = new wxTextCtrl(this, wxID_ANY, "", wxPoint(-1, -1),
                wxSize(-1, 90), wxTE_MULTILINE);
    m_readTxtCtrl = new wxTextCtrl(this, wxID_ANY, "", wxPoint(-1, -1),
                wxSize(-1, 90), wxTE_MULTILINE);

    // First line
    fgs->Add(new wxStaticText(this, wxID_ANY, "Processor :"));
    fgs->Add(m_processorCombo, 1, wxEXPAND);
    fgs->Add(new wxStaticText(this, wxID_ANY, ""), 1, wxEXPAND);

    // Second line
    fgs->Add(new wxStaticText(this, wxID_ANY, ""));
    fgs2 = new wxFlexGridSizer(2, 4, 9, 9);
    fgs2->Add(new wxStaticText(this, wxID_ANY, "MDIO Pin :"));
    fgs2->Add(m_mdioCombo, 1, wxEXPAND);
    fgs2->Add(new wxStaticText(this, wxID_ANY, "MDC Pin :"));
    fgs2->Add(m_mdcCombo, 1, wxEXPAND);
    fgs2->Add(new wxStaticText(this, wxID_ANY, "Address (0x..):"));
    fgs2->Add(m_addrTxtCtrl, 1, wxEXPAND);
    fgs2->Add(new wxStaticText(this, wxID_ANY, "Register (0x..):"));
    fgs2->Add(m_regTxtCtrl, 1, wxEXPAND);
    fgs2->AddGrowableCol(1, 1);
    fgs2->AddGrowableCol(3, 1);
    fgs->Add(fgs2, 1, wxEXPAND);
    fgs->Add(m_autoscanBtn);

    // Third line
    fgs->Add(new wxStaticText(this, wxID_ANY, "Data to Write :"));
    fgs->Add(m_writeTxtCtrl, 1, wxEXPAND);
    fgs->Add(m_writeBtn);

    // Fourth line
    fgs->Add(new wxStaticText(this, wxID_ANY, "Data Read :"));
    fgs->Add(m_readTxtCtrl, 1, wxEXPAND);
    fgs->Add(m_readBtn);

    fgs->AddGrowableCol(1, 1);

    hbox->Add(fgs, 1, wxALL | wxEXPAND, 15);
    SetSizer(hbox);

    FitInside();
    SetScrollRate(5, 5);
}

void MdioPage::setConnectMode(void)
{
    m_processorCombo->Enable(true);
    m_mdioCombo->Enable(true);
    m_mdcCombo->Enable(true);

    m_autoscanBtn->Enable(true);
    m_writeBtn->Enable(true);
    m_readBtn->Enable(true);

    m_regTxtCtrl->Enable(true);
    m_addrTxtCtrl->Enable(true);
    m_writeTxtCtrl->Enable(true);
    m_readTxtCtrl->Enable(true);
}

void MdioPage::setDisconnectMode(void)
{
    m_processorCombo->Enable(false);
    m_mdioCombo->Enable(false);
    m_mdcCombo->Enable(false);

    m_autoscanBtn->Enable(false);
    m_writeBtn->Enable(false);
    m_readBtn->Enable(false);

    m_regTxtCtrl->Enable(false);
    m_addrTxtCtrl->Enable(false);
    m_writeTxtCtrl->Enable(false);
    m_readTxtCtrl->Enable(false);
}
