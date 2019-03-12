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
* @file   CpuData.cpp
* @brief  Implement class CpuData to display Processor IO.
* @author Sébastien CORBEAU <sebastien.corbeau@viveris.fr>
*/
#include "gui/CpuPage.h"

#include "gui/MainEventId.h"

static const int MAX_NB_COLUMN = 8;
static const int MIN_GPIO_BY_COLUMN = 10;

CpuPage::CpuPage(wxWindow *parent,
        MainFrame *frame,
        CpuData *p_cpu)
                        : MainPage(parent, wxID_ANY, true)
{
    wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
    wxSizerFlags flags;
    wxFlexGridSizer *fgs = NULL;
    int nb_gpio_per_column;
    size_t i;
    bool toggle_available;
    size_t nb_gpio;
    size_t nb_usable_gpio = 0;
    size_t nb_column;
    int baseEvtId;

    flags.Center();

    m_cpu = p_cpu;
    baseEvtId = frame->GetCpuCheckboxEventIdBase();
    nb_usable_gpio = p_cpu->getNbUsablePins();

    nb_column = nb_usable_gpio / MIN_GPIO_BY_COLUMN;
    if(nb_column > MAX_NB_COLUMN){
        nb_column = 7;
    }

    if(nb_column > 0) {
        nb_gpio_per_column = nb_usable_gpio / nb_column;
        nb_gpio = nb_gpio_per_column * nb_column;
    } else {
        nb_gpio_per_column = nb_usable_gpio;
        nb_gpio = nb_usable_gpio;
    }

    for(i=0; i<nb_gpio; i++) {
        PinData *pin = p_cpu->getPinData(i);

        toggle_available = false;
        if(0 == (i%nb_gpio_per_column)) {
            if(0 != i) {
                hbox->Add(fgs, 1, wxALL | wxEXPAND, 1);
            }

            fgs = new wxFlexGridSizer(nb_gpio_per_column+1, 5, 3, 3);
            fgs->Add(new wxStaticText(this, wxID_ANY, "Name"));
            fgs->Add(new wxStaticText(this, wxID_ANY, "O"), flags);
            fgs->Add(new wxStaticText(this, wxID_ANY, "OE"), flags);
            fgs->Add(new wxStaticText(this, wxID_ANY, "I"), flags);
            fgs->Add(new wxStaticText(this, wxID_ANY, "T"), flags);
        }
        fgs->Add(new wxStaticText(this, wxID_ANY, pin->getName()));
        if(pin->isOutputPin()) {
            fgs->Add(new wxCheckBox(this, baseEvtId+i, ""));
            frame->ConnectOutputProcessor(baseEvtId+i);
            toggle_available = true;
        } else {
            fgs->Add(new wxStaticText(this, wxID_ANY, " "));
        }

        if(pin->isTristatePin()) {
            fgs->Add(new wxCheckBox(this, baseEvtId+i+nb_usable_gpio, ""));
            frame->ConnectOutputEnableProcessor(baseEvtId+i+nb_usable_gpio);
            toggle_available = true;
        } else {
            fgs->Add(new wxStaticText(this, wxID_ANY, " "));
        }

        if(pin->isInputPin()) {
            wxCheckBox *chkbox = new wxCheckBox(this, wxID_ANY, "");
            chkbox->Enable(false);
            fgs->Add(chkbox);
        } else {
            fgs->Add(new wxStaticText(this, wxID_ANY, "   "));
        }

        if(toggle_available) {
            fgs->Add(new wxCheckBox(this, baseEvtId+i+(2*nb_usable_gpio), ""));
            frame->ConnectToggleProcessor(baseEvtId+i+(2*nb_usable_gpio));
        } else {
            fgs->Add(new wxStaticText(this, wxID_ANY, " "));
        }
    }

    if(fgs) {
        hbox->Add(fgs, 1, wxALL | wxEXPAND, 1);
    }

    // Display last gpio if necessary
    if(nb_usable_gpio-nb_gpio) {
        fgs = new wxFlexGridSizer(nb_usable_gpio-nb_gpio+1, 5, 3, 3);
        fgs->Add(new wxStaticText(this, wxID_ANY, "Name"));
        fgs->Add(new wxStaticText(this, wxID_ANY, "O"), flags);
        fgs->Add(new wxStaticText(this, wxID_ANY, "OE"), flags);
        fgs->Add(new wxStaticText(this, wxID_ANY, "I"), flags);
        fgs->Add(new wxStaticText(this, wxID_ANY, "T"), flags);
        for(; i<nb_usable_gpio; i++) {
            PinData *pin = p_cpu->getPinData(i);

            toggle_available = false;

            // Gpio name
            fgs->Add(new wxStaticText(this, wxID_ANY, pin->getName()));

            // GPIO is output
            if(pin->isOutputPin()) {
                fgs->Add(new wxCheckBox(this, baseEvtId+i, ""));
                frame->ConnectOutputProcessor(baseEvtId+i);
                toggle_available = true;
            } else {
                fgs->Add(new wxStaticText(this, wxID_ANY, " "));
            }

            // GPIO is three state
            if(pin->isTristatePin()) {
                fgs->Add(new wxCheckBox(this, baseEvtId+i+nb_usable_gpio, ""));
                frame->ConnectOutputEnableProcessor(baseEvtId+i+nb_usable_gpio);
                toggle_available = true;
            } else {
                fgs->Add(new wxStaticText(this, wxID_ANY, " "));
            }

            // GPIO has input state
            if(pin->isInputPin()) {
                wxCheckBox *chkbox = new wxCheckBox(this, wxID_ANY, "");
                chkbox->Enable(false);
                fgs->Add(chkbox);
            } else {
                fgs->Add(new wxStaticText(this, wxID_ANY, "   "));
            }

            if(toggle_available) {
                fgs->Add(new wxCheckBox(this, baseEvtId+i+(2*nb_usable_gpio), ""));
                frame->ConnectToggleProcessor(baseEvtId+i+(2*nb_usable_gpio));
            } else {
                fgs->Add(new wxStaticText(this, wxID_ANY, " "));
            }
        }
        hbox->Add(fgs, 1, wxALL | wxEXPAND, 15);
    }

    SetSizer(hbox);

    FitInside();
    SetScrollRate(5, 5);
}

CpuPage::~CpuPage()
{
    // TODO : Clear list of check box
}

void CpuPage::setConnectMode(void)
{
    // NOTHING TODO HERE : PROCESSOR PAGE CAN BE LOAD WITHOUT PROBING
}

void CpuPage::setDisconnectMode(void)
{
    // NOTHING TODO HERE : PROCESSOR PAGE CAN BE LOAD WITHOUT PROBING
}

