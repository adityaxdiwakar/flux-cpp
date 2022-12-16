#include <iostream>
#include <cpr/cpr.h>
#include "session.h"

using namespace std;

int main() {
  auto session = AmeritradeSession("refresh", "consumer_key", "root_url");
  cout << session << endl;

  return 0;
}
