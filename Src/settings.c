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

static GtkWidget *settings_life_height;
static GtkWidget *settings_life_width;
static GtkWidget *settings_life_lifesavednb;
static GtkWidget *settings_ok;
static CONFIG newcfg;

void
default_config( void )
{

	config.life_width  = 1024;
	config.life_height = 1024;
	config.lifesavednb = 30;

	rndgen.w = 6;
	rndgen.h = 6;
	rndgen.x = (config.life_width - rndgen.w) / 2;
	rndgen.y = (config.life_height - rndgen.h) / 2;
	rndgen.nbmin = 5;
	rndgen.nbmax = 12;

}								// default_config


static void
write_config_to_dialog( void )
{
	memmove( &newcfg, &config, sizeof( CONFIG ) );
}								// write_config_to_dialog


static void
read_newcfg_from_dialog( void )
{
	GtkAdjustment *adj;

	adj = GTK_RANGE( settings_life_height )->adjustment;
	newcfg.life_height = ( int ) adj->value;
	adj = GTK_RANGE( settings_life_width )->adjustment;
	newcfg.life_width = ( int ) adj->value;
	printf( "%d %d %d  %d\n", newcfg.life_height, newcfg.life_width,
	   newcfg.lifesavednb, memcmp( &config, &newcfg, sizeof( CONFIG ) ) );
	gtk_widget_set_sensitive( settings_ok, memcmp( &config, &newcfg, sizeof( CONFIG ) ) );
}								// read_newcfg_from_dialog


gboolean
on_settings_life_height_event( GtkWidget * widget,
   GdkEvent * event,
   gpointer user_data )
{

//  if ( (event->type == GDK_EXPOSE) || (event->type == GDK_KEY_PRESS) )
	{
		GtkAdjustment *adj = GTK_RANGE( widget )->adjustment;

		newcfg.life_height = ( int ) adj->value;
		gtk_widget_set_sensitive( settings_ok, memcmp( &config, &newcfg, sizeof( CONFIG ) ) );
	}
	return FALSE;
}								// on_settings_life_height_event

gboolean
on_settings_life_width_event( GtkWidget * widget,
   GdkEvent * event,
   gpointer user_data )
{

//  if ( (event->type == GDK_EXPOSE) || (event->type == GDK_KEY_PRESS) )
	{
		GtkAdjustment *adj = GTK_RANGE( widget )->adjustment;

		newcfg.life_width = ( int ) adj->value;
		gtk_widget_set_sensitive( settings_ok, memcmp( &config, &newcfg, sizeof( CONFIG ) ) );
	}
	return FALSE;
}								// on_settings_life_width_event

gboolean
on_settings_life_lifesavednb_event( GtkWidget * widget,
   GdkEvent * event,
   gpointer user_data )
{

//  if ( (event->type == GDK_EXPOSE) || (event->type == GDK_KEY_PRESS) )
	{
		GtkAdjustment *adj = GTK_RANGE( widget )->adjustment;

		newcfg.lifesavednb = ( int ) adj->value;
		gtk_widget_set_sensitive( settings_ok, memcmp( &config, &newcfg, sizeof( CONFIG ) ) );
	}
	return FALSE;
}								// on_settings_life_lifesavednb_event

void
on_settings_ok_clicked( GtkButton * button,
   gpointer user_data )
{
}								// on_settings_ok_clicked


void
on_settings_cancel_clicked( GtkButton * button,
   gpointer user_data )
{
}								// on_settings_cancel_clicked


