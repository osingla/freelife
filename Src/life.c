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

#define MAX_POINTS 1000
static gint on_npoints,
  off_npoints;
static GdkPoint on_points[MAX_POINTS],
  off_points[MAX_POINTS];

static void
test_gen_stable( const UBYTE * curr_gen )
{
	int n;
	char msg[200];

	/*
       If neither birth nor death, population is stable
    */
	if ( ( life_birth == 0 ) && ( life_death == 0 ) )

	{

		/*--- Show into life field window ---*/
		gtk_widget_show( hsep_stable );
		gtk_widget_show( label_stable );
		sprintf( msg, "Generation stable: 1" );
		gtk_label_set_text( GTK_LABEL( label_stable ), msg );

		/*--- Population stable ---*/
		is_stability = TRUE;
		stability_period = 1;
		return;
	}							// if

	/*
       Compare with some previous generations
    */
	for ( n = gen_kept_nb - 1; n >= 0; n-- )
	{

		if ( memcmp( curr_gen, gen_kept[n], life_size ) == 0 )
		{

			/*
               Show into life field window
            */
			gtk_widget_show( hsep_stable );
			gtk_widget_show( label_stable );
			sprintf( msg, "Generation stable: %d", gen_kept_nb - n );
			gtk_label_set_text( GTK_LABEL( label_stable ), msg );

			/*
               Population stable
            */
			is_stability = TRUE;
			stability_period = gen_kept_nb - n;
			return;
		}
	}

}								// test_gen_stable


static void
test_pop_stable( void )
{
	int n;
	int val;
	char msg[200];

	if ( gen_kept_nb < max_nb_gen_kept )
		return;
	val = gen_kept_popnb[0];
	for ( n = 1; n < gen_kept_nb; n++ )
		if ( gen_kept_popnb[n] != val )
			return;

	/*
       Show into life field window
    */
	gtk_widget_show( hsep_stable );
	gtk_widget_show( label_stable );
	sprintf( msg, "Generation stable: %d", gen_kept_nb );
	gtk_label_set_text( GTK_LABEL( label_stable ), msg );
	is_stability = TRUE;
	stability_period = gen_kept_nb;

}								// test_pop_stable


#define COUNT( val, nb, pw, mask, icol ) \
{ \
	if ( val ) \
 \
{ \
		if ( ( nb == 2 ) || ( nb == 3 ) ) \
\
		{ \
			life_stable++; \
			*pw |= mask; \
            p_on_points->x = col + icol; \
            p_on_points++->y = row; \
            on_npoints++; \
		} \
\
		else \
\
		{ \
			life_death++; \
            p_off_points->x = col + icol; \
            p_off_points++->y = row; \
            off_npoints++; \
		} \
	} \
\
	else \
\
	{ \
		if ( nb == 3 ) \
\
		{ \
			life_birth++; \
			*pw |= mask; \
            p_on_points->x = col + icol; \
            p_on_points++->y = row; \
            on_npoints++; \
		} \
	} \
}


inline UBYTE *
field_to_use( void )
{
	return ( life_gen % 2 ) ? field2 : field1;
}								// field_to_use


