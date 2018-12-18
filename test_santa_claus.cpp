
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "child_data_mgmt.h"
#include "tour_plan.h"

#include "shortcut.h"
#include "test_santa_claus.h"

struct Dummy{
	int val;
};

// List Tests
TEST(create_list)
{
	List *list = list_create();
	ASSERT_FALSE(list == 0, "List has to be created");
	list_delete(list);
}

TEST(list_add_elements)
{
	List *list = list_create();

	struct Dummy dummies[] = {
			{1},
			{2},
			{3}
	};
	list_add(list, &dummies[0]);
	list_add(list, &dummies[1]);
	list_add(list, &dummies[2]);
	Node* head = list_get_first(list);
	Node* second = list_get_next(head);
	Node* third = list_get_next(second);
	Dummy *first_dummy = (Dummy*) list_get_data(head);
	Dummy *second_dummy = (Dummy*) list_get_data(second);
	Dummy *third_dummy = (Dummy*) list_get_data(third);

	ASSERT_EQUALS(3, first_dummy->val);
	ASSERT_EQUALS(2, second_dummy->val);
	ASSERT_EQUALS(1, third_dummy->val);
	ASSERT_TRUE(list_get_next(third) == 0, "Last node has a null pointer as next");

	list_delete(list);
}

TEST(list_add_element_after)
{
	List *list = list_create();

	struct Dummy dummies[] = {
			{1},
			{2},
			{3}
	};
	list_add(list, &dummies[0]);
	Node *head = list_get_first(list);
	list_insert_after(head, &dummies[1]);
	Node *second = list_get_next(head);
	list_insert_after(second, &dummies[2]);
	Node *third = list_get_next(second);
	Dummy *first_dummy = (Dummy*) list_get_data(head);
	Dummy *second_dummy = (Dummy*) list_get_data(second);
	Dummy *third_dummy = (Dummy*) list_get_data(third);

	ASSERT_EQUALS(1, first_dummy->val);
	ASSERT_EQUALS(2, second_dummy->val);
	ASSERT_EQUALS(3, third_dummy->val);
	ASSERT_TRUE(list_get_next(third) == 0, "Last node has a null pointer as next");

	list_delete(list);
}

// ChildDataMgmt Tests
TEST(create_cdm)
{
	ChildDataMgmt *cdm = cdm_create();
	ASSERT_FALSE(cdm == 0, "ChildDataMgmt has to be created");
	cdm_delete(cdm);
}

TEST(cdm_add_data)
{
	ChildDataMgmt *cdm = cdm_create();

	ChildData child_infos[] = {
			{"TestCity1", "Tester1", 0.9},
			{"TestCity2", "Tester2", 0.6},
			{"TestCity1", "Tester3", 0.3}
	};
	cdm_add_data(cdm, &child_infos[0]);
	cdm_add_data(cdm, &child_infos[1]);
	cdm_add_data(cdm, &child_infos[2]);
	Node *head = cdm_get_sorted_data(cdm);
	Node *second = list_get_next(head);
	Node *third = list_get_next(second);
	ChildData *first_child = (ChildData*) list_get_data(head);
	ChildData *second_child = (ChildData*) list_get_data(second);
	ChildData *third_child = (ChildData*) list_get_data(third);

	ASSERT_EQUALS("Tester1", first_child->name);
	ASSERT_EQUALS("TestCity1", first_child->city);
	ASSERT_EQUALS("Tester3", second_child->name);
	ASSERT_EQUALS("TestCity1", second_child->city);
	ASSERT_EQUALS("Tester2", third_child->name);
	ASSERT_EQUALS("TestCity2", third_child->city);
	ASSERT_TRUE(list_get_next(third) == 0, "Only three elements in the list");

	cdm_delete(cdm);
}

//TourPlan Tests
TEST(plan_calc_presents)
{
	ASSERT_EQUALS(0, plan_calc_presents(-312.8));
	ASSERT_EQUALS(0, plan_calc_presents(0.0));
	ASSERT_EQUALS(0, plan_calc_presents(0.1));
	ASSERT_EQUALS(0, plan_calc_presents(0.2));
	ASSERT_EQUALS(0, plan_calc_presents(0.3));
	ASSERT_EQUALS(0, plan_calc_presents(0.4));
	ASSERT_EQUALS(0, plan_calc_presents(0.5));
	ASSERT_EQUALS(1, plan_calc_presents(0.6));
	ASSERT_EQUALS(2, plan_calc_presents(0.7));
	ASSERT_EQUALS(3, plan_calc_presents(0.8));
	ASSERT_EQUALS(4, plan_calc_presents(0.9));
	ASSERT_EQUALS(5, plan_calc_presents(1.0));
	ASSERT_EQUALS(5, plan_calc_presents(6.2));
}

TEST(plan_create_plan)
{
	ChildDataMgmt *cdm = cdm_create();
	ChildData child_infos[] = {
			{"TestCity1", "Tester1", 0.9},
			{"TestCity2", "Tester2", 0.6},
			{"TestCity1", "Tester3", 0.3}
	};
	cdm_add_data(cdm, &child_infos[0]);
	cdm_add_data(cdm, &child_infos[1]);
	cdm_add_data(cdm, &child_infos[2]);

	TourPlan *plan = plan_createTour(cdm);
	ASSERT_FALSE(plan == 0, "TourPlan has to be created");
	ASSERT_EQUALS(3, plan->total_children);
	ASSERT_EQUALS(5, plan->total_presents);

	List *city_plans = plan->city_plans;
	Node *first_city = list_get_first(city_plans);
	Node *second_city = list_get_next(first_city);
	ASSERT_TRUE(list_get_next(second_city) == 0, "Only two cities are in the plan");

	CityPlan *first_city_plan = (CityPlan*) list_get_data(first_city);
	ASSERT_EQUALS("TestCity2", first_city_plan->city);
	List *child_plans = first_city_plan->child_plans;
	Node *first_child = list_get_first(child_plans);
	ASSERT_TRUE(list_get_next(first_child) == 0, "Only a single child in this city");
	ChildPlan *first_child_plan = (ChildPlan*) list_get_data(first_child);
	ASSERT_EQUALS("Tester2", first_child_plan->name);
	ASSERT_EQUALS(1, first_child_plan->presents);

	CityPlan *second_city_plan = (CityPlan*) list_get_data(second_city);
	ASSERT_EQUALS("TestCity1", second_city_plan->city);
	child_plans = second_city_plan->child_plans;
	first_child = list_get_first(child_plans);
	Node *second_child = list_get_next(first_child);
	ASSERT_TRUE(list_get_next(second_child) == 0, "Only two children in this city");
	first_child_plan = (ChildPlan*) list_get_data(first_child);
	ChildPlan *second_child_plan = (ChildPlan*) list_get_data(second_child);
	ASSERT_EQUALS("Tester3", first_child_plan->name);
	ASSERT_EQUALS(0, first_child_plan->presents);
	ASSERT_EQUALS("Tester1", second_child_plan->name);
	ASSERT_EQUALS(4, second_child_plan->presents);

	plan_delete(plan);
	cdm_delete(cdm);
}
