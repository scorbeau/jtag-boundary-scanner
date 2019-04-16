/*
 * Jtag Boundary Scanner
 * Copyright (c) 2019 Viveris Technologies
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
* @author Sébastien CORBEAU <sebastien.corbeau@viveris.fr>
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

static const int PIN_NAME_WIDTH = 130;
static const int CHK_BOX_WIDTH = 25;
static const int ITEM_HEIGHT = 15;
static const int MAX_NB_COLUMN = 8;
static const int MIN_GPIO_BY_COLUMN = 10;
static const int BOX_MARGIN = 1;
static const int CHKBOX_MARGIN = 20;

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
	size_t nb_gpio = 0;
	size_t nb_usable_gpio = 0;
	size_t nb_column = 0;
	int nb_gpio_per_column = 0;
	size_t i=0;
	Fl_Box *pinNameTitle = 0;
	Fl_Box *outputTitle = 0;
	Fl_Box *outputEnTitle = 0;
	Fl_Box *inputTitle = 0;
	Fl_Box *toggleTitle = 0;

	m_cpuIndex = p_cpuIndex;
	m_systemData =	p_win->getModel();

	Fl_Scroll *scroll = new Fl_Scroll(p_x+TabsModel::SCROLL_BORDER,
									  p_y+TabsModel::SCROLL_BORDER,
									  p_w-(2*TabsModel::SCROLL_BORDER),
									  p_h-(2*TabsModel::SCROLL_BORDER));
	scroll->end();

	if(m_cpuIndex < m_systemData->getNbCpu()) {
		//printf("Nb CPU %ld\n", m_systemData->getNbCpu());
		cpu = m_systemData->getCpu(m_cpuIndex);
		nb_usable_gpio = cpu->getNbUsablePins();

		nb_column = nb_usable_gpio / MIN_GPIO_BY_COLUMN;
		if(nb_column > MAX_NB_COLUMN){
			nb_column = 7;
		}

		if(nb_column > 0) {
			nb_gpio_per_column = nb_usable_gpio / nb_column;
			nb_gpio = nb_gpio_per_column * nb_column;
		} else {
			nb_gpio_per_column = nb_usable_gpio;
			nb_gpio = nb_usable_gpio;
		}

		if(!p_label)
			copy_label(cpu->getCpuName().c_str());

		for(i=0; i<nb_gpio; i++) {
			const PinData *pin = cpu->getUsablePin(i);
			Fl_Check_Button *outputChkBox = 0;
			Fl_Check_Button *outputEnChkBox = 0;
			Fl_Check_Button *inputChkBox = 0;
			Fl_Check_Button *toggleChkBox = 0;

			if(0 == (i%nb_gpio_per_column)) {
				Fl_Box *column = new Fl_Box(FL_ENGRAVED_BOX,
											scroll->x()+BOX_MARGIN+((i/nb_gpio_per_column)*(PIN_NAME_WIDTH+4*CHK_BOX_WIDTH)),
											scroll->y()+BOX_MARGIN,
											PIN_NAME_WIDTH+4*CHK_BOX_WIDTH,
											(nb_gpio_per_column+1)*(CHKBOX_MARGIN),
											"");
				scroll->add(column);

				pinNameTitle = new Fl_Box(FL_FRAME_BOX,
										  column->x(),
										  column->y(),
										  PIN_NAME_WIDTH,
										  ITEM_HEIGHT,
										  "Pin");
				pinNameTitle->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
				scroll->add(pinNameTitle);
				outputTitle = new Fl_Box(FL_FRAME_BOX,
										 pinNameTitle->x()+pinNameTitle->w(),
										 column->y(),
										 CHK_BOX_WIDTH,
										 ITEM_HEIGHT,
										 "O");
				outputTitle->align(FL_ALIGN_INSIDE);
				scroll->add(outputTitle);
				outputEnTitle = new Fl_Box(FL_FRAME_BOX,
										   outputTitle->x()+outputTitle->w(),
										   column->y(),
										   CHK_BOX_WIDTH,
										   ITEM_HEIGHT,
										   "OE");
				outputEnTitle->align(FL_ALIGN_INSIDE);
				scroll->add(outputEnTitle);
				inputTitle = new Fl_Box(FL_FRAME_BOX,
										outputEnTitle->x()+outputEnTitle->w(),
										column->y(),
										CHK_BOX_WIDTH,
										ITEM_HEIGHT,
										"I");
				inputTitle->align(FL_ALIGN_INSIDE);
				scroll->add(inputTitle);
				toggleTitle = new Fl_Box(FL_FRAME_BOX,
										 inputTitle->x()+inputTitle->w(),
										 column->y(),
										 CHK_BOX_WIDTH,
										 ITEM_HEIGHT,
										 "T");
				toggleTitle->align(FL_ALIGN_INSIDE);
				scroll->add(toggleTitle);
			}
			Fl_Box *pinNameLbl = new Fl_Box(pinNameTitle->x(),
											pinNameTitle->y()+pinNameTitle->h()+((i%nb_gpio_per_column)*CHKBOX_MARGIN),
											PIN_NAME_WIDTH,
											ITEM_HEIGHT);
			pinNameLbl->copy_label(pin->getName().c_str());
			pinNameLbl->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
			scroll->add(pinNameLbl);

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
			m_cpuPinCheckBoxes.push_back(new CpuPinCheckBox(outputChkBox,
						outputEnChkBox, inputChkBox, toggleChkBox));
		}
	}

	// Display last gpio if necessary
	if(nb_usable_gpio-nb_gpio) {
		Fl_Box *column = new Fl_Box(FL_ENGRAVED_BOX,
									scroll->x()+BOX_MARGIN+((nb_gpio/nb_gpio_per_column)*(PIN_NAME_WIDTH+4*CHK_BOX_WIDTH)),
									scroll->y()+BOX_MARGIN,
									PIN_NAME_WIDTH+4*CHK_BOX_WIDTH,
									(nb_gpio_per_column+1)*(CHKBOX_MARGIN),
									"");
		scroll->add(column);
		pinNameTitle = new Fl_Box(FL_FRAME_BOX,
								  column->x(),
								  column->y(),
								  PIN_NAME_WIDTH,
								  ITEM_HEIGHT,
								  "Pin");
		pinNameTitle->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
		scroll->add(pinNameTitle);
		outputTitle = new Fl_Box(FL_FRAME_BOX,
								 pinNameTitle->x()+pinNameTitle->w(),
								 column->y(),
								 CHK_BOX_WIDTH,
								 ITEM_HEIGHT,
								 "O");
		outputTitle->align(FL_ALIGN_INSIDE);
		scroll->add(outputTitle);
		outputEnTitle = new Fl_Box(FL_FRAME_BOX,
								   outputTitle->x()+outputTitle->w(),
								   column->y(),
								   CHK_BOX_WIDTH,
								   ITEM_HEIGHT,
								   "OE");
		outputEnTitle->align(FL_ALIGN_INSIDE);
		scroll->add(outputEnTitle);
		inputTitle = new Fl_Box(FL_FRAME_BOX,
								outputEnTitle->x()+outputEnTitle->w(),
								column->y(),
								CHK_BOX_WIDTH,
								ITEM_HEIGHT,
								"I");
		inputTitle->align(FL_ALIGN_INSIDE);
		scroll->add(inputTitle);
		toggleTitle = new Fl_Box(FL_FRAME_BOX,
								 inputTitle->x()+inputTitle->w(),
								 column->y(),
								 CHK_BOX_WIDTH,
								 ITEM_HEIGHT,
								 "T");
		toggleTitle->align(FL_ALIGN_INSIDE);
		scroll->add(toggleTitle);
		for(; i<nb_usable_gpio; i++) {
			const PinData *pin = cpu->getUsablePin(i);
			Fl_Check_Button *outputChkBox = 0;
			Fl_Check_Button *outputEnChkBox = 0;
			Fl_Check_Button *inputChkBox = 0;
			Fl_Check_Button *toggleChkBox = 0;

			Fl_Box *pinNameLbl = new Fl_Box(pinNameTitle->x(),
											pinNameTitle->y()+pinNameTitle->h()+((i%nb_gpio_per_column)*CHKBOX_MARGIN),
											PIN_NAME_WIDTH,
											ITEM_HEIGHT);
			pinNameLbl->copy_label(pin->getName().c_str());
			pinNameLbl->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
			scroll->add(pinNameLbl);

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
			m_cpuPinCheckBoxes.push_back(new CpuPinCheckBox(outputChkBox,
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
			m_cpuPinCheckBoxes[i]->setInputState(pin->getInputState());
		}
		if(pin->isOutput()) {
			m_cpuPinCheckBoxes[i]->setOutputState(pin->getOutputState());
		}
		if(pin->isTristate()) {
			m_cpuPinCheckBoxes[i]->setOutputEnableState(pin->getOutputEnableState());
		}
	}
}

int CpuTab::getCpuIndex(void)
{
	return m_cpuIndex;
}

const CpuPinCheckBox* CpuTab::getPinCheckBoxes(size_t p_index) const
{
	if(p_index < m_cpuPinCheckBoxes.size())
		return m_cpuPinCheckBoxes[p_index];

	return NULL;
}