void
compute_gen( void )
{
	UBYTE *p0;
	UBYTE *pv1,
	 *pv2,
	 *pv3,
	  v1,
	  v2,
	  v3,
	 *pw;
	int row,
	  col;
	int nb;
    GdkPoint *p_on_points,
       *p_off_points;

	/*
        Save generation #0
    */
	if ( life_gen == 1 )
	{
//      new_graph_data( Generation, Population, 0, 0, 0 );
		memmove( gen0_kept, ( life_gen % 2 ) ? field1 : field2, life_size );
	}							// if

	life_birth = life_death = life_stable = 0;
	on_npoints  = 0;
	off_npoints = 0;
    p_on_points  = on_points;
    p_off_points = off_points;
	if ( life_gen % 2 )
	{
		p0 = field1;
		memset( field2, 0, life_size );
		pv1 = &field1[0 * life_bpl];
		pv2 = &field1[1 * life_bpl];
		pv3 = &field1[2 * life_bpl];
		pw = &field2[1 * life_bpl];
	}
	else
	{
		p0 = field2;
		memset( field1, 0, life_size );
		pv1 = &field2[0 * life_bpl];
		pv2 = &field2[1 * life_bpl];
		pv3 = &field2[2 * life_bpl];
		pw = &field1[1 * life_bpl];
	}

	for ( row = 1; row < config.life_height-1; row++ )
	{
		for ( col = 8; col < config.life_width-8; col += 8 )
		{

			// Case 0
			++pw;
			v1 = *++pv1;
			v2 = *++pv2;
			v3 = *++pv3;
			nb =
			   ( ( *( pv1 - 1 ) ) & 0x01 ) + ( ( v1 & 0x80 ) >> 7 ) +
			   ( ( v1 & 0x40 ) >> 6 ) + ( ( *( pv2 - 1 ) ) & 0x01 ) +
			   ( ( v2 & 0x40 ) >> 6 ) + ( ( *( pv3 - 1 ) ) & 0x01 ) +
			   ( ( v3 & 0x80 ) >> 7 ) + ( ( v3 & 0x40 ) >> 6 );
			COUNT( v2 & 0x80, nb, pw, 0x80, 0 );

			// Case 1
			nb =
			   ( ( v1 & 0x80 ) >> 7 ) + ( ( v1 & 0x40 ) >> 6 ) + ( ( v1 & 0x20 ) >> 5 ) +
			   ( ( v2 & 0x80 ) >> 7 ) + ( ( v2 & 0x20 ) >> 5 ) + ( ( v3 & 0x80 ) >> 7 ) +
			   ( ( v3 & 0x40 ) >> 6 ) + ( ( v3 & 0x20 ) >> 5 );
			COUNT( v2 & 0x40, nb, pw, 0x40, 1 );

			// Case 2
			nb =
			   ( ( v1 & 0x40 ) >> 6 ) + ( ( v1 & 0x20 ) >> 5 ) + ( ( v1 & 0x10 ) >> 4 ) +
			   ( ( v2 & 0x40 ) >> 6 ) + ( ( v2 & 0x10 ) >> 4 ) + ( ( v3 & 0x40 ) >> 6 ) +
			   ( ( v3 & 0x20 ) >> 5 ) + ( ( v3 & 0x10 ) >> 4 );
			COUNT( v2 & 0x20, nb, pw, 0x20, 2 );

			// Case 3
			nb =
			   ( ( v1 & 0x20 ) >> 5 ) + ( ( v1 & 0x10 ) >> 4 ) + ( ( v1 & 0x08 ) >> 3 ) +
			   ( ( v2 & 0x20 ) >> 5 ) + ( ( v2 & 0x08 ) >> 3 ) + ( ( v3 & 0x20 ) >> 5 ) +
			   ( ( v3 & 0x10 ) >> 4 ) + ( ( v3 & 0x08 ) >> 3 );
			COUNT( v2 & 0x10, nb, pw, 0x10, 3 );

			// Case 4
			nb =
			   ( ( v1 & 0x10 ) >> 4 ) + ( ( v1 & 0x08 ) >> 3 ) + ( ( v1 & 0x04 ) >> 2 ) +
			   ( ( v2 & 0x10 ) >> 4 ) + ( ( v2 & 0x04 ) >> 2 ) + ( ( v3 & 0x10 ) >> 4 ) +
			   ( ( v3 & 0x08 ) >> 3 ) + ( ( v3 & 0x04 ) >> 2 );
			COUNT( v2 & 0x08, nb, pw, 0x08, 4 );

			// Case 5
			nb =
			   ( ( v1 & 0x08 ) >> 3 ) + ( ( v1 & 0x04 ) >> 2 ) + ( ( v1 & 0x02 ) >> 1 ) +
			   ( ( v2 & 0x08 ) >> 3 ) + ( ( v2 & 0x02 ) >> 1 ) + ( ( v3 & 0x08 ) >> 3 ) +
			   ( ( v3 & 0x04 ) >> 2 ) + ( ( v3 & 0x02 ) >> 1 );
			COUNT( v2 & 0x04, nb, pw, 0x04, 5 );

			// Case 6
			nb = ( ( v1 & 0x04 ) >> 2 ) + ( ( v1 & 0x02 ) >> 1 ) + ( v1 & 0x01 ) +
			   ( ( v2 & 0x04 ) >> 2 ) + ( v2 & 0x01 ) +
			   ( ( v3 & 0x04 ) >> 2 ) + ( ( v3 & 0x02 ) >> 1 ) + ( v3 & 0x01 );
			COUNT( v2 & 0x02, nb, pw, 0x02, 6 );

			// Case 7
			nb =
			   ( ( v1 & 0x02 ) >> 1 ) + ( v1 & 0x01 ) + ( ( ( *( pv1 +
						1 ) ) & 0x80 ) >> 7 ) + ( ( v2 & 0x02 ) >> 1 ) + ( ( ( *( pv2 +
						1 ) ) & 0x80 ) >> 7 ) + ( ( v3 & 0x02 ) >> 1 ) + ( v3 & 0x01 ) +
			   ( ( ( *( pv3 + 1 ) ) & 0x80 ) >> 7 );
			COUNT( v2 & 0x01, nb, pw, 0x01, 7 );
		}						// for (col)
		pv1++;
		pv2++;
		pv3++;
		pw++;
		pv1++;
		pv2++;
		pv3++;
		pw++;
	}							// for (row)
	if ( off_npoints )
		gdk_draw_points( pixmap_field, field_off_color, off_points, off_npoints );
	if ( on_npoints )
		gdk_draw_points( pixmap_field, field_on_color, on_points, on_npoints );

    /*
        Ask for update screen
    */
	gtk_widget_queue_draw( GTK_WIDGET( fielddraw ) );
	gtk_widget_queue_draw( GTK_WIDGET( zoom_area ) );
	life_pop = life_stable + life_birth;
	show_infos(  );


	/*--- Update the generations kept to see if ... ---*/
	if ( gen_kept_nb < max_nb_gen_kept )
	{
		gen_kept_popnb[gen_kept_nb] = life_pop;
		memmove( gen_kept[gen_kept_nb++], p0, life_size );
	}
	else
	{
		memmove( &gen_kept_popnb[0], &gen_kept_popnb[1], sizeof( int ) * ( gen_kept_nb - 1 ) );
		gen_kept_popnb[gen_kept_nb - 1] = life_pop;
		memmove( &gen_kept_base[0], &gen_kept_base[life_size], life_size * ( gen_kept_nb - 1 ) );
		memmove( gen_kept[gen_kept_nb - 1], p0, life_size );
	}

	/*
        Test if this generation is stable
    */
	test_gen_stable( field_to_use(  ) );

}								// compute_gen


