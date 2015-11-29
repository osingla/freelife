/**
 *
 * @file vars_glo.h
 *
 * @brief Global Variables.
 *
 */

#ifndef VARGLO_H_
#define VARGLO_H_

#ifndef COMMON
#	define COMMON extern	/**< TBD **/
#	define GINIT(v)
#else
#	define __MAIN__
#	define GINIT(v) = v
#endif

/*--- General types ---*/
typedef unsigned char UBYTE;
typedef struct
{
	int life_width,
	  life_height;
	int lifesavednb;
}
CONFIG;

COMMON CONFIG config;


/*
    Display log information ?
*/
COMMON int is_display_log GINIT( 1 );

/*
    Windows
*/
COMMON GtkWidget *zoom_wnd GINIT( NULL );
COMMON GtkWidget *field_wnd GINIT( NULL );


/*--- Public variables related to: main.c --- */
COMMON int life_bpl;
COMMON int life_size;
COMMON int life_gen;
COMMON int life_pop;
COMMON int life_stable;
COMMON int life_birth;
COMMON int life_death;



/*--- Field of life ---*/
COMMON UBYTE *field1 GINIT( NULL );
COMMON UBYTE *field2 GINIT( NULL );

#define CURRENT_FIELD \
   ( life_gen % 2 ) ? field2 : field1
#ifdef __MAIN__
UBYTE mask[8] = {
	0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01
};
#else						   /*  */
extern UBYTE mask[8];
#endif						   /*  */


/*--- Public variables related to: field.c --- */
COMMON GdkPixmap *pixmap_field GINIT( NULL );


/*--- Public variables related to: zoom.c --- */
COMMON GdkPixmap *pixmap_zoom GINIT( NULL );

// Generations kept to see if stability
COMMON int *gen_kept_popnb;

COMMON UBYTE *gen_kept_base;
COMMON int max_nb_gen_kept;

COMMON UBYTE **gen_kept;
COMMON int gen_kept_nb;
COMMON int is_stability;
COMMON int stability_period;


// Statistics
typedef struct
{
	unsigned int total_pop;
	unsigned int total_births;
	unsigned int total_deaths;
	unsigned int total_surviv;
	unsigned int total_ctime;				   // compute time in msec
	unsigned int total_dtime;				   // draw time in msec
	unsigned int total_ttime;				   // total time in msec
}
STATS;

COMMON STATS gstats;

// Graphics
typedef struct
{
	unsigned int pop;
	unsigned int births;
	unsigned int deaths;
	unsigned int surviv;
}
GRAPHDATA;

COMMON GRAPHDATA *graphdata;
COMMON int graphdata_allcd;					   // Nb of cells of the array allocated

#define	GRAPHDATA_ALLCD_SZ	16

// Life Rules Structure
typedef struct
{
	UBYTE births;							   // 8 bits
	UBYTE births_prob[8];					   // Probabilities [0-100], or 0xFF if none
	UBYTE deaths;							   // 8 bits
	UBYTE deaths_prob[8];					   // Probabilities [0-100], or 0xFF if none
	UBYTE surviv;							   // 8 bits
	UBYTE surviv_prob[8];					   // Probabilities [0-100], or 0xFF if none
}
LRULES;

COMMON LRULES wrk_lrules;					   // Common lrules
COMMON int is_std_rules;					   // Are we using standard rules ?

#define	STD_BIRTHS	0x04		/* 0000 0100 */
#define STD_DEATHS	0xF9		/* 1111 1001 */

// Generation kept in case of automatic/manual seeking
COMMON UBYTE *gen_start_kept_seek;
COMMON UBYTE *gen_best_kept_seek;

// Generation 0 kept
COMMON UBYTE *gen0_kept;

// Set to TRUE while computing next generations (Shift-F3)
COMMON int is_comp_generations;


#define ZOOM_CELL_WIDTH		15
#define ZOOM_CELL_HEIGHT	15
#define ZOOM_ON_SZ			11
#define ZOOM_OFF_SZ			3
COMMON int zoom_xstart GINIT( -1 );
COMMON int zoom_ystart GINIT( -1 );
COMMON int zoom_width GINIT( -1 );
COMMON int zoom_height GINIT( -1 );
COMMON int zoom_xoffset,
  zoom_yoffset;

COMMON GtkWidget *info_gen;
COMMON GtkWidget *info_birth;
COMMON GtkWidget *info_pop;
COMMON GtkWidget *info_death;
COMMON GtkWidget *hsep_stable;
COMMON GtkWidget *label_stable;
COMMON GtkWidget *btn_stop;
COMMON int end_comp_generations;

COMMON GtkWidget *field_scrolledwnd;
COMMON GtkWidget *fielddraw;
COMMON GtkWidget *zoom_scrolledwindow GINIT( NULL );
COMMON GtkWidget *zoom_area;
COMMON GtkWidget *menu_OptionsGrid;			   	// Use by is_grid()
#ifdef SHOW_REDRAW_TIME
COMMON GtkWidget *wgt_label_redrawtime;			// Information: redraw time
#endif
COMMON GdkGC *zoom_on_color;
COMMON GdkGC *zoom_off_color;
COMMON GdkGC *zoom_none_color;
COMMON GdkGC *field_on_color;
COMMON GdkGC *field_off_color;

COMMON	GtkWidget	*zoom_xy;
COMMON	GtkWidget	*zoom_maxgen;

typedef struct
{
	struct
	{
		int	x, y;
		int w, h;
	};
	int nbmin, nbmax;
}	rndgen_t;
COMMON	rndgen_t rndgen;
#define GENRND(a, b ) a + (int) ((double)(b - a + 1) * rand() / (RAND_MAX + (double)1.0));

#endif /*VARGLO_H_*/
