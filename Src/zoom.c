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

static GtkWidget *LifeCenterGeneration;
static GtkWidget *LifePrevGen;
static GtkWidget *LifeNextGen;
static GtkWidget *LifeNextGens;
static GtkWidget *LifeRestoreStartingGen;

gint
close_app( GtkWidget * widget,
   gpointer data )
{
	printf( " bye!\n" );

//  save_config();
	gtk_main_quit(  );
	return ( TRUE );
}								// close_app


inline static void
draw_zoom_cell_on( const int x,
   const int y )
{
/*
	gdk_draw_rectangle( pixmap_zoom, zoom_on_color, TRUE,
	   x + ( ZOOM_CELL_WIDTH - ZOOM_OFF_SZ ) / 2,
	   y + ( ZOOM_CELL_HEIGHT - ZOOM_OFF_SZ ) / 2, 
	   ZOOM_ON_SZ, ZOOM_ON_SZ );
*/
	gdk_draw_arc( pixmap_zoom, zoom_on_color, TRUE,
	   x + ( ZOOM_CELL_WIDTH - ZOOM_ON_SZ ) / 2,
	   y + ( ZOOM_CELL_HEIGHT - ZOOM_ON_SZ ) / 2, 
	   ZOOM_ON_SZ, ZOOM_ON_SZ, 
	   0, 360 * 64 );
}								// draw_zoom_cell_on


inline static void
draw_zoom_cell_off( const int x,
   const int y )
{
	gdk_draw_rectangle( pixmap_zoom, zoom_off_color, TRUE,
	   x + ( ZOOM_CELL_WIDTH - ZOOM_OFF_SZ ) / 2,
	   y + ( ZOOM_CELL_HEIGHT - ZOOM_OFF_SZ ) / 2, 
	   ZOOM_OFF_SZ, ZOOM_OFF_SZ );
}								// draw_zoom_cell_off


void
on_FileLoad_activate( GtkMenuItem * menuitem,
   gpointer user_data )
{

	/*
	 * Do nothing if life computation in progress
	 */
	if ( is_comp_generations )
		return;
}								// on_FileLoad_activate

void
on_FileSave_activate( GtkMenuItem * menuitem,
   gpointer user_data )
{

	/*
	 * Do nothing if life computation in progress
	 */
	if ( is_comp_generations )
		return;
}								// on_FileSave_activate

void
on_FileSaveText_activate( GtkMenuItem * menuitem,
   gpointer user_data )
{

	/*
	 * Do nothing if life computation in progress
	 */
	if ( is_comp_generations )
		return;
}								// on_FileSaveText_activate

void
on_FilePrint_activate( GtkMenuItem * menuitem,
   gpointer user_data )
{

	/*
	 * Do nothing if life computation in progress
	 */
	if ( is_comp_generations )
		return;
}								// on_FilePrint_activate

void
on_FileExit_activate( GtkMenuItem * menuitem,
   gpointer user_data )
{
	gtk_widget_destroy( zoom_wnd );
	gtk_widget_destroy( field_wnd );
}								// on_FileExit_activate

void
on_OptionsGrid_activate( GtkMenuItem * menuitem,
   gpointer user_data )
{
	if ( pixmap_zoom )
		gtk_widget_queue_draw( GTK_WIDGET( zoom_area ) );
}								// on_OptionsGrid_activate

void
on_OptionsSettings_activate( GtkMenuItem * menuitem,
   gpointer user_data )
{

	/*
	 * Do nothing if life computation in progress
	 */
	if ( is_comp_generations )
		return;
	create_settings(  );
}								// on_OptionsSettings_activate

void
on_LifeClear_activate( GtkMenuItem * menuitem,
   gpointer user_data )
{

	/*
	 * Do nothing if life computation in progress
	 */
	if ( is_comp_generations )
		return;
	clear_life( TRUE );
}								// on_LifeClear_activate

void
on_LifeCenterZoom_activate( GtkMenuItem * menuitem,
   gpointer user_data )
{
	center_zoom(  );
}								// on_LifeCenterZoom_activate

void
on_LifeCenterGeneration_activate( GtkMenuItem * menuitem,
   gpointer user_data )
{

	/*
	 * Do nothing if life computation in progress
	 */
	if ( is_comp_generations )
		return;
}								// on_LifeCenterGeneration_activate

void
on_FilePrevGen_activate( GtkMenuItem * menuitem,
   gpointer user_data )
{

	/*
	 * Do nothing if life computation in progress
	 */
	if ( is_comp_generations )
		return;
	restore_prev_gen(  );
}								// on_FilePrevGen_activate


#if 0
void
throw_away_events( GdkEvent * event )
{
	GdkEvent *next_event;

	printf( "xxx\n" );

	/*
	 * If there are any events pending then get the next one.
	 */
	next_event = gdk_event_peek(  );
	if ( next_event )

	{

		/*
		 * Throw both the peeked copy and the queued copy away 
		 */
		gdk_event_free( next_event );
		next_event = gdk_event_get(  );
		gdk_event_free( next_event );
	}
}								// throw_away_events
#endif						   /*  */


void
clear_pending_events( void )
{
	GdkEvent *next_event;

	gdk_flush(  );
	for ( ;; )

	{
		next_event = gdk_event_peek(  );
		if ( next_event )

		{

			/*
			 * Throw both the peeked copy and the queued copy away 
			 */
			gdk_event_free( next_event );
			next_event = gdk_event_get(  );
			gdk_event_free( next_event );
		}

		else
			break;
	}
}								// clear_pending_events


void
on_LifeNextGen_activate( GtkMenuItem * menuitem,
   gpointer user_data )
{

	/*
	 * Do nothing if life computation in progress
	 */
	if ( is_comp_generations )
		return;
	gdk_flush(  );
	if ( !gtk_events_pending(  ) )
	{
		clear_pending_events(  );
		life_gen++;
		compute_gen(  );
		gdk_flush(  );
	}
}								// on_LifeNextGen_activate


void
on_FileNextGens_activate( GtkMenuItem * menuitem,
   gpointer user_data )
{

	/*
	 * Do nothing if life computation in progress
	 */
	if ( is_comp_generations )
		return;
	compute_generations(  );
	gdk_flush(  );
}								// on_FileNextGens_activate


void
on_LifeRestoreStartingGen_activate( GtkMenuItem * menuitem,
   gpointer user_data )
{

	/*
	 * Do nothing if life computation in progress
	 */
	if ( is_comp_generations )
		return;
	restore_gen0(  );
}								// on_LifeRestoreStartingGen_activate


void
on_LifeStats_activate( GtkMenuItem * menuitem,
   gpointer user_data )
{

	/*
	 * Do nothing if life computation in progress
	 */
	if ( is_comp_generations )
		return;
	fprintf( stderr, "Not yet implemented\n" );
}								// on_LifeStats_activate

void
on_LifeGraph_activate( GtkMenuItem * menuitem,
   gpointer user_data )
{

	/*
	 * Do nothing if life computation in progress
	 */
	if ( is_comp_generations )
		return;
	fprintf( stderr, "Not yet implemented\n" );
}								// on_LifeGraph_activate

