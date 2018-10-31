#include <array>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>
#include <mutex>

#include <thread>
#include <vector>

std::mutex mtx;

inline void clearline(std::ostream &os) {
      os << "\r                                                           \r";
}

void printarray(const std::array<int, 10> &a, std::ostream &os) {
	clearline(os);
	os << "\t";
        std::copy(a.begin(), a.end(), std::ostream_iterator<int>(std::cout, " "));
	os.flush();
}

void update_array(std::array<int, 10>& array_of_ints, std::ostream &os, size_t index) {
	for(size_t i=0; i<9; ++i) {
		{
			{
				std::scoped_lock lock(mtx);
				array_of_ints[index]++;
				printarray(array_of_ints, os);	
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(100*index));
		}
	}
}
	
int main() {

  std::cout << "\n";

  std::array<int, 10> array_of_ints = { {0,0,0,0,0,0,0,0,0,0 } };

  std::vector<std::thread> vec_of_threads;

  for(size_t i=0; i<array_of_ints.size(); ++i) {
	vec_of_threads.emplace_back(update_array, std::ref(array_of_ints), std::ref(std::cout), i);
  }

  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::this_thread::sleep_for(std::chrono::seconds(1));

       for (auto &thread : vec_of_threads) thread.join();
  std::cout << "\n\n";


  return 0;
}
