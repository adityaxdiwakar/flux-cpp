#include <iostream>
#include <cpr/cpr.h>

int main() {
  std::cout << "Starting request..." << std::endl;
  
  cpr::Response r = cpr::Get(cpr::Url{"https://api.diwakar.io/"});

  std::cout << "Status code: " << r.status_code << '\n';
  std::cout << "Header:\n";

  for (const std::pair<const std::basic_string<char>, std::basic_string<char>>& kv : r.header) {
    std::cout << '\t' << kv.first << ':' << kv.second << '\n';
  }
  std::cout << "\n" << "Text: " << r.text << '\n';

  return 0;
}
