#include "int_array.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <string>

class int_array::content {
  int const m_size;
  int* const m_data;

public:
  content(int size)
    : m_size(size)
    , m_data(new int[size])
  {}

  ~content()
  {
    delete[] m_data;
  }

  content(int_array::content const& other)
    : m_size(other.m_size)
    , m_data(new int[other.m_size])
  {
    std::copy(
        other.m_data,
        other.m_data + other.m_size,
        m_data);
  }

  content(int_array::content&&) = delete;

  int_array::content& operator=(int_array::content const&) = delete;
  int_array::content& operator=(int_array::content&&) = delete;

  int size() const
  {
    return m_size;
  }

  int get_value(int i) const
  {
    return m_data[i];
  }

  void set_value(int i, int x)
  {
    m_data[i] = x;
  }

  void clear()
  {
    std::fill(m_data, m_data + m_size, 0);
  }
};

int_array::int_array(int size)
  : m_wrapped_content(size)
{}

int int_array::size() const noexcept
{
  return m_wrapped_content.query(
      std::bind(
        &int_array::content::size,
        std::placeholders::_1));
}

int int_array::get(int i) const
{
  return m_wrapped_content.query(
      std::bind(
        &int_array::content::get_value,
        std::placeholders::_1,
        i));
}

void int_array::set(int i, int x)
{
  m_wrapped_content.modify(
      std::bind(
        &int_array::content::set_value,
        std::placeholders::_1,
        i,
        x));
}

void int_array::clear()
{
  m_wrapped_content.modify(
      std::bind(
        &int_array::content::clear,
        std::placeholders::_1));
}

