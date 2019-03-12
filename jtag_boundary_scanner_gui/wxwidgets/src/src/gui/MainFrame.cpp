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
* @file   MainFrame.cpp
* @brief  Implements class MainFrame application.
* @author Sébastien CORBEAU <sebastien.corbeau@viveris.fr>
*/
#include "gui/MainFrame.h"
#include "gui/MainEventId.h"
#include "gui/ProbePage.h"
#include "gui/I2cPage.h"
#include "gui/SpiPage.h"
#include "gui/MdioPage.h"
#include "gui/CpuPage.h"

#include "images/JTAGBoundaryScanner_small.xpm"

#include "version.h"

// ----------------------------------------------------------------------------
// event tables
// ----------------------------------------------------------------------------

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    // Event menu
    EVT_MENU(EVT_Menu_File_Quit,        MainFrame::OnQuit)
    EVT_MENU(EVT_Menu_Help_About,       MainFrame::OnAbout)
    EVT_MENU(EVT_Menu_File_Ld_Bsdl,     MainFrame::OnLoadBsdl)

    // Event tab probe
    EVT_BUTTON(EVT_Probe_Btn_Connect,   MainFrame::OnConnectProbe)
    EVT_BUTTON(EVT_Probe_Btn_Refresh,   MainFrame::OnRefreshProbe)

    // Event tab I2C
    EVT_BUTTON(EVT_I2c_Btn_Autoscan,    MainFrame::OnAutoscanI2c)
    EVT_BUTTON(EVT_I2c_Btn_Write,       MainFrame::OnWriteI2c)
    EVT_BUTTON(EVT_I2c_Btn_Read,        MainFrame::OnReadI2c)
    EVT_COMBOBOX(EVT_I2c_Combo_Proc,    MainFrame::OnProcessorI2c)

    // Event tab SPI
    EVT_BUTTON(EVT_Spi_Btn_Write,       MainFrame::OnWriteSpi)
    EVT_COMBOBOX(EVT_Spi_Combo_Proc,    MainFrame::OnProcessorSpi)

    // Event tab MDIO
    EVT_BUTTON(EVT_Mdio_Btn_Autoscan,    MainFrame::OnAutoscanMdio)
    EVT_BUTTON(EVT_Mdio_Btn_Write,       MainFrame::OnWriteMdio)
    EVT_BUTTON(EVT_Mdio_Btn_Read,        MainFrame::OnReadMdio)
    EVT_COMBOBOX(EVT_Mdio_Combo_Proc,    MainFrame::OnProcessorMdio)
wxEND_EVENT_TABLE()

// Define MainFrame constructor
MainFrame::MainFrame(const ProbeData &p_probeData)
       : wxFrame((wxFrame *)NULL,
                 wxID_ANY,
                 "JTAG Boundary Scanner",
                 wxDefaultPosition,
                 wxSize (800, 600))
{
    wxSizer *sizerV = new wxBoxSizer(wxVERTICAL);

    m_checkboxCpuEvtBaseId = EVT_Processor_Chkbox;

    m_probeData = p_probeData;
    m_jtagCore = jtagcore_init();
    if(!m_jtagCore) {
        printf("Failed to init jtagcore");
        exit(-1);
    }

    SetIcon(wxICON(JTAGBoundaryScanner_small));

    CreateStatusBar();

    m_menu = NULL;

    wxMenu *fileMenu = new wxMenu;
    fileMenu->Append(EVT_Menu_File_Ld_Bsdl, "&Load BSDL file\tCtrl-L");
    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_EXIT);

    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(wxID_ABOUT);

    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(fileMenu, "&File");
    menuBar->Append(helpMenu, "&Help");

    SetMenuBar(menuBar);

    m_panel = new wxPanel(this, wxID_ANY);
    m_notebook = new wxNotebook(m_panel, wxID_ANY);
    m_notebook->AddPage(new ProbePage(m_notebook),      "Probes");
    m_notebook->AddPage(new I2cPage(m_notebook),        "I2C");
    m_notebook->AddPage(new SpiPage(m_notebook),        "SPI");
    m_notebook->AddPage(new MdioPage(m_notebook),       "MDIO");

    sizerV->Add(m_notebook, 1, wxALL | wxEXPAND, 15);

    m_panel->SetSizerAndFit(sizerV);

    SetStatusText("JTAG Boundary Scanner");

    ManageConnection();
}

MainFrame::~MainFrame()
{
    jtagcore_deinit(m_jtagCore);
#warning "Delete processor data"
#if 0
    if(m_menu)
        delete m_menu;

    if(m_panel)
        delete m_panel;

    if(m_notebook)
        delete m_notebook;
#endif
}

