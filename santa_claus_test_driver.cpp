
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "child_data_mgmt.h"
#include "tour_plan.h"

#include "shortcut.h"
#include "test_santa_claus.h"

int main(int argc, char *argv[])
{
	ADD_TEST(create_list);
	ADD_TEST(list_add_elements);
	ADD_TEST(list_add_element_after);

	ADD_TEST(create_cdm);
	ADD_TEST(cdm_add_data);

	ADD_TEST(plan_calc_presents);
	ADD_TEST(plan_create_plan);

	run_tests();
	return 0;
}