void
on_LifeInterGen_7_172_activate( GtkMenuItem * menuitem,
   gpointer user_data )
{

	/*
	 * Do nothing if life computation in progress
	 */
	if ( is_comp_generations )
		return;

	/*
        Create a simple generation
    */
	clear_life( TRUE );
	field1[511 * life_bpl + 63] = 0x38;
	field1[512 * life_bpl + 63] = 0x24;
	field1[513 * life_bpl + 63] = 0x22;
	life_gen = 0;
	life_pop = 7;
	life_birth = life_death = life_stable = 0;
	gtk_widget_queue_draw( GTK_WIDGET( fielddraw ) );

}								// on_LifeInterGen_7_172_activate


static void
build_random_population( int clean_maxnb_gen )
{
	clear_life( clean_maxnb_gen );
	int nb = GENRND( rndgen.nbmin, rndgen.nbmax );
	for ( life_pop = 0; life_pop < nb; )
	{
		int x = GENRND( rndgen.x, rndgen.x + rndgen.w - 1);
		int y = GENRND( rndgen.y, rndgen.y + rndgen.h - 1);
		int a = ( y * life_bpl ) + ( x / 8 );
		if ( !( field1[a] & mask[x % 8] ) )
		{
			field1[a] |= mask[x % 8];
			life_pop++;
		}						// if
	}							// for (life_pop)
	life_gen = 0;
	life_birth = life_death = life_stable = 0;
	gtk_widget_queue_draw( GTK_WIDGET( fielddraw ) );
}								// build_random_population


void
on_LifeRandomGen_activate( GtkMenuItem * menuitem,
   gpointer user_data )
{

	/*
	 * Do nothing if life computation in progress
	 */
	if ( is_comp_generations )
		return;

	/*
        Create a simple generation
    */
	build_random_population( TRUE );

}								// on_LifeRandomGen_activate


void
on_LifeSeekInterGen_activate( GtkMenuItem * menuitem,
   gpointer user_data )
{

	/*
	 * Do nothing if life computation in progress
	 */
	if ( is_comp_generations )
		return;

	/*
        Create a simple generation
    */
	UBYTE *maxgen_kept = malloc( life_size );
	int max_life_gen = 0;
	end_comp_generations = FALSE;
	while ( !end_comp_generations )
	{
		build_random_population( FALSE );
		compute_generations(  );
		if ( life_gen > max_life_gen )
		{
			max_life_gen = life_gen;
			memmove( maxgen_kept, gen0_kept, life_size );

			/*
				Show current position
			*/
			char buff[80];
			sprintf( buff, "Max gen = %d (pop=%d)", max_life_gen, life_pop );
			gtk_label_set_text( GTK_LABEL( zoom_maxgen ), buff );

		}
		gdk_flush(  );
	}

	memmove( gen0_kept, maxgen_kept, life_size );
	free( maxgen_kept );

}								// on_LifeSeekInterGen_activate


void
on_RulesStd_activate( GtkMenuItem * menuitem,
   gpointer user_data )
{

	/*
	 * Do nothing if life computation in progress
	 */
	if ( is_comp_generations )
		return;
	fprintf( stderr, "Not yet implemented\n" );
}								// on_RulesStd_activate

void
on_RuleDefine_activate( GtkMenuItem * menuitem,
   gpointer user_data )
{

	/*
	 * Do nothing if life computation in progress
	 */
	if ( is_comp_generations )
		return;
	fprintf( stderr, "Not yet implemented\n" );
}								// on_RuleDefine_activate

void
on_RuleLoad_activate( GtkMenuItem * menuitem,
   gpointer user_data )
{

	/*
	 * Do nothing if life computation in progress
	 */
	if ( is_comp_generations )
		return;
	fprintf( stderr, "Not yet implemented\n" );
}								// on_RuleLoad_activate

void
on_RuleSave_activate( GtkMenuItem * menuitem,
   gpointer user_data )
{

	/*
	 * Do nothing if life computation in progress
	 */
	if ( is_comp_generations )
		return;
	fprintf( stderr, "Not yet implemented\n" );
}								// on_RuleSave_activate

void
on_HelpRules_activate( GtkMenuItem * menuitem,
   gpointer user_data )
{

	/*
	 * Do nothing if life computation in progress
	 */
	if ( is_comp_generations )
		return;
	fprintf( stderr, "Not yet implemented\n" );
}								// on_HelpRules_activate

void
on_HelpAbout_activate( GtkMenuItem * menuitem,
   gpointer user_data )
{

	/*
	 * Do nothing if life computation in progress
	 */
	if ( is_comp_generations )
		return;
	fprintf( stderr, "Not yet implemented\n" );
}								// on_HelpAbout_activate


static gboolean
on_zoom_area_button_press_event( GtkWidget * widget,
   GdkEventButton * event,
   gpointer user_data )
{
	int x,
	  y;

	UBYTE *field;
	int prev_state,
	  state;

	/*
	 * Make sure it's a button event
	 */
	if ( event->type != GDK_BUTTON_PRESS )
		return FALSE;

	/*
	 * Do nothing if life computation in progress
	 */
	if ( is_comp_generations )
		return FALSE;

	/*
	 * Convert mouse position to board position [1..8]
	 */
	x = ( int ) event->x / ZOOM_CELL_WIDTH + zoom_xstart;
	y = ( int ) event->y / ZOOM_CELL_HEIGHT + zoom_ystart;
	if ( ( x < 0 ) || ( x >= config.life_width ) || ( y < 0 ) || ( y >= config.life_height ) )
		return FALSE;

	/*
	 * Update zoom area
	 */
	field = CURRENT_FIELD;
	prev_state = ( field[( y * life_bpl ) + ( x / 8 )] & mask[x % 8] );
	switch ( event->button )
	{
		case 1:
			field[( y * life_bpl ) + ( x / 8 )] ^= mask[x % 8];
			break;
		case 2:
			field[( y * life_bpl ) + ( x / 8 )] |= mask[x % 8];
			break;
		case 3:
			field[( y * life_bpl ) + ( x / 8 )] &= ~mask[x % 8];
			break;
	}

	/*
	 * Update population number
	 */
	state = ( field[( y * life_bpl ) + ( x / 8 )] & mask[x % 8] );
	if ( !prev_state && state )
		life_pop++;

	else if ( prev_state && !state )
		life_pop--;
	show_life_pop(  );

	/*
	 * Ask to Redraw both zoom and field
	 */
	gtk_widget_queue_draw( GTK_WIDGET( fielddraw ) );
	gtk_widget_queue_draw( GTK_WIDGET( zoom_area ) );

	return FALSE;
}								// on_zoom_area_button_press_event


