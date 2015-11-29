/**
 * @file all.h
 *
 * freelife: Conway Game of Life \n
 * Copyright (C) 1999-2007  Olivier Singla \n
 * http://freelife.sourceforge.net/ \n
 */

#ifndef ALL_H_
#define ALL_H_

#define __STDC_CONSTANT_MACROS 	/**< TBD **/
#define _GNU_SOURCE				/**< TBD **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/time.h>
#include <assert.h>
#include <ctype.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

#include <gdk/gdkx.h>
#include <X11/Xlib.h>

#include "life.h"
#include "field.h"
#include "main.h"
#include "settings.h"
#include "utils.h"
#include "zoom.h"

#include "vars_glo.h"

#endif                         /*ALL_H_ */
