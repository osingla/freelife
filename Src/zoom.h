/**
 * @file field.h
 *
 * freelife: Conway Game of Life \n
 * Copyright (C) 1999-2007  Olivier Singla \n
 * http://freelife.sourceforge.net/ \n
 */

#ifndef _ZOOM_H_
#define __ZOOM_H_

gint close_app( GtkWidget * widget,
   gpointer data );
void on_FileLoad_activate( GtkMenuItem * menuitem,
   gpointer user_data );
void on_FileSave_activate( GtkMenuItem * menuitem,
   gpointer user_data );
void on_FileSaveText_activate( GtkMenuItem * menuitem,
   gpointer user_data );
void on_FilePrint_activate( GtkMenuItem * menuitem,
   gpointer user_data );
void on_FileExit_activate( GtkMenuItem * menuitem,
   gpointer user_data );
void on_OptionsGrid_activate( GtkMenuItem * menuitem,
   gpointer user_data );
void on_OptionsSettings_activate( GtkMenuItem * menuitem,
   gpointer user_data );
void on_LifeClear_activate( GtkMenuItem * menuitem,
   gpointer user_data );
void on_LifeCenterZoom_activate( GtkMenuItem * menuitem,
   gpointer user_data );
void on_LifeCenterGeneration_activate( GtkMenuItem * menuitem,
   gpointer user_data );
void on_FilePrevGen_activate( GtkMenuItem * menuitem,
   gpointer user_data );
void clear_pending_events( void );
void on_LifeNextGen_activate( GtkMenuItem * menuitem,
   gpointer user_data );
void on_FileNextGens_activate( GtkMenuItem * menuitem,
   gpointer user_data );
void on_LifeRestoreStartingGen_activate( GtkMenuItem * menuitem,
   gpointer user_data );
void on_LifeStats_activate( GtkMenuItem * menuitem,
   gpointer user_data );
void on_LifeGraph_activate( GtkMenuItem * menuitem,
   gpointer user_data );
void on_LifeInterGen_7_172_activate( GtkMenuItem * menuitem,
   gpointer user_data );
void on_LifeRandomGen_activate( GtkMenuItem * menuitem,
   gpointer user_data );
void on_LifeSeekInterGen_activate( GtkMenuItem * menuitem,
   gpointer user_data );
void on_RulesStd_activate( GtkMenuItem * menuitem,
   gpointer user_data );
void on_RuleDefine_activate( GtkMenuItem * menuitem,
   gpointer user_data );
void on_RuleLoad_activate( GtkMenuItem * menuitem,
   gpointer user_data );
void on_RuleSave_activate( GtkMenuItem * menuitem,
   gpointer user_data );
void on_HelpRules_activate( GtkMenuItem * menuitem,
   gpointer user_data );
void on_HelpAbout_activate( GtkMenuItem * menuitem,
   gpointer user_data );
void get_zoom_infos( void );
int redraw_pixmap_zoom( void );
GtkWidget *create_menu_item( GtkWidget * wgt_menu,
   char *label,
   char *xpm[],
   int sensitive,
   int acc_key,
   int acc_control,
   GCallback cb,
   gpointer user_data );
void create_zoom( void );
void center_zoom( void );
int is_grid( void );
void enable_LifeCenterGeneration( const int flag );
void enable_PrevGen( const int flag );
void enable_NextGen( const int flag );
void enable_NextGens( const int flag );
void enable_RestoreStartingGen( const int flag );

#endif                         /*_ZOOM_H_ */
