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

static gboolean
on_fielddraw_button_press_event( GtkWidget * widget,
   GdkEventButton * event,
   gpointer user_data )
{
	int x,
	  y;
	GtkAdjustment *hadj,
	 *vadj;
	GdkCursor *cursor;

	cursor = gdk_cursor_new( GDK_FLEUR );
	gdk_window_set_cursor( fielddraw->window, cursor );
	gdk_cursor_destroy( cursor );

	/*
	 * Make sure it's a button event
	 */
	if ( event->type != GDK_BUTTON_PRESS )
		return FALSE;

	/*
	 * Get mouse position
	 */
	x = ( int ) event->x;
	y = ( int ) event->y;
	if ( ( x < 0 ) || ( x >= config.life_width ) || ( y < 0 ) || ( y >= config.life_height ) )
		return FALSE;

	/*
	 * Do nothing if cursor is already on the hand
	 */
	zoom_xoffset = zoom_yoffset = 0;
	if ( ( x >= zoom_xstart ) && ( x < zoom_xstart + zoom_width ) &&
	   ( y >= zoom_ystart ) && ( y < zoom_ystart + zoom_height ) )

	{
		zoom_xoffset = x - zoom_xstart;
		zoom_yoffset = y - zoom_ystart;
		return FALSE;
	}

#ifdef TRACE_EVENTS
	TRACE( "field: on_fielddraw_button_press_event: \n" );
#endif

	/*
	 * Move zoom window
	 */
	hadj = gtk_scrolled_window_get_hadjustment( GTK_SCROLLED_WINDOW( zoom_scrolledwindow ) );
	vadj = gtk_scrolled_window_get_vadjustment( GTK_SCROLLED_WINDOW( zoom_scrolledwindow ) );
	gtk_adjustment_set_value( hadj, x );
	gtk_adjustment_set_value( vadj, y );

	return FALSE;

}								// on_fielddraw_button_press_event


static gboolean
on_fielddraw_button_release_event( GtkWidget * widget,
   GdkEventButton * event,
   gpointer user_data )
{
	GdkCursor *cursor;

	cursor = gdk_cursor_new( GDK_TOP_LEFT_ARROW );
	gdk_window_set_cursor( fielddraw->window, cursor );
	gdk_cursor_destroy( cursor );

	return FALSE;

}								// on_fielddraw_button_release_event


static gboolean
on_fielddraw_motion_notify_event( GtkWidget * widget,
   GdkEventMotion * event,
   gpointer user_data )
{
	int x,
	  y;
	GtkAdjustment *hadj,
	 *vadj;

	/*
	 * Get mouse position
	 */
	x = ( int ) event->x;
	y = ( int ) event->y;
	if ( ( x < 0 ) || ( x >= config.life_width ) || ( y < 0 ) || ( y >= config.life_height ) )
		return FALSE;

#ifdef TRACE_EVENTS
	TRACE( "field: on_fielddraw_motion_notify_event: x=%-3d y=%-3d\n", x, y );
#endif

	/*
	 * Move zoom window
	 */
	hadj = gtk_scrolled_window_get_hadjustment( GTK_SCROLLED_WINDOW( zoom_scrolledwindow ) );
	vadj = gtk_scrolled_window_get_vadjustment( GTK_SCROLLED_WINDOW( zoom_scrolledwindow ) );
	gtk_adjustment_set_value( hadj, x - zoom_xoffset );
	gtk_adjustment_set_value( vadj, y - zoom_yoffset );

	return FALSE;

}								// on_fielddraw_motion_notify_event


static gboolean
on_fielddraw_key_press_event( GtkWidget * widget,
   GdkEventKey * event,
   gpointer user_data )
{

#ifdef TRACE_EVENTS
	TRACE( "field: on_fielddraw_key_press_event\n" );
#endif

	return FALSE;

}


static gboolean
on_fielddraw_configure_event( GtkWidget * widget,
   GdkEventConfigure * event,
   gpointer user_data )
{
#ifdef TRACE_EVENTS
	TRACE( "field: on_fielddraw_configure_event\n" );
#endif
	return FALSE;
}


static gboolean
on_field_configure_event( GtkWidget * widget,
   GdkEventConfigure * event,
   gpointer user_data )
{
#ifdef TRACE_EVENTS
	TRACE( "field: on_field_configure_event\n" );
#endif
	return FALSE;
}


static void
on_stop_clicked( GtkButton * button,
   gpointer user_data )
{
	end_comp_generations = TRUE;
}								// on_stop_clicked


