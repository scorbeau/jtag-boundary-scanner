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
* @file   I2CTab.c
* @brief  Implement TODO.
* @author Sébastien CORBEAU <sebastien.corbeau@viveris.fr>
*/

//TODO: Remove string
#include <string>

#include <FL/Fl_Box.H>

#include "gui/I2CTab.h"

static const int ITEM_HEIGHT = 20;
static const int BOARD_MARGIN = 1;
static const int CHOICE_WIDTH = 250;
static const int X_MARGIN = 15;
static const int Y_MARGIN = 15;
static const int LABEL_WIDTH = 75;

static void testCallback(Fl_Widget *w, void * ptr);

I2CTab::I2CTab(MainWindow *p_win,
		 int p_x,
		 int p_y,
		 int p_w,
		 int p_h,
		 const char *p_label)
	: TabsModel(p_x, p_y, p_w, p_h, p_label, false)
{
	m_systemData = p_win->getModel();
	Fl_Scroll *scroll = new Fl_Scroll(p_x+TabsModel::SCROLL_BORDER,
									  p_y+TabsModel::SCROLL_BORDER,
									  p_w-(2*TabsModel::SCROLL_BORDER),
									  p_h-(2*TabsModel::SCROLL_BORDER));
	scroll->end();

	Fl_Box *lbl = new Fl_Box(scroll->x()+BOARD_MARGIN,
							 scroll->y()+BOARD_MARGIN,
							 LABEL_WIDTH,
							 ITEM_HEIGHT,
							 "CPU(s) :");
	lbl->align(FL_ALIGN_CLIP|FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
	scroll->add(lbl);

	m_cpuChoice = new Fl_Choice(lbl->x() + lbl->w() + X_MARGIN,
								lbl->y(),
								CHOICE_WIDTH,
								ITEM_HEIGHT);
#if 1
	for(int i=0;i<3; i++) {
		std::string test = "CPU";
		test += i;
		m_cpuChoice->add(test.c_str());
	}
#endif
	scroll->add(m_cpuChoice);
	m_cpuChoice->callback(testCallback, this);

	lbl = new Fl_Box(scroll->x()+BOARD_MARGIN,
					 m_cpuChoice->y() + m_cpuChoice->h() + Y_MARGIN,
					 LABEL_WIDTH,
					 ITEM_HEIGHT,
					 "SDA Pin:");
	lbl->align(FL_ALIGN_CLIP|FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
	scroll->add(lbl);

	m_sdaChoice = new Fl_Choice(lbl->x() + lbl->w() + X_MARGIN,
								lbl->y(),
								CHOICE_WIDTH,
								ITEM_HEIGHT);
	for(int i=0;i<3; i++) {
		std::string test = "SDA";
		test += i;
		m_sdaChoice->add(test.c_str());
	}
	scroll->add(m_sdaChoice);

	lbl = new Fl_Box(m_sdaChoice->x() + m_sdaChoice->w() + X_MARGIN,
					 m_sdaChoice->y(),
					 LABEL_WIDTH,
					 ITEM_HEIGHT,
					 "SCL Pin:");
	lbl->align(FL_ALIGN_CLIP|FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
	scroll->add(lbl);

	m_sclChoice = new Fl_Choice(lbl->x() + lbl->w() + X_MARGIN,
								lbl->y(),
								CHOICE_WIDTH,
								ITEM_HEIGHT);
	for(int i=0;i<3; i++) {
		std::string test = "SCL";
		test += i;
		m_sclChoice->add(test.c_str());
	}
	scroll->add(m_sclChoice);
}

I2CTab::~I2CTab()
{

}

void I2CTab::refresh(void)
{
	/* I2C Rfresh when new connection */
}

void I2CTab::refreshCpuPin(void)
{
	printf("%s\n", __PRETTY_FUNCTION__);
}

static void testCallback(Fl_Widget *w, void * ptr)
{
	((I2CTab*)ptr)->refreshCpuPin();
}
