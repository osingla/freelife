/**
 * @file field.h
 *
 * freelife: Conway Game of Life \n
 * Copyright (C) 1999-2007  Olivier Singla \n
 * http://freelife.sourceforge.net/ \n
 */

#ifndef _UTILS_H_
#define _UTILS_H_

GdkGC *create_color( GtkWidget * wgt,
   const long red,
   const long green,
   const long blue );
void set_notebook_tab( GtkWidget * notebook,
   gint page_num,
   GtkWidget * widget );
double now( void );

#endif                         /*_UTILS_H_ */
