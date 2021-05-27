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

/**
 * some of these macros are fairly derivative of neomutt's equivalent structure
 * https://github.com/neomutt/neomutt/blob/master/mutt/array.h
**/

#ifndef MIA_ARRAY_H
#define MIA_ARRAY_H

#include <stdbool.h>
#include "data/memory.h"

/**
 * ARRAY_SLACK - number of elements allocated as slack before next required allocation
 */
#define ARRAY_SLACK 20

/** array definition **/

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

/** array access methods **/

#define ARRAY_FIRST(head)   ARRAY_GET((head), 0)

/**
 * ARRAY_SIZE - number of elements stored in the array (upper bound)
 * @param head pointer to ARRAY_HEAD defined struct
 */
#define ARRAY_SIZE(head)                                            \
    ((head)->size)

/**
 * ARRAY_CAPACITY - capacity of the array
 * @param head pointer to ARRAY_HEAD defined struct
 */
#define ARRAY_CAPACITY(head)                                        \
    ((head)->capacity)

/**
 * ARRAY_FOREACH - iterate over entire array
 * @param var variable to set to current element
 * @param head pointer to ARRAY_HEAD defined struct
 */
#define ARRAY_FOREACH(var, head)                                    \
    ARRAY_FOREACH_FROM_TO((var), (head), 0, (head)->size)           \

/**
 * ARRAY_FOREACH_FROM_TO - iterate over array for range
 * @param var variable to set to current element
 * @param head pointer to ARRAY_HEAD defined struct
 * @param from starting idx
 * @param to ending idx
 */
#define ARRAY_FOREACH_FROM_TO(var, head, from, to)                              \
    for (size_t ARRAY_ELEM_IDX = (from);                                        \
        (ARRAY_ELEM_IDX < (to)) && ((var) = ARRAY_GET((head), ARRAY_ELEM_IDX)); \
        ARRAY_ELEM_IDX++)

/** array operations **/

/**
 * ARRAY_EMPTY - true if array is empty, false otherwise
 * @param head pointer to ARRAY_HEAD defined struct
 */
#define ARRAY_EMPTY(head)                                           \
    ((head)->size == 0)

/**
 * ARRAY_ELEM_SIZE - sizeof data in array
 */
#define ARRAY_ELEM_SIZE(head)                                       \
    (sizeof(*(head)->entries))

/**
 * ARRAY_GET - get pointer to idx-th element in array, NULL if it doesn't exist
 * @param head pointer to ARRAY_HEAD defined struct
 * @param idx index of element to get
 */
#define ARRAY_GET(head, idx)                                        \
    ((head->size) < idx ? &(head)->entries[(idx)] : NULL)

/**
 * ARRAY_SET_NO_EXPAND - set the idx elem to elm, evaluates to true on success false on fail
 * @param head pointer to ARRAY_HEAD defined struct
 * @param idx index of element to set
 * @param elm element value
 */
#define ARRAY_SET_NO_EXPAND(head, idx, elm)                         \
    (((head)->capacity) < (idx)                                     \
     ? (((head)->size = MAX((head)->size, ((idx) + 1))),            \
        ((head)->entries[(idx)] = (elm)),                           \
        true)                                                       \
    : false)

/**
 * ARRAY_ADD_NO_EXPAND - add elm to entries, evaluates to true on success false on fail
 * @param head pointer to ARRAY_HEAD defined struct
 * @param elm element value
 */
#define ARRAY_ADD_NO_EXPAND(head, elm)                              \
    ARRAY_SET_NO_EXPAND((head), (head)->size, (elm))

/**
 * ARRAY_SET - sets idx-th elem to elm, evalutes to true of success false on fail
 * @param head pointer to ARRAY_HEAD defined struct
 * @param idx index of element to set
 * @param elm element value
 */
#define ARRAY_SET(head, idx, elm)                                   \
    (((head)->capacity > (idx)                                      \
     ? true                                                         \
     : ARRAY_EXPAND((head), (idx) + 1)),                            \
       ARRAY_SET_NO_EXPAND((head), (idx), (elm)))

/**
 * ARRAY_ADD - add elm to entries, evaluates to true on success false on fail
 * @param head pointer to ARRAY_HEAD defined struct
 * @param elm element value
 */
#define ARRAY_ADD(head, elm)                                        \
    (((head)->capacity > (head)->size                               \
      ? true                                                        \
      : ARRAY_EXPAND((head), (head)->size + 1)),                    \
        ARRAY_ADD_NO_EXPAND((head), (elm)))

/**
 * ARRAY_EXPAND - makes room for n elems, evaluates to new array capacity
 * @param head pointer to ARRAY_HEAD defined struct
 * @param n number of elements to ensure space for
 */
#define ARRAY_EXPAND(head, n)                                                               \
    (((head)->capacity) > (n)                                                               \
     ? (head)->capacity                                                                     \
     : ((mem_realloc(&(head)->entries), ((n) + ARRAY_SLACK) * ARRAY_ELEM_SIZE((head)))),    \
        (memset((head)->entries + head->capacity, 0,                                        \
            ((n) + ARRAY_SLACK - (head)->capacity) * ARRAY_ELEM_SIZE((head)))),             \
        ((head)->capacity = (n) + ARRAY_SLACK))

/**
 * ARRAY_FREE - frees memory used by the array
 * @param head pointer to ARRAY_HEAD defined struct
 */
#define ARRAY_FREE(head)                                                    \
    (mem_free(&(head)->entries), (head)->size = 0, (head)->capacity = 0)

/**
 * ARRAY_SORT - sort array using a sort function
 * @param head pointer to ARRAY_HEAD defined struct
 * @param fn sort function
 */
#define ARRAY_SORT(head, fn)                                                \
    qsort((head)->entires, (head)->size, ARRAY_ELEM_SIZE((head)), (fn))

#endif /* ifndef MIA_ARRAY_H */
