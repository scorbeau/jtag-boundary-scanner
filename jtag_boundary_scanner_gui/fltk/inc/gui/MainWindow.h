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
* @file   MainWindows.h
* @brief  Declare MainWindows class (application windows).
* @author Sébastien CORBEAU <seb.corbeau@gmail.com>
*/
#ifndef GUI_MAINWINDOW_H_
#define GUI_MAINWINDOW_H_

#include <string>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Native_File_Chooser.H>

#include <gui/MenuBar.h>
#include <gui/TabsMenu.h>

class SystemController;
class SystemData;
class CpuTab;

class MainWindow : public Fl_Window
{
public:
	MainWindow(SystemController *p_controller,
				const char *p_applName,
				int p_width = 1024,
				int p_height = 600);
	~MainWindow();

	int run(void);
	void callBack(Fl_Widget *w);
	void callBack2(Fl_Widget *w);
	void loadBsdl(Fl_Widget *w);
	void connect(Fl_Widget *w);

	void refresh(void);

	int getMenuBarEnd(void);

	const SystemData* getModel(void);
	CpuTab* getCurrentCpuTab(void);

private:
	MenuBar *m_menu;
	TabsMenu *m_tabs;
	Fl_Native_File_Chooser *m_fileChooser;

	SystemController *m_controller;
};

#endif /* GUI_MAINWINDOW_H_ */
