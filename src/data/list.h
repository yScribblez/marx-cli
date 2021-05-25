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

#ifndef MIA_LIST_H
#define MIA_LIST_H

#include <stddef.h>
#include <stdbool.h>
#include "queue.h"

/**
 * struct ListNode - list node with char* payload
 */
struct ListNode {
    char *data;
    LIST_ENTRY(ListNode) entries;
};
LIST_HEAD(ListHead, ListNode);

void list_free(struct ListHead *h);
void list_clear(struct ListHead *h);
bool list_compare(struct ListHead *ah, struct ListHead *bh);
struct ListNode *list_find(const struct ListHead *h, const char *data);
struct ListNode *list_insert_head(struct ListHead *h, char *data);
struct ListNode *list_insert_after(struct ListNode *n, char *data);
struct ListNode *list_insert_before(struct ListNode *n, char *data);

#endif /* ifndef MIA_LIST_H */