static gboolean
on_zoom_area_motion_notify_event( GtkWidget * widget,
   GdkEventMotion * event,
   gpointer user_data )
{
	int x,
	  y;
	static int prev_x = -1,
	  prev_y = -1;

	UBYTE *field;
	int prev_state,
	  state;

	/*
	 * Do nothing if life computation in progress
	 */
	if ( is_comp_generations )
		return FALSE;

	/*
	 * Convert mouse position to board position [1..8]
	 */
	x = ( int ) event->x / ZOOM_CELL_WIDTH + zoom_xstart;
	y = ( int ) event->y / ZOOM_CELL_HEIGHT + zoom_ystart;
	if ( ( x == prev_x ) && ( y == prev_y ) )
		return TRUE;
	if ( ( x < 0 ) || ( x >= config.life_width ) || ( y < 0 ) || ( y >= config.life_height ) )
		return FALSE;

#ifdef TRACE_EVENTS
	TRACE( "zoom: on_zoom_area_motion_notify_event: state=%X\n", event->state );
#endif

	/*
		Show current position
	*/
	char buff[80];
	sprintf( buff, "x,y = %d , %d", x, y );
	gtk_label_set_text( GTK_LABEL( zoom_xy ), buff );

	/*
	 * Update zoom area
	 */
	field = CURRENT_FIELD;
	prev_state = ( field[( y * life_bpl ) + ( x / 8 )] & mask[x % 8] );
	int which_button = 0;
	if ( event->state & GDK_BUTTON1_MASK )
		which_button = 1;
	else if ( event->state & GDK_BUTTON2_MASK )
		which_button = 2;
	else if ( event->state & GDK_BUTTON3_MASK )
		which_button = 3;
	switch ( which_button )
	{
		case 1:
			field[( y * life_bpl ) + ( x / 8 )] ^= mask[x % 8];
			break;
		case 2:
			field[( y * life_bpl ) + ( x / 8 )] |= mask[x % 8];
			break;
		case 3:
			field[( y * life_bpl ) + ( x / 8 )] &= ~mask[x % 8];
			break;
	}
	prev_x = x;
	prev_y = y;

	/*
	 * Update population number
	 */
	state = ( field[( y * life_bpl ) + ( x / 8 )] & mask[x % 8] );
	if ( !prev_state && state )
		life_pop++;

	else if ( prev_state && !state )
		life_pop--;
	show_life_pop(  );

	/*
	 * Ask to Redraw bot zoom and field
	 */
	gtk_widget_queue_draw( GTK_WIDGET( fielddraw ) );
	gtk_widget_queue_draw( GTK_WIDGET( zoom_area ) );

	return FALSE;
}								// on_zoom_area_motion_notify_event


void
get_zoom_infos( void )
{
	GtkAdjustment *hadj,
	 *vadj;

	hadj = gtk_scrolled_window_get_hadjustment( GTK_SCROLLED_WINDOW( zoom_scrolledwindow ) );
	zoom_xstart = hadj->value;
	vadj = gtk_scrolled_window_get_vadjustment( GTK_SCROLLED_WINDOW( zoom_scrolledwindow ) );
	zoom_ystart = vadj->value;

	zoom_width  = zoom_wnd->allocation.width / ZOOM_CELL_WIDTH;
	zoom_height = zoom_wnd->allocation.height / ZOOM_CELL_HEIGHT;

}								// get_zoom_infos


static gboolean
on_zoom_area_configure_event( GtkWidget * widget,
   GdkEventConfigure * event,
   gpointer user_data )
{
#ifdef TRACE_EVENTS
	TRACE( "zoom: on_zoom_area_configure_event\n" );
#endif
	if ( pixmap_zoom )
		gdk_pixmap_unref( pixmap_zoom );
	pixmap_zoom =
	   gdk_pixmap_new( zoom_scrolledwindow->window, zoom_scrolledwindow->allocation.width,
	   zoom_scrolledwindow->allocation.height, -1 );
	get_zoom_infos(  );

	return FALSE;

}								// on_zoom_area_configure_event


int
redraw_pixmap_zoom( void )
{
	UBYTE *field,
	 *pw;
	int row,
	  col;
	int x,
	  y;
	int grid;
	int pop;
#ifdef SHOW_REDRAW_TIME
	double t0;
	static int cnt=0;
#endif

#ifdef SHOW_REDRAW_TIME
	t0 = now(  );
#endif

	get_zoom_infos(  );
	field = CURRENT_FIELD;
	grid = is_grid(  );
	gdk_draw_rectangle( pixmap_zoom, zoom_none_color, TRUE, 0, 0,
	   zoom_scrolledwindow->allocation.width, zoom_scrolledwindow->allocation.height );
	pop = 0;
	for ( y = 0, row = zoom_ystart; 
		  row < zoom_ystart + zoom_height; 
		  row++, y += ZOOM_CELL_HEIGHT )
	{
		pw = &field[( row * life_bpl ) + ( zoom_xstart / 8 )];
		for ( x = 0, col = zoom_xstart; 
			  col < zoom_xstart + zoom_width; 
			  col++, x += ZOOM_CELL_WIDTH )

		{
			if ( *pw & mask[col % 8] )
			{
				draw_zoom_cell_on( x, y );
				pop++;
			}
			else if ( grid )
			{
				draw_zoom_cell_off( x, y );
			}
			if ( col % 8 == 7 )
				pw++;
		}						// for (x)
	}							// for (y)

	gdk_draw_drawable( zoom_area->window,
	   zoom_area->style->fg_gc[GTK_WIDGET_STATE( zoom_area )], pixmap_zoom, 
	   0, 0, 0, 0,
	   zoom_scrolledwindow->allocation.width, zoom_scrolledwindow->allocation.height );

#ifdef SHOW_REDRAW_TIME
	{
		char tmp[100];
		double t1,
		  d;

		t1 = now(  );
		d = t1 - t0;
		sprintf( tmp, "%d - Redraw display time: %.0f microsec",
		   ++cnt, d );
		gtk_label_set_text( GTK_LABEL( wgt_label_redrawtime ), tmp );
	}
#endif

	return pop;
}								// redraw_pixmap_zoom


static gboolean
on_zoom_area_expose_event( GtkWidget * widget,
   GdkEventExpose * event,
   gpointer user_data )
{
#ifdef TRACE_EVENTS
	TRACE( "zoom: on_zoom_area_expose_event\n" );
#endif
	redraw_pixmap_zoom(  );
	return FALSE;
}								// on_zoom_area_expose_event


static gboolean
on_zoom_scrolledwindow_event( GtkWidget * widget,
   GdkEvent * event,
   gpointer user_data )
{
	get_zoom_infos(  );
	gtk_widget_queue_draw( GTK_WIDGET( zoom_area ) );
	gtk_widget_queue_draw( GTK_WIDGET( fielddraw ) );
	return FALSE;
}								// on_zoom_scrolledwindow_event


