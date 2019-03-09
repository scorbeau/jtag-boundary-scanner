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
* @brief  Declare class MdioPage to display MDIO bus menu.
* @author Sébastien CORBEAU <sebastien.corbeCau@viveris.fr>
*/
#ifndef GUI_MDIO_PAGE_H__
#define GUI_MDIO_PAGE_H__

#include "wxWidgetsInc.h"
#include "MainPage.h"

// and the panel taking up MyFrame client area
class MdioPage : public MainPage
{
public:
    MdioPage(wxWindow *parent);

    void setConnectMode(void);
    void setDisconnectMode(void);
private:
    wxComboBox *m_processorCombo;
    wxComboBox *m_mdioCombo;
    wxComboBox *m_mdcCombo;

    wxButton   *m_autoscanBtn;
    wxButton   *m_writeBtn;
    wxButton   *m_readBtn;

    wxTextCtrl *m_addrTxtCtrl;
    wxTextCtrl *m_regTxtCtrl;
    wxTextCtrl *m_writeTxtCtrl;
    wxTextCtrl *m_readTxtCtrl;
};

#endif /* GUI_MDIO_PAGE_H__ */

