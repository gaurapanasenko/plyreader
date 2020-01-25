/*
 * ply-reader-window.c
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

#include <gtk/gtk.h>

#include "ply-reader-app.h"
#include "ply-reader-window.h"
#include "ply-reader-tab-label.h"

struct _PlyReaderWindow
{
  GtkApplicationWindow parent;
};

typedef struct _PlyReaderWindowPrivate PlyReaderWindowPrivate;

struct _PlyReaderWindowPrivate
{
  GtkWidget *notebook;
};

G_DEFINE_TYPE_WITH_PRIVATE (PlyReaderWindow, ply_reader_window, GTK_TYPE_APPLICATION_WINDOW);

static void
ply_reader_window_init (PlyReaderWindow *win)
{
  gtk_widget_init_template (GTK_WIDGET (win));
}

static void
ply_reader_window_class_init (PlyReaderWindowClass *class)
{
  gtk_widget_class_set_template_from_resource (GTK_WIDGET_CLASS (class),
                                               "/top/elfiny/plyreader/ui/window.ui");
  gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (class), PlyReaderWindow, notebook);
}

PlyReaderWindow *
ply_reader_window_new (PlyReaderApp *app)
{
  return g_object_new (PLY_READER_WINDOW_TYPE, "application", app, NULL);
}

static gint
find_tab_num_at_pos (GtkNotebook *notebook,
                     gint         screen_x,
                     gint         screen_y)
{
  GtkPositionType tab_pos;
  GtkAllocation tab_allocation;
  gint page_num;

  tab_pos = gtk_notebook_get_tab_pos (notebook);

  for (page_num = 0; ; page_num++)
  {
    GtkWidget *page;
    GtkWidget *tab_label;
    gint max_x, max_y, x_root, y_root;

    page = gtk_notebook_get_nth_page (notebook, page_num);

    if (page == NULL)
    {
      break;
    }

    tab_label = gtk_notebook_get_tab_label (notebook, page);
    g_return_val_if_fail (tab_label != NULL, -1);

    if (!gtk_widget_get_mapped (tab_label))
    {
      continue;
    }

    gdk_window_get_origin (gtk_widget_get_window (tab_label), &x_root, &y_root);

    gtk_widget_get_allocation (tab_label, &tab_allocation);
    max_x = x_root + tab_allocation.x + tab_allocation.width;
    max_y = y_root + tab_allocation.y + tab_allocation.height;

    if ((tab_pos == GTK_POS_TOP || tab_pos == GTK_POS_BOTTOM) &&
        screen_x <= max_x)
    {
      return page_num;
    }

    if ((tab_pos == GTK_POS_LEFT || tab_pos == GTK_POS_RIGHT) &&
        screen_y <= max_y)
    {
      return page_num;
    }
  }

  return -1;
}

static void
pr_notebook_close_button_clicked (GtkButton   *button,
                                  GtkNotebook *notebook)
{
  /*if (event->type == GDK_BUTTON_PRESS &&
      (event->state & gtk_accelerator_get_default_mod_mask ()) == 0)
  {
    gint tab_clicked;

    tab_clicked = find_tab_num_at_pos (notebook, event->x_root, event->y_root);
    if (tab_clicked >= 0)
    {
      switch (event->button)
      {
        case GDK_BUTTON_MIDDLE:
          gtk_notebook_remove_page (notebook, tab_clicked);
          return GDK_EVENT_STOP;

        default:
          break;
      }
    }
  }

  return GDK_EVENT_STOP;*/
}
/*
GtkWidget *
ply_reader_window_tab_create (GtkWidget* notebook, const gchar *basename)
{
  GtkWidget *box, *label, *button, *image;
  GtkStyleContext *context;
  box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

  label = gtk_label_new(basename);
  gtk_widget_show (label);
  gtk_box_pack_start(GTK_BOX(box), label, 1, 1, 0);

  image = gtk_image_new_from_icon_name("window-close", GTK_ICON_SIZE_BUTTON);

  button = gtk_button_new();
  gtk_button_set_image(GTK_BUTTON(button), image);
  context = gtk_widget_get_style_context(button);
  gtk_style_context_add_class(context, "flat");
  gtk_style_context_add_class(context, "small-button");
  g_signal_connect (button, "clicked", G_CALLBACK (pr_notebook_button_press_event), notebook);

  gtk_box_pack_start(GTK_BOX(box), button, 1, 0, 0);
  gtk_widget_show_all(box);



  return box;
}*/

void
ply_reader_window_open (PlyReaderWindow *win,
                            GFile              *file)
{
  PlyReaderWindowPrivate *priv;
  gchar *basename;
  PlyReaderTabLabel * plabel;
  GtkWidget *scrolled, *view, *label;
  gchar *contents;
  gsize length;

  priv = ply_reader_window_get_instance_private (win);
  basename = g_file_get_basename (file);

  scrolled = gtk_scrolled_window_new (NULL, NULL);
  plabel = ply_reader_tab_label_new(priv->notebook, scrolled, basename);
  label = GTK_WIDGET (plabel);
  gtk_widget_show (scrolled);
  gtk_widget_set_hexpand (scrolled, TRUE);
  gtk_widget_set_vexpand (scrolled, TRUE);
  view = gtk_text_view_new ();
  gtk_text_view_set_editable (GTK_TEXT_VIEW (view), FALSE);
  gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW (view), FALSE);
  gtk_widget_show (view);
  gtk_container_add (GTK_CONTAINER (scrolled), view);
  gtk_notebook_append_page (GTK_NOTEBOOK (priv->notebook), scrolled, label);

  if (g_file_load_contents (file, NULL, &contents, &length, NULL, NULL))
    {
      GtkTextBuffer *buffer;

      buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));
      gtk_text_buffer_set_text (buffer, contents, length);
      g_free (contents);
    }

  g_free (basename);
}
