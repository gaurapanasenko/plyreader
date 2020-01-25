/*
 * ply-reader-window.h
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

#ifndef __PLY_READER_WINDOW_H
#define __PLY_READER_WINDOW_H

#include <gtk/gtk.h>
#include "ply-reader-app.h"

#define PLY_READER_WINDOW_TYPE (ply_reader_window_get_type ())
G_DECLARE_FINAL_TYPE (PlyReaderWindow, ply_reader_window, PLY_READER, WINDOW, GtkApplicationWindow)


PlyReaderWindow       *ply_reader_window_new          (PlyReaderApp *app);
void                   ply_reader_window_open         (PlyReaderWindow *win,
                                                       GFile           *file);


#endif /* __PLY_READER_WINDOW_H */
