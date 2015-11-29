/**
 *
 * @file vars_glo.h
 *
 * @brief Global Variables.
 *
 */

#ifndef LIFE_H_
#define LIFE_H_

#if 0
#if defined(PRINT_TRACE)
#	define TRACE(fmt, args...)	printf( fmt, ## args )
#else
#	define TRACE(fmt, args...)
#endif
#endif

void compute_gen( void );
void show_life_pop( void );
void show_infos( void );
void compute_generations( void );
void restore_prev_gen( void );
void restore_gen0( void );

#endif /*LIFE_H_*/
