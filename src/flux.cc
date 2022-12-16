#include <iostream>
#include <cpr/cpr.h>
#include "session.hpp"

using namespace std;

int main() {
  auto session = AmeritradeSession("refresh", "consumer_key", "https://api.tdameritrade.com/v1/");
  cout << session << endl;

  session.get_access_token();

  return 0;
}
