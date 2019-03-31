#include "minunit.h"
#include <cstl/list.h>

static cstl_list *list;

void test_setup() {
	list = cstl_newList();
}

void test_teardown() {
	cstl_freeList(list);
}

MU_TEST_SUITE(test_suite) {
	MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
}

int main(int argc, char *argv[]) {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return 0;
}