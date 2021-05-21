/**
 * doubly-linked list
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

// http://www.manpagez.com/man/3/queue/ (for future reference)

#include <stdio.h>
#include <string.h>
#include "data/list.h"
#include "data/memory.h"

/**
 * list_free - free list and clear data
 * @param h head of list
 */
void list_free(struct ListHead *h) {
    if (!h) return;

    struct ListNode *np, *np_temp;
    LIST_FOREACH_SAFE(np, h, entries, np_temp) {
        LIST_REMOVE(np, entries);
        mem_free(np->data);
        mem_free(np);
    }

    LIST_INIT(h);
}

/**
 * list_clear - free list without clearing data
 * @param h head of list
 */
void list_clear(struct ListHead *h) {
    if (!h) return;

    struct ListNode *np, *np_temp;
    LIST_FOREACH_SAFE(np, h, entries, np_temp) {
        LIST_REMOVE(np, entries);
        mem_free(np);
    }

    LIST_INIT(h);
}

/**
 * list_compare - compares two lists
 * @param ah head of first list
 * @param bh head of second list
 */
bool list_compare(struct ListHead *ah, struct ListHead *bh) {
    if (!ah || !bh) return false;

    struct ListNode *anp, *bnp;
    for (anp = LIST_FIRST(ah), bnp = LIST_FIRST(bh); anp != LIST_END(ah) && bnp != LIST_END(bh);
            anp = LIST_NEXT(anp, entries), bnp = LIST_NEXT(bnp, entries)) {
        if (strcmp(anp->data, bnp->data)) return false;
    }
    if ((anp != LIST_END(ah)) || (bnp != LIST_END(bh))) return false;

    return true;
}

/**
 * list_find - find an element in the list
 * @param h head of list
 * @param data element to search for
 */
struct ListNode *list_find(const struct ListHead *h, const char *data) {
    if (!h) return NULL;

    struct ListNode *np;
    LIST_FOREACH(np, h, entries) {
        if (strcmp(np->data, data) == 0) return np;
    }

    return NULL;
}

/**
 * list_insert_head - insert an element at the front of the list
 * @param h head of list
 * @param data element to insert
 */
struct ListNode *list_insert_head(struct ListHead *h, char *data) {
    if (!h) return NULL;

    struct ListNode *np = mem_malloc(sizeof(struct ListNode));
    np->data = data;
    LIST_INSERT_HEAD(h, np, entries);

    return np;
}

/**
 * list_insert_after - insert an element after a given node
 * @param n node
 * @param data element to insert
 */
struct ListNode *list_insert_after(struct ListNode *n, char *data) {
    if (!n) return NULL;

    struct ListNode *np = mem_malloc(sizeof(struct ListNode));
    np->data = data;
    LIST_INSERT_AFTER(n, np, entries);

    return np;
}

/**
 * list_insert_before - insert an element before a given node
 * @param n node
 * @param data element to insert
 */
struct ListNode *list_insert_before(struct ListNode *n, char *data) {
    if (!n) return NULL;

    struct ListNode *np = mem_malloc(sizeof(struct ListNode));
    np->data = data;
    LIST_INSERT_BEFORE(n, np, entries);

    return np;
}
