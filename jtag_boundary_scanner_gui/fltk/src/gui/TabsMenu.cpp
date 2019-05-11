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
* @file   Tabs.c
* @brief  Implement tabs index.
* @author Sébastien CORBEAU <sebastien.corbeau@viveris.fr>
*/
#include <FL/Fl_Widget.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Scroll.H>

#include <gui/TabsMenu.h>
#include <gui/TestTab.h>
#include "gui/ProbeTab.h"
#include "gui/I2CTab.h"
#include <gui/MainWindow.h>

TabsMenu::TabsMenu(int p_x, int p_y, int p_w, int p_h) :
		Fl_Tabs(p_x, p_y, p_w, p_h)
{
	MainWindow *p = (MainWindow *)parent();
	selection_color(FL_BACKGROUND_COLOR);
	ProbeTab *probeTabs = new ProbeTab(p,
									   p_x+TABS_MENU_BOARDER,
									   p_y+TABS_MENU_HEIGHT,
									   p_w-(TABS_MENU_BOARDER*2),
									   p_h-(TABS_MENU_HEIGHT*2),
									   "Probes");
	probeTabs->end();
	I2CTab *i2cTabs = new I2CTab(p,
								 p_x+TABS_MENU_BOARDER,
								 p_y+TABS_MENU_HEIGHT,
								 p_w-(TABS_MENU_BOARDER*2),
								 p_h-(TABS_MENU_HEIGHT*2),
								 "I2C");
	i2cTabs->end();

#if 0
	TestTab *test = new TestTab(p_x+TABS_MENU_BOARDER,
								p_y+TABS_MENU_HEIGHT,
								p_w-(TABS_MENU_BOARDER*2),
								p_h-(TABS_MENU_HEIGHT*2),
								"Seb");
	test->end();
	Fl_Group *g2 = new Fl_Group(p_x+TABS_MENU_BOARDER, p_y+TABS_MENU_HEIGHT, p_w-(TABS_MENU_BOARDER*2), p_h-(TABS_MENU_HEIGHT*2),"Bbb");
	Fl_Scroll *s2 = new Fl_Scroll(g2->x()+10, g2->y()+10, g2->w()-(20), g2->h()-(20));
	new Fl_Button(60, 90,200,25,"But 1 Tab B");
	new Fl_Button(60, 120,200,25,"But 2 Tab B");
	new Fl_Button(60, 150,200,25,"But 3 Tab B");
	s2->end();
	g2->end();
#endif

	resize(p_x, p_y, p_w, p_h);
}

TabsMenu::~TabsMenu()
{

}

// Keep tab size constant
void TabsMenu::resize(int p_x, int p_y, int p_w, int p_h) {
	Fl_Widget *p = parent();
	while (p->parent()) p = p->parent();

	p_w = p->w() - (2*TabsMenu::TABS_MENU_BOARDER);
	p_h = p->h() - ((2*TabsMenu::TABS_MENU_BOARDER) + ((MainWindow*) p)->getMenuBarEnd());

	//printf("%s p_x=%d p_y=%d p_w=%d p_h=%d\n", __PRETTY_FUNCTION__, p_x, p_y, p_w, p_h);
	//printf("%s x=%d y=%d w=%d h=%d\n", __PRETTY_FUNCTION__, x(), y(), w(), h());
	Fl_Tabs::resize(this->x(), this->y(), p_w, p_h);
	int max_labelsize = TABS_MENU_HEIGHT; // minimum tab label size
	// Pass #1: hunt fo largest label size
	for(int t=0; t<children(); t++ ) {
		Fl_Widget *w = child(t);
		if(max_labelsize < w->labelsize())
			max_labelsize = w->labelsize();
	}
	max_labelsize += TABS_MENU_HEIGHT; // extra vertical space
	// Pass #2: Apply largest label size to all children
	for(int t=0; t<children(); t++) {
		Fl_Widget *w = child(t);
		w->resize(w->x(), this->y() + max_labelsize, w->w(), p_h - max_labelsize);
	}
}

void TabsMenu::addTabs(TabsModel *tabs)
{
	add(tabs);
	resize(x(), y(), w(), h());
	redraw();
}
void TabsMenu::deleteTabs(const char* label)
{

	int i;
	//printf("%s delete tabs label %s\n", __PRETTY_FUNCTION__, label);

	for(i=0; i < children(); i++) {
		Fl_Widget *c = child(i);
		if(!strcmp(c->label(), label)) {
			//printf("%s Found\n", label);
			c->hide();
			c->redraw();
			remove(c);
			delete c;
		}
	}
	redraw();
	parent()->redraw();
}

void TabsMenu::cleanCpuTabs(void)
{
	int i;
	for(i=0; i<children(); i++) {
		TabsModel *tab = (TabsModel *)child(i);
		if(tab->isCpuTab()) {
			tab->hide();
			tab->redraw();
			remove(tab);
			delete tab;
		}
	}
	redraw();
	parent()->redraw();
}
