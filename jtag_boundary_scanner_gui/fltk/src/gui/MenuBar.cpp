/*
 * Jtag Boundary Scanner
 * Copyright (c) 2019 S. Corbeau
 *
 * Compate WinAPI for Linux is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 3.0 of the License, or (at your option) any later version.
 *
 * Compate WinAPI for Linux is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License version 3 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Compate WinAPI for Linuxs; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

/**
* @file   MainBar.cpp
* @brief  Implement MenuBar of main windows.
* @author Sébastien CORBEAU <seb.corbeau@gmail.com>
*/
#include <stdlib.h>
#include <stdio.h>
#include <gui/MenuBar.h>
#include <gui/MainWindow.h>

static void MenuExitCallback(Fl_Widget *w, void * ptr);
static void MenuAboutCallback(Fl_Widget *w, void * ptr);
static void MenuOpenBsdlCallback(Fl_Widget *w, void * ptr);
static void MenuConnectCallback(Fl_Widget *w, void * ptr);
static void MenuTotoCallBack(Fl_Widget *w, void * ptr);
static void MenuTitiCallBack(Fl_Widget *w, void * ptr);

MenuBar::MenuBar(int p_width) : Fl_Menu_Bar(0, 0, p_width, MENU_BAR_HEIGHT)
{
	add("&File/&Open BSDL", FL_COMMAND+'o', MenuOpenBsdlCallback, (void*)this);
	add("&File/&Connect",  0, MenuConnectCallback);
	add("&File/&Quit",  "^q", MenuExitCallback);
	add("&File/toto", 0, MenuTotoCallBack);
	add("&File/titi", 0, MenuTitiCallBack);
	add("&Help/&About", 0, MenuAboutCallback);
}

MenuBar::~MenuBar()
{

}

void MenuBar::resize(int p_x, int p_y, int p_w, int p_h)
{
	//printf("%s x=%d y=%d w=%d h=%d\n", __PRETTY_FUNCTION__, x, y, w, h);
	w(p_w);
	h(MENU_BAR_HEIGHT);
	redraw();
}

static void MenuExitCallback(Fl_Widget *w, void * ptr)
{
	printf("Exit\n");
	exit(0);
}

static void MenuAboutCallback(Fl_Widget *w, void * ptr)
{
	const Fl_Menu_Item *item = ((Fl_Menu_Bar*)w)->mvalue();

	if ( strcmp(item->label(), "&About") == 0 ) { printf("About\n"); }
}

static void MenuOpenBsdlCallback(Fl_Widget *w, void * ptr)
{
	Fl_Widget *p = w->parent();
	while (p->parent()) p = p->parent();
	((MainWindow*)p)->loadBsdl(w);
}

static void MenuConnectCallback(Fl_Widget *w, void * ptr)
{
	Fl_Widget *p = w->parent();
	while (p->parent()) p = p->parent();
	((MainWindow*)p)->connect(w);
}

static void MenuTotoCallBack(Fl_Widget *w, void * ptr)
{
	Fl_Widget *p = w->parent();
	while (p->parent()) p = p->parent();
	((MainWindow*)p)->callBack(w);
}

static void MenuTitiCallBack(Fl_Widget *w, void * ptr)
{
	Fl_Widget *p = w->parent();
	while (p->parent()) p = p->parent();
	((MainWindow*)p)->callBack2(w);
}
