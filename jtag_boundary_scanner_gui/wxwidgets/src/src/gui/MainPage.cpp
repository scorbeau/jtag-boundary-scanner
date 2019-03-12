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
* @file   MainPage.cpp
* @brief  Declare class MainPage inherited by all page.
 for panel application.
* @author Sébastien CORBEAU <sebastien.corbeau@viveris.fr>
*/
#include "gui/MainPage.h"

MainPage::MainPage(wxWindow *parent, wxWindowID id, bool isProcessor) :
         wxScrolledWindow(parent, id)
{
    m_isProcessor = isProcessor;
}

bool MainPage::isProcessorPage(void)
{
    return m_isProcessor;
}

