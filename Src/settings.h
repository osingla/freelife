/**
 * @file field.h
 *
 * freelife: Conway Game of Life \n
 * Copyright (C) 1999-2007  Olivier Singla \n
 * http://freelife.sourceforge.net/ \n
 */

#ifndef _SETTINGS_H_
#define _SETTINGS_H_

void default_config( void );
gboolean on_settings_life_height_event( GtkWidget * widget,
   GdkEvent * event,
   gpointer user_data );
gboolean on_settings_life_width_event( GtkWidget * widget,
   GdkEvent * event,
   gpointer user_data );
gboolean on_settings_life_lifesavednb_event( GtkWidget * widget,
   GdkEvent * event,
   gpointer user_data );
void on_settings_ok_clicked( GtkButton * button,
   gpointer user_data );
void on_settings_cancel_clicked( GtkButton * button,
   gpointer user_data );
void create_settings( void );

#endif                         /*_SETTINGS_H_ */
