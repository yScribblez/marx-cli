/**
 * vector-like data structure
 *
 * @authors
 * Copyright (C) 2021 Lawson Probasco <ldprobasco@gmail.com>
 *
 * @copyright
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 2 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MIA_ARRAY_H
#define MIA_ARRAY_H

#include <stdbool.h>
#include "memory.h"

/**
 * ARRAY_SLACK - number of elements allocated as slack before next required allocation
 */
#define ARRAY_SLACK 20

/**
 * ARRAY_HEAD - define struct for auto-resizing array
 * @param name name of struct
 * @param type type of elements stored in array
 */
#define ARRAY_HEAD(name, type)                                      \
    struct name {				                                    \
        size_t size; /** number of elements in array **/            \
        size_t capacity; /** max number of elements in array **/	\
        type *entries; /** elements as a c array **/			    \
    }

/**
 * ARRAY_HEAD_INITIALIZER - initialize an array
 */
#define ARRAY_HEAD_INITIALIZER                                      \
    { 0, 0, NULL }

#endif /* ifndef MIA_ARRAY_H */