void
show_life_pop( void )
{
	char msg[80];

	sprintf( msg, "%d", life_pop );
	gtk_label_set_text( GTK_LABEL( info_pop ), msg );

//  enable_LifeCenterGeneration( (life_pop > 0) );
//  enable_NextGen( (life_pop > 0) );
//  enable_NextGens( (life_pop > 0) );
}								// show_life_pop


void
show_infos( void )
{
	char msg[80];


#define SHOW( w, v ) \
	if ( v == -1 ) \
		strcpy( msg, "" ); \
	else \
		sprintf( msg, "%d", v ); \
	gtk_label_set_text( GTK_LABEL( w ), msg )
	SHOW( info_gen, life_gen );
	SHOW( info_birth, life_birth );
	SHOW( info_death, life_death );
#undef SHOW

	show_life_pop(  );

//  enable_PrevGen( (gen_kept_nb > 0) );
//  enable_RestoreStartingGen( (life_gen > 0) );
	gdk_flush(  );
}								// show_infos


void
compute_generations( void )
{

	/*
       Set to TRUE while computing next generations (Shift-F2)
    */
	if ( is_comp_generations )
		return;

	/*
       Do nothing if population empty !
    */
	if ( life_pop == 0 )
		return;

	/*
       Iconify the zoom window
    */
//  iconify_window( ABW_zoom, TRUE );

	/*
       Disable all access to the zoom window
    */
//  busyWindow( ABW_zoom, TRUE );

	/*
       Show 'Stop' button on the life field window
    */
	gtk_widget_show( btn_stop );

//  PtRealizeWidget( ABW_status_btn_stop );

	/*
       Set to TRUE while computing next generations (Shift-F2)
    */
	is_comp_generations = TRUE;

	/*
       Life field: Clear stable infos
    */
//  PtUnrealizeWidget( ABW_status_stable_label );
//  PtUnrealizeWidget( ABW_status_stable_period );

	/*
       Generations kept to see if stability
    */
	is_stability = FALSE;

	/*
       If seek window is open, then block all input
    */
//  if ( ABW_seek )
//      busyWindow( ABW_seek, TRUE );

	/*
       Field of life has focus
    */
//  window_focus( ABW_life );

	/*
       Hide the graphics window if opened
    */
//  if ( ABW_graph != NULL )
//      PtUnrealizeWidget( ABW_graph );


	/*
       To compute time for doing complete next generations
    */
//  start_nextgens = time( NULL );

	/*
      Compute next generations until 
	      - the button 'Stop' is pressed
	      - the generation is stable or dead. */
	for ( end_comp_generations = FALSE; !end_comp_generations; )
	{

		/*
           Let gtk handle pending events
        */
		gdk_flush(  );
		while ( gtk_events_pending(  ) )
			gtk_main_iteration(  );

		/*
           Compute the next generation
        */
		life_gen++;
		compute_gen(  );

		/*
           End if no population or stability
        */
		if ( ( life_pop == 0 ) || ( is_stability ) )
			break;

	}							// for (;;)
	is_comp_generations = FALSE;

	/*
       Stop computing generations
    */
	gtk_widget_hide( btn_stop );

	/*
       To compute time for doing complete next generations
    */
//  nextgens_timeelps = difftime( time( NULL ), start_nextgens );
//  if ( ABW_stats )
//      setString( ABW_stats_lastnextgens, "%d", nextgens_timeelps );

	/*
       Des-hide the graphics window if opened
    */
//  if ( ABW_graph != NULL )
//      PtRealizeWidget( ABW_graph );

	/*
       Restore access to the zoom window
    */
//  busyWindow( ABW_zoom, FALSE );

	/*
       If seek window is open, then unblock all input
    */

	/*
       Enable the button 'Reload starting generation', only of seek window is open
    */
#if 0
	if ( ABW_seek )
	{
		busyWindow( ABW_seek, FALSE );
		ghostBtn( ABW_seek_btn_reloadstartgen, FALSE );
		ghostBtn( ABW_seek_btn_reloadbestgen, FALSE );
	}

#endif						   /*  */

	/*
       Enable/Disable option 'Save' of the menu
    */
#if 0
	ApModifyItemState( &file_menu,
	   ( Population > 0 ) ? AB_ITEM_NORMAL : AB_ITEM_DIM, ABN_file_save,
	   ABN_file_save_text, ABN_file_print, NULL );

#endif						   /*  */

	/*
       Des-Iconify the zoom window
    */
#if 0
	iconify_window( ABW_zoom, FALSE );
	window_focus( ABW_zoom );

#endif						   /*  */

}								// compute_generations


