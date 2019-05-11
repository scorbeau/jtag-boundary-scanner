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
* @file   ProbeTab.cpp
* @brief  Implement Probe tab GUI class.
* @author Sébastien CORBEAU <sebastien.corbeau@viveris.fr>
*/
#include <FL/Fl.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Round_Button.H>

#include "gui/ProbeTab.h"
#include "configuration.h"
#include "jtag_core.h"

static const int ITEM_HEIGHT = 20;
static const int PROBE_CHOICE_WIDTH = 250;
static const int REFRESH_PROBE_WIDTH = 90;
static const int CONNECT_PROBE_WIDTH = 90;
static const int BOARD_MARGIN = 1;
static const int X_MARGIN = 15;
static const int Y_MARGIN = 15;
static const int LST_Y_MARGIN = 1;
static const int LABEL_WIDTH = 75;
static const int ROUND_BTN_WIDTH = 150;

static const char *CONNECT_LABEL = "Connect";
static const char *DISCONNECT_LABEL = "Disconnect";

static const char *NO_REFRESH_LABEL = "No refresh";
static const char *REFRESH_20MS_LABEL = "20 ms refresh";
static const char *REFRESH_200MS_LABEL = "200 ms refresh";
static const char *REFRESH_1S_LABEL = "1s refresh";

static const char *SAMPLE_MODE_LABEL = "Sample mode";
static const char *EXTTEST_MODE_LABEL = "EXT test mode";

static void refreshProbeCallback(Fl_Widget *w, void * ptr);
static void connectProbeCallback(Fl_Widget *w, void * ptr);
static void updateRefreshTime(Fl_Widget *w, void * ptr);
static void updateMode(Fl_Widget *w, void * ptr);

