/*
 * ply-reader-app.h
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

#ifndef __PLY_READER_APP_H
#define __PLY_READER_APP_H

#include <gtk/gtk.h>


#define PLY_READER_APP_TYPE (ply_reader_app_get_type ())
G_DECLARE_FINAL_TYPE (PlyReaderApp, ply_reader_app, PLY_READER, APP, GtkApplication)


PlyReaderApp     *ply_reader_app_new         (void);

#endif /* __PLY_READER_APP_H */