void
restore_prev_gen( void )
{

	/*
       No previous generation ?
    */
	if ( ( life_gen == 0 ) || ( gen_kept_nb == 0 ) )
		return;

	/*
       Restore the generations kept to see if ...
    */
	if ( ( --life_gen % 2 ) == 0 )
		memmove( field1, gen_kept[--gen_kept_nb], life_size );
	else
		memmove( field2, gen_kept[--gen_kept_nb], life_size );

#if 0

	/*
       Count the number of cells inside the field and show it
    */
	setString( ABW_status_pop, "%d", Population = count_nb_cells( bitmap_to_use(  ) ) );
	setString( ABW_status_birth, "" );
	setString( ABW_status_death, "" );

	/*
       Life field: Clear stable infos
    */
	PtUnrealizeWidget( ABW_status_stable_label );
	PtUnrealizeWidget( ABW_status_stable_period );

	/*
       Generations kept to see if stability
    */
	is_stability = FALSE;

	/*
       Life field: Draw informations (Generation, Population)
    */
	setString( ABW_status_gen, "%d", Generation );
	setString( ABW_status_pop, "%d", Population );
	setString( ABW_status_birth, "" );
	setString( ABW_status_death, "" );

	/*
       Redraw the zoom pane
    */
	do_zoom_redraw(  );

	/*
       Optimization
    */
	opt_x1 = 1;
	opt_x2 = FIELD_WIDTH8 - 2;
	opt_y1 = 1;
	opt_y2 = FIELD_HEIGHT - 2;

	/*
       Update the graphic display ?
    */
	if ( ( ABW_graph != NULL ) && ( !is_comp_generations ) )
		graph_redraw(  );
	return ( Pt_CONTINUE );

#endif						   /*  */

	/*
       Redraw both zoom and field
    */
	life_pop = redraw_pixmap_zoom(  );
	redraw_pixmap_field(  );
	life_stable = 0;
	life_birth = life_death = -1;
	show_infos(  );

}								// restore_prev_gen


void
restore_gen0( void )
{

	/*
       No generation 0 ?
    */
	if ( life_gen == 0 )
		return;

	/*
       Restore generation #0
    */
	life_gen = 0;
	memmove( field1, gen0_kept, life_size );
	gen_kept_nb = 0;

	/*
       Redraw both zoom and field
    */
	life_pop = redraw_pixmap_zoom(  );
	redraw_pixmap_field(  );
	life_stable = 0;
	life_birth = life_death = -1;
	show_infos(  );

}								// restore_gen0
