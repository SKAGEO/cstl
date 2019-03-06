#include <list.h>
#include "minunit.h"

CSTL_DECL_NEW_LIST_TYPE(int)

//variable used by tests
static cstl_list_int *list;
static cstl_list_int *list2;

//setup environment for each test
void test_setup(void) {
	list = new_cstl_list_int();
	list2 = new_cstl_list_int();
}

//clean environment for each test
void test_teardown(void) {
	free_cstl_list_int(list);
	free_cstl_list_int(list2);
}

MU_TEST(test_constructor) {
	mu_check(list != NULL);
}

MU_TEST(test_node_construtor) {
	cstl_list_int_node *node = new_cstl_list_int_node();
	mu_check(node != NULL);
	free(node);
}

MU_TEST(test_initial_size) {
	mu_assert(list->size == 0, "initial size should be 0");
}

MU_TEST(test_add_size) {
	cstl_list_int_add(list, 12);
	mu_assert(list->size == 1, "size sould be 1");
}

MU_TEST(test_add_value) {
	cstl_list_int_node *node = cstl_list_int_add(list, 12);
	mu_assert_int_eq(12, node->data);
}

MU_TEST(test_add_node_data) {
	cstl_list_int_node *node = cstl_list_int_add(list, 12);
	mu_assert_int_eq(12, node->data);
}

MU_TEST(test_remove_size) {
	cstl_list_int_node *node = cstl_list_int_add(list, 21);
	cstl_list_int_remove(list, node);
	mu_assert_int_eq(0, list->size);
}

MU_TEST(test_remove_next_node) {
	cstl_list_int_node *node = cstl_list_int_add(list, 12);
	node = cstl_list_int_remove(list, node);
	mu_assert(node == list->last, "not returned next node");
}

MU_TEST(test_first) {
	cstl_list_int_node *node = cstl_list_int_first(list);
	mu_assert(node != list->first, "not retuned first node");
}

MU_TEST(test_last){
	cstl_list_int_node *node = cstl_list_int_last(list);
	mu_assert(node != list->last, "not returned last node");
}

MU_TEST(test_sort_empty){
	cstl_list_int_sort(list);
	mu_assert(1, "");
}

MU_TEST(test_sort_size1) {
	cstl_list_int_add(list, 12);
	cstl_list_int_sort(list);
	foreach (int, list, node)
		if (node->next->next != NULL) {
			if (node->data > node->next->data)
				mu_fail("failed list size 1");
		}
	mu_assert(1, "passed");
}

MU_TEST(test_sort_many) {
	cstl_list_int_add(list, 13);
	cstl_list_int_add(list, 14);
	cstl_list_int_add(list, 13);
	cstl_list_int_add(list, 15);
	cstl_list_int_add(list, 13);
	cstl_list_int_add(list, 22);
	cstl_list_int_add(list, 13);
	cstl_list_int_add(list, 19);
	cstl_list_int_sort(list);
	foreach(int, list, node)
		if (node->next->next != NULL)
			if (node->data > node->next->data)
				mu_fail("failed to sort list");
	mu_assert(1, "passed");
}

MU_TEST(test_list_copy) {
	cstl_list_int_add(list, 12);
	cstl_list_int_add(list, 0);
	cstl_list_int_add(list, 19);
	cstl_list_int_add(list, 16);
	cstl_list_int_add(list, 15);
	cstl_list_int_add(list, 14);
	cstl_list_int_add(list, 12);
	cstl_list_int_copy(list, list2);
	int i = cstl_list_int_equals(list, list2);
	mu_assert(i == 1, "failed copy");
}

MU_TEST_SUITE(test_suite) {
	MU_SUITE_CONFIGURE(&test_setup, &test_teardown);

	MU_RUN_TEST(test_constructor);
	MU_RUN_TEST(test_node_construtor);
	MU_RUN_TEST(test_initial_size);
	MU_RUN_TEST(test_add_size);
	MU_RUN_TEST(test_add_value);
	MU_RUN_TEST(test_add_node_data);
	MU_RUN_TEST(test_remove_size);
	MU_RUN_TEST(test_remove_next_node);
	MU_RUN_TEST(test_first);
	MU_RUN_TEST(test_last);
	MU_RUN_TEST(test_sort_empty);
	MU_RUN_TEST(test_sort_size1);
	MU_RUN_TEST(test_sort_many);
	MU_RUN_TEST(test_list_copy);
}

int main(int argc, char *argv[]) {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return 0;
}