#include <iostream>
#include <cpr/cpr.h>
#include "session.hpp"

using namespace std;

int main() {
  if (!getenv("REFRESH_TOKEN") || !getenv("CONSUMER_KEY")) {
    cout << "error: both REFRESH_TOKEN and CONSUMER_KEY env must be set" << endl;
    return -1;
  }

  auto session = AmeritradeSession(getenv("REFRESH_TOKEN"), getenv("CONSUMER_KEY"), "https://api.tdameritrade.com/v1/");
  cout << session << endl;

  return 0;
}
