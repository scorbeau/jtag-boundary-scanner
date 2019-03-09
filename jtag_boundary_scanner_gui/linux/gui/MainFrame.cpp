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
#include "MainFrame.h"
#include "MainEventId.h"
#include "ProbePage.h"
#include "I2cPage.h"
#include "SpiPage.h"
#include "MdioPage.h"
#include "ProcessorPage.h"

#include "images/JTAGBoundaryScanner_small.xpm"

#include "../version.h"

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

void MainFrame::ConnectOutputProcessor(int p_eventId)
{
    Connect(p_eventId,
            wxEVT_COMMAND_CHECKBOX_CLICKED,
            wxCommandEventHandler(MainFrame::OnOutputProcessor));
}

void MainFrame::ConnectOutputEnableProcessor(int p_eventId)
{
    Connect(p_eventId,
            wxEVT_COMMAND_CHECKBOX_CLICKED,
            wxCommandEventHandler(MainFrame::OnOutputEnableProcessor));
}

void MainFrame::ConnectToggleProcessor(int p_eventId)
{
    printf("Bind %d\n", p_eventId);
    Bind(wxEVT_COMMAND_CHECKBOX_CLICKED,
        &MainFrame::OnToogleProcessor,
        this,
        p_eventId,
        p_eventId);
//            wxEVT_COMMAND_CHECKBOX_CLICKED, wxEVT_COMMAND_CHECKBOX_CLICKED, NULL);
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
    ProcessorData *processor;
    int err;
    unsigned long id;
    int nb_pins;
    wxString fname;
    char buffer[512];
    int type;
    int i;
    int proc_idx;

    wxFileDialog dlg(this, "Open BSDL file", wxEmptyString, wxEmptyString,
                    "BSDL and BSD file (*.bsdl;*.bsd)|*.bsdl;*.bsd|Text file (*.txt)|*.txt|Any file (*)|*",
                    wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_CHANGE_DIR);
    if (dlg.ShowModal() == wxID_OK) {
        fname = dlg.GetPath ();
        strncpy(buffer, fname.mb_str(), sizeof(buffer)-1);
        //printf("Path %s\n", buffer);
        err = jtagcore_loadbsdlfile(m_jtagCore, buffer, -1);
        if(err < 0) {
            (void)wxMessageBox(wxString::FromUTF8("Invalid BSDL file:\n") +
                               fname,
                               "BSDL file error",
                               wxOK | wxICON_ERROR);
        } else {
            proc_idx = err;
            //printf("jtagcore_loadbsdlfile ret %d\n", err);
            id = jtagcore_get_bsdl_id(m_jtagCore, buffer);
            err = jtagcore_get_dev_name(m_jtagCore,
                                        proc_idx, 
                                        buffer,
                                        NULL);
            //printf("Processor name %s err %d\n", buffer, err);
            if(!err) {
                processor = new ProcessorData(std::string(buffer),
                                              id,
                                              proc_idx);
                // printf("Id = %16X\n", id);
                nb_pins = jtagcore_get_number_of_pins(m_jtagCore, proc_idx);
                //printf("Nb pins %d\n", nb_pins);
                i = 0;
                do {
                    err = jtagcore_get_pin_properties(m_jtagCore,
                                                      proc_idx,
                                                      i,
                                                      buffer,
                                                      sizeof(buffer),
                                                      &type);
                    if(!err) {
                        //printf("Name %s type %d\r\n", buffer, type);

                        processor->addGpio(std::string(buffer),
                                           type,
                                           false,
                                           false,
                                           false,
                                           false);
                    }
                    i++;
                } while((i<nb_pins) && (!err));

                if(err) {
                    delete processor;
                    (void)wxMessageBox(wxString::FromUTF8("Failed to get "
                                   "processor data from :\n") +
                                   fname,
                                   "BSDL file error",
                                   wxOK | wxICON_ERROR);
                } else {
                    m_notebook->AddPage(new ProcessorPage(m_notebook,
                                                          this,
                                                          processor),
                                        processor->getProcessorName());
                    m_cpudata.push_back(processor);
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
    printf("%s\n", __func__);
}

void MainFrame::OnOutputEnableProcessor(wxCommandEvent& event)
{
    printf("%s\n", __func__);
}

void MainFrame::OnToogleProcessor(wxCommandEvent& event)
{
    printf("%s\n", __func__);
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