static void
create_menu_btn( GtkWidget * wgt_menubar,
   GtkWidget ** wgt_menubtn,
   GtkWidget ** wgt_menu,
   char *label,
   int side,
   void ( *pcb_activate ) ( GtkMenuItem *,
	  gpointer ) )
{
	*wgt_menubtn = gtk_menu_item_new_with_label( label );
	gtk_widget_show( *wgt_menubtn );
	gtk_container_add( GTK_CONTAINER( wgt_menubar ), *wgt_menubtn );
	switch ( side )

	{
		case GTK_SIDE_LEFT:
			break;
		case GTK_SIDE_RIGHT:
			gtk_menu_item_right_justify( GTK_MENU_ITEM( *wgt_menubtn ) );
			break;
		default:
			assert( 0 );
	}							// switch
	if ( pcb_activate != NULL )
		g_signal_connect( G_OBJECT( *wgt_menubtn ), "activate", G_CALLBACK( pcb_activate ), NULL );
	*wgt_menu = gtk_menu_new(  );
	gtk_menu_item_set_submenu( GTK_MENU_ITEM( *wgt_menubtn ), *wgt_menu );
}								// create_menu_btn

GtkWidget *
create_menu_item( GtkWidget * wgt_menu,
   char *label,
   char *xpm[],
   int sensitive,
   int acc_key,
   int acc_control,
   GCallback cb,
   gpointer user_data )
{
	GtkWidget *wgt_menu_item;
	GtkAccelGroup *wgt_accel_group;

	wgt_menu_item = gtk_menu_item_new_with_label( label );
	gtk_widget_set_sensitive( wgt_menu_item, sensitive );
	gtk_widget_show( wgt_menu_item );
	gtk_container_add( GTK_CONTAINER( wgt_menu ), wgt_menu_item );
	g_signal_connect( G_OBJECT( wgt_menu_item ), "activate", G_CALLBACK( cb ), user_data );
	if ( acc_key != 0 )

	{
		wgt_accel_group = gtk_accel_group_new(  );

//      gtk_window_add_accel_group( GTK_WINDOW( wgt_wnd_tree ), wgt_accel_group );
		gtk_widget_add_accelerator( wgt_menu_item, "activate", wgt_accel_group, acc_key,
		   acc_control, GTK_ACCEL_VISIBLE );
	}
	return wgt_menu_item;
}								// create_menu_item


