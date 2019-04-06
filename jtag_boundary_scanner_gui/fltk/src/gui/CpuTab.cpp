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
* @file   CpuTab.cpp
* @brief  Implement TODO.
* @author Sébastien CORBEAU <seb.corbeau@gmail.com>
*/
//TODO: Delete if not use
#include <stdio.h>

#include <gui/CpuTab.h>
#include <gui/MainWindow.h>

#include <model/CpuData.h>
#include <model/PinData.h>

#include <FL/Fl_Widget.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Check_Button.H>

//TODO: Delete
#include <string>

static const int PIN_NAME_WIDTH = 150;
static const int CHK_BOX_WIDTH = 25;
static const int ITEM_HEIGHT = 15;

CpuTab::CpuTab(MainWindow *p_win,
			   size_t p_cpuIndex,
			   int p_x,
			   int p_y,
			   int p_w,
			   int p_h,
			   const char *p_label)
	: TabsModel(p_x, p_y, p_w, p_h, p_label, true)
{
	const CpuData *cpu;
	m_cpuIndex = p_cpuIndex;
	m_systemData =	p_win->getModel();

	if(!p_label)
		label("Unknown cpu");

	Fl_Scroll *scroll = new Fl_Scroll(p_x+TabsModel::SCROLL_BORDER,
									  p_y+TabsModel::SCROLL_BORDER,
									  p_w-(2*TabsModel::SCROLL_BORDER),
									  p_h-(2*TabsModel::SCROLL_BORDER));

	Fl_Box *pinNameTitle  = new Fl_Box(FL_FRAME_BOX,
									   scroll->x(),
									   scroll->y(),
									   PIN_NAME_WIDTH,
									   ITEM_HEIGHT,
									   "Pin");
	pinNameTitle->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
	Fl_Box *outputTitle  = new Fl_Box(FL_FRAME_BOX,
									  pinNameTitle->x()+pinNameTitle->w(),
									  scroll->y(),
									  CHK_BOX_WIDTH,
									  ITEM_HEIGHT,
									  "O");
	outputTitle->align(FL_ALIGN_INSIDE);
	Fl_Box *outputEnTitle  = new Fl_Box(FL_FRAME_BOX,
										outputTitle->x()+outputTitle->w(),
										scroll->y(),
										CHK_BOX_WIDTH,
										ITEM_HEIGHT,
										"OE");
	outputEnTitle->align(FL_ALIGN_INSIDE);
	Fl_Box *inputTitle  = new Fl_Box(FL_FRAME_BOX,
									 outputEnTitle->x()+outputEnTitle->w(),
									 scroll->y(),
									 CHK_BOX_WIDTH,
									 ITEM_HEIGHT,
									 "I");
	inputTitle->align(FL_ALIGN_INSIDE);
	Fl_Box *toggleTitle  = new Fl_Box(FL_FRAME_BOX,
									  inputTitle->x()+inputTitle->w(),
									  scroll->y(),
									  CHK_BOX_WIDTH,
									  ITEM_HEIGHT,
									  "T");
	toggleTitle->align(FL_ALIGN_INSIDE);
	scroll->end();

	//printf("Title create %p\n", m_systemData);

	if(m_cpuIndex < m_systemData->getNbCpu()) {
		//printf("Nb CPU %ld\n", m_systemData->getNbCpu());
		cpu = m_systemData->getCpu(m_cpuIndex);
		if(!p_label)
			copy_label(cpu->getCpuName().c_str());
		//printf("CPU nb pins %ld\n", cpu->getNbUsablePins());
		for(size_t i=0; i<cpu->getNbUsablePins(); i++) {
			const PinData *pin = cpu->getUsablePin(i);
			Fl_Check_Button *outputChkBox = 0;
			Fl_Check_Button *outputEnChkBox = 0;
			Fl_Check_Button *inputChkBox = 0;
			Fl_Check_Button *toggleChkBox = 0;

			Fl_Box *pinNameLbl = new Fl_Box(pinNameTitle->x(),
											pinNameTitle->y()+pinNameTitle->h()+(i*20),
											PIN_NAME_WIDTH,
											ITEM_HEIGHT);
			pinNameLbl->copy_label(pin->getName().c_str());
			pinNameLbl->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
			scroll->add(pinNameLbl);
			//pinNameLbl->redraw();
			if(pin->isOutput()) {
				outputChkBox = new Fl_Check_Button(
							pinNameLbl->x()+pinNameLbl->w(),
							pinNameLbl->y(),
							CHK_BOX_WIDTH,
							ITEM_HEIGHT);
				scroll->add(outputChkBox);
			}

			if(pin->isTristate()) {
				outputEnChkBox = new Fl_Check_Button(
							pinNameLbl->x()+pinNameLbl->w()+CHK_BOX_WIDTH,
							pinNameLbl->y(),
							CHK_BOX_WIDTH,
							ITEM_HEIGHT);
				scroll->add(outputEnChkBox);
			}

			if(pin->isInput()) {
				inputChkBox = new Fl_Check_Button(
							pinNameLbl->x()+pinNameLbl->w()+(2*CHK_BOX_WIDTH),
							pinNameLbl->y(),
							CHK_BOX_WIDTH,
							ITEM_HEIGHT);
				inputChkBox->deactivate();
				scroll->add(inputChkBox);
			}

			if(pin->isOutput() || pin->isTristate())
			{
				toggleChkBox = new Fl_Check_Button(
							pinNameLbl->x()+pinNameLbl->w()+(3*CHK_BOX_WIDTH),
							pinNameLbl->y(),
							CHK_BOX_WIDTH,
							ITEM_HEIGHT);
				toggleChkBox->align(FL_ALIGN_CENTER);
				scroll->add(toggleChkBox);
			}

			// Save check button
			m_cpuPin.push_back(new CpuPinCheckBox(outputChkBox,
						outputEnChkBox, inputChkBox, toggleChkBox));
		}
	}
}

CpuTab::~CpuTab()
{

}

void CpuTab::refresh(void)
{
	const CpuData *cpu = m_systemData->getCpu(m_cpuIndex);

	if(!cpu)
		return;

	for(size_t i=0; i<cpu->getNbUsablePins();i++) {
		const PinData *pin = cpu->getUsablePin(i);
		if(pin->isInput()) {
			m_cpuPin[i]->setInputState(pin->getInputState());
		}
		if(pin->isOutput()) {
			m_cpuPin[i]->setOutputState(pin->getOutputState());
		}
		if(pin->isTristate()) {
			m_cpuPin[i]->setOutputEnableState(pin->getOutputEnableState());
		}
	}
}

int CpuTab::getCpuIndex(void)
{
	return m_cpuIndex;
}
