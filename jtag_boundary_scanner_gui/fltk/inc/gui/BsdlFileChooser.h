/*
 * Jtag Boundary Scanner
 * Copyright (c) 2019 Viveris Technologies
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
 * along with Compate WinAPI for Linuxs; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

/**
* @file   BsdlFileChooser.h
* @brief  Declare BSDL file chooser window.
* @author Sébastien CORBEAU <sebastien.corbeau@viveris.fr>
*/
#ifndef GUI_BSDLFILECHOOSER_H_
#define GUI_BSDLFILECHOOSER_H_

#include <string>

#include <FL/Fl.H>
#include <FL/Fl_Native_File_Chooser.H>

class BsdlFileChooser {
public:
	BsdlFileChooser();
	~BsdlFileChooser();

	std::string getSelectBsdlFile(void);
private:
	Fl_Native_File_Chooser *m_fileChooser;
};

#endif /* GUI_BSDLFILECHOOSER_H_ */
