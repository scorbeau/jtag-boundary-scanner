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
#include <FL/Fl_Button.H>
#include <FL/Fl_BMP_Image.H>
#include <FL/Fl_Box.H>

#include "gui/AboutWindow.h"

static const int ABOUT_WINDOWS_WIDTH = 550;
static const int ABOUT_WINDOWS_HEIGHT = 250;
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
		Fl_Window(ABOUT_WINDOWS_WIDTH, ABOUT_WINDOWS_HEIGHT, p_applName)
{
	Fl_BMP_Image *vtImg = new Fl_BMP_Image("viveris.bmp");
	Fl_Box *boxImg = new Fl_Box(BORDER, BORDER, vtImg->w(), vtImg->h());
	boxImg->image(vtImg);
	boxImg->redraw();
	Fl_Box *aboutTxt = new Fl_Box(boxImg->x()+boxImg->w()+BORDER,
								  BORDER,
								  w()-(boxImg->x()+boxImg->w()+2*BORDER),
								  boxImg->h(),
								  "JTAG Boundary Scanner Version 3.0.0\nCopyright (C) Viveris Technologies 2008-2019\nhttps://www.viveris.fr/\nhttps://github.com/viveris/jtag-boundary-scanner\n");

	Fl_Button *btnOk = new Fl_Button(w()-BORDER-OK_BUTTON_WIDTH,
									 aboutTxt->y() + aboutTxt->h() + BORDER,
									 OK_BUTTON_WIDTH,
									 OK_BUTTON_HEIGHT,
									 "OK");
	btnOk->callback(callbackOkButton);
	size(w(), btnOk->y()+btnOk->h()+BORDER);
	end();
	show();
}

AboutWindow::~AboutWindow()
{

}
