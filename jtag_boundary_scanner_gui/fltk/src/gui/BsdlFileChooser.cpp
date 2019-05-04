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
* @file   BsdlFileChooser.cpp
* @brief  Implement BSDL file chooser window.
* @author Sébastien CORBEAU <sebastien.corbeau@viveris.fr>
*/
#include <gui/BsdlFileChooser.h>

static const char* untitled_default(void);

BsdlFileChooser::BsdlFileChooser() {
	m_fileChooser = new Fl_Native_File_Chooser();
	m_fileChooser->filter("BSD or BSDL files\t*.{bsdl,bsd}\n"
						  "TXT files\t*.txt\n");
	m_fileChooser->preset_file(untitled_default());
}

BsdlFileChooser::~BsdlFileChooser() {
	delete m_fileChooser;
}

std::string BsdlFileChooser::getSelectBsdlFile(void)
{
	std::string ret = "";
	printf("%s : entry\n", __PRETTY_FUNCTION__);
	m_fileChooser->title("Open BSDL file");
	m_fileChooser->type(Fl_Native_File_Chooser::BROWSE_FILE);		// only picks files that exist
	switch ( m_fileChooser->show() ) {
		case -1: break;	// Error
		case  1: break;	// Cancel
		default:		// Choice
			m_fileChooser->preset_file(m_fileChooser->filename());
			ret = std::string(m_fileChooser->filename());
		break;
	}
	return ret;
}

static const char* untitled_default(void)
{
#ifdef __linux
	const char *home = getenv("HOME") ? getenv("HOME") : ".";
#else
	const char *home = getenv("HOME_PATH") ? getenv("HOME_PATH") : ".";
#endif
	return home;
}
