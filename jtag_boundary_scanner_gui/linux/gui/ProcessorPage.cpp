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
* @file   ProcessorPage.cpp
* @brief  Implement class ProcessorPage to display Processor IO.
* @author Sébastien CORBEAU <sebastien.corbeau@viveris.fr>
*/
#include "ProcessorPage.h"

#include "MainEventId.h"

static const int MAX_NB_COLUMN = 8;
static const int MIN_GPIO_BY_COLUMN = 10;

ProcessorPage::ProcessorPage(wxWindow *parent,
        MainFrame *frame,
        ProcessorData *p_processor)
                        : MainPage(parent, wxID_ANY, true)
{
    wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
    wxSizerFlags flags;
    wxFlexGridSizer *fgs;
    m_processor = p_processor;
    int nb_gpio_per_column;
    size_t i;
    size_t j;
    bool toggle_available;
    size_t nb_gpio;
    size_t nb_usable_gpio = 0;
    size_t nb_column;

    flags.Center();

    nb_usable_gpio = p_processor->getNbUsableGpio();

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

    //printf("Nb gpio by column %d\n", nb_gpio_per_column);

    fgs = new wxFlexGridSizer(nb_gpio_per_column+1, 5, 3, 3);
    j=0;
    for(i=0; j<nb_gpio; i++) {
        GpioData *gpio = p_processor->getGpioData(i);
        if(!gpio->isGpioUsable()) {
            continue;
        }

        toggle_available = false;
        //printf("GPIO[%d] %s", j, gpio->getName().c_str());
        if((0 == i) || (0 == (j%nb_gpio_per_column))) {
            
            fgs->Add(new wxStaticText(this, wxID_ANY, "Name"));
            fgs->Add(new wxStaticText(this, wxID_ANY, "O"), flags);
            fgs->Add(new wxStaticText(this, wxID_ANY, "OE"), flags);
            fgs->Add(new wxStaticText(this, wxID_ANY, "I"), flags);
            fgs->Add(new wxStaticText(this, wxID_ANY, "T"), flags);
        }
        fgs->Add(new wxStaticText(this, wxID_ANY, gpio->getName()));
        if(gpio->isOutputGpio()) {
            //printf(" out");
            // TODO update wxID_ANY ?
            fgs->Add(new wxCheckBox(this, wxID_ANY, ""));
            frame->ConnectOutputProcessor(EVT_Processor_Chkbox);
            // TODO Bind to event handler.
            toggle_available = true;
        } else {
            fgs->Add(new wxStaticText(this, wxID_ANY, " "));
        }

        if(gpio->isTristateGpio()) {
            //printf(" 3-state");
            // TODO update wxID_ANY ?
            fgs->Add(new wxCheckBox(this, wxID_ANY, ""));
            frame->ConnectOutputEnableProcessor(EVT_Processor_Chkbox);
            // TODO Bind to event handler.
            toggle_available = true;
        } else {
            fgs->Add(new wxStaticText(this, wxID_ANY, " "));
        }

        if(gpio->isInputGpio()) {
            //printf(" in");
            wxCheckBox *chkbox = new wxCheckBox(this, wxID_ANY, "");
            chkbox->Enable(false);
            // TODO update wxID_ANY ?
            fgs->Add(chkbox);
            // TODO Bind to event handler.
        } else {
            fgs->Add(new wxStaticText(this, wxID_ANY, "   "));
        }

        if(toggle_available) {
            fgs->Add(new wxCheckBox(this, EVT_Processor_Chkbox+j+(2*nb_usable_gpio), ""));
            frame->ConnectToggleProcessor(EVT_Processor_Chkbox+j+(2*nb_usable_gpio));
        } else {
            fgs->Add(new wxStaticText(this, wxID_ANY, " "));
        }

        //printf("\n");
        j++;
        if(0 == (j%nb_gpio_per_column)) {
            hbox->Add(fgs, 1, wxALL | wxEXPAND, 1);
            if(i<p_processor->getNbPins())
                fgs = new wxFlexGridSizer(nb_gpio_per_column+1, 5, 3, 3);
        }
    }

    // Display last gpio if necessary
    if(nb_usable_gpio-nb_gpio) {
        fgs = new wxFlexGridSizer(nb_usable_gpio-nb_gpio+1, 5, 3, 3);
        fgs->Add(new wxStaticText(this, wxID_ANY, "Name"));
        fgs->Add(new wxStaticText(this, wxID_ANY, "O"));
        fgs->Add(new wxStaticText(this, wxID_ANY, "OE"));
        fgs->Add(new wxStaticText(this, wxID_ANY, "I"));
        fgs->Add(new wxStaticText(this, wxID_ANY, "T"));
        for(; i<p_processor->getNbPins(); i++) {
            GpioData *gpio = p_processor->getGpioData(i);
            if(!gpio->isGpioUsable()) {
                continue;
            }
            toggle_available = false;
            //printf("GPIO[%d] %s", i, gpio->getName().c_str());

            // GPio name
            fgs->Add(new wxStaticText(this, wxID_ANY, gpio->getName()));

            // GPIO is output
            if(gpio->isOutputGpio()) {
                //printf(" out");
                // TODO update wxID_ANY ?
                fgs->Add(new wxCheckBox(this, wxID_ANY, ""));
                frame->ConnectOutputProcessor(EVT_Processor_Chkbox);
                // TODO Bind to event handler.
                toggle_available = true;
            } else {
                fgs->Add(new wxStaticText(this, wxID_ANY, " "));
            }

            // GPIO is three state
            if(gpio->isTristateGpio()) {
                //printf(" 3-state");
                // TODO update wxID_ANY ?
                fgs->Add(new wxCheckBox(this, wxID_ANY, ""));
                frame->ConnectOutputEnableProcessor(EVT_Processor_Chkbox);
                // TODO Bind to event handler.
                toggle_available = true;
            } else {
                fgs->Add(new wxStaticText(this, wxID_ANY, " "));
            }

            // GPIO has input state
            if(gpio->isInputGpio()) {
                //printf(" in");
                wxCheckBox *chkbox = new wxCheckBox(this, wxID_ANY, "");
                chkbox->Enable(false);
                // TODO update wxID_ANY ?
                fgs->Add(chkbox);
                // TODO Bind to event handler.
            } else {
                fgs->Add(new wxStaticText(this, wxID_ANY, "   "));
            }

            if(toggle_available) {
                fgs->Add(new wxCheckBox(this, EVT_Processor_Chkbox+i+(2*p_processor->getNbUsableGpio()), ""));
                frame->ConnectToggleProcessor(EVT_Processor_Chkbox+i+(2*p_processor->getNbUsableGpio()));
            } else {
                fgs->Add(new wxStaticText(this, wxID_ANY, " "));
            }
            j++;
            //printf("\n");
        }
        hbox->Add(fgs, 1, wxALL | wxEXPAND, 15);
    }

    SetSizer(hbox);

    FitInside();
    SetScrollRate(5, 5);
}

ProcessorPage::~ProcessorPage()
{
    // TODO : Clear list of check box
}

void ProcessorPage::setConnectMode(void)
{
    // NOTHING TODO HERE : PROCESSOR PAGE CAN BE LOAD WITHOUT PROBING
}

void ProcessorPage::setDisconnectMode(void)
{
    // NOTHING TODO HERE : PROCESSOR PAGE CAN BE LOAD WITHOUT PROBING
}