void
create_zoom( void )
{
	GtkWidget *vbox1;
	GtkWidget *main_menu;
	GtkWidget *File;
	GtkWidget *File_menu;
	GtkWidget *FileLoad;
	GtkWidget *FileSave;
	GtkWidget *FileSaveText;
	GtkWidget *separator1;
	GtkWidget *FilePrint;
	GtkWidget *separator2;
	GtkWidget *FileExit;
	GtkWidget *Options;
	GtkWidget *Options_menu;
	GtkWidget *separator3;
	GtkWidget *OptionsSettings;
	GtkWidget *Life;
	GtkWidget *Life_menu;
	GtkWidget *LifeClear;
	GtkWidget *separator4;
	GtkWidget *LifeCenterZoom;
	GtkWidget *separator5;
	GtkWidget *separator6;
	GtkWidget *separator7;
	GtkWidget *LifeStats;
	GtkWidget *LifeGraph;
	GtkWidget *separator8;
	GtkWidget *LifeInterGen;
	GtkWidget *LifeRandomGen;
	GtkWidget *LifeSeekInterGen;
	GtkWidget *Rules;
	GtkWidget *Rules_menu;
	GtkWidget *RulesStd;
	GtkWidget *separator9;
	GtkWidget *RuleDefine;
	GtkWidget *separator10;
	GtkWidget *RuleLoad;
	GtkWidget *RuleSave;
	GtkWidget *Help;
	GtkWidget *Help_menu;
	GtkWidget *HelpRules;
	GtkWidget *separator11;
	GtkWidget *HelpAbout;
	GtkWidget *hseparator2;
	GtkWidget *table1;
	GtkWidget *label5;
	GtkWidget *label8;
	GtkWidget *label9;
	GtkWidget *label3;
	GtkWidget *label2;
	GtkWidget *label4;
	GtkWidget *label6;
	GtkWidget *label7;
	GtkAccelGroup *accel_group;
	GtkAdjustment *hadj,
	 *vadj;
	GtkWidget *wgt_menubtn_arrange_now,
	 *wgt_menu_arrange_now;

	zoom_wnd = gtk_window_new( GTK_WINDOW_TOPLEVEL );
	gtk_signal_connect( GTK_OBJECT( zoom_wnd ), "destroy",
	   GTK_SIGNAL_FUNC( gtk_widget_destroyed ), &zoom_wnd );
	gtk_signal_connect( GTK_OBJECT( zoom_wnd ), "delete-event", 
	   GTK_SIGNAL_FUNC( close_app ), NULL );

	gtk_window_set_title( GTK_WINDOW( zoom_wnd ), "Zoom of Life" );
	gtk_widget_set_usize( zoom_wnd, 640, 480 );
	gtk_window_set_policy( GTK_WINDOW( zoom_wnd ), TRUE, TRUE, FALSE );
	vbox1 = gtk_vbox_new( FALSE, 0 );

	gtk_widget_show( vbox1 );
	gtk_container_add( GTK_CONTAINER( zoom_wnd ), vbox1 );
	main_menu = gtk_menu_bar_new(  );

	gtk_widget_show( main_menu );
	gtk_box_pack_start( GTK_BOX( vbox1 ), main_menu, FALSE, TRUE, 0 );
	File = gtk_menu_item_new_with_label( "File" );

	gtk_widget_show( File );
	gtk_container_add( GTK_CONTAINER( main_menu ), File );
	File_menu = gtk_menu_new(  );

	gtk_menu_item_set_submenu( GTK_MENU_ITEM( File ), File_menu );
	FileLoad = gtk_menu_item_new_with_label( "Load" );

	gtk_widget_show( FileLoad );
	gtk_container_add( GTK_CONTAINER( File_menu ), FileLoad );
	gtk_signal_connect( GTK_OBJECT( FileLoad ), "activate",
	   GTK_SIGNAL_FUNC( on_FileLoad_activate ), NULL );
	accel_group = gtk_accel_group_new(  );
	gtk_window_add_accel_group( GTK_WINDOW( zoom_wnd ), accel_group );
	gtk_widget_add_accelerator( FileLoad, "activate", accel_group, GDK_L,
	   GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE );
	FileSave = gtk_menu_item_new_with_label( "Save" );

	gtk_widget_show( FileSave );
	gtk_container_add( GTK_CONTAINER( File_menu ), FileSave );
	gtk_signal_connect( GTK_OBJECT( FileSave ), "activate",
	   GTK_SIGNAL_FUNC( on_FileSave_activate ), NULL );
	gtk_widget_add_accelerator( FileSave, "activate", accel_group, GDK_S,
	   GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE );
	FileSaveText = gtk_menu_item_new_with_label( "Save as Text file" );

	gtk_widget_show( FileSaveText );
	gtk_container_add( GTK_CONTAINER( File_menu ), FileSaveText );
	gtk_signal_connect( GTK_OBJECT( FileSaveText ), "activate",
	   GTK_SIGNAL_FUNC( on_FileSaveText_activate ), NULL );
	separator1 = gtk_menu_item_new(  );

	gtk_widget_show( separator1 );
	gtk_container_add( GTK_CONTAINER( File_menu ), separator1 );
	FilePrint = gtk_menu_item_new_with_label( "Print" );

	gtk_widget_show( FilePrint );
	gtk_container_add( GTK_CONTAINER( File_menu ), FilePrint );
	gtk_signal_connect( GTK_OBJECT( FilePrint ), "activate",
	   GTK_SIGNAL_FUNC( on_FilePrint_activate ), NULL );
	gtk_widget_add_accelerator( FilePrint, "activate", accel_group, GDK_P,
	   GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE );
	separator2 = gtk_menu_item_new(  );

	gtk_widget_show( separator2 );
	gtk_container_add( GTK_CONTAINER( File_menu ), separator2 );
	FileExit = gtk_menu_item_new_with_label( "Exit" );

	gtk_widget_show( FileExit );
	gtk_container_add( GTK_CONTAINER( File_menu ), FileExit );
	gtk_signal_connect( GTK_OBJECT( FileExit ), "activate",
	   GTK_SIGNAL_FUNC( on_FileExit_activate ), NULL );
	gtk_widget_add_accelerator( FileExit, "activate", accel_group, GDK_X,
	   GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE );
	Options = gtk_menu_item_new_with_label( "Options" );

	gtk_widget_show( Options );
	gtk_container_add( GTK_CONTAINER( main_menu ), Options );
	Options_menu = gtk_menu_new(  );

	gtk_menu_item_set_submenu( GTK_MENU_ITEM( Options ), Options_menu );
	menu_OptionsGrid = gtk_check_menu_item_new_with_label( "Grid" );

	gtk_widget_show( menu_OptionsGrid );
	gtk_container_add( GTK_CONTAINER( Options_menu ), menu_OptionsGrid );
	gtk_signal_connect( GTK_OBJECT( menu_OptionsGrid ), "activate",
	   GTK_SIGNAL_FUNC( on_OptionsGrid_activate ), NULL );
	gtk_widget_add_accelerator( menu_OptionsGrid, "activate", accel_group, GDK_G,
	   GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE );
	gtk_check_menu_item_set_active( GTK_CHECK_MENU_ITEM( menu_OptionsGrid ), TRUE );
	separator3 = gtk_menu_item_new(  );

	gtk_widget_show( separator3 );
	gtk_container_add( GTK_CONTAINER( Options_menu ), separator3 );
	OptionsSettings = gtk_menu_item_new_with_label( "Settings" );

	gtk_widget_show( OptionsSettings );
	gtk_container_add( GTK_CONTAINER( Options_menu ), OptionsSettings );
	gtk_signal_connect( GTK_OBJECT( OptionsSettings ), "activate",
	   GTK_SIGNAL_FUNC( on_OptionsSettings_activate ), NULL );
	gtk_widget_add_accelerator( OptionsSettings, "activate", accel_group, GDK_T,
	   GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE );
	Life = gtk_menu_item_new_with_label( "Life" );

	gtk_widget_show( Life );
	gtk_container_add( GTK_CONTAINER( main_menu ), Life );
	Life_menu = gtk_menu_new(  );

	gtk_menu_item_set_submenu( GTK_MENU_ITEM( Life ), Life_menu );
	LifeClear = gtk_menu_item_new_with_label( "Clear field" );

	gtk_widget_show( LifeClear );
	gtk_container_add( GTK_CONTAINER( Life_menu ), LifeClear );
	gtk_signal_connect( GTK_OBJECT( LifeClear ), "activate",
	   GTK_SIGNAL_FUNC( on_LifeClear_activate ), NULL );
	gtk_widget_add_accelerator( LifeClear, "activate", accel_group, GDK_F10,
	   GDK_SHIFT_MASK, GTK_ACCEL_VISIBLE );
	separator4 = gtk_menu_item_new(  );

	gtk_widget_show( separator4 );
	gtk_container_add( GTK_CONTAINER( Life_menu ), separator4 );
	LifeCenterZoom = gtk_menu_item_new_with_label( "Center zoom" );

	gtk_widget_show( LifeCenterZoom );
	gtk_container_add( GTK_CONTAINER( Life_menu ), LifeCenterZoom );
	gtk_signal_connect( GTK_OBJECT( LifeCenterZoom ), "activate",
	   GTK_SIGNAL_FUNC( on_LifeCenterZoom_activate ), NULL );
	gtk_widget_add_accelerator( LifeCenterZoom, "activate", accel_group, GDK_F5, 0, GTK_ACCEL_VISIBLE );
	LifeCenterGeneration = gtk_menu_item_new_with_label( "Center Generation" );

	gtk_widget_show( LifeCenterGeneration );
	gtk_container_add( GTK_CONTAINER( Life_menu ), LifeCenterGeneration );
	gtk_signal_connect( GTK_OBJECT( LifeCenterGeneration ), "activate",
	   GTK_SIGNAL_FUNC( on_LifeCenterGeneration_activate ), NULL );
	gtk_widget_add_accelerator( LifeCenterGeneration, "activate", accel_group, GDK_F5,
	   GDK_SHIFT_MASK, GTK_ACCEL_VISIBLE );
	separator5 = gtk_menu_item_new(  );

	gtk_widget_show( separator5 );
	gtk_container_add( GTK_CONTAINER( Life_menu ), separator5 );
	LifePrevGen = gtk_menu_item_new_with_label( "Previous generation" );

	gtk_widget_show( LifePrevGen );
	gtk_container_add( GTK_CONTAINER( Life_menu ), LifePrevGen );
	gtk_signal_connect( GTK_OBJECT( LifePrevGen ), "activate",
	   GTK_SIGNAL_FUNC( on_FilePrevGen_activate ), NULL );
	gtk_widget_add_accelerator( LifePrevGen, "activate", accel_group, GDK_F2, 0, GTK_ACCEL_VISIBLE );
	LifeNextGen = gtk_menu_item_new_with_label( "Next generation" );

	gtk_widget_show( LifeNextGen );
	gtk_container_add( GTK_CONTAINER( Life_menu ), LifeNextGen );
	gtk_signal_connect( GTK_OBJECT( LifeNextGen ), "activate",
	   GTK_SIGNAL_FUNC( on_LifeNextGen_activate ), NULL );
	gtk_widget_add_accelerator( LifeNextGen, "activate", accel_group, GDK_F3, 0, GTK_ACCEL_VISIBLE );
	LifeNextGens = gtk_menu_item_new_with_label( "Next generations" );

	gtk_widget_show( LifeNextGens );
	gtk_container_add( GTK_CONTAINER( Life_menu ), LifeNextGens );
	gtk_signal_connect( GTK_OBJECT( LifeNextGens ), "activate",
	   GTK_SIGNAL_FUNC( on_FileNextGens_activate ), NULL );
	gtk_widget_add_accelerator( LifeNextGens, "activate", accel_group, GDK_F3,
	   GDK_SHIFT_MASK, GTK_ACCEL_VISIBLE );
	separator6 = gtk_menu_item_new(  );

	gtk_widget_show( separator6 );
	gtk_container_add( GTK_CONTAINER( Life_menu ), separator6 );
	LifeRestoreStartingGen = gtk_menu_item_new_with_label( "Restore starting generation" );

	gtk_widget_show( LifeRestoreStartingGen );
	gtk_container_add( GTK_CONTAINER( Life_menu ), LifeRestoreStartingGen );
	gtk_signal_connect( GTK_OBJECT( LifeRestoreStartingGen ), "activate",
	   GTK_SIGNAL_FUNC( on_LifeRestoreStartingGen_activate ), NULL );
	gtk_widget_add_accelerator( LifeRestoreStartingGen, "activate", accel_group, GDK_F9,
	   GDK_SHIFT_MASK, GTK_ACCEL_VISIBLE );
	separator7 = gtk_menu_item_new(  );

	gtk_widget_show( separator7 );
	gtk_container_add( GTK_CONTAINER( Life_menu ), separator7 );
	LifeStats = gtk_menu_item_new_with_label( "Statistics" );

	gtk_widget_show( LifeStats );
	gtk_container_add( GTK_CONTAINER( Life_menu ), LifeStats );
	gtk_signal_connect( GTK_OBJECT( LifeStats ), "activate",
	   GTK_SIGNAL_FUNC( on_LifeStats_activate ), NULL );
	gtk_widget_add_accelerator( LifeStats, "activate", accel_group, GDK_F4, 0, GTK_ACCEL_VISIBLE );
	LifeGraph = gtk_menu_item_new_with_label( "Graphics" );

	gtk_widget_show( LifeGraph );
	gtk_container_add( GTK_CONTAINER( Life_menu ), LifeGraph );
	gtk_signal_connect( GTK_OBJECT( LifeGraph ), "activate",
	   GTK_SIGNAL_FUNC( on_LifeGraph_activate ), NULL );
	gtk_widget_add_accelerator( LifeGraph, "activate", accel_group, GDK_F5, 0, GTK_ACCEL_VISIBLE );
	separator8 = gtk_menu_item_new(  );

	gtk_widget_show( separator8 );
	gtk_container_add( GTK_CONTAINER( Life_menu ), separator8 );

	LifeRandomGen = gtk_menu_item_new_with_label( "Random generation" );
	gtk_widget_show( LifeRandomGen );
	gtk_container_add( GTK_CONTAINER( Life_menu ), LifeRandomGen );
	gtk_signal_connect( GTK_OBJECT( LifeRandomGen ), "activate",
	   GTK_SIGNAL_FUNC( on_LifeRandomGen_activate ), NULL );
	gtk_widget_add_accelerator( LifeRandomGen, "activate", accel_group, GDK_F6, 0, GTK_ACCEL_VISIBLE );

	create_menu_btn( Life_menu, &wgt_menubtn_arrange_now, &wgt_menu_arrange_now,
	   "Interesting generations", GTK_SIDE_LEFT, NULL );
	LifeInterGen =
	   create_menu_item( wgt_menu_arrange_now, "7-172", NULL, TRUE, GDK_L,
	   GDK_CONTROL_MASK | GDK_SHIFT_MASK, G_CALLBACK( on_LifeInterGen_7_172_activate ), NULL );

	LifeSeekInterGen = gtk_menu_item_new_with_label( "Seek interestring generations" );
	gtk_widget_show( LifeSeekInterGen );
	gtk_container_add( GTK_CONTAINER( Life_menu ), LifeSeekInterGen );
	gtk_signal_connect( GTK_OBJECT( LifeSeekInterGen ), "activate",
	   GTK_SIGNAL_FUNC( on_LifeSeekInterGen_activate ), NULL );
	gtk_widget_add_accelerator( LifeSeekInterGen, "activate", accel_group, GDK_F7, 0, GTK_ACCEL_VISIBLE );

	Rules = gtk_menu_item_new_with_label( "Rules" );
	gtk_widget_show( Rules );
	gtk_container_add( GTK_CONTAINER( main_menu ), Rules );
	Rules_menu = gtk_menu_new(  );

	gtk_menu_item_set_submenu( GTK_MENU_ITEM( Rules ), Rules_menu );
	RulesStd = gtk_menu_item_new_with_label( "Standard rules" );

	gtk_widget_show( RulesStd );
	gtk_container_add( GTK_CONTAINER( Rules_menu ), RulesStd );
	gtk_signal_connect( GTK_OBJECT( RulesStd ), "activate",
	   GTK_SIGNAL_FUNC( on_RulesStd_activate ), NULL );
	separator9 = gtk_menu_item_new(  );

	gtk_widget_show( separator9 );
	gtk_container_add( GTK_CONTAINER( Rules_menu ), separator9 );
	RuleDefine = gtk_menu_item_new_with_label( "Define a new rule" );

	gtk_widget_show( RuleDefine );
	gtk_container_add( GTK_CONTAINER( Rules_menu ), RuleDefine );
	gtk_signal_connect( GTK_OBJECT( RuleDefine ), "activate",
	   GTK_SIGNAL_FUNC( on_RuleDefine_activate ), NULL );
	gtk_widget_add_accelerator( RuleDefine, "activate", accel_group, GDK_F7, 0, GTK_ACCEL_VISIBLE );
	separator10 = gtk_menu_item_new(  );

	gtk_widget_show( separator10 );
	gtk_container_add( GTK_CONTAINER( Rules_menu ), separator10 );
	RuleLoad = gtk_menu_item_new_with_label( "Load a rule" );

	gtk_widget_show( RuleLoad );
	gtk_container_add( GTK_CONTAINER( Rules_menu ), RuleLoad );
	gtk_signal_connect( GTK_OBJECT( RuleLoad ), "activate",
	   GTK_SIGNAL_FUNC( on_RuleLoad_activate ), NULL );
	RuleSave = gtk_menu_item_new_with_label( "Save the rule" );

	gtk_widget_show( RuleSave );
	gtk_container_add( GTK_CONTAINER( Rules_menu ), RuleSave );
	gtk_signal_connect( GTK_OBJECT( RuleSave ), "activate",
	   GTK_SIGNAL_FUNC( on_RuleSave_activate ), NULL );
	Help = gtk_menu_item_new_with_label( "Help" );

	gtk_widget_show( Help );
	gtk_container_add( GTK_CONTAINER( main_menu ), Help );
	gtk_menu_item_right_justify( GTK_MENU_ITEM( Help ) );
	Help_menu = gtk_menu_new(  );

	gtk_menu_item_set_submenu( GTK_MENU_ITEM( Help ), Help_menu );
	HelpRules = gtk_menu_item_new_with_label( "Rules of Life" );

	gtk_widget_show( HelpRules );
	gtk_container_add( GTK_CONTAINER( Help_menu ), HelpRules );
	gtk_signal_connect( GTK_OBJECT( HelpRules ), "activate",
	   GTK_SIGNAL_FUNC( on_HelpRules_activate ), NULL );
	gtk_widget_add_accelerator( HelpRules, "activate", accel_group, GDK_F1, 0, GTK_ACCEL_VISIBLE );
	separator11 = gtk_menu_item_new(  );

	gtk_widget_show( separator11 );
	gtk_container_add( GTK_CONTAINER( Help_menu ), separator11 );
	HelpAbout = gtk_menu_item_new_with_label( "About Life" );

	gtk_widget_show( HelpAbout );
	gtk_container_add( GTK_CONTAINER( Help_menu ), HelpAbout );
	gtk_signal_connect( GTK_OBJECT( HelpAbout ), "activate",
	   GTK_SIGNAL_FUNC( on_HelpAbout_activate ), NULL );
	zoom_scrolledwindow = gtk_scrolled_window_new( NULL, NULL );

	gtk_widget_show( zoom_scrolledwindow );
	gtk_box_pack_start( GTK_BOX( vbox1 ), zoom_scrolledwindow, TRUE, TRUE, 0 );
	gtk_signal_connect( GTK_OBJECT( zoom_scrolledwindow ), "event",
	   GTK_SIGNAL_FUNC( on_zoom_scrolledwindow_event ), NULL );
	gtk_range_set_update_policy( GTK_RANGE( GTK_SCROLLED_WINDOW( zoom_scrolledwindow )->
		  hscrollbar ), GTK_POLICY_AUTOMATIC );
	gtk_range_set_update_policy( GTK_RANGE( GTK_SCROLLED_WINDOW( zoom_scrolledwindow )->
		  vscrollbar ), GTK_POLICY_AUTOMATIC );
	hadj = ( GtkAdjustment * ) gtk_adjustment_new( 0, 0, config.life_width, 1, 10, 100 );
	vadj = ( GtkAdjustment * ) gtk_adjustment_new( 0, 0, config.life_height, 1, 10, 100 );
	gtk_scrolled_window_set_hadjustment( GTK_SCROLLED_WINDOW( zoom_scrolledwindow ), hadj );
	gtk_scrolled_window_set_vadjustment( GTK_SCROLLED_WINDOW( zoom_scrolledwindow ), vadj );

	zoom_area = gtk_drawing_area_new(  );
	gtk_drawing_area_size( GTK_DRAWING_AREA( zoom_area ),
	   config.life_width * ZOOM_CELL_WIDTH, config.life_height * ZOOM_CELL_HEIGHT );
	gtk_widget_show( zoom_area );
//  gtk_scrolled_window_add_with_viewport( GTK_SCROLLED_WINDOW( zoom_scrolledwindow ),
//      zoom_area );
    is_display_log = 0;
	gtk_container_add( GTK_CONTAINER( zoom_scrolledwindow ), zoom_area );
    is_display_log = 1;
	gtk_widget_set_events( zoom_area,
	   GDK_POINTER_MOTION_MASK | GDK_BUTTON_MOTION_MASK | 
	   GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK );
	gtk_signal_connect( GTK_OBJECT( zoom_area ), "configure_event",
	   GTK_SIGNAL_FUNC( on_zoom_area_configure_event ), NULL );
	gtk_signal_connect( GTK_OBJECT( zoom_area ), "button_press_event",
	   GTK_SIGNAL_FUNC( on_zoom_area_button_press_event ), NULL );
	gtk_signal_connect( GTK_OBJECT( zoom_area ), "motion_notify_event",
	   GTK_SIGNAL_FUNC( on_zoom_area_motion_notify_event ), NULL );
	gtk_signal_connect( GTK_OBJECT( zoom_area ), "expose_event",
	   GTK_SIGNAL_FUNC( on_zoom_area_expose_event ), NULL );

	hseparator2 = gtk_hseparator_new(  );
	gtk_widget_show( hseparator2 );
	gtk_box_pack_start( GTK_BOX( vbox1 ), hseparator2, FALSE, FALSE, 3 );

	table1 = gtk_table_new( 2, 4, FALSE );

	gtk_widget_show( table1 );
	gtk_box_pack_start( GTK_BOX( vbox1 ), table1, FALSE, TRUE, 0 );
	label5 = gtk_label_new( "seek interesting generations" );

	gtk_widget_show( label5 );
	gtk_table_attach( GTK_TABLE( table1 ), label5, 1, 2, 1, 2,
	   ( GtkAttachOptions ) GTK_EXPAND | GTK_FILL, ( GtkAttachOptions ) GTK_EXPAND | GTK_FILL, 0, 0 );
	gtk_label_set_justify( GTK_LABEL( label5 ), GTK_JUSTIFY_LEFT );
	gtk_misc_set_alignment( GTK_MISC( label5 ), 0, 0.5 );
	label8 = gtk_label_new( "next generation (one step)" );

	gtk_widget_show( label8 );
	gtk_table_attach( GTK_TABLE( table1 ), label8, 3, 4, 0, 1,
	   ( GtkAttachOptions ) GTK_EXPAND | GTK_FILL, ( GtkAttachOptions ) GTK_EXPAND | GTK_FILL, 0, 0 );
	gtk_misc_set_alignment( GTK_MISC( label8 ), 0, 0.5 );
	label9 = gtk_label_new( "next generations" );

	gtk_widget_show( label9 );
	gtk_table_attach( GTK_TABLE( table1 ), label9, 3, 4, 1, 2,
	   ( GtkAttachOptions ) GTK_EXPAND | GTK_FILL, ( GtkAttachOptions ) GTK_EXPAND | GTK_FILL, 0, 0 );
	gtk_misc_set_alignment( GTK_MISC( label9 ), 0, 0.5 );
	label3 = gtk_label_new( "previous generation" );

	gtk_widget_show( label3 );
	gtk_table_attach( GTK_TABLE( table1 ), label3, 1, 2, 0, 1,
	   ( GtkAttachOptions ) GTK_EXPAND | GTK_FILL, ( GtkAttachOptions ) GTK_EXPAND | GTK_FILL, 0, 0 );
	gtk_label_set_justify( GTK_LABEL( label3 ), GTK_JUSTIFY_LEFT );
	gtk_misc_set_alignment( GTK_MISC( label3 ), 0, 0.5 );
	label2 = gtk_label_new( "F2" );

	gtk_widget_show( label2 );
	gtk_table_attach( GTK_TABLE( table1 ), label2, 0, 1, 0, 1,
	   ( GtkAttachOptions ) GTK_FILL, ( GtkAttachOptions ) GTK_EXPAND | GTK_FILL, 0, 0 );
	gtk_label_set_justify( GTK_LABEL( label2 ), GTK_JUSTIFY_LEFT );
	gtk_misc_set_alignment( GTK_MISC( label2 ), 0, 0.5 );
	gtk_misc_set_padding( GTK_MISC( label2 ), 8, 0 );
	label4 = gtk_label_new( "F7" );

	gtk_widget_show( label4 );
	gtk_table_attach( GTK_TABLE( table1 ), label4, 0, 1, 1, 2,
	   ( GtkAttachOptions ) GTK_FILL, ( GtkAttachOptions ) GTK_EXPAND | GTK_FILL, 0, 0 );
	gtk_label_set_justify( GTK_LABEL( label4 ), GTK_JUSTIFY_LEFT );
	gtk_misc_set_alignment( GTK_MISC( label4 ), 0, 0.5 );
	gtk_misc_set_padding( GTK_MISC( label4 ), 8, 0 );

	label6 = gtk_label_new( "F3" );
	gtk_widget_show( label6 );
	gtk_table_attach( GTK_TABLE( table1 ), label6, 2, 3, 0, 1,
	   ( GtkAttachOptions ) GTK_FILL, ( GtkAttachOptions ) GTK_EXPAND | GTK_FILL, 0, 0 );
	gtk_label_set_justify( GTK_LABEL( label6 ), GTK_JUSTIFY_LEFT );
	gtk_misc_set_alignment( GTK_MISC( label6 ), 0, 0.5 );
	gtk_misc_set_padding( GTK_MISC( label6 ), 8, 0 );

	label7 = gtk_label_new( "Shift F3" );
	gtk_widget_show( label7 );
	gtk_table_attach( GTK_TABLE( table1 ), label7, 2, 3, 1, 2,
	   ( GtkAttachOptions ) GTK_FILL, ( GtkAttachOptions ) GTK_EXPAND | GTK_FILL, 0, 0 );
	gtk_misc_set_alignment( GTK_MISC( label7 ), 0, 0.5 );
	gtk_misc_set_padding( GTK_MISC( label7 ), 8, 0 );
	gtk_widget_show( zoom_wnd );
	zoom_on_color = create_color( zoom_scrolledwindow, 0xFFFF, 0x0000, 0x0000 );
	zoom_off_color = create_color( zoom_scrolledwindow, 0xFFFF, 0x0000, 0x0000 );
	zoom_none_color = create_color( zoom_scrolledwindow, 0xC000, 0xC000, 0xC000 );

	hseparator2 = gtk_hseparator_new(  );
	gtk_widget_show( hseparator2 );
	gtk_box_pack_start( GTK_BOX( vbox1 ), hseparator2, FALSE, FALSE, 3 );

	GtkWidget *hbox1 = gtk_hbox_new( FALSE, 0 );
	gtk_widget_show( hbox1 );
	gtk_box_pack_start( GTK_BOX( vbox1 ), hbox1, FALSE, FALSE, 3 );

	zoom_xy = gtk_label_new( "" );
	gtk_container_add( GTK_CONTAINER( hbox1 ), zoom_xy );
	gtk_misc_set_alignment( GTK_MISC( zoom_xy ), 0, 0.5 );
	gtk_widget_show( zoom_xy );

	zoom_maxgen = gtk_label_new( "" );
	gtk_container_add( GTK_CONTAINER( hbox1 ), zoom_maxgen );
	gtk_misc_set_alignment( GTK_MISC( zoom_maxgen ), 0, 0.5 );
	gtk_widget_show( zoom_maxgen );

	label5 = gtk_label_new( "freelife" );
	gtk_container_add( GTK_CONTAINER( hbox1 ), label5 );
	gtk_misc_set_alignment( GTK_MISC( label5 ), 1, 0.5 );
	gtk_widget_show( label5 );

#ifdef SHOW_REDRAW_TIME
	hseparator2 = gtk_hseparator_new(  );
	gtk_widget_show( hseparator2 );
	gtk_box_pack_start( GTK_BOX( vbox1 ), hseparator2, FALSE, FALSE, 3 );

	wgt_label_redrawtime = gtk_label_new( "Redraw time: " );
	gtk_widget_show( wgt_label_redrawtime );
	gtk_box_pack_start( GTK_BOX( vbox1 ), wgt_label_redrawtime, FALSE, FALSE, 3 );

#endif

}								// create_zoom

