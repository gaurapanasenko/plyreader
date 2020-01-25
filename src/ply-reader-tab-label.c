/*
 * ply-reader-tab-label.c
 * This file is part of PLY Reader.
 *
 * Copyright (C) 2020 Yehor Panasenko <yehor.panasenko@gmail.com>
 *
 * PLY Reader is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * PLY Reader is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with PLY Reader.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ply-reader-tab-label.h"

struct _PlyReaderTabLabel
{
	GtkBox parent_instance;

  GtkWidget *tab;
  GtkWidget *name;
  GtkWidget *button;
};

enum
{
	CLOSE_CLICKED,
	LAST_SIGNAL
};

static guint signals[LAST_SIGNAL];

G_DEFINE_TYPE (PlyReaderTabLabel, ply_reader_tab_label, GTK_TYPE_BOX);

static void
ply_reader_tab_label_close_clicked (PlyReaderTabLabel *tab_label)
{
}

static void
ply_reader_tab_label_class_init (PlyReaderTabLabelClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

	signals[CLOSE_CLICKED] =
		g_signal_new_class_handler ("close-clicked",
		                            G_TYPE_FROM_CLASS (klass),
		                            G_SIGNAL_RUN_LAST,
                                G_CALLBACK (ply_reader_tab_label_close_clicked),
		                            NULL, NULL, NULL,
		                            G_TYPE_NONE,
		                            0);

  /* Bind class to template */
	gtk_widget_class_set_template_from_resource (widget_class,
                                               "/top/elfiny/plyreader/ui/tab-label.ui");
  gtk_widget_class_bind_template_child (widget_class, PlyReaderTabLabel, name);
  gtk_widget_class_bind_template_child (widget_class, PlyReaderTabLabel, button);

}

static void
ply_reader_tab_label_init (PlyReaderTabLabel *tab_label)
{
	gtk_widget_init_template (GTK_WIDGET (tab_label));

  /*g_signal_connect (tab_label->close_button,
	                  "clicked",
	                  G_CALLBACK (close_button_clicked_cb),
                    tab_label);*/
}

GtkWidget *
ply_reader_tab_label_get_tab (PlyReaderTabLabel *tab_label)
{
  g_return_val_if_fail (PLY_READER_IS_TAB_LABEL (tab_label), NULL);

	return tab_label->tab;
}

PlyReaderTabLabel *
ply_reader_tab_label_new (GtkWidget   *notebook,
                          GtkWidget   *tab,
                          const gchar *basename)
{
  PlyReaderTabLabel * tab_label = g_object_new (PLY_READER_TAB_LABEL_TYPE,
                                                "tab", tab,
                                                NULL);
  gtk_label_set_label (GTK_LABEL (tab_label->name), basename);
  return tab_label;
}