ProbeTab::ProbeTab(MainWindow *p_win,
				   int p_x,
				   int p_y,
				   int p_w,
				   int p_h,
				   const char *p_label) :
		TabsModel(p_x, p_y, p_w, p_h, p_label, false)
{
	m_systemData =	p_win->getModel();
	Fl_Scroll *scroll = new Fl_Scroll(p_x+TabsModel::SCROLL_BORDER,
									  p_y+TabsModel::SCROLL_BORDER,
									  p_w-(2*TabsModel::SCROLL_BORDER),
									  p_h-(2*TabsModel::SCROLL_BORDER));
	scroll->end();

	Fl_Box *lbl = new Fl_Box(scroll->x()+BOARD_MARGIN,
							scroll->y()+BOARD_MARGIN,
							LABEL_WIDTH,
							ITEM_HEIGHT,
							"Probe(s) :");
	lbl->align(FL_ALIGN_CLIP|FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
	scroll->add(lbl);
	m_probeChoice = new Fl_Choice(lbl->x() + lbl->w() + Y_MARGIN,
								  lbl->y(),
								  PROBE_CHOICE_WIDTH,
								  ITEM_HEIGHT);

	for(size_t i=0; i<m_systemData->getNbProbe(); i++) {
		m_probeChoice->add(m_systemData->getProbe(i)->getName().c_str());
	}
	if(m_systemData->getNbProbe() > 0)
		m_probeChoice->value(0);

	scroll->add(m_probeChoice);

	Fl_Button *refreshBtn = new Fl_Button(scroll->x()+BOARD_MARGIN,
				m_probeChoice->y()+m_probeChoice->h()+Y_MARGIN,
				REFRESH_PROBE_WIDTH,
				ITEM_HEIGHT,
				"Refresh");
	refreshBtn->callback(refreshProbeCallback, this);
	scroll->add(refreshBtn);

	m_connectBtn = new Fl_Button(
				refreshBtn->x() + refreshBtn->w() + X_MARGIN,
				m_probeChoice->y()+m_probeChoice->h()+Y_MARGIN,
				CONNECT_PROBE_WIDTH,
				ITEM_HEIGHT,
				CONNECT_LABEL);
	m_connectBtn->callback(connectProbeCallback, this);
	scroll->add(m_connectBtn);

	m_modeGroup = new Fl_Group(scroll->x()+BOARD_MARGIN,
						m_connectBtn->y()+m_connectBtn->h()+Y_MARGIN,
						scroll->w()-(2 * BOARD_MARGIN),
						3 * (ITEM_HEIGHT+LST_Y_MARGIN));
	{
		Fl_Box *lbl2 = new Fl_Box(m_modeGroup->x(),
								  m_modeGroup->y(),
								  m_modeGroup->w(),
								  ITEM_HEIGHT,
								  "Mode : ");
		lbl2->align(FL_ALIGN_CLIP|FL_ALIGN_LEFT|FL_ALIGN_INSIDE);

		Fl_Round_Button* o = new Fl_Round_Button(m_modeGroup->x(),
				lbl2->y() + lbl2->h() + LST_Y_MARGIN,
				ROUND_BTN_WIDTH,
				ITEM_HEIGHT,
				SAMPLE_MODE_LABEL);
		o->type(102);
		o->down_box(FL_ROUND_DOWN_BOX);
		o->callback((Fl_Callback*) updateMode);
		if(JTAG_CORE_SAMPLE_SCANMODE == m_systemData->getScanMode())
			o->set();

		Fl_Round_Button* o2 = new Fl_Round_Button(m_modeGroup->x(),
				o->y() + o->h() + LST_Y_MARGIN,
				ROUND_BTN_WIDTH,
				ITEM_HEIGHT,
				EXTTEST_MODE_LABEL);
		o2->type(102);
		o2->down_box(FL_ROUND_DOWN_BOX);
		o2->callback((Fl_Callback*) updateMode);
		if(JTAG_CORE_EXTEST_SCANMODE == m_systemData->getScanMode())
			o2->set();
	}
	m_modeGroup->end();
	scroll->add(m_modeGroup);

	m_refreshGroup = new Fl_Group(scroll->x()+BOARD_MARGIN,
				m_modeGroup->y()+ m_modeGroup->h() + Y_MARGIN,
				scroll->w()-(2 * BOARD_MARGIN),
				5 * (ITEM_HEIGHT+LST_Y_MARGIN));
	{
		Fl_Box *lbl2 = new Fl_Box(m_refreshGroup->x(),
								  m_refreshGroup->y(),
								  m_refreshGroup->w(),
								  ITEM_HEIGHT,
								  "Refresh time(s) : ");
		lbl2->align(FL_ALIGN_CLIP|FL_ALIGN_LEFT|FL_ALIGN_INSIDE);

		Fl_Round_Button* o = new Fl_Round_Button(m_refreshGroup->x(),
				lbl2->y() + lbl2->h() + LST_Y_MARGIN,
				ROUND_BTN_WIDTH,
				ITEM_HEIGHT,
				NO_REFRESH_LABEL);
		o->type(102);
		o->down_box(FL_ROUND_DOWN_BOX);
		o->callback((Fl_Callback*) updateRefreshTime);
		if(NO_REFRESH_VAL == m_systemData->getRefreshTime())
			o->set();

		Fl_Round_Button* o2 = new Fl_Round_Button(m_refreshGroup->x(),
				o->y() + o->h() + LST_Y_MARGIN,
				ROUND_BTN_WIDTH,
				ITEM_HEIGHT,
				REFRESH_20MS_LABEL);
		o2->type(102);
		o2->down_box(FL_ROUND_DOWN_BOX);
		o2->callback((Fl_Callback*) updateRefreshTime);
		if(REFRESH_20MS_VAL == m_systemData->getRefreshTime())
			o2->set();

		Fl_Round_Button* o3 = new Fl_Round_Button(m_refreshGroup->x(),
				o2->y() + o2->h() + LST_Y_MARGIN,
				ROUND_BTN_WIDTH,
				ITEM_HEIGHT,
				REFRESH_200MS_LABEL);
		o3->type(102);
		o3->down_box(FL_ROUND_DOWN_BOX);
		o3->callback((Fl_Callback*) updateRefreshTime);
		if(REFRESH_200MS_VAL == m_systemData->getRefreshTime())
			o3->set();

		Fl_Round_Button* o4 = new Fl_Round_Button(m_refreshGroup->x(),
				o3->y() + o3->h() + LST_Y_MARGIN,
				ROUND_BTN_WIDTH,
				ITEM_HEIGHT,
				REFRESH_1S_LABEL);
		o4->type(102);
		o4->down_box(FL_ROUND_DOWN_BOX);
		o4->callback((Fl_Callback*) updateRefreshTime);
		if(REFRESH_200MS_VAL == m_systemData->getRefreshTime())
			o4->set();
	}
	m_refreshGroup->end();
	scroll->add(m_refreshGroup);

	m_refreshGroup->hide();
	m_modeGroup->hide();
	//printf("%s probe currebnt index %d ptr %p \n", __PRETTY_FUNCTION__, m_probeChoice->value(), m_probeChoice);
}

ProbeTab::~ProbeTab()
{

}

void ProbeTab::refresh(void)
{

}

int ProbeTab::getProbeIndex(void)
{
	//printf("%s Probe index %d ptr %p \n", __PRETTY_FUNCTION__, m_probeChoice->value(), m_probeChoice);
	return m_probeChoice->value();
}

void ProbeTab::showJtagParameters(bool p_visible)
{
	if(p_visible) {
		m_modeGroup->show();
		m_refreshGroup->show();
	} else {
		m_modeGroup->hide();
		m_refreshGroup->hide();
	}
}

static void refreshProbeCallback(Fl_Widget *w, void * ptr)
{
	printf("Refresh probe list !\n");
}

static void connectProbeCallback(Fl_Widget *w, void * ptr)
{
	Fl_Button *btn = (Fl_Button *) w;
	Fl_Widget *parent = w->parent();
	Fl_Widget *p;

	if(parent->parent())
		parent = parent->parent();

	p = parent;
	while (p->parent()) p = p->parent();

	//printf("Connect probe ! Label \"%s\" \n", btn->label());
	if(btn->label() == CONNECT_LABEL) {
		if(0 == ((MainWindow*)p)->connect(parent)) {
			btn->label(DISCONNECT_LABEL);
			((ProbeTab*) ptr)->showJtagParameters();
		}
	} else {
		((MainWindow*)p)->disconnect(0);
		btn->label(CONNECT_LABEL);
		((ProbeTab*) ptr)->showJtagParameters(false);
	}
}

static void updateRefreshTime(Fl_Widget *w, void * ptr)
{
	int refreshTime = 0;
	Fl_Widget *p = w->parent();

	while (p->parent()) p = p->parent();
	//printf("Label : %s\n", w->label());

	if(w->label() == NO_REFRESH_LABEL)
	{
		refreshTime = NO_REFRESH_VAL;
	} else if(w->label() == REFRESH_20MS_LABEL) {
		refreshTime = REFRESH_20MS_VAL;
	} else if(w->label() == REFRESH_200MS_LABEL) {
		refreshTime = REFRESH_200MS_VAL;
	} else if(w->label() == REFRESH_1S_LABEL) {
		refreshTime = REFRESH_1S_VAL;
	} else {
		// Unknown choice: Nothing to do.
	}

	((MainWindow*)p)->updateRefreshTime(refreshTime);
}

static void updateMode(Fl_Widget *w, void * ptr)
{
	int mode = 0;
	Fl_Widget *p = w->parent();

	while (p->parent()) p = p->parent();

	//printf("Label : %s\n", w->label());
	if(w->label() == SAMPLE_MODE_LABEL) {
		mode = JTAG_CORE_SAMPLE_SCANMODE;
	} else if(w->label() == EXTTEST_MODE_LABEL) {
		mode = JTAG_CORE_EXTEST_SCANMODE;
	} else {
		// Unknown choice: Nothing to do.
	}

	((MainWindow*)p)->updateScanMode(mode);
}
