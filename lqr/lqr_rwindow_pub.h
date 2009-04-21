/* LiquidRescaling Library
 * Copyright (C) 2007-2009 Carlo Baldassi (the "Author") <carlobaldassi@gmail.com>.
 * All Rights Reserved.
 *
 * This library implements the algorithm described in the paper
 * "Seam Carving for Content-Aware Image Resizing"
 * by Shai Avidan and Ariel Shamir
 * which can be found at http://www.faculty.idc.ac.il/arik/imret.pdf
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; version 3 dated June, 2007.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/> 
 */


#ifndef __LQR_READER_WINDOW_PUB_H__
#define __LQR_READER_WINDOW_PUB_H__

#ifndef __LQR_BASE_H__
#error "lqr_base.h must be included prior to lqr_rwindow_pub.h"
#endif /* __LQR_BASE_H__ */

enum _LqrEnergyReaderType
{
  LQR_ER_BRIGHT,                /* read brightness */
  LQR_ER_LUMA,                  /* read luma */
  LQR_ER_RGBA,                  /* read RGBA */
  LQR_ER_CUSTOM                 /* reader the buffer as-is*/
};

typedef enum _LqrEnergyReaderType LqrEnergyReaderType;

struct _LqrReaderWindow;

typedef struct _LqrReaderWindow LqrReaderWindow;

gdouble lqr_rwindow_read_bright (LqrReaderWindow * rwindow, gint x, gint y);
gdouble lqr_rwindow_read_luma (LqrReaderWindow * rwindow, gint x, gint y);
gdouble lqr_rwindow_read_rgba (LqrReaderWindow * rwindow, gint x, gint y, gint channel);
gdouble lqr_rwindow_read_custom (LqrReaderWindow * rwindow, gint x, gint y, gint channel);

LqrEnergyReaderType lqr_rwindow_get_read_t (LqrReaderWindow * rwindow);
gint lqr_rwindow_get_radius (LqrReaderWindow * rwindow);

#endif /* __LQR_READER_WINDOW_PUB_H__ */

