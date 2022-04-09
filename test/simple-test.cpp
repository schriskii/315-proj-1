#include "unity.h"
#include "map.hpp"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_simple(void) {
	Map map;
	
	TEST_ASSERT_EQUAL(true, map.add("Jimmy John", 100));
	TEST_ASSERT_EQUAL(true, map.add("Jimmy Joseph", 101));
	TEST_ASSERT_EQUAL(false, map.add("Jimmy John", 102));
	
	TEST_ASSERT_EQUAL(true, map.remove("Jimmy John"));
	TEST_ASSERT_EQUAL(true, map.add("Jimmy John", 102));
	
	int id = 0;
	map.get("Jimmy Jingle", id);
	TEST_ASSERT_EQUAL(0, id);
	map.get("Jimmy Joseph", id);
	TEST_ASSERT_EQUAL(101, id);
	
	TEST_ASSERT_EQUAL(2, map.howMany("Jimmy J"));
	TEST_ASSERT_EQUAL(0, map.howMany("Jimmy Joooooo"));
	
	TEST_ASSERT_EQUAL(15, map.size());
	TEST_ASSERT_EQUAL(true, map.remove("Jimmy John"));
	TEST_ASSERT_EQUAL(13, map.size());
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_simple);
    return UNITY_END();
}
