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
* @file   BoundaryFileWindow.cpp
* @brief  Implement Boundary file selector window.
* @author Sébastien CORBEAU <sebastien.corbeau@viveris.fr>
*/
#include <FL/Fl_Box.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Pixmap.H>

#include <string>
#include <sstream>

#include <string.h>

#include "gui/BoundaryFileWindow.h"
#include "gui/BsdlFileChooser.h"
#include "gui/img/JTAGBoundaryScanner_small.xpm"

static const int BOUNDARY_FILE_WINDOW_WIDTH = 550;
static const int BOUNDARY_FILE_WINDOW_HEIGHT = 200;
static const int BORDER = 10;
static const int BUTTON_SELECT_WIDTH = 20;
static const int BUTTON_WIDTH = 90;
static const int ITEM_HEIGHT = 20;
static const int LABEL_WIDTH = 150;
static const char *BUTTON_CANCEL_LABEL = "&Cancel";
static const char *BUTTON_OK_LABEL = "&OK";
static const char *ROUND_BUTTON_EXIST_BSDL_LABEL = "Select install BSDL file.";
static const char *ROUND_BUTTON_SELECT_BSDL_LABEL = "Select BSDL file on disk.";

static void callbackButton(Fl_Widget *w, void *param)
{
	BoundaryFileWindow *win = (BoundaryFileWindow*) w->parent();
	Fl_Button *btn = (Fl_Button*) w;

	printf("%s\n", __PRETTY_FUNCTION__);

	if(win) {
		if(!strcmp(btn->label(), BUTTON_OK_LABEL)) {
			win->setCancelRequest(false);
		}
		win->hide();
	}
}

static void callbackChoice(Fl_Round_Button *btn, void *param)
{
	BoundaryFileWindow *win = (BoundaryFileWindow*) param;

	//printf("Button label : %s\n", btn->label());

	if(!strcmp(btn->label(), ROUND_BUTTON_EXIST_BSDL_LABEL)) {
		win->selectInstallBsdlChoice(true);
	} else {
		win->selectInstallBsdlChoice(false);
	}
}

static void callbackSelectBsdl(Fl_Widget *w, void *param)
{
	BoundaryFileWindow *win = (BoundaryFileWindow*) param;
	BsdlFileChooser fileChooser;
	printf("Here select bsdl\n");
	win->setSelectedBsdlPath(fileChooser.getSelectBsdlFile().c_str());
}

