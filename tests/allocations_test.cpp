#include "cow.h"

#include <catch.hpp>
#include <cstdint>

static int content_count = 0;

struct dummy_content {
  dummy_content() {
    ++content_count;
  }

  dummy_content(dummy_content const&) {
    ++content_count;
  }

  dummy_content(dummy_content&&) = delete;
  dummy_content& operator=(dummy_content const&) = delete;
  dummy_content& operator=(dummy_content&&) = delete;

  ~dummy_content() {
    --content_count;
  }
};

std::nullptr_t dummy_function(dummy_content const&) {
  return nullptr;
}

std::uintptr_t get_adderss_backdoor(dummy_content const& x) {
    return reinterpret_cast<std::uintptr_t>(&x);
}

class dummy {
  cow::wrapper<dummy_content> m_wrapped_content;

public:
  auto get() const {
    return m_wrapped_content.query(&dummy_function);
  }

  auto modify() {
    return m_wrapped_content.modify(&dummy_function);
  }

  std::uintptr_t get_content_adderss_backdoor() const
  {
    return m_wrapped_content.query(&get_adderss_backdoor);
  }
};

TEST_CASE("Creating a wrapper creates a content") {
  auto const content_count_before = content_count;
  dummy d;
  auto const content_count_after = content_count;

  REQUIRE (content_count_after == content_count_before + 1);
}

TEST_CASE("Deleting a wrapper deletes the content") {
  auto const content_count_before = content_count;
  {
    dummy d;
  }
  auto const content_count_after = content_count;

  REQUIRE (content_count_after == content_count_before);
}

TEST_CASE("Copying a wrapper shares the content") {
  dummy d;
  auto const content_count_before = content_count;
  auto const content_address_before = d.get_content_adderss_backdoor();
  dummy x = d;
  dummy y = x;
  auto const content_count_after = content_count;

  REQUIRE (content_count_after == content_count_before);
  REQUIRE (x.get_content_adderss_backdoor() == content_address_before);
  REQUIRE (y.get_content_adderss_backdoor() == content_address_before);
}

TEST_CASE("Getting does not affect the content") {
  dummy d;
  auto const content_count_before = content_count;
  auto const content_address_before = d.get_content_adderss_backdoor();
  d.get();
  auto const content_count_after = content_count;
  auto const content_address_after = d.get_content_adderss_backdoor();

  REQUIRE (content_count_after == content_count_before);
  REQUIRE (content_address_after == content_address_before);
}

TEST_CASE("Modification of a unique wrapper does not affect the content") {
  dummy d;
  auto const content_count_before = content_count;
  auto const content_address_before = d.get_content_adderss_backdoor();
  d.modify();
  auto const content_count_after = content_count;
  auto const content_address_after = d.get_content_adderss_backdoor();

  REQUIRE (content_count_after == content_count_before);
  REQUIRE (content_address_after == content_address_before);
}

TEST_CASE("Modification of a sharing wrapper copies the content") {
  dummy d;
  auto const content_count_before = content_count;
  auto const content_address_before = d.get_content_adderss_backdoor();
  auto x = d;
  auto y = x;
  d.modify();
  auto const content_count_after = content_count;

  REQUIRE (content_count_after == content_count_before + 1);
  REQUIRE (d.get_content_adderss_backdoor() != content_address_before);
  REQUIRE (x.get_content_adderss_backdoor() == content_address_before);
  REQUIRE (y.get_content_adderss_backdoor() == content_address_before);
}