static void
create_hand_field( void )
{
	UBYTE *field,
	 *pw;
	int row,
	  col;
	static int prev_zoom_xstart = -1,
	  prev_zoom_ystart;
	static int prev_zoom_width,
	  prev_zoom_height;


#define MAX_POINTS 100
	static gint on_npoints;
	static GdkPoint on_points[MAX_POINTS];

	get_zoom_infos(  );
	field = CURRENT_FIELD;

	/*
	 * --- Redraw previous zoom area ---
	 */
	if ( prev_zoom_xstart != -1 )

	{
		gdk_draw_rectangle( pixmap_field, field_off_color, TRUE, prev_zoom_xstart,
		   prev_zoom_ystart, prev_zoom_width, prev_zoom_height );
		on_npoints = 0;
		for ( row = prev_zoom_ystart; row < prev_zoom_ystart + prev_zoom_height; row++ )

		{
			pw = &field[( row * life_bpl ) + ( prev_zoom_xstart / 8 )];
			for ( col = prev_zoom_xstart; col < prev_zoom_xstart + prev_zoom_width; col++ )

			{
				if ( *pw & mask[col % 8] )

				{
					on_points[on_npoints].x = col;
					on_points[on_npoints++].y = row;
				}
				if ( col % 8 == 7 )
					pw++;
			}
		}
		if ( on_npoints )
			gdk_draw_points( pixmap_field, field_on_color, on_points, on_npoints );
	}

	/*
	 * --- X-draw current zoom area ---
	 */
	gdk_draw_rectangle( pixmap_field, field_on_color, TRUE, zoom_xstart, zoom_ystart,
	   zoom_width, zoom_height );
	on_npoints = 0;
	for ( row = zoom_ystart; row < zoom_ystart + zoom_height; row++ )
	{
		pw = &field[( row * life_bpl ) + ( zoom_xstart / 8 )];
		for ( col = zoom_xstart; col < zoom_xstart + zoom_width; col++ )

		{
			if ( *pw & mask[col % 8] )

			{
				on_points[on_npoints].x = col;
				on_points[on_npoints++].y = row;
			}
			if ( col % 8 == 7 )
				pw++;
		}
	}
	if ( on_npoints )
		gdk_draw_points( pixmap_field, field_off_color, on_points, on_npoints );
	prev_zoom_xstart = zoom_xstart;
	prev_zoom_ystart = zoom_ystart;
	prev_zoom_width = zoom_width;
	prev_zoom_height = zoom_height;

}								// create_hand_field


void
redraw_pixmap_field( void )
{
	create_hand_field(  );
	gdk_draw_pixmap( fielddraw->window,
	   fielddraw->style->fg_gc[GTK_WIDGET_STATE( fielddraw )], pixmap_field, 0, 0, 0, 0,
	   config.life_width, config.life_height );
}								// redraw_pixmap_field


static gboolean
on_fielddraw_expose_event( GtkWidget * widget,
   GdkEventExpose * event,
   gpointer user_data )
{
#ifdef TRACE_EVENTS
	TRACE( "field: on_fielddraw_expose_event\n" );
#endif
	redraw_pixmap_field(  );
	return FALSE;
}								// on_fielddraw_expose_event


