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
* @file   MainEventId.h
* @brief  Define event identifier.
* @author Sébastien CORBEAU <sebastien.corbeau@viveris.fr>
*/
#ifndef GUI_MAIN_EVENT_ID_H__
#define GUI_MAIN_EVENT_ID_H__

// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------
enum
{
    // Menu event (define by framework)
    EVT_Menu_File_Quit = wxID_EXIT,
    EVT_Menu_Help_About = wxID_ABOUT,

    // Menu event (define by user)
    EVT_Menu_File_Ld_Bsdl = wxID_HIGHEST+1,

    // Probe panel event
    EVT_Probe_Btn_Connect,
    EVT_Probe_Btn_Refresh,

    // I2C panel event
    EVT_I2c_Btn_Autoscan,
    EVT_I2c_Btn_Write,
    EVT_I2c_Btn_Read,
    EVT_I2c_Combo_Proc,

    // SPI panel event
    EVT_Spi_Btn_Write,
    EVT_Spi_Combo_Proc,

    // MDIO panel event
    EVT_Mdio_Btn_Autoscan,
    EVT_Mdio_Btn_Write,
    EVT_Mdio_Btn_Read,
    EVT_Mdio_Combo_Proc,

    // Proc panel event
    EVT_Processor_Chkbox,

    EVT_MAX
};

#endif /* GUI_MAIN_EVENT_ID_H__ */

