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
        PROP_0,
        PROP_TAB,
        LAST_PROP
};

static GParamSpec *properties[LAST_PROP];

enum
{
	CLOSE_CLICKED,
	LAST_SIGNAL
};

static guint signals[LAST_SIGNAL];

G_DEFINE_TYPE (PlyReaderTabLabel, ply_reader_tab_label, GTK_TYPE_BOX);

static void
ply_reader_tab_label_set_property (GObject      *object,
                                   guint         prop_id,
                                   const GValue *value,
                                   GParamSpec   *pspec)
{
  PlyReaderTabLabel *tab_label = PLY_READER_TAB_LABEL (object);

  switch (prop_id)
  {
    case PROP_TAB:
      g_return_if_fail (tab_label->tab == NULL);
      tab_label->tab = GTK_WIDGET (g_value_get_object (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}

static void
ply_reader_tab_label_get_property (GObject    *object,
                                   guint       prop_id,
                                   GValue     *value,
                                   GParamSpec *pspec)
{
  PlyReaderTabLabel *tab_label = PLY_READER_TAB_LABEL (object);

  switch (prop_id)
  {
    case PROP_TAB:
      g_value_set_object (value, tab_label->tab);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}

static void
ply_reader_tab_label_close_clicked (PlyReaderTabLabel *tab_label)
{
}

static void
ply_reader_tab_label_class_init (PlyReaderTabLabelClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  object_class->set_property = ply_reader_tab_label_set_property;
  object_class->get_property = ply_reader_tab_label_get_property;

  properties[PROP_TAB] =
    g_param_spec_object ("tab",
                         "Tab",
                         "The PLY Reader",
                         GTK_TYPE_WIDGET,
                         G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY);

  g_object_class_install_properties (object_class, LAST_PROP, properties);

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
ply_reader_tab_label_clicked(GtkWidget         *widget,
                             PlyReaderTabLabel *tab_label)
{
  g_signal_emit (tab_label, signals[CLOSE_CLICKED], 0, NULL);
}

static void
ply_reader_tab_label_init (PlyReaderTabLabel *tab_label)
{
	gtk_widget_init_template (GTK_WIDGET (tab_label));

  g_signal_connect (tab_label->button,
	                  "clicked",
                    G_CALLBACK (ply_reader_tab_label_clicked),
                    tab_label);
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

