/**
 * testing list data structure
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

#include <string.h>
#include "acutest.h"
#include "data/list.h"
#include "data/memory.h"

struct ListHead test_list_create(const char *items[], bool copy)
{
  struct ListHead lh = LIST_HEAD_INITIALIZER(lh);

  for (size_t i = 0; items[i]; i++) {
    struct ListNode *np = mem_calloc(1, sizeof(struct ListNode));
    if (copy) np->data = strdup(items[i]);
    else np->data = (char *) items[i];
    LIST_INSERT_HEAD(&lh, np, entries);
  }

  return lh;
}

void test_example(void) {
    // static const char *items[] = {"One", "Two", "Three", NULL};
    static const char *items[] = {"One", NULL};
    struct ListHead h = test_list_create(items, true);
    list_clear(&h);
    TEST_CHECK_(1, "list_clear(&h)");
}

TEST_LIST = {
    { "example", test_example },
    { NULL, NULL }
};
