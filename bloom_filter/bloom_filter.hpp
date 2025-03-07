#ifndef bloom_filter_HPP
#define bloom_filter_HPP

#include <concepts>
#include <type_traits>

template <typename T>
concept primitive = std::is_arithmetic_v<T>;

template <typename T>
concept composite = requires(T v) {
  { v.data() } -> std::convertible_to<const void*>;
  { v.size() } -> std::convertible_to<std::size_t>;
};

template <typename T>
concept hashable = primitive<T> || composite<T>;

template <hashable T>
class bloom_filter {
  public:
    bloom_filter();
    ~bloom_filter();

  private:
    // Add private members here
};

#endif // bloom_filter_HPP
