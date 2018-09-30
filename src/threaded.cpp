#include <iostream>
#include <thread>
#include <chrono>

inline void clear_line() {
	std::cout << "\r                                                           \r";
}

void reprint_lines(const std::string& string) {
	
}


int main() {
  std::cout << "\n\tHello World!" << std::flush;

std::this_thread::sleep_for (std::chrono::seconds(1));
  clear_line();
  std::cout << "\tBoogers" << std::flush;
std::this_thread::sleep_for (std::chrono::seconds(1));
   std::cout << "\n\n";
  return 0;
}
