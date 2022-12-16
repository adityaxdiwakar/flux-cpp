#include <iostream>
#include <cpr/cpr.h>
#include "session.hpp"

using namespace std;

int main() {
  auto session = AmeritradeSession("refresh", "consumer_key", "root_url");
  cout << session << endl;

  session.get_access_token();

  return 0;
}
