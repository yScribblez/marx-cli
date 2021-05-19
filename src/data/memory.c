/**
 * memory management wrappers
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

// @TODO: additional logic for when/if logging is implemented

#include <stdlib.h>
#include "memory.h"

/**
 * mem_free - frees memory from heap
 * @param ptr pointer to memory region to be free
 */
void mem_free(void *ptr) {
    if (!ptr) return;

    free(ptr);
}

/**
 * mem_malloc - allocates memory on the heap
 * @param size size of memory region to be allocated
 */
void *mem_malloc(size_t size) {
    if (size == 0) return NULL;

    return malloc(size);
}

/**
 * mem_realloc - reallocates heap memory region
 * @param ptr pointer to region to be reallocated
 * @param size pointer size of memory region after reallocation
 */
void *mem_realloc(void *ptr, size_t size) {
    if (!ptr) return NULL;

    if (size == 0) {
        free(ptr);
        return NULL;
    }

    return realloc(ptr, size);
}

/**
 * mem_calloc - allocates and zeros out heap memory region
 * @param nmemb number of objects
 * @param size size of objects
 */
void *mem_calloc(size_t nmemb, size_t size) {
    if ((nmemb == 0) || (size == 0)) return NULL;
    return calloc(nmemb, size);
}
