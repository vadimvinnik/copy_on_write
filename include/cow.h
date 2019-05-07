#pragma once

#include <cassert>
#include <memory>

namespace cow
{

template <typename T>
class wrapper
{
public:
  using content_t = T;
  using content_ptr_t = std::shared_ptr<T>;
  using this_t = wrapper<T>;

  template <typename... Args>
  explicit wrapper(Args&&... args)
    : m_content_ptr(
        std::make_shared<content_t>(
          std::forward<Args>(args)...))
  {}

  wrapper(this_t const&) = default;
  wrapper(this_t&&) = default;
  this_t& operator=(this_t const&) = default;
  this_t& operator=(this_t&&) = default;

  template <typename F>
  auto query(F f) const
  {
    return f(const_get());
  }

  template <typename F>
  auto modify(F f)
  {
    if (!m_content_ptr.unique())
    {
      m_content_ptr = std::make_shared<content_t>(const_get());
    }

    assert(m_content_ptr.unique());

    f(*m_content_ptr);
  }

private:
  content_t const& const_get() const
  {
    return *m_content_ptr;
  }

  content_ptr_t m_content_ptr;
};

}

