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
#include <FL/Fl_Button.H>

#include "gui/I2CTab.h"

static const int ITEM_HEIGHT = 20;
static const int MULTI_LINE_ITEM_HEIGHT = 100;
static const int BOARD_MARGIN = 1;
static const int CHOICE_WIDTH = 125;
static const int CHK_BOX_WIDTH = 25;
static const int X_MARGIN = 15;
static const int Y_MARGIN = 15;
static const int LABEL_WIDTH = 120;
static const int LONG_LABEL_WIDTH = 150;
static const int BTN_WIDTH = 90;

static const char *AUTOSCAN_BTN_LABEL = "Autoscan";
static const char *WRITE_BTN_LABEL = "Write";
static const char *READ_BTN_LABEL = "Read";

static void refreshPinCallback(Fl_Widget *w, void * ptr);
static void autoscanCallback(Fl_Widget *w, void * ptr);
static void writeCallback(Fl_Widget *w, void * ptr);
static void readCallback(Fl_Widget *w, void * ptr);

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
	scroll->add(m_cpuChoice);
	m_cpuChoice->callback(refreshPinCallback, this);

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
	scroll->add(m_sclChoice);

	// Resize CPU choice to make IHM more readable
	m_cpuChoice->resize(m_cpuChoice->x(),
						m_cpuChoice->y(),
						m_sclChoice->x()+m_sclChoice->w() - m_cpuChoice->x(),
						m_cpuChoice->h());

	lbl = new Fl_Box(scroll->x()+BOARD_MARGIN,
					 m_sdaChoice->y() + m_sdaChoice->h() + Y_MARGIN,
					 LABEL_WIDTH,
					 ITEM_HEIGHT,
					 "Address :");
	lbl->align(FL_ALIGN_CLIP|FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
	scroll->add(lbl);

	m_address = new Fl_Input(lbl->x() + lbl->w() + X_MARGIN,
							 lbl->y(),
							 CHOICE_WIDTH,
							 ITEM_HEIGHT);
	m_address->tooltip("I2C slave address in HEX");
	scroll->add(m_address);

	m_10bitAddr = new Fl_Check_Button(
			m_address->x() + m_address->w() + X_MARGIN,
			m_address->y(),
			CHK_BOX_WIDTH,
			ITEM_HEIGHT);
	scroll->add(m_10bitAddr);

	lbl = new Fl_Box(m_10bitAddr->x() + m_10bitAddr->w() + X_MARGIN,
					 m_10bitAddr->y(),
					 LABEL_WIDTH,
					 ITEM_HEIGHT,
					 "10-bit address");
	lbl->align(FL_ALIGN_CLIP|FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
	scroll->add(lbl);
	lbl->resize(lbl->x(),
				lbl->y(),
				m_sclChoice->x()+m_sclChoice->w() - lbl->x(),
				lbl->h());

	Fl_Button *btn = new Fl_Button(lbl->x()+lbl->w()-BTN_WIDTH,
								   m_10bitAddr->y()+m_10bitAddr->h()+Y_MARGIN,
								   BTN_WIDTH,
								   ITEM_HEIGHT,
								   AUTOSCAN_BTN_LABEL);
	btn->callback(autoscanCallback, this);
	scroll->add(btn);

	lbl = new Fl_Box(scroll->x()+BOARD_MARGIN,
					 btn->y() + btn->h() + Y_MARGIN,
					 LABEL_WIDTH,
					 ITEM_HEIGHT,
					 "Data(s) to write :");
	lbl->align(FL_ALIGN_CLIP|FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
	scroll->add(lbl);

	m_dataToWrite = new Fl_Multiline_Input(lbl->x() + lbl->w() + X_MARGIN,
										   lbl->y(),
										   CHOICE_WIDTH,
										   MULTI_LINE_ITEM_HEIGHT);
	m_dataToWrite->tooltip("Data(s) to send in HEX");
	m_dataToWrite->resize(m_dataToWrite->x(),
						  m_dataToWrite->y(),
						  m_sclChoice->x()+m_sclChoice->w()-m_dataToWrite->x(),
						  m_dataToWrite->h());

	scroll->add(m_dataToWrite);

	btn = new Fl_Button(m_dataToWrite->x() + m_dataToWrite->w() - BTN_WIDTH,
						m_dataToWrite->y() + m_dataToWrite->h() + Y_MARGIN,
						BTN_WIDTH,
						ITEM_HEIGHT,
						WRITE_BTN_LABEL);
	btn->callback(writeCallback, this);
	scroll->add(btn);

	lbl = new Fl_Box(scroll->x()+BOARD_MARGIN,
					 btn->y() + btn->h() + Y_MARGIN,
					 LABEL_WIDTH,
					 ITEM_HEIGHT,
					 "Data(s) read :");
	lbl->align(FL_ALIGN_CLIP|FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
	scroll->add(lbl);

	m_dataRead = new Fl_Multiline_Output(lbl->x() + lbl->w() + X_MARGIN,
										 lbl->y(),
										 m_dataToWrite->w(),
										 MULTI_LINE_ITEM_HEIGHT);
	m_dataRead->tooltip("Data(s) read in HEX");
	scroll->add(m_dataRead);
	m_dataRead->value("aeaezrr\nzezeze\nzeezeze\n");

	btn = new Fl_Button(m_dataRead->x() + m_dataRead->w() - BTN_WIDTH,
						m_dataRead->y() + m_dataRead->h() + Y_MARGIN,
						BTN_WIDTH,
						ITEM_HEIGHT,
						READ_BTN_LABEL);
	btn->callback(readCallback, this);
	scroll->add(btn);

	m_nbDataToRead = new Fl_Int_Input(btn->x() - (CHOICE_WIDTH + X_MARGIN),
									  btn->y(),
									  CHOICE_WIDTH,
									  ITEM_HEIGHT);
	m_nbDataToRead->tooltip("Number of data to read");
	scroll->add(m_nbDataToRead);

	lbl = new Fl_Box(scroll->x()+BOARD_MARGIN,
					 btn->y(),
					 LONG_LABEL_WIDTH,
					 ITEM_HEIGHT,
					 "Nb data(s) to read :");
	lbl->align(FL_ALIGN_CLIP|FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
	scroll->add(lbl);
}

I2CTab::~I2CTab()
{

}

void I2CTab::refresh(void)
{

}

void I2CTab::refreshCpuList(void)
{
	m_cpuChoice->clear();

	for(size_t i=0; i<m_systemData->getNbCpu(); i++) {
		const CpuData *cpu = m_systemData->getCpu(i);
		m_cpuChoice->add(cpu->getCpuName().c_str());
	}

	if(m_cpuChoice->size() > 0) {
		m_cpuChoice->value(0);
	}

	refreshCpuPinList();
}

void I2CTab::refreshCpuPinList(void)
{
	printf("%s\n", __PRETTY_FUNCTION__);
	m_sclChoice->clear();
	m_sdaChoice->clear();

	if(m_cpuChoice->size() > 0) {
		const CpuData *cpu = m_systemData->getCpu(m_cpuChoice->value());

		for(size_t i=0; i<cpu->getNbUsablePins(); i++) {
			const PinData *pin = cpu->getUsablePin(i);
			m_sdaChoice->add(pin->getName().c_str());
			m_sclChoice->add(pin->getName().c_str());
		}

		if(cpu->getNbUsablePins() > 0) {
			m_sdaChoice->value(0);
			m_sclChoice->value(0);
		}
	}
}

static void refreshPinCallback(Fl_Widget *w, void * ptr)
{
	((I2CTab*)ptr)->refreshCpuPinList();
}

static void autoscanCallback(Fl_Widget *w, void * ptr)
{
	printf("%s\n", __PRETTY_FUNCTION__);
}

static void writeCallback(Fl_Widget *w, void * ptr)
{
	printf("%s\n", __PRETTY_FUNCTION__);
}

static void readCallback(Fl_Widget *w, void * ptr)
{
	printf("%s\n", __PRETTY_FUNCTION__);
}
