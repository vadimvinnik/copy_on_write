#include "int_array.h"

#include <catch.hpp>

class int_array_test_fixture
{
public:
  static constexpr int size = 2;
  int_array_test_fixture()
    : origin(size)
  {
    origin.set(0, 11);
    origin.set(1, 37);
  }

protected:
  int_array origin;
};

TEST_CASE_METHOD(int_array_test_fixture, "Get data back", "[int_array]")
{
  REQUIRE(origin.size() == 2);
  REQUIRE(origin.get(0) == 11);
  REQUIRE(origin.get(1) == 37);
}

TEST_CASE_METHOD(int_array_test_fixture, "Modify a single object", "[int_array]")
{
  origin.set(0, 17);
  origin.set(1, 53);

  REQUIRE(origin.size() == 2);
  REQUIRE(origin.get(0) == 17);
  REQUIRE(origin.get(1) == 53);
}

TEST_CASE_METHOD(int_array_test_fixture, "Copy and get data", "[int_array]")
{
  auto copy1 = origin;
  auto copy2 = copy1;

  REQUIRE(copy2.size() == 2);
  REQUIRE(copy2.get(0) == 11);
  REQUIRE(copy2.get(1) == 37);
}

TEST_CASE_METHOD(int_array_test_fixture, "Copy and modify", "[int_array]")
{
  auto copy1 = origin;
  auto copy2 = copy1;

  origin.set(0, 1);
  copy1.set(1, 2);

  REQUIRE(copy2.size() == 2);
  REQUIRE(copy2.get(0) == 11);
  REQUIRE(copy2.get(1) == 37);
}

