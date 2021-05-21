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

void test_clear(void) {
    static const char *items[] = {"One", "Two", "Three", NULL};
    struct ListHead h = test_list_create(items, false);
    list_clear(&h);
    TEST_CHECK_(1, "list_clear(&h)");
}

void test_free(void) {
    static const char *items[] = {"One", "Two", "Three", NULL};
    struct ListHead h = test_list_create(items, true);
    list_free(&h);
    TEST_CHECK_(1, "list_free(&h)");
}

void test_compare(void) {
    static const char *items[] = {"One", "Two", "Three", NULL};
    static const char *items_diff[] = {"One", "Two", NULL};
    struct ListHead ah = test_list_create(items, false);
    struct ListHead bh = test_list_create(items, false);
    struct ListHead ch = test_list_create(items_diff, false);
    TEST_CHECK_(list_compare(&ah, &bh) == true, "list_compare(&ah, &bh)");
    TEST_CHECK_(list_compare(&ah, &ch) == false, "list_compare(&ah, &ch)");
}

void test_find(void) {
    static const char *items[] = {"One", "Two", "Three", NULL};
    struct ListHead ah = test_list_create(items, false);
    TEST_CHECK_(list_find(&ah, "One") != NULL, "list_find(&ah, \"One\")");
    TEST_CHECK_(list_find(&ah, "Two") != NULL, "list_find(&ah, \"Two\")");
    TEST_CHECK_(list_find(&ah, "Three") != NULL, "list_find(&ah, \"Three\")");
    TEST_CHECK_(list_find(&ah, "Four") == NULL, "list_find(&ah, \"Four\")");
}

void test_insert_head(void) {
    static const char *items[] = {"One", "Two", "Three", NULL};
    struct ListHead ah = test_list_create(items, false);
    TEST_CHECK(LIST_FIRST(&ah) == list_find(&ah, "Three"));
    list_insert_head(&ah, "Four");
    TEST_CHECK_(1, "list_insert_head(&h, \"Four\")");
    TEST_CHECK(LIST_FIRST(&ah) == list_find(&ah, "Four"));
}

void test_insert_after(void) {
    static const char *items[] = {"One", "Two", "Three", NULL};
    struct ListHead ah = test_list_create(items, false);
    struct ListNode *two = list_find(&ah, "Two");
    TEST_CHECK(two->entries.le_next == list_find(&ah, "One"));
    struct ListNode *four = list_insert_after(two, "Four");
    TEST_CHECK_(1, "list_insert_after(two, \"Four\")");
    TEST_CHECK(two->entries.le_next == four);
}

void test_insert_before(void) {
    static const char *items[] = {"One", "Two", "Three", NULL};
    struct ListHead ah = test_list_create(items, false);
    struct ListNode *two = list_find(&ah, "Two");
    TEST_CHECK(two->entries.le_next == list_find(&ah, "One"));
    struct ListNode *four = list_insert_before(two, "Four");
    TEST_CHECK_(1, "list_insert_before(two, \"Four\")");
    TEST_CHECK(four->entries.le_next == two);
}

TEST_LIST = {
    { "test_clear", test_clear },
    { "test_free", test_free },
    { "test_compare", test_compare },
    { "test_find", test_find },
    { "test_insert_head", test_insert_head },
    { "test_insert_after", test_insert_after },
    { "test_insert_before", test_insert_before },
    { NULL, NULL }
};
