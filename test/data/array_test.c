/**
 * testing array implementation
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

#include "unity.h"
#include "data/array.h"

struct TestStruct {
    size_t a;
    size_t b;
};

ARRAY_HEAD(ArrayHead, struct TestStruct);
struct ArrayHead h;

void setUp(void) {
    h.size = 0;
    h.capacity = 0;
    h.entries = NULL;
}

void tearDown(void) {
    // ARRAY_FREE(&h);
}

void test_free(void) {
    // ARRAY_FREE(&h);
    TEST_ASSERT(1);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_free);
    return UNITY_END();
}