int MainFrame::GetCpuCheckboxEventIdBase(void)
{
    return m_checkboxCpuEvtBaseId;
}

void MainFrame::ConnectOutputProcessor(int p_eventId)
{
    Bind(wxEVT_COMMAND_CHECKBOX_CLICKED,
        &MainFrame::OnOutputProcessor,
        this,
        p_eventId,
        p_eventId);
}

void MainFrame::ConnectOutputEnableProcessor(int p_eventId)
{
    Bind(wxEVT_COMMAND_CHECKBOX_CLICKED,
        &MainFrame::OnOutputEnableProcessor,
        this,
        p_eventId,
        p_eventId);
}

void MainFrame::ConnectToggleProcessor(int p_eventId)
{
    Bind(wxEVT_COMMAND_CHECKBOX_CLICKED,
        &MainFrame::OnToggleProcessor,
        this,
        p_eventId,
        p_eventId);
}

void MainFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}

void MainFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    (void)wxMessageBox("JTAG Boundary Scanner" JTAG_BOUNDARY_SCANNER_VERSION
                       "\n(c) 2008-2019 Viveris Technologies\n"
                       "http://www.viveris.fr\n"
                       "http://github.com/viveris/jtag-boundary-scanner\n",
                       "About JTAG Boundary Scanner",
                       wxOK | wxICON_INFORMATION);
}

void MainFrame::OnLoadBsdl(wxCommandEvent& event)
{
    CpuData *cpu;
    int err;
    unsigned long id;
    int nb_pins;
    wxString fname;
    char buffer[512];
    int type;
    int i;
    int cpuIdx;

    wxFileDialog dlg(this, "Open BSDL file", wxEmptyString, wxEmptyString,
                    "BSDL and BSD file (*.bsdl;*.bsd)|*.bsdl;*.bsd|Text file (*.txt)|*.txt|Any file (*)|*",
                    wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_CHANGE_DIR);
    if (dlg.ShowModal() == wxID_OK) {
        fname = dlg.GetPath ();
        strncpy(buffer, fname.mb_str(), sizeof(buffer)-1);
        //printf("Path %s\n", buffer);
        cpuIdx = jtagcore_loadbsdlfile(m_jtagCore, buffer, -1);
        if(cpuIdx < 0) {
            (void)wxMessageBox(wxString::FromUTF8("Invalid BSDL file:\n") +
                               fname,
                               "BSDL file error",
                               wxOK | wxICON_ERROR);
        } else {
            //printf("jtagcore_loadbsdlfile ret %d\n", err);
            id = jtagcore_get_bsdl_id(m_jtagCore, buffer);
            err = jtagcore_get_dev_name(m_jtagCore,
                                        cpuIdx, 
                                        buffer,
                                        NULL);
            //printf("Processor name %s err %d\n", buffer, err);
            if(!err) {
                cpu = new CpuData(std::string(buffer), id, cpuIdx);
                //printf("Id = %16X\n", id);
                nb_pins = jtagcore_get_number_of_pins(m_jtagCore, cpuIdx);
                //printf("Nb pins %d\n", nb_pins);

                i = 0;
                while((i<nb_pins) && (!err)) {
                    err = jtagcore_get_pin_properties(m_jtagCore,
                                                      cpuIdx,
                                                      i,
                                                      buffer,
                                                      sizeof(buffer),
                                                      &type);
                    if(!err) {
                        //printf("Name %s type %d\r\n", buffer, type);

                        cpu->addPin(std::string(buffer),
                                    type,
                                    false,
                                    false,
                                    false,
                                    false);
                    }
                    i++;
                }

                if(err) {
                    delete cpu;
                    (void)wxMessageBox(wxString::FromUTF8("Failed to get "
                                   "processor data from :\n") +
                                   fname,
                                   "BSDL file error",
                                   wxOK | wxICON_ERROR);
                } else {
                    m_notebook->AddPage(new CpuPage(m_notebook, this, cpu),
                                        cpu->getCpuName());
                    m_cpudata.push_back(cpu);
                    m_checkboxCpuEvtBaseId += (3*cpu->getNbUsablePins());
                }
            }
        }
    }
}

void MainFrame::OnRefreshProbe(wxCommandEvent& event)
{
    printf("Refresh Probe\n");
}

void MainFrame::OnConnectProbe(wxCommandEvent& event)
{
    ManageConnection();
}

void MainFrame::OnAutoscanI2c(wxCommandEvent& event)
{
    printf("Autoscan I2C\n");
}