BoundaryFileWindow::BoundaryFileWindow(const char *p_applName,
									   const CpuData* p_cpu) :
		Fl_Window(BOUNDARY_FILE_WINDOW_WIDTH,
				BOUNDARY_FILE_WINDOW_HEIGHT,
				p_applName)
{
	std::stringstream hexStringStream;
	hexStringStream << std::hex << p_cpu->getCpuId();

	std::string cpuMsg = "Please select BSDL for CPU ";
	cpuMsg += std::to_string(p_cpu->getCpuJtagIndex());
	cpuMsg += " in JTAG chain with id 0x";
	cpuMsg += hexStringStream.str();
	Fl_Box *msg = new Fl_Box(BORDER,
					BORDER,
					BOUNDARY_FILE_WINDOW_WIDTH - (2*BORDER),
					ITEM_HEIGHT);
	msg->copy_label(cpuMsg.c_str());

	Fl_Group *group = new Fl_Group(BORDER,
					msg->y()+msg->h()+BORDER,
					BOUNDARY_FILE_WINDOW_WIDTH - (2*BORDER),
					BOUNDARY_FILE_WINDOW_HEIGHT - (2*ITEM_HEIGHT + 4*BORDER));

	Fl_Round_Button *existBsdlBtn = new Fl_Round_Button(group->x()+1,
					group->y()+1,
					group->w()-2,
					ITEM_HEIGHT,
					ROUND_BUTTON_EXIST_BSDL_LABEL);
	existBsdlBtn->type(102);
	existBsdlBtn->callback((Fl_Callback*)callbackChoice, this);

	Fl_Box *lbl1 = new Fl_Box(group->x()+1,
					existBsdlBtn->y()+existBsdlBtn->h()+BORDER,
					LABEL_WIDTH,
					ITEM_HEIGHT,
					"Found BSDL file(s) :");
	lbl1->align(FL_ALIGN_CLIP|FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
	m_bsdlChoice = new Fl_Choice(lbl1->x()+lbl1->w()+BORDER,
					lbl1->y(),
					group->w() - (2+lbl1->w()+BORDER),
					ITEM_HEIGHT);
	if(p_cpu->getNbBsdlFiles()) {
		for(size_t i=0; i<p_cpu->getNbBsdlFiles(); i++) {
			m_bsdlChoice->add(p_cpu->getBsdlFile(i).c_str());
		}
		m_bsdlChoice->value(0);
	}

	Fl_Round_Button *selectBsdlBtn = new Fl_Round_Button(group->x()+1,
					m_bsdlChoice->y()+m_bsdlChoice->h()+BORDER,
					group->w()-2,
					ITEM_HEIGHT,
					ROUND_BUTTON_SELECT_BSDL_LABEL);
	selectBsdlBtn->type(102);
	selectBsdlBtn->callback((Fl_Callback*)callbackChoice, this);

	Fl_Box *lbl2 = new Fl_Box(group->x()+1,
					selectBsdlBtn->y()+selectBsdlBtn->h()+BORDER,
					LABEL_WIDTH,
					ITEM_HEIGHT,
					"BSDL file path :");
	lbl2->align(FL_ALIGN_CLIP|FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
	m_bsdlInput = new Fl_Input(lbl2->x()+lbl2->w()+BORDER,
						lbl2->y(),
						group->w() - (2+lbl2->w()+BUTTON_SELECT_WIDTH+2*BORDER),
						ITEM_HEIGHT);
	m_selectFileBtn = new Fl_Button(m_bsdlInput->x()+m_bsdlInput->w()+BORDER,
						m_bsdlInput->y(),
						BUTTON_SELECT_WIDTH,
						ITEM_HEIGHT,
						"...");
	m_selectFileBtn->callback((Fl_Callback*)callbackSelectBsdl, this);
	group->end();

	Fl_Button *cancelBtn = new Fl_Button(w() - (2*BUTTON_WIDTH + 2*BORDER),
					group->y()+group->h()+BORDER,
					BUTTON_WIDTH,
					ITEM_HEIGHT,
					BUTTON_CANCEL_LABEL);
	cancelBtn->callback(callbackButton, 0);
	Fl_Button *okBtn = new Fl_Button(w() - (BUTTON_WIDTH + BORDER),
					group->y()+group->h()+BORDER,
					BUTTON_WIDTH,
					ITEM_HEIGHT,
					BUTTON_OK_LABEL);
	okBtn->callback(callbackButton, 0);
	end();

	if(p_cpu->getNbBsdlFiles()) {
		selectInstallBsdlChoice(true);
		existBsdlBtn->set();
	} else {
		selectInstallBsdlChoice(false);
		selectBsdlBtn->set();
	}

	m_cancelRequest = true;

	show();

#ifdef __linux
	Fl_Pixmap *pixmap = new Fl_Pixmap(JTAGBoundaryScanner_small_xpm);
	icon(new Fl_RGB_Image(pixmap, FL_GRAY));
#else
#warning "TODO: Implement for windows"
#endif
}

BoundaryFileWindow::~BoundaryFileWindow()
{

}

bool BoundaryFileWindow::isCancelRequest(void)
{
	return m_cancelRequest;
}

void BoundaryFileWindow::setCancelRequest(bool cancel)
{
	m_cancelRequest = cancel;
}

void BoundaryFileWindow::selectInstallBsdlChoice(bool selectInstallBsdl)
{
	if(selectInstallBsdl) {
		m_bsdlChoice->activate();
		m_bsdlInput->deactivate();
		m_selectFileBtn->deactivate();
	} else {
		m_bsdlChoice->deactivate();
		m_bsdlInput->activate();
		m_selectFileBtn->activate();
	}
}

void BoundaryFileWindow::setSelectedBsdlPath(const char* path)
{
	m_bsdlInput->value(path);
}

bool BoundaryFileWindow::isInstalledBsdl(void)
{
	return m_bsdlChoice->active() ? true : false;
}

int BoundaryFileWindow::getInstalledBsdlIndex(void)
{
	return m_bsdlChoice->active() ? m_bsdlChoice->value() : -1;
}

std::string BoundaryFileWindow::getBsdlPath(void)
{
	std::string ret = "";

	if(m_bsdlInput->active()) {
		ret = std::string(m_bsdlInput->value());
	} else {
		printf("No choice selected\n");
	}

	return ret;
}
