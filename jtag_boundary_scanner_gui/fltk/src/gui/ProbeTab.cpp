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

#include "gui/ProbeTab.h"

static const int ITEM_HEIGHT = 20;
static const int PROBE_CHOICE_WIDTH = 200;
static const int REFRESH_PROBE_WIDTH = 90;
static const int CONNECT_PROBE_WIDTH = 90;
static const int BOX_MARGIN = 1;
static const int X_MARGIN = 15;
static const int Y_MARGIN = 15;

static const char *CONNECT_LABEL = "Connect";
static const char *DISCONNECT_LABEL = "Disconnect";

static void RefreshProbeCallback(Fl_Widget *w, void * ptr);
static void ConnectProbeCallback(Fl_Widget *w, void * ptr);

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

	m_probeChoice = new Fl_Choice(scroll->x()+BOX_MARGIN,
									  scroll->y()+BOX_MARGIN,
									  PROBE_CHOICE_WIDTH,
									  ITEM_HEIGHT,
									  "Probe : ");

	for(size_t i=0; i<m_systemData->getNbProbe(); i++) {
		m_probeChoice->add(m_systemData->getProbe(i)->getName().c_str());
	}
	if(m_systemData->getNbProbe() > 0)
		m_probeChoice->value(0);

	scroll->add(m_probeChoice);

	Fl_Button *refreshBtn = new Fl_Button(scroll->x()+BOX_MARGIN,
				m_probeChoice->y()+m_probeChoice->h()+Y_MARGIN,
				REFRESH_PROBE_WIDTH,
				ITEM_HEIGHT,
				"Refresh");
	refreshBtn->callback(RefreshProbeCallback, NULL);
	scroll->add(refreshBtn);

	m_connectBtn = new Fl_Button(
				refreshBtn->x() + refreshBtn->w() + X_MARGIN,
				m_probeChoice->y()+m_probeChoice->h()+Y_MARGIN,
				CONNECT_PROBE_WIDTH,
				ITEM_HEIGHT,
				CONNECT_LABEL);
	m_connectBtn->callback(ConnectProbeCallback, NULL);
	scroll->add(m_connectBtn);

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

static void RefreshProbeCallback(Fl_Widget *w, void * ptr)
{
	printf("Refresh probe list !\n");
}

static void ConnectProbeCallback(Fl_Widget *w, void * ptr)
{
	Fl_Button *btn = (Fl_Button *) w;
	Fl_Widget *parent = w->parent();
	Fl_Widget *p;

	if(parent->parent())
		parent = parent->parent();

	p = parent;
	while (p->parent()) p = p->parent();

	//printf("Connect probe ! Label \"%s\" \n", btn->label());
	if(!strcmp(btn->label(), CONNECT_LABEL)) {
		if(0 == ((MainWindow*)p)->connect(parent))
			btn->label(DISCONNECT_LABEL);
	} else {
		((MainWindow*)p)->disconnect(0);
		btn->label(CONNECT_LABEL);
	}
}
