/* LiquidRescaling Library
 * Copyright (C) 2007 Carlo Baldassi (the "Author") <carlobaldassi@yahoo.it>.
 * All Rights Reserved.
 *
 * This library implements the algorithm described in the paper
 * "Seam Carving for Content-Aware Image Resizing"
 * by Shai Avidan and Ariel Shamir
 * which can be found at http://www.faculty.idc.ac.il/arik/imret.pdf
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3 dated June, 2007.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/> 
 */


#ifndef __LQR_PROGRESS_H__
#define __LQR_PROGRESS_H__

#define LQR_PROGRESS_MAX_MESSAGE_LENGTH (1024)

struct _LqrProgress;

typedef struct _LqrProgress LqrProgress;

typedef gboolean (*LqrProgressFuncInit)(const gchar*);
typedef gboolean (*LqrProgressFuncUpdate)(gdouble);
typedef gboolean (*LqrProgressFuncEnd)(const gchar*);

struct _LqrProgress
{
  LqrProgressFuncInit init;
  LqrProgressFuncUpdate update;
  LqrProgressFuncEnd end;
  gchar init_width_message[LQR_PROGRESS_MAX_MESSAGE_LENGTH];
  gchar end_width_message[LQR_PROGRESS_MAX_MESSAGE_LENGTH];
  gchar init_height_message[LQR_PROGRESS_MAX_MESSAGE_LENGTH];
  gchar end_height_message[LQR_PROGRESS_MAX_MESSAGE_LENGTH];
};

LqrProgress * lqr_progress_new(void);

gboolean lqr_progress_init(LqrProgress * p, const gchar * message);
gboolean lqr_progress_update(LqrProgress * p, gdouble percentage);
gboolean lqr_progress_end(LqrProgress * p, const gchar * message);

gboolean lqr_progress_set_init_width_message(LqrProgress *p, const gchar * message);
gboolean lqr_progress_set_init_height_message(LqrProgress *p, const gchar * message);
gboolean lqr_progress_set_end_width_message(LqrProgress *p, const gchar * message);
gboolean lqr_progress_set_end_height_message(LqrProgress *p, const gchar * message);

#endif /* __LQR_PROGRESS_H__ */




