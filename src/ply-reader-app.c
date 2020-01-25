/*
 * ply-reader-app.c
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
#include "ply-reader-actions.h"

struct _PlyReaderApp
{
  GtkApplication parent;
};

G_DEFINE_TYPE(PlyReaderApp, ply_reader_app, GTK_TYPE_APPLICATION);

static void
ply_reader_app_init (PlyReaderApp *app)
{
}

static void
ply_reader_add_app_menu(GApplication *app)
{
  GtkBuilder *builder;
  GMenuModel *app_menu;
  builder = gtk_builder_new_from_resource ("/top/elfiny/plyreader/ui/app-menu.ui");
  app_menu = G_MENU_MODEL (gtk_builder_get_object (builder, "appmenu"));
  gtk_application_set_app_menu (GTK_APPLICATION (app), app_menu);
  g_object_unref (builder);
}

static void
ply_reader_app_startup (GApplication *app)
{
  const gchar *quit_accels[2] = { "<Ctrl>Q", NULL };
  const gchar *open_accels[2] = { "<Ctrl>O", NULL };

  G_APPLICATION_CLASS (ply_reader_app_parent_class)->startup (app);

  g_action_map_add_action_entries (G_ACTION_MAP (app),
                                   app_entries, G_N_ELEMENTS (app_entries),
                                   app);
  gtk_application_set_accels_for_action (GTK_APPLICATION (app),
                                         "app.quit",
                                         quit_accels);
  gtk_application_set_accels_for_action (GTK_APPLICATION (app),
                                         "app.open",
                                         open_accels);
  //ply_reader_add_app_menu(app);
}

static void
ply_reader_app_activate (GApplication *app)
{
  PlyReaderWindow *win;

  win = ply_reader_window_new (PLY_READER_APP (app));
  gtk_window_present (GTK_WINDOW (win));
}

static void
ply_reader_app_open (GApplication  *app,
                     GFile        **files,
                     gint           n_files,
                     const gchar   *hint)
{
  GList *windows;
  PlyReaderWindow *win;
  int i;

  windows = gtk_application_get_windows (GTK_APPLICATION (app));
  if (windows)
    win = PLY_READER_WINDOW (windows->data);
  else
    win = ply_reader_window_new (PLY_READER_APP (app));

  for (i = 0; i < n_files; i++)
    ply_reader_window_open (win, files[i]);

  gtk_window_present (GTK_WINDOW (win));
}

static void
ply_reader_app_class_init (PlyReaderAppClass *class)
{
  G_APPLICATION_CLASS (class)->startup = ply_reader_app_startup;
  G_APPLICATION_CLASS (class)->activate = ply_reader_app_activate;
  G_APPLICATION_CLASS (class)->open = ply_reader_app_open;
}

PlyReaderApp *
ply_reader_app_new (void)
{
  return g_object_new (PLY_READER_APP_TYPE,
                       "application-id", "top.elfiny.plyreader",
                       "flags", G_APPLICATION_HANDLES_OPEN,
                       NULL);
}
