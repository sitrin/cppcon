#include <iostream>
#include <boost/coroutine2/all.hpp>

int main() {

  typedef boost::coroutines2::coroutine<size_t> coro_t;

  coro_t::pull_type source([&](coro_t::push_type &sink) {
    size_t first = 1, second = 1;
    sink(first);
    sink(second);
    while (true) {
      size_t third = first + second;
      first = second;
      second = third;
      sink(third);
    }
  });

  for (size_t i = 0; i < 4; ++i) {
    std::cout << source.get() << " ";
    source();
  }

  std::cout << "\n";

  return 0;
}