void MainFrame::OnWriteI2c(wxCommandEvent& event)
{
    printf("Write I2C\n");
}

void MainFrame::OnReadI2c(wxCommandEvent& event)
{
    printf("Read I2C\n");
}

void MainFrame::OnProcessorI2c(wxCommandEvent& event)
{
    printf("I2C Processor select\n");
}

void MainFrame::OnWriteSpi(wxCommandEvent& event)
{
    printf("Write SPI\n");
}

void MainFrame::OnProcessorSpi(wxCommandEvent& event)
{
    printf("SPI Processor select\n");
}

void MainFrame::OnAutoscanMdio(wxCommandEvent& event)
{
    printf("MDIO autoscan\n");
}

void MainFrame::OnWriteMdio(wxCommandEvent& event)
{
    printf("MDIO write\n");
}

void MainFrame::OnReadMdio(wxCommandEvent& event)
{
    printf("MDIO read\n");
}

void MainFrame::OnProcessorMdio(wxCommandEvent& event)
{
    printf("MDIO Processor select\n");
}

void MainFrame::OnOutputProcessor(wxCommandEvent& event)
{
    wxCheckBox *chkbox = NULL;
    PinData *pin = NULL;
    int evtId = event.GetId();

    chkbox = (wxCheckBox*)event.GetEventObject();

    printf("%s event id %d type %d\n", __func__, evtId, event.GetEventType());
    printf("chkbox %s\n", chkbox->GetName().mb_str().data());
    printf("status %d\n", chkbox->IsChecked());

    pin = getPinFromChkBoxEvt(evtId);
    if(pin)
        pin->setOutputState(chkbox->IsChecked());
}

void MainFrame::OnOutputEnableProcessor(wxCommandEvent& event)
{
    wxCheckBox *chkbox = NULL;
    PinData *pin = NULL;
    int evtId = event.GetId();

    chkbox = (wxCheckBox*)event.GetEventObject();

    printf("%s event id %d type %d\n", __func__, evtId, event.GetEventType());
    printf("chkbox %s\n", chkbox->GetName().mb_str().data());
    printf("status %d\n", chkbox->IsChecked());

    pin = getPinFromChkBoxEvt(evtId);
    if(pin)
        pin->setOutputEnableState(chkbox->IsChecked());
}

void MainFrame::OnToggleProcessor(wxCommandEvent& event)
{
    wxCheckBox *chkbox = NULL;
    PinData *pin = NULL;
    int evtId = event.GetId();

    chkbox = (wxCheckBox*)event.GetEventObject();

    printf("%s event id %d type %d\n", __func__, evtId, event.GetEventType());
    printf("chkbox %s\n", chkbox->GetName().mb_str().data());
    printf("status %d\n", chkbox->IsChecked());

    pin = getPinFromChkBoxEvt(evtId);
    if(pin)
        pin->setToggleState(chkbox->IsChecked());

}

void MainFrame::ManageConnection(void)
{
    size_t i;
    MainPage *page;

    if(m_probeData.isConnect()) {
        for(i=0; i<m_notebook->GetPageCount(); i++) {
            page = (MainPage*)m_notebook->GetPage(i);
            page->setDisconnectMode();
        }
    } else {
       for(i=0; i<m_notebook->GetPageCount(); i++) {
            page =(MainPage*)m_notebook->GetPage(i);
            page->setConnectMode();
        }
    }
    m_probeData.setConnect(!m_probeData.isConnect());
}

PinData* MainFrame::getPinFromChkBoxEvt(int checkEvtId)
{
    CpuData *cpu = NULL;
    PinData *pin = NULL;
    int baseEvtId = EVT_Processor_Chkbox;
    size_t i;

    i = 0;
    while((i < m_cpudata.size()) && !cpu) {
        if(checkEvtId < (baseEvtId+((int)m_cpudata[i]->getNbUsablePins()*3))) {
            cpu = m_cpudata[i];
        } else {
            baseEvtId += (int)m_cpudata[i]->getNbUsablePins()*3;
            i++;
        }
    }

    if(cpu) {
        checkEvtId -= baseEvtId;
        while((checkEvtId >= 0) && !pin)
        {
            if(((int)checkEvtId-(int)cpu->getNbUsablePins()) < 0)
            {
                pin = cpu->getPinData(checkEvtId);
            } else {
                i++;
                checkEvtId -= cpu->getNbUsablePins();
            }
        }
    }

    if(pin)
        printf("Found pin %s\n", pin->getName().c_str());

    return pin;
}

