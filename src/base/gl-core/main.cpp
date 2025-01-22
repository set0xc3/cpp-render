#include <boost/thread.hpp>
#include <iostream>

void hello() { std::cout << "Hello from thread!" << std::endl; }

int main() {
  boost::thread thrd(&hello);
  thrd.join();
  return 0;
}
