/*
 * ply-reader-actions.h
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

#ifndef __PLY_READER_ACTIONS_H
#define __PLY_READER_ACTIONS_H

#include <gtk/gtk.h>
#include "ply-reader-window.h"

void
ply_reader_open_activated (GSimpleAction *action,
                   GVariant      *parameter,
                   gpointer       app);

void
ply_reader_about_activated (GSimpleAction *action,
                   GVariant      *parameter,
                   gpointer       app);

void
ply_reader_quit_activated (GSimpleAction *action,
                   GVariant      *parameter,
                   gpointer       app);

static GActionEntry app_entries[] =
{
  { "open", ply_reader_open_activated, NULL, NULL, NULL },
  { "about", ply_reader_about_activated, NULL, NULL, NULL },
  { "quit", ply_reader_quit_activated, NULL, NULL, NULL }
};

#endif /* __PLY_READER_ACTIONS_H */
