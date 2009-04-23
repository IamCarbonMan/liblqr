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


#ifndef __LQR_ENERGY_BUFFER_PUB_H__
#define __LQR_ENERGY_BUFFER_PUB_H__

#ifndef __LQR_BASE_H__
#error "lqr_base.h must be included prior to lqr_energy_buffer_pub.h"
#endif /* __LQR_BASE_H__ */

enum _LqrEnergyReaderType
{
  LQR_ER_BRIGHT,                /* read brightness */
  LQR_ER_LUMA,                  /* read luma */
  LQR_ER_RGBA,                  /* read RGBA */
  LQR_ER_CUSTOM                 /* reader the buffer as-is*/
};

typedef enum _LqrEnergyReaderType LqrEnergyReaderType;

struct _LqrEnergyBuffer;

typedef struct _LqrEnergyBuffer LqrEnergyBuffer;

gfloat lqr_energy_buffer_read_bright (LqrEnergyBuffer * ebuffer, gint x, gint y);
gfloat lqr_energy_buffer_read_luma (LqrEnergyBuffer * ebuffer, gint x, gint y);
gfloat lqr_energy_buffer_read_rgba (LqrEnergyBuffer * ebuffer, gint x, gint y, gint channel);
void * lqr_energy_buffer_read_custom (LqrEnergyBuffer * ebuffer, gint x, gint y, gint channel);

LqrEnergyReaderType lqr_energy_buffer_get_read_t (LqrEnergyBuffer * ebuffer);
gint lqr_energy_buffer_get_radius (LqrEnergyBuffer * ebuffer);

#endif /* __LQR_ENERGY_BUFFER_PUB_H__ */

