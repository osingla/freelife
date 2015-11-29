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

#define COMMON
#include "all.h"

void
allocate_fields( void )
{
	int n;

	if ( field1 )

	{
		free( field1 );
		free( field2 );
	}
	field1 = malloc( life_size );
	memset( field1, 0, life_size );
	field2 = malloc( life_size );
	memset( field2, 0, life_size );

	/*
        Generations kept to see if
    */
	max_nb_gen_kept = config.lifesavednb;
	gen_kept_popnb = calloc( max_nb_gen_kept, sizeof( int ) );
	gen_kept = calloc( max_nb_gen_kept, sizeof( UBYTE * ) );
	gen_kept_base = calloc( max_nb_gen_kept, life_size );
	for ( n = 0; n < max_nb_gen_kept; n++ )
		gen_kept[n] = &gen_kept_base[life_size * n];
	gen_kept_nb = 0;
	is_stability = FALSE;

	/*
        Generation kept in case of automatic/manual seeking
    */
	gen_start_kept_seek = malloc( life_size );
	gen_best_kept_seek = malloc( life_size );

	/*
        Generation 0 kept
    */
	gen0_kept = malloc( life_size );

	/*
        Graph data
    */
	graphdata = malloc( sizeof( GRAPHDATA ) * GRAPHDATA_ALLCD_SZ );
	graphdata_allcd = GRAPHDATA_ALLCD_SZ;

}								// allocate_fields


void
clear_life( int clean_maxnb_gen )
{

	memset( field1, 0, life_size );
	memset( field2, 0, life_size );
	life_gen = 0;
	life_pop = life_birth = life_death = life_stable = 0;
	gen_kept_nb = 0;
	gtk_widget_queue_draw( GTK_WIDGET( fielddraw ) );

	/*
        Set to TRUE while computing next generations (Shift-F2)
    */
	is_comp_generations = FALSE;
	gtk_widget_hide( hsep_stable );
	gtk_widget_hide( label_stable );
	center_zoom(  );
	show_infos(  );

	if ( clean_maxnb_gen )
		gtk_label_set_text( GTK_LABEL( zoom_maxgen ), "" );

}								// clear_life


static void
create_field_pixmap( void )
{
	pixmap_field = gdk_pixmap_new( field_wnd->window, config.life_width, config.life_height, -1 );
	gdk_draw_rectangle( pixmap_field, field_off_color, TRUE, 0, 0, config.life_width,
	   config.life_height );
}								// create_field_pixmap


static void
my_glog( const gchar * log_domain,
   GLogLevelFlags log_level,
   const gchar * message,
   gpointer user_data )
{

	if ( is_display_log )
		g_log_default_handler( log_domain, log_level, message, user_data );
		
}								// my_glog



int
main( int argc,
   char *argv[] )
{

	gtk_set_locale(  );
	gtk_init( &argc, &argv );

	/*
        This is done mainly to enable the debugger to put a breakpoint on these functions
    */
	is_display_log = FALSE;
	g_log_set_handler( "GLib",
	   ( GLogLevelFlags ) ( G_LOG_LEVEL_ERROR | G_LOG_LEVEL_CRITICAL | G_LOG_LEVEL_WARNING |
		  G_LOG_LEVEL_MESSAGE | G_LOG_LEVEL_INFO | G_LOG_LEVEL_DEBUG | G_LOG_FLAG_FATAL ),
	   my_glog, NULL );
	g_log_set_handler( "GLib-GObject",
	   ( GLogLevelFlags ) ( G_LOG_LEVEL_ERROR | G_LOG_LEVEL_CRITICAL | G_LOG_LEVEL_WARNING |
		  G_LOG_LEVEL_MESSAGE | G_LOG_LEVEL_INFO | G_LOG_LEVEL_DEBUG | G_LOG_FLAG_FATAL ),
	   my_glog, NULL );
	g_log_set_handler( "Gdk",
	   ( GLogLevelFlags ) ( G_LOG_LEVEL_ERROR | G_LOG_LEVEL_CRITICAL | G_LOG_LEVEL_WARNING |
		  G_LOG_LEVEL_MESSAGE | G_LOG_LEVEL_INFO | G_LOG_LEVEL_DEBUG | G_LOG_FLAG_FATAL ),
	   my_glog, NULL );
	g_log_set_handler( "Gtk",
	   ( GLogLevelFlags ) ( G_LOG_LEVEL_ERROR | G_LOG_LEVEL_CRITICAL | G_LOG_LEVEL_WARNING |
		  G_LOG_LEVEL_MESSAGE | G_LOG_LEVEL_INFO | G_LOG_LEVEL_DEBUG | G_LOG_FLAG_FATAL ),
	   my_glog, NULL );
	g_log_set_handler( NULL,
	   ( GLogLevelFlags ) ( G_LOG_LEVEL_ERROR | G_LOG_LEVEL_CRITICAL | G_LOG_LEVEL_WARNING |
		  G_LOG_LEVEL_MESSAGE | G_LOG_LEVEL_INFO | G_LOG_LEVEL_DEBUG | G_LOG_FLAG_FATAL ),
	   my_glog, NULL );

	default_config(  );
	life_bpl = config.life_width / 8;
	life_size = life_bpl * config.life_height;
	allocate_fields(  );
	create_field(  );
	create_zoom(  );
	create_field_pixmap(  );
	center_zoom(  );
	show_infos(  );

	gtk_main(  );

	return 0;
}								// main
