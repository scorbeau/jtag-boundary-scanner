/*
 * Compat WinAPI for Linux
 * Copyright (c) 2008 - 2019 S. Corbeau
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
* @file   MainWindows.cpp
* @brief  Implement MainWindows class (application windows.
* @author Sébastien CORBEAU <sebastien.corbeau@viveris.fr>
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <FL/Fl.H>

#include <gui/MainWindow.h>
#include <gui/CpuTab.h>
#include "gui/ProbeTab.h"
#include "gui/AboutWindow.h"

#include "controller/SystemController.h"

#ifdef __linux
#include <FL/Fl_Pixmap.H>
#include <gui/img/JTAGBoundaryScanner_small.xpm>
#else
#warning "TODO: Managed icon on windows"
#endif

static const char* untitled_default(void);

MainWindow::MainWindow(SystemController *p_controller, const char *p_applName,
						int p_width, int p_height) :
		Fl_Window(p_width, p_height, p_applName)
{
	int err;
	Fl::scheme("gtk+");

	m_controller = p_controller;
	err = m_controller->initJtagCore();
	if(err) {
		printf("JTAG core init failed\n");
		exit(-1);
	} else {
		printf("JTAG core init done\n");
		m_controller->refreshProbeList();
	}

	printf("Application name %s\n", p_applName);
	begin();
	m_menu = new MenuBar(p_width);

	printf("On creation tabs x=%d y=%d w=%d h=%d\n", TabsMenu::TABS_MENU_BOARDER,
				TabsMenu::TABS_MENU_BOARDER + m_menu->y() + m_menu->h(),
				p_width-(2*TabsMenu::TABS_MENU_BOARDER),
				p_height-(2*TabsMenu::TABS_MENU_BOARDER + m_menu->y() + m_menu->h()));
	m_tabs = new TabsMenu(TabsMenu::TABS_MENU_BOARDER,
				TabsMenu::TABS_MENU_BOARDER + m_menu->y() + m_menu->h(),
				p_width-(2*TabsMenu::TABS_MENU_BOARDER),
				p_height-(2*TabsMenu::TABS_MENU_BOARDER + m_menu->y() + m_menu->h()));

	m_tabs->end();
	end();
	resizable(this);

#ifdef __linux
	Fl_Pixmap *pixmap = new Fl_Pixmap(JTAGBoundaryScanner_small_xpm);
	icon(new Fl_RGB_Image(pixmap, FL_GRAY));
#else
#warning "TODO: Implement for windows"
#endif
	m_fileChooser = new Fl_Native_File_Chooser();
	m_fileChooser->filter("BSD or BSDL files\t*.{bsdl,bsd}\n"
						  "TXT files\t*.txt\n");
	m_fileChooser->preset_file(untitled_default());
}

MainWindow::~MainWindow()
{
	//delete m_menu;
	delete m_tabs;
	delete m_fileChooser;
}

int MainWindow::run(void)
{
	show();
	return(Fl::run());
}

int MainWindow::getMenuBarEnd(void)
{
	return m_menu->y() + m_menu->h();
}

void MainWindow::callBack(Fl_Widget *w)
{
#if 0
	printf("%s : entry\n", __PRETTY_FUNCTION__);
	m_controller->startJtagRefreshThread();
#endif
#if 0
	m_tabs->addTabs(new CpuTab(this,
								m_tabs->x()+TabsMenu::TABS_MENU_BOARDER,
								m_tabs->y()+TabsMenu::TABS_MENU_HEIGHT,
								m_tabs->w()-(TabsMenu::TABS_MENU_BOARDER*2),
								m_tabs->h()-(TabsMenu::TABS_MENU_HEIGHT*2),
								"New"));
#endif
}

void MainWindow::callBack2(Fl_Widget *w)
{
#if 0
	printf("%s : entry\n", __PRETTY_FUNCTION__);
	m_controller->stopJtagRefreshThread();
#endif
#if 0
	m_tabs->deleteTabs("New");
#endif
}

void MainWindow::loadBsdl(Fl_Widget *w)
{
	//CpuData *cpu = 0;
	printf("%s : entry\n", __PRETTY_FUNCTION__);
	m_fileChooser->title("Open");
	m_fileChooser->type(Fl_Native_File_Chooser::BROWSE_FILE);		// only picks files that exist
	switch ( m_fileChooser->show() ) {
		case -1: break;	// Error
		case  1: break;	// Cancel
		default:		// Choice
			m_fileChooser->preset_file(m_fileChooser->filename());
			printf("%s\n", m_fileChooser->filename());
			/* cpu = */ m_controller->createCpuFromBsdl(
						std::string(m_fileChooser->filename()));
		break;
	}
}

