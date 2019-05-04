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
* @file   AboutWindow.cpp
* @brief  Implement class to manage About window.
* @author Sébastien CORBEAU <sebastien.corbeau@viveris.fr>
*/
#include <string>

#include <FL/Fl_Button.H>
#include <FL/Fl_BMP_Image.H>
#include <FL/Fl_Box.H>

#include <jtag_core.h>
#include <winapi_compat.h>

#include "gui/AboutWindow.h"
#include "version.h"

static const int ABOUT_WINDOW_WIDTH = 550;
static const int ABOUT_WINDOW_HEIGHT = 160;
static const int BORDER = 10;
static const int OK_BUTTON_WIDTH = 90;
static const int OK_BUTTON_HEIGHT = 20;

static void callbackOkButton(Fl_Widget *w, void *param)
{
	AboutWindow *win = (AboutWindow*) w->parent();
	if(win)
		win->hide();
}

AboutWindow::AboutWindow(const char *p_applName) :
		Fl_Window(ABOUT_WINDOW_WIDTH, ABOUT_WINDOW_HEIGHT, p_applName)
{
	std::string aboutString;
	Fl_BMP_Image *vtImg = new Fl_BMP_Image("viveris.bmp");
	Fl_Box *boxImg = new Fl_Box(BORDER, BORDER, vtImg->w(), vtImg->h());
	boxImg->image(vtImg);
	boxImg->redraw();
	Fl_Box *aboutTxt = new Fl_Box(boxImg->x()+boxImg->w()+BORDER,
								  BORDER,
								  w()-(boxImg->x()+boxImg->w()+2*BORDER),
								  h()-(OK_BUTTON_HEIGHT + 3*BORDER));
	aboutString = "JTAG Boundary Scanner Version : ";
	aboutString += JTAG_BOUNDARY_SCANNER_APPL_VERSION;
	aboutString += "\nLib JTAG Core Version : ";
	aboutString += LIB_JTAG_CORE_VERSION;
	aboutString += "\nLib WinAPI Compat Version : ";
	aboutString += LIB_WINAPI_COMPAT_VERSION;
	aboutString += "\nCopyright (C) Viveris Technologies 2008-2019\n";
	aboutString += "https://www.viveris.fr/\n";
	aboutString += "https://github.com/viveris/jtag-boundary-scanner\n";
	aboutTxt->copy_label(aboutString.c_str());

	Fl_Button *btnOk = new Fl_Button(w()-BORDER-OK_BUTTON_WIDTH,
									 aboutTxt->y() + aboutTxt->h() + BORDER,
									 OK_BUTTON_WIDTH,
									 OK_BUTTON_HEIGHT,
									 "OK");
	btnOk->callback(callbackOkButton);

	end();
	show();
}

AboutWindow::~AboutWindow()
{

}
