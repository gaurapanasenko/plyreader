/*
 * ply-reader-actions.c
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

#include "ply-reader-actions.h"
#include "ply-reader-window.h"

void
ply_reader_open_activated (GSimpleAction *action,
                           GVariant      *parameter,
                           gpointer       app)
{
  GtkWidget *dialog;
  GtkFileChooserAction action_open = GTK_FILE_CHOOSER_ACTION_OPEN;
  gint res;
  GList *windows;
  PlyReaderWindow *parent_window;

  windows = gtk_application_get_windows (GTK_APPLICATION (app));
  if (windows)
    parent_window = PLY_READER_WINDOW (windows->data);
  else
    parent_window = ply_reader_window_new (PLY_READER_APP (app));

  dialog = gtk_file_chooser_dialog_new ("Open File",
                                        GTK_WINDOW (parent_window),
                                        action_open,
                                        "_Cancel",
                                        GTK_RESPONSE_CANCEL,
                                        "_Open",
                                        GTK_RESPONSE_ACCEPT,
                                        NULL);

  res = gtk_dialog_run (GTK_DIALOG (dialog));
  if (res == GTK_RESPONSE_ACCEPT)
    {
      GFile *file;
      GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
      file = gtk_file_chooser_get_file (chooser);
      ply_reader_window_open(parent_window, file);
    }

  gtk_widget_destroy (dialog);
}

void
ply_reader_about_responsed (GtkDialog *dialog,
                            gint       response_id,
                            gpointer   user_data) {
  gtk_widget_destroy (GTK_WIDGET (dialog));
}

void
ply_reader_about_activated (GSimpleAction *action,
                            GVariant      *parameter,
                            gpointer       app)
{
  GtkBuilder *builder;
  GObject *dialog;
  builder = gtk_builder_new_from_resource ("/top/elfiny/plyreader/ui/about.ui");
  dialog = gtk_builder_get_object (builder, "about_dialog");
  g_object_unref (builder);
  g_signal_connect (dialog, "response", G_CALLBACK (gtk_widget_destroy), dialog);
  gtk_dialog_run (GTK_DIALOG (dialog));
}

void
ply_reader_quit_activated (GSimpleAction *action,
                           GVariant      *parameter,
                           gpointer       app)
{
  g_application_quit (G_APPLICATION (app));
}
