/*  freelife
 *  Copyright (C) 2000, 2003 Olivier Singla
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

#include "all.h"

#include <gtk-2.0/gtk/gtknotebook.h>
GdkGC *
create_color( GtkWidget * wgt,
   const long red,
   const long green,
   const long blue )
{
	GdkGC *gc;
	GdkColor *c = ( GdkColor * ) g_malloc( sizeof( GdkColor ) );

	/*
	 * --- Create a gc --- 
	 */
	gc = gdk_gc_new( wgt->window );

	/*
	 * --- Fill it in. --- 
	 */
	c->red = red;
	c->green = green;
	c->blue = blue;
	gdk_color_alloc( gdk_colormap_get_system(  ), c );

	/*
	 * --- Set the forground to the color --- 
	 */
	gdk_gc_set_foreground( gc, c );
	gdk_gc_set_background( gc, c );

	/*
	 * --- Return it. --- 
	 */
	return ( gc );
}								// create_color



/* This is an internally used function to set notebook tab widgets. */
void
set_notebook_tab( GtkWidget * notebook,
   gint page_num,
   GtkWidget * widget )
{
	GtkNotebookPage *page;
	GtkWidget *notebook_page;

#warning TODO!
#if 0
	page = ( GtkNotebookPage * ) g_list_nth( GTK_NOTEBOOK( notebook )->children, page_num )->data;
	notebook_page = page->child;
	gtk_widget_ref( notebook_page );
	gtk_notebook_remove_page( GTK_NOTEBOOK( notebook ), page_num );
	gtk_notebook_insert_page( GTK_NOTEBOOK( notebook ), notebook_page, widget, page_num );
	gtk_widget_unref( notebook_page );

#endif						   /*  */
}


double
now( void )
{
	static struct timeval _tv;
	static struct timezone _tz;
	static int first = TRUE;
	struct timeval tv;
	struct timezone tz;

	if ( first )
	{
		gettimeofday( &_tv, &_tz );
		first = FALSE;
	}

	gettimeofday( &tv, &tz );
	return ( ( ( double ) tv.tv_sec - ( double ) _tv.tv_sec ) * ( double ) 1000000 ) +
	   ( ( double ) tv.tv_usec );
}								// now
