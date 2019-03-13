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
MainFrame::MainFrame(SystemController *p_controller)
       : wxFrame((wxFrame *)NULL,
                 wxID_ANY,
                 "JTAG Boundary Scanner",
                 wxDefaultPosition,
                 wxSize (800, 600))
{
    wxSizer *sizerV = new wxBoxSizer(wxVERTICAL);

    m_checkboxCpuEvtBaseId = EVT_Processor_Chkbox;

    m_controller = p_controller;

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
    m_notebook->AddPage(new ProbePage(m_notebook, this),    "Probes");
    m_notebook->AddPage(new I2cPage(m_notebook),            "I2C");
    m_notebook->AddPage(new SpiPage(m_notebook),            "SPI");
    m_notebook->AddPage(new MdioPage(m_notebook),           "MDIO");

    sizerV->Add(m_notebook, 1, wxALL | wxEXPAND, 15);

    m_panel->SetSizerAndFit(sizerV);

    SetStatusText("JTAG Boundary Scanner");

    m_controller->disconnectProbe();
    disconnectProbe();
}

MainFrame::~MainFrame()
{
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

SystemData* MainFrame::getDataModel(void)
{
    return m_controller->getSystemData();
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

    wxFileDialog dlg(this, "Open BSDL file", wxEmptyString, wxEmptyString,
                    "BSDL and BSD file (*.bsdl;*.bsd)|*.bsdl;*.bsd|Text file (*.txt)|*.txt|Any file (*)|*",
                    wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_CHANGE_DIR);
    if (dlg.ShowModal() == wxID_OK) {
        cpu = m_controller->loadBsdlFile(dlg.GetPath().ToStdString());
        if(!cpu) {
            (void)wxMessageBox(wxString::FromUTF8("Invalid BSDL file:\n") +
                               dlg.GetPath(),
                               "BSDL file error",
                               wxOK | wxICON_ERROR);
        } else {
            m_notebook->AddPage(new CpuPage(m_notebook, this, cpu),
                                cpu->getCpuName());
            m_checkboxCpuEvtBaseId += (3*cpu->getNbUsablePins());
        }
    }
}

void MainFrame::OnRefreshProbe(wxCommandEvent& event)
{
    wxButton *btn = (wxButton*) event.GetEventObject();
    ProbePage *page = (ProbePage*) btn->GetParent();
    printf("Refresh Probe\n");
    // Refresh model
    m_controller->refreshProbe();
    page->refreshProbeList();
}

void MainFrame::OnConnectProbe(wxCommandEvent& event)
{
    wxButton *btn = (wxButton*) event.GetEventObject();
    ProbePage *page = (ProbePage*) btn->GetParent();
    int index = 0;

    printf("Current selected probe %d\n", page->getSelectedProbeIndex());

    if(btn->GetLabel() == "Connect") {
        // TODO: Get probe indentifier
        index = m_controller->connectToProbe(0);
        if(index == -1) {
            //TODO: Add probe name
            (void)wxMessageBox("Failed to connect to:\n",
                               "Probe connection failed !",
                               wxOK | wxICON_ERROR);
        }
        connectProbe();
    } else {
        m_controller->disconnectProbe();
        disconnectProbe();
    }
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

void MainFrame::connectProbe(void)
{
    size_t i;
    MainPage *page;

    for(i=0; i<m_notebook->GetPageCount(); i++) {
        page = (MainPage*)m_notebook->GetPage(i);
        page->setConnectMode();
    }
}

void MainFrame::disconnectProbe(void)
{
    size_t i;
    MainPage *page;

    for(i=0; i<m_notebook->GetPageCount(); i++) {
        page = (MainPage*)m_notebook->GetPage(i);
        page->setDisconnectMode();
    }
}

PinData* MainFrame::getPinFromChkBoxEvt(int checkEvtId)
{
    CpuData *cpu = NULL;
    PinData *pin = NULL;
    int baseEvtId = EVT_Processor_Chkbox;
    size_t i;

    i = 0;
    while((i < m_controller->getNbCpu()) && !cpu) {
        if(checkEvtId < (baseEvtId+((int)m_controller->getCpu(i)->getNbUsablePins()*3))) {
            cpu = m_controller->getCpu(i);
        } else {
            baseEvtId += (int)m_controller->getCpu(i)->getNbUsablePins()*3;
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

