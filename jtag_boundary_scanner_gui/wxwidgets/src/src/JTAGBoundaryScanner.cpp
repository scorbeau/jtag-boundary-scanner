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
* @file   JTAGBoundaryScanner.cpp
* @brief  JTAG Boundary Scanner wxWidget GUI.
* @author Sébastien CORBEAU <sebastien.corbeau@viveris.fr>
*/

#include "SystemController.h"
#include "gui/MainFrame.h"

// Define a new application
class JtagBoundaryScanner: public wxApp
{
public:
    bool OnInit() wxOVERRIDE;
};

wxIMPLEMENT_APP(JtagBoundaryScanner);

// The `main program' equivalent, creating the windows and returning the
// main frame
bool JtagBoundaryScanner::OnInit()
{
    SystemController *controller = new SystemController();
    controller->refreshProbe();

    if ( !wxApp::OnInit() )
        return false;

    // Create the main frame window
    MainFrame* frame = new MainFrame(controller);

    frame->Show(true);

    return true;
}


