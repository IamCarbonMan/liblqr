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

#ifndef __LQR_RASTER_H__
#define __LQR_RASTER_H__

#ifndef __LQR_BASE_H__
#error "lqr_base.h must be included prior to lqr_raster.h"
#endif /* __LQR_BASE_H__ */

#ifndef __LQR_GRADIENT_H__
#error "lqr_gradient.h must be included prior to lqr_raster.h"
#endif /* __LQR_GRADIENT_H__ */

/**** LQR_RASTER CLASS DEFINITION ****/
/* This is the representation of the multisize image
 * The image is stored internally as a one-dimentional
 * array of LqrData points, called map.
 * The points are ordered by rows. */
struct _LqrRaster
{
  gint w_start, h_start;        /* original width & height */
  gint w, h;                    /* current width & height */
  gint w0, h0;                  /* map array width & height */

  gint level;                   /* (in)visibility level (1 = full visibility) */
  gint max_level;               /* max level computed so far
                                 * it is not level <= max_level
                                 * but rather level <= 2 * max_level - 1
                                 * since levels are shifted upon inflation
                                 */

  gint bpp;                     /* number of bpp of the image */

  gint transposed;              /* flag to set transposed state */
  gboolean aux;                 /* flag to set if raster is auxiliary */

  gboolean resize_aux_layers;   /* flag to determine whether the auxiliary layers are resized */
  gboolean output_seams;        /* flag to determine whether to output the seam map */
  LqrResizeOrder resize_order;  /* resize order */
  LqrColourRGBA seam_colour_start;     /* start colour for the seam map */
  LqrColourRGBA seam_colour_end;       /* end colour for the seam map */

  LqrRaster *pres_raster;       /* preservation layer raster */
  LqrRaster *disc_raster;       /* discard layer raster */

  gfloat rigidity;              /* rigidity value (can straighten seams) */
  gdouble *rigidity_map;        /* the rigidity function */
  gint delta_x;                 /* max displacement of seams (currently is only meaningful if 0 or 1 */

  guchar *rgb;                  /* array of rgb points */
  gint *vs;                     /* array of visibility levels */
  gdouble *en;                  /* array of energy levels */
  gdouble *bias;                /* array of energy levels */
  gdouble *m;                   /* array of auxiliary energy values */
  gint *least;                  /* array of pointers */
  gint *_raw;                   /* array of array-coordinates, for seam computation */
  gint **raw;                   /* array of array-coordinates, for seam computation */

  LqrCursor *c;                 /* cursor to be used as image reader */

  gint *vpath;                  /* array of array-coordinates representing a vertical seam */
  gint *vpath_x;                /* array of abscisses representing a vertical seam */

  LqrGradFunc gf;                    /* pointer to a gradient function */

  LqrProgress * progress;	/* pointer to progress update functions */

  LqrSeamsBufferList * flushed_vs;  /* linked list of pointers to flushed visibility maps buffers */

};


/* LQR_RASTER CLASS FUNCTIONS */

/** private functions **/

/* build maps */
gboolean lqr_raster_build_maps (LqrRaster * r, gint depth);     /* build all */
void lqr_raster_build_emap (LqrRaster * r);     /* energy */
void lqr_raster_build_mmap (LqrRaster * r);     /* minpath */
gboolean lqr_raster_build_vsmap (LqrRaster * r, gint depth);    /* visibility */

/* internal functions for maps computation */
inline gdouble lqr_raster_read (LqrRaster * r, gint x, gint y); /* read the average value at given point */
void lqr_raster_compute_e (LqrRaster * r, gint x, gint y);      /* compute energy of point at c (fast) */
void lqr_raster_update_emap (LqrRaster * r);    /* update energy map after seam removal */
void lqr_raster_update_mmap (LqrRaster * r);    /* minpath */
void lqr_raster_build_vpath (LqrRaster * r);    /* compute seam path */
void lqr_raster_carve (LqrRaster * r);  /* updates the "raw" buffer */
void lqr_raster_update_vsmap (LqrRaster * r, gint l);   /* update visibility map after seam removal */
void lqr_raster_finish_vsmap (LqrRaster * r);   /* complete visibility map (last seam) */
void lqr_raster_copy_vsmap (LqrRaster * r, LqrRaster * dest);   /* copy vsmap on another raster */
gboolean lqr_raster_inflate (LqrRaster * r, gint l);    /* adds enlargment info to map */

/* image manipulations */
gboolean lqr_raster_resize_width (LqrRaster * r, gint w1);   /* liquid resize width */
gboolean lqr_raster_resize_height (LqrRaster * r, gint h1);   /* liquid resize height */
void lqr_raster_set_width (LqrRaster * r, gint w1);
gboolean lqr_raster_transpose (LqrRaster * r);

/** public functions **/

/* constructor & destructor */
LqrRaster * lqr_raster_new (guchar * buffer, gint width, gint height, gint bpp);
void lqr_raster_destroy (LqrRaster * r);

/* initialize */
gboolean lqr_raster_init (LqrRaster *r, gint delta_x, gfloat rigidity);

/* set attributes */
void lqr_raster_set_gradient_function (LqrRaster * r, LqrGradFuncType gf_ind);
void lqr_raster_set_output_seams (LqrRaster *r, LqrColourRGBA seam_colour_start, LqrColourRGBA seam_colour_end);
void lqr_raster_set_resize_order (LqrRaster *r, LqrResizeOrder resize_order);
gboolean lqr_raster_attach_pres_layer (LqrRaster * r, guchar * buffer, gint bpp);
gboolean lqr_raster_attach_disc_layer (LqrRaster * r, guchar * buffer, gint bpp);
void lqr_raster_set_progress (LqrRaster *r, LqrProgress *p);

/* image manipulations */
gboolean lqr_raster_resize (LqrRaster * r, gint w1, gint h1);   /* liquid resize */
gboolean lqr_raster_flatten (LqrRaster * r);    /* flatten the multisize image */

/* readout */
gint lqr_raster_get_width (LqrRaster * r);
gint lqr_raster_get_height (LqrRaster * r);
gint lqr_raster_read_x (LqrRaster * r);
gint lqr_raster_read_y (LqrRaster * r);
void lqr_raster_read_reset (LqrRaster * r);
gboolean lqr_raster_read_next (LqrRaster * r);
guchar lqr_raster_read_c (LqrRaster * r, gint col);


#endif /* __LQR_RASTER_H__ */