void
center_zoom( void )
{
	int x,
	  y;

	GtkAdjustment *hadj,
	 *vadj;
	int field_width,
	  field_height;


	/*
	 * --- Get size of field window --- 
	 */
	field_width = field_scrolledwnd->allocation.width;
	field_height = field_scrolledwnd->allocation.height;
	get_zoom_infos(  );

	/*
	 * --- Move zoom window --- 
	 */
	x = ( config.life_width - field_width ) / 2;
	y = ( config.life_height - field_height ) / 2;
	hadj = gtk_scrolled_window_get_hadjustment( GTK_SCROLLED_WINDOW( field_scrolledwnd ) );
	vadj = gtk_scrolled_window_get_vadjustment( GTK_SCROLLED_WINDOW( field_scrolledwnd ) );
	gtk_adjustment_set_value( hadj, x );
	gtk_adjustment_set_value( vadj, y );
	gtk_scrolled_window_set_hadjustment( GTK_SCROLLED_WINDOW( field_scrolledwnd ), hadj );
	gtk_scrolled_window_set_vadjustment( GTK_SCROLLED_WINDOW( field_scrolledwnd ), vadj );
	gtk_widget_queue_draw( GTK_WIDGET( fielddraw ) );

	/*
	 * --- Move zoom window --- 
	 */
	x = ( config.life_width - zoom_width ) / 2;
	y = ( config.life_height - zoom_height ) / 2;
	hadj = gtk_scrolled_window_get_hadjustment( GTK_SCROLLED_WINDOW( zoom_scrolledwindow ) );
	vadj = gtk_scrolled_window_get_vadjustment( GTK_SCROLLED_WINDOW( zoom_scrolledwindow ) );
	gtk_adjustment_set_value( hadj, x );
	gtk_adjustment_set_value( vadj, y );
	gtk_scrolled_window_set_hadjustment( GTK_SCROLLED_WINDOW( zoom_scrolledwindow ), hadj );
	gtk_scrolled_window_set_vadjustment( GTK_SCROLLED_WINDOW( zoom_scrolledwindow ), vadj );
	gtk_widget_queue_draw( GTK_WIDGET( zoom_area ) );

}								// center_zoom

int
is_grid( void )
{
	GtkCheckMenuItem *menuitem = GTK_CHECK_MENU_ITEM( menu_OptionsGrid );

	return menuitem->active;
}								// is_grid

void
enable_LifeCenterGeneration( const int flag )
{
	gtk_widget_set_sensitive( LifeCenterGeneration, flag );
}								// enable_LifeCenterGeneration

void
enable_PrevGen( const int flag )
{
	gtk_widget_set_sensitive( LifePrevGen, flag );
}								// enable_PrevGen

void
enable_NextGen( const int flag )
{
	gtk_widget_set_sensitive( LifeNextGen, flag );
}								// enable_NextGen

void
enable_NextGens( const int flag )
{
	gtk_widget_set_sensitive( LifeNextGens, flag );
}								// enable_NextGens

void
enable_RestoreStartingGen( const int flag )
{
	gtk_widget_set_sensitive( LifeRestoreStartingGen, flag );
}								// enable_RestoreStartingGen
