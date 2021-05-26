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

    struct ListNode *np, *np_temp, *np_del;
    TAILQ_FOREACH_SAFE(np, h, entries, np_temp) {
        np_del = np;
        TAILQ_REMOVE(h, np, entries);
        mem_free(np_del->data);
        mem_free(np_del);
    }

    TAILQ_INIT(h);
}

/**
 * list_clear - free list without clearing data
 * @param h head of list
 */
void list_clear(struct ListHead *h) {
    if (!h) return;

    struct ListNode *np, *np_temp, *np_del;
    TAILQ_FOREACH_SAFE(np, h, entries, np_temp) {
        np_del = np;
        TAILQ_REMOVE(h, np, entries);
        mem_free(np_del);
    }

    TAILQ_INIT(h);
}

/**
 * list_compare - compares two lists
 * @param ah head of first list
 * @param bh head of second list
 */
bool list_compare(struct ListHead *ah, struct ListHead *bh) {
    if (!ah || !bh) return false;

    struct ListNode *anp, *bnp;
    for (anp = TAILQ_FIRST(ah), bnp = TAILQ_FIRST(bh); anp != TAILQ_END(ah) && bnp != TAILQ_END(bh);
            anp = TAILQ_NEXT(anp, entries), bnp = TAILQ_NEXT(bnp, entries)) {
        if (strcmp(anp->data, bnp->data)) return false;
    }
    if ((anp != TAILQ_END(ah)) || (bnp != TAILQ_END(bh))) return false;

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
    TAILQ_FOREACH(np, h, entries) {
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
    TAILQ_INSERT_HEAD(h, np, entries);

    return np;
}

/**
 * list_insert_after - insert an element after a given node
 * @param n node
 * @param data element to insert
 */
struct ListNode *list_insert_after(struct ListHead *h, struct ListNode *n, char *data) {
    if (!n) return NULL;

    struct ListNode *np = mem_malloc(sizeof(struct ListNode));
    np->data = data;
    TAILQ_INSERT_AFTER(h, n, np, entries);

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
    TAILQ_INSERT_BEFORE(n, np, entries);

    return np;
}