void
create_field( void )
{
	GtkWidget *field_viewport;
	GtkWidget *vbox2;
	GtkWidget *hseparator3;
	GtkWidget *table2;
	GtkWidget *label_gen;
	GtkWidget *label_pop;
	GtkWidget *label_birth;
	GtkWidget *label_death;
	GtkWidget *hbox5;

	field_wnd = gtk_window_new( GTK_WINDOW_TOPLEVEL );

	gtk_widget_set_usize( field_wnd, 300, 220 );
	gtk_signal_connect( GTK_OBJECT( field_wnd ), "configure_event",
	   GTK_SIGNAL_FUNC( on_field_configure_event ), NULL );
	gtk_window_set_title( GTK_WINDOW( field_wnd ), "Field of life" );
	gtk_window_set_policy( GTK_WINDOW( field_wnd ), TRUE, TRUE, FALSE );

	/*
	 * --- Connect signals for destruction --- 
	 */
	gtk_signal_connect( GTK_OBJECT( field_wnd ), "destroy",
	   GTK_SIGNAL_FUNC( gtk_widget_destroyed ), &field_wnd );
	gtk_signal_connect( GTK_OBJECT( field_wnd ), "delete-event", 
		GTK_SIGNAL_FUNC( close_app ), NULL );

	vbox2 = gtk_vbox_new( FALSE, 0 );
	gtk_widget_show( vbox2 );
	gtk_container_add( GTK_CONTAINER( field_wnd ), vbox2 );

	field_scrolledwnd = gtk_scrolled_window_new( NULL, NULL );
	gtk_widget_show( field_scrolledwnd );
	gtk_container_add( GTK_CONTAINER( vbox2 ), field_scrolledwnd );
	gtk_widget_set_usize( field_scrolledwnd, config.life_width, config.life_height );
	gtk_scrolled_window_set_policy( GTK_SCROLLED_WINDOW( field_scrolledwnd ),
	   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC );

	field_viewport = gtk_viewport_new( NULL, NULL );
	gtk_widget_show( field_viewport );
	gtk_container_add( GTK_CONTAINER( field_scrolledwnd ), field_viewport );
	gtk_widget_set_usize( field_viewport, config.life_width, config.life_height );

	fielddraw = gtk_drawing_area_new(  );
	gtk_widget_show( fielddraw );
	gtk_container_add( GTK_CONTAINER( field_viewport ), fielddraw );
	gtk_widget_set_usize( fielddraw, config.life_width, config.life_height );
	gtk_widget_set_events( fielddraw,
	   GDK_BUTTON_MOTION_MASK | GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK | GDK_KEY_PRESS_MASK );
	gtk_signal_connect( GTK_OBJECT( fielddraw ), "button_press_event",
	   GTK_SIGNAL_FUNC( on_fielddraw_button_press_event ), NULL );
	gtk_signal_connect( GTK_OBJECT( fielddraw ), "button_release_event",
	   GTK_SIGNAL_FUNC( on_fielddraw_button_release_event ), NULL );
	gtk_signal_connect( GTK_OBJECT( fielddraw ), "motion_notify_event",
	   GTK_SIGNAL_FUNC( on_fielddraw_motion_notify_event ), NULL );
	gtk_signal_connect( GTK_OBJECT( fielddraw ), "key_press_event",
	   GTK_SIGNAL_FUNC( on_fielddraw_key_press_event ), NULL );
	gtk_signal_connect( GTK_OBJECT( fielddraw ), "configure_event",
	   GTK_SIGNAL_FUNC( on_fielddraw_configure_event ), NULL );
	gtk_signal_connect( GTK_OBJECT( fielddraw ), "expose_event",
	   GTK_SIGNAL_FUNC( on_fielddraw_expose_event ), NULL );

	hseparator3 = gtk_hseparator_new(  );
	gtk_widget_show( hseparator3 );
	gtk_box_pack_start( GTK_BOX( vbox2 ), hseparator3, FALSE, FALSE, 3 );
	table2 = gtk_table_new( 2, 4, FALSE );

	gtk_widget_show( table2 );
	gtk_box_pack_start( GTK_BOX( vbox2 ), table2, FALSE, TRUE, 0 );
	label_gen = gtk_label_new( "Generation" );

	gtk_widget_show( label_gen );
	gtk_table_attach( GTK_TABLE( table2 ), label_gen, 0, 1, 0, 1,
	   ( GtkAttachOptions ) GTK_EXPAND | GTK_FILL, ( GtkAttachOptions ) GTK_EXPAND | GTK_FILL, 0, 0 );
	gtk_label_set_justify( GTK_LABEL( label_gen ), GTK_JUSTIFY_LEFT );
	gtk_misc_set_alignment( GTK_MISC( label_gen ), 0, 0.5 );
	gtk_misc_set_padding( GTK_MISC( label_gen ), 3, 0 );
	label_pop = gtk_label_new( "Population" );

	gtk_widget_show( label_pop );
	gtk_table_attach( GTK_TABLE( table2 ), label_pop, 2, 3, 0, 1,
	   ( GtkAttachOptions ) GTK_EXPAND | GTK_FILL, ( GtkAttachOptions ) GTK_EXPAND | GTK_FILL, 0, 0 );
	gtk_label_set_justify( GTK_LABEL( label_pop ), GTK_JUSTIFY_LEFT );
	gtk_misc_set_alignment( GTK_MISC( label_pop ), 0, 0.5 );
	gtk_misc_set_padding( GTK_MISC( label_pop ), 3, 0 );
	label_birth = gtk_label_new( "Birth" );

	gtk_widget_show( label_birth );
	gtk_table_attach( GTK_TABLE( table2 ), label_birth, 0, 1, 1, 2,
	   ( GtkAttachOptions ) GTK_EXPAND | GTK_FILL, ( GtkAttachOptions ) GTK_EXPAND | GTK_FILL, 0, 0 );
	gtk_label_set_justify( GTK_LABEL( label_birth ), GTK_JUSTIFY_LEFT );
	gtk_misc_set_alignment( GTK_MISC( label_birth ), 0, 0.5 );
	gtk_misc_set_padding( GTK_MISC( label_birth ), 3, 0 );
	label_death = gtk_label_new( "Death" );

	gtk_widget_show( label_death );
	gtk_table_attach( GTK_TABLE( table2 ), label_death, 2, 3, 1, 2,
	   ( GtkAttachOptions ) GTK_EXPAND | GTK_FILL, ( GtkAttachOptions ) GTK_EXPAND | GTK_FILL, 0, 0 );
	gtk_label_set_justify( GTK_LABEL( label_death ), GTK_JUSTIFY_LEFT );
	gtk_misc_set_alignment( GTK_MISC( label_death ), 0, 0.5 );
	gtk_misc_set_padding( GTK_MISC( label_death ), 3, 0 );
	info_gen = gtk_label_new( "" );

	gtk_widget_show( info_gen );
	gtk_table_attach( GTK_TABLE( table2 ), info_gen, 1, 2, 0, 1,
	   ( GtkAttachOptions ) GTK_EXPAND | GTK_FILL, ( GtkAttachOptions ) GTK_EXPAND | GTK_FILL, 0, 0 );
	gtk_label_set_justify( GTK_LABEL( info_gen ), GTK_JUSTIFY_LEFT );
	gtk_misc_set_alignment( GTK_MISC( info_gen ), 0, 0.5 );
	gtk_misc_set_padding( GTK_MISC( info_gen ), 3, 0 );
	info_birth = gtk_label_new( "" );

	gtk_widget_show( info_birth );
	gtk_table_attach( GTK_TABLE( table2 ), info_birth, 1, 2, 1, 2,
	   ( GtkAttachOptions ) GTK_EXPAND | GTK_FILL, ( GtkAttachOptions ) GTK_EXPAND | GTK_FILL, 0, 0 );
	gtk_label_set_justify( GTK_LABEL( info_birth ), GTK_JUSTIFY_LEFT );
	gtk_misc_set_alignment( GTK_MISC( info_birth ), 0, 0.5 );
	gtk_misc_set_padding( GTK_MISC( info_birth ), 3, 0 );
	info_pop = gtk_label_new( "" );

	gtk_widget_show( info_pop );
	gtk_table_attach( GTK_TABLE( table2 ), info_pop, 3, 4, 0, 1,
	   ( GtkAttachOptions ) GTK_EXPAND | GTK_FILL, ( GtkAttachOptions ) GTK_EXPAND | GTK_FILL, 0, 0 );
	gtk_label_set_justify( GTK_LABEL( info_pop ), GTK_JUSTIFY_LEFT );
	gtk_misc_set_alignment( GTK_MISC( info_pop ), 0, 0.5 );
	gtk_misc_set_padding( GTK_MISC( info_pop ), 3, 0 );
	info_death = gtk_label_new( "" );

	gtk_widget_show( info_death );
	gtk_table_attach( GTK_TABLE( table2 ), info_death, 3, 4, 1, 2,
	   ( GtkAttachOptions ) GTK_EXPAND | GTK_FILL, ( GtkAttachOptions ) GTK_EXPAND | GTK_FILL, 0, 0 );
	gtk_label_set_justify( GTK_LABEL( info_death ), GTK_JUSTIFY_LEFT );
	gtk_misc_set_alignment( GTK_MISC( info_death ), 0, 0.5 );
	gtk_misc_set_padding( GTK_MISC( info_death ), 3, 0 );
	hsep_stable = gtk_hseparator_new(  );

	gtk_widget_show( hsep_stable );
	gtk_box_pack_start( GTK_BOX( vbox2 ), hsep_stable, FALSE, TRUE, 0 );
	gtk_widget_hide( hsep_stable );
	hbox5 = gtk_hbox_new( FALSE, 0 );

	gtk_widget_show( hbox5 );
	gtk_box_pack_start( GTK_BOX( vbox2 ), hbox5, FALSE, TRUE, 0 );
	label_stable = gtk_label_new( "Generation stable:" );

	gtk_widget_show( label_stable );
	gtk_box_pack_start( GTK_BOX( hbox5 ), label_stable, TRUE, TRUE, 0 );
	gtk_label_set_justify( GTK_LABEL( label_stable ), GTK_JUSTIFY_LEFT );
	gtk_misc_set_padding( GTK_MISC( label_stable ), 8, 0 );
	gtk_widget_hide( label_stable );
	btn_stop = gtk_button_new_with_label( "Stop (Esc)" );

	gtk_widget_show( btn_stop );
	gtk_box_pack_start( GTK_BOX( vbox2 ), btn_stop, FALSE, FALSE, 0 );
	gtk_widget_set_usize( btn_stop, 31, -1 );
	gtk_signal_connect( GTK_OBJECT( btn_stop ), "clicked", GTK_SIGNAL_FUNC( on_stop_clicked ), NULL );
	gtk_widget_hide( btn_stop );
	gtk_widget_show( field_wnd );
	field_off_color = create_color( field_wnd, 0xC000, 0xC000, 0xC000 );
	field_on_color  = create_color( field_wnd, 0x0000, 0x0000, 0x0000 );

}								// create_field
