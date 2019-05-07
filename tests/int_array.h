#pragma once

#include "cow.h"

class int_array {
  class content;
  cow::wrapper<content> m_wrapped_content;

public:
  explicit int_array(int size);

  int_array(int_array const&) = default;
  int_array(int_array&&) = default;
  int_array& operator=(int_array const& other) = default;
  int_array& operator=(int_array&& other) = default;

  int size() const noexcept;
  int get(int i) const;
  void set(int i, int x);
  void clear();
};