int MainWindow::connect(Fl_Widget *w)
{
	ProbeTab *probeTab = (ProbeTab *) w;
	int err = 0;
	const SystemData *data =  m_controller->getSystemData();
	//TODO Get Probe index
	printf("Probe index %d\r\n", probeTab->getProbeIndex());
	const ProbeData *probe = data->getProbe(probeTab->getProbeIndex());
	if(probe) {
		err = m_controller->scanProcessor(probe->getIdentifier());
		if(err)
			fl_alert("Failed to scan JTAG chain\n");
	} else {
		fl_alert("Probe not found\n");
		err = -1;
	}
	if(!err) {
		for(size_t i=0; i<data->getNbCpu(); i++) {
			const CpuData *cpu = data->getCpu(i);
			printf("CPU[%ld] :\n", i);
			printf("\t-Id : 0x%08lX\n", cpu->getCpuId());
			printf("\t-JTAG index : %d\n", cpu->getCpuJtagIndex());

			if(0 == cpu->getNbBsdlFiles()) {
				printf("\t-No BSDL file found\n");
				//TODO: Open BSDL manually and check id OK
			} else if (1 == cpu->getNbBsdlFiles()) {
				err = m_controller->loadCpuBsdl(i, 0);
				if(err)
					fl_alert("Failed to load %s for CPU %s\n",
							cpu->getBsdlFile(0).c_str(),
							cpu->getCpuName().c_str());
			} else {
				// TODO: Add windows to select good BSDL
				printf("\t-BSDL file(s):\n");
				for(size_t j=0; j<cpu->getNbBsdlFiles(); j++) {
					printf("\t\t-%s\n", cpu->getBsdlFile(j).c_str());
				}
			}
		}
#if 0
		if(data->getNbCpu() > 0) {
			printf("Add CPU[0] pins\n");
			err = m_controller->loadCpuBsdl(0, 0);
		}
#endif
	}

	if(!err)
	{
		printf("Create new tab\n");
		m_tabs->addTabs(new CpuTab(this,
								   0,
								   m_tabs->x()+TabsMenu::TABS_MENU_BOARDER,
								   m_tabs->y()+TabsMenu::TABS_MENU_HEIGHT,
								   m_tabs->w()-(TabsMenu::TABS_MENU_BOARDER*2),
								   m_tabs->h()-(TabsMenu::TABS_MENU_HEIGHT*2)));
		m_controller->startJtagRefreshThread();
	}

	return err;
}

void MainWindow::disconnect(Fl_Widget *w)
{
	if(m_controller->isJtagRefreshThreadStart())
	{
		m_controller->stopJtagRefreshThread();
	}
	m_tabs->cleanCpuTabs();

}

void MainWindow::about(Fl_Widget *w)
{
	std::string name = std::string("About ") +std::string(this->label());
	AboutWindow * aboutWindow = new AboutWindow(name.c_str());

	printf("%s entry\n", __PRETTY_FUNCTION__);

	deactivate();
	m_menu->deactivate();

	while(aboutWindow->shown()) Fl::wait();

	m_menu->activate();
	activate();

	delete aboutWindow;
#if 0

	if(!m_aboutWindow)
		printf("Error\n");
	m_aboutWindow->show();
#endif
}

const SystemData* MainWindow::getModel(void)
{
	return m_controller->getSystemData();
}

CpuTab* MainWindow::getCurrentCpuTab(void)
{
	TabsModel* tab = 0;

	printf("%s : Entry point\n", __PRETTY_FUNCTION__);

	if(!m_tabs)
		return NULL;

	tab = (TabsModel*)m_tabs->value();

	if(tab && tab->isCpuTab()) {
		return (CpuTab*) tab;
	}

	return NULL;
}

void MainWindow::refresh(void)
{
	TabsModel* tab = (TabsModel*)m_tabs->value();

	if(tab && tab->isCpuTab())
		tab->refresh();
}

static const char* untitled_default(void)
{
	const char *home =
			getenv("HOME") ? getenv("HOME") :			// Linux home
			getenv("HOME_PATH") ? getenv("HOME_PATH") :	// Windows home
			".";										// other  current path
	return home;
}