void
create_settings( void )
{
	GtkWidget *settings;
	GtkWidget *dialog_vbox1;
	GtkWidget *notebook1;
	GtkWidget *vbox3;
	GtkWidget *frame1;
	GtkWidget *table3;
	GtkWidget *label13;
	GtkWidget *label14;
	GtkWidget *hbox1;
	GtkWidget *label15;
	GtkWidget *hseparator4;
	GtkWidget *hbox2;
	GtkWidget *label16;
	GtkWidget *settings_life_mem;
	GtkWidget *vbox4;
	GtkWidget *hbox3;
	GtkWidget *label18;
	GtkWidget *empty_notebook_page;
	GtkWidget *label10;
	GtkWidget *label11;
	GtkWidget *label12;
	GtkWidget *dialog_action_area1;
	GtkWidget *hbuttonbox1;
	GtkWidget *settings_cancel;

	settings = gtk_dialog_new(  );

	gtk_window_set_title( GTK_WINDOW( settings ), "Settings" );
	gtk_window_set_policy( GTK_WINDOW( settings ), TRUE, TRUE, FALSE );
	dialog_vbox1 = GTK_DIALOG( settings )->vbox;

	gtk_widget_show( dialog_vbox1 );
	notebook1 = gtk_notebook_new(  );

	gtk_widget_show( notebook1 );
	gtk_box_pack_start( GTK_BOX( dialog_vbox1 ), notebook1, TRUE, TRUE, 0 );
	vbox3 = gtk_vbox_new( FALSE, 4 );

	gtk_widget_show( vbox3 );
	gtk_container_add( GTK_CONTAINER( notebook1 ), vbox3 );
	frame1 = gtk_frame_new( "Dimension" );

	gtk_widget_show( frame1 );
	gtk_box_pack_start( GTK_BOX( vbox3 ), frame1, TRUE, TRUE, 0 );
	table3 = gtk_table_new( 2, 2, FALSE );

	gtk_widget_show( table3 );
	gtk_container_add( GTK_CONTAINER( frame1 ), table3 );
	settings_life_height =
	   gtk_hscale_new( GTK_ADJUSTMENT( gtk_adjustment_new( 1024, 512, 2048, 128, 128, 128 ) ) );

	gtk_widget_show( settings_life_height );
	gtk_table_attach( GTK_TABLE( table3 ), settings_life_height, 1, 2, 0, 1,
	   ( GtkAttachOptions ) GTK_EXPAND | GTK_FILL, ( GtkAttachOptions ) GTK_EXPAND | GTK_FILL, 0, 0 );
	gtk_signal_connect( GTK_OBJECT( settings_life_height ), "event",
	   GTK_SIGNAL_FUNC( on_settings_life_height_event ), NULL );
	gtk_scale_set_digits( GTK_SCALE( settings_life_height ), 0 );
	settings_life_width =
	   gtk_hscale_new( GTK_ADJUSTMENT( gtk_adjustment_new( 1024, 512, 2048, 128, 128, 128 ) ) );

	gtk_widget_show( settings_life_width );
	gtk_table_attach( GTK_TABLE( table3 ), settings_life_width, 1, 2, 1, 2,
	   ( GtkAttachOptions ) GTK_EXPAND | GTK_FILL, ( GtkAttachOptions ) GTK_EXPAND | GTK_FILL, 0, 0 );
	gtk_signal_connect( GTK_OBJECT( settings_life_width ), "event",
	   GTK_SIGNAL_FUNC( on_settings_life_width_event ), NULL );
	gtk_scale_set_digits( GTK_SCALE( settings_life_width ), 0 );
	label13 = gtk_label_new( "Height" );

	gtk_widget_show( label13 );
	gtk_table_attach( GTK_TABLE( table3 ), label13, 0, 1, 0, 1,
	   ( GtkAttachOptions ) GTK_FILL, ( GtkAttachOptions ) GTK_EXPAND | GTK_FILL, 8, 0 );
	gtk_label_set_justify( GTK_LABEL( label13 ), GTK_JUSTIFY_LEFT );
	gtk_misc_set_alignment( GTK_MISC( label13 ), 0, 0.5 );
	label14 = gtk_label_new( "Width" );

	gtk_widget_show( label14 );
	gtk_table_attach( GTK_TABLE( table3 ), label14, 0, 1, 1, 2,
	   ( GtkAttachOptions ) GTK_FILL, ( GtkAttachOptions ) GTK_EXPAND | GTK_FILL, 8, 0 );
	gtk_label_set_justify( GTK_LABEL( label14 ), GTK_JUSTIFY_LEFT );
	gtk_misc_set_alignment( GTK_MISC( label14 ), 0, 0.5 );
	hbox1 = gtk_hbox_new( FALSE, 0 );

	gtk_widget_show( hbox1 );
	gtk_box_pack_start( GTK_BOX( vbox3 ), hbox1, TRUE, TRUE, 0 );
	label15 = gtk_label_new( "Number of saved generations\nin order to check stable population:" );

	gtk_widget_show( label15 );
	gtk_box_pack_start( GTK_BOX( hbox1 ), label15, FALSE, TRUE, 0 );
	gtk_label_set_justify( GTK_LABEL( label15 ), GTK_JUSTIFY_FILL );
	gtk_misc_set_alignment( GTK_MISC( label15 ), 0, 0.5 );
	gtk_misc_set_padding( GTK_MISC( label15 ), 8, 0 );
	settings_life_lifesavednb =
	   gtk_hscale_new( GTK_ADJUSTMENT( gtk_adjustment_new( 20, 5, 100, 1, 10, 10 ) ) );

	gtk_widget_show( settings_life_lifesavednb );
	gtk_box_pack_start( GTK_BOX( hbox1 ), settings_life_lifesavednb, TRUE, TRUE, 0 );
	gtk_signal_connect( GTK_OBJECT( settings_life_lifesavednb ), "event",
	   GTK_SIGNAL_FUNC( on_settings_life_lifesavednb_event ), NULL );
	gtk_scale_set_digits( GTK_SCALE( settings_life_lifesavednb ), 0 );
	hseparator4 = gtk_hseparator_new(  );

	gtk_widget_show( hseparator4 );
	gtk_box_pack_start( GTK_BOX( vbox3 ), hseparator4, TRUE, TRUE, 0 );
	hbox2 = gtk_hbox_new( FALSE, 0 );

	gtk_widget_show( hbox2 );
	gtk_box_pack_start( GTK_BOX( vbox3 ), hbox2, TRUE, TRUE, 0 );
	label16 = gtk_label_new( "Amount of memory needed:" );

	gtk_widget_show( label16 );
	gtk_box_pack_start( GTK_BOX( hbox2 ), label16, FALSE, TRUE, 0 );
	gtk_label_set_justify( GTK_LABEL( label16 ), GTK_JUSTIFY_LEFT );
	gtk_misc_set_alignment( GTK_MISC( label16 ), 0, 0.5 );
	gtk_misc_set_padding( GTK_MISC( label16 ), 8, 0 );
	settings_life_mem = gtk_label_new( "12 M" );

	gtk_widget_show( settings_life_mem );
	gtk_box_pack_start( GTK_BOX( hbox2 ), settings_life_mem, TRUE, TRUE, 0 );
	vbox4 = gtk_vbox_new( FALSE, 0 );

	gtk_widget_show( vbox4 );
	gtk_container_add( GTK_CONTAINER( notebook1 ), vbox4 );
	hbox3 = gtk_hbox_new( FALSE, 0 );

	gtk_widget_show( hbox3 );
	gtk_box_pack_start( GTK_BOX( vbox4 ), hbox3, TRUE, TRUE, 0 );
	label18 = gtk_label_new( "Background color:" );

	gtk_widget_show( label18 );
	gtk_box_pack_start( GTK_BOX( hbox3 ), label18, FALSE, TRUE, 0 );
	gtk_label_set_justify( GTK_LABEL( label18 ), GTK_JUSTIFY_LEFT );
	gtk_misc_set_alignment( GTK_MISC( label18 ), 0, 0.5 );
	gtk_misc_set_padding( GTK_MISC( label18 ), 8, 0 );
	empty_notebook_page = gtk_vbox_new( FALSE, 0 );
	gtk_widget_show( empty_notebook_page );
	gtk_container_add( GTK_CONTAINER( notebook1 ), empty_notebook_page );
	label10 = gtk_label_new( "Life" );

	gtk_widget_show( label10 );
	set_notebook_tab( notebook1, 0, label10 );
	label11 = gtk_label_new( "Field" );

	gtk_widget_show( label11 );
	set_notebook_tab( notebook1, 1, label11 );
	label12 = gtk_label_new( "Zoom" );

	gtk_widget_show( label12 );
	set_notebook_tab( notebook1, 2, label12 );
	dialog_action_area1 = GTK_DIALOG( settings )->action_area;

	gtk_widget_show( dialog_action_area1 );
	gtk_container_border_width( GTK_CONTAINER( dialog_action_area1 ), 10 );
	hbuttonbox1 = gtk_hbutton_box_new(  );

	gtk_widget_show( hbuttonbox1 );
	gtk_box_pack_start( GTK_BOX( dialog_action_area1 ), hbuttonbox1, TRUE, TRUE, 0 );
	settings_ok = gtk_button_new_with_label( "Ok" );

	gtk_widget_show( settings_ok );
	gtk_container_add( GTK_CONTAINER( hbuttonbox1 ), settings_ok );
	gtk_signal_connect( GTK_OBJECT( settings_ok ), "clicked",
	   GTK_SIGNAL_FUNC( on_settings_ok_clicked ), NULL );
	gtk_widget_set_sensitive( settings_ok, FALSE );
	settings_cancel = gtk_button_new_with_label( "Cancel" );

	gtk_widget_show( settings_cancel );
	gtk_container_add( GTK_CONTAINER( hbuttonbox1 ), settings_cancel );
	gtk_signal_connect( GTK_OBJECT( settings_cancel ), "clicked",
	   GTK_SIGNAL_FUNC( on_settings_cancel_clicked ), NULL );
	write_config_to_dialog(  );
	gtk_widget_show( settings );

}								// create_settings
