#include "acutest.h"
#include "data/list.h"

void test_example(void) {
    TEST_CHECK(1 == 1);
}

TEST_LIST = {
    { "example", test_example },
    { NULL, NULL }
};
