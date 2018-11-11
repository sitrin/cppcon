#include <array>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>
#include <mutex>

#include <thread>
#include <vector>

void non_threadsafe_increment_array(std::array<size_t, 10> &a) {
  for (size_t i = 0; i < 100'000; ++i) {
      for(auto& item : a) ++item;
  }
}

void threadsafe_increment_array(std::array<size_t, 10> &a) {
  static std::mutex mtx;
  for (size_t i = 0; i < 100'000; ++i) {
      std::scoped_lock lock(mtx);
      for(auto& item : a) ++item;
  }
}

int main() {

  constexpr size_t NUM_THREADS = 13;

  std::array<size_t, 10> array_of_counters = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  std::vector<std::thread> vec_of_threads;

  auto start = std::chrono::system_clock::now();
  for (size_t i = 0; i < NUM_THREADS; ++i) {
    vec_of_threads.emplace_back(non_threadsafe_increment_array, std::ref(array_of_counters));
  }

  for (auto &thread : vec_of_threads)
    thread.join();
  std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - start;

  std::cout << "\n";
  std::copy(array_of_counters.begin(), array_of_counters.end(), std::ostream_iterator<size_t>(std::cout, " "));
  std::cout << "\n\nElapsed seconds (not threadsafe): " << elapsed_seconds.count() << "\n\n";

  // clear thread vector and counter arrays
  vec_of_threads.clear();
  std::fill_n(array_of_counters.begin(), array_of_counters.size(), 0);

  start = std::chrono::system_clock::now();
  for (size_t i = 0; i < NUM_THREADS; ++i) {
    vec_of_threads.emplace_back(threadsafe_increment_array, std::ref(array_of_counters));
  }

  for (auto &thread : vec_of_threads)
    thread.join();
  elapsed_seconds = std::chrono::system_clock::now() - start;

  std::cout << "\n";
  std::copy(array_of_counters.begin(), array_of_counters.end(), std::ostream_iterator<size_t>(std::cout, " "));
  std::cout << "\n\nElapsed seconds (threadsafe): " << elapsed_seconds.count() << "\n\n";

  return 0;
}
