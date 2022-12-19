#include <iostream>
#include <vector>
#include <cpr/cpr.h>
#include "nlohmann/json.hpp"
#include "quotes.hpp"
#include "session.hpp"

using namespace std;

int main() {
  if (!getenv("REFRESH_TOKEN") || !getenv("CONSUMER_KEY")) {
    cout << "error: both REFRESH_TOKEN and CONSUMER_KEY env must be set" << endl;
    return -1;
  }

  auto session = AmeritradeSession(
    getenv("REFRESH_TOKEN"), 
    getenv("CONSUMER_KEY"), 
    "https://api.tdameritrade.com/v1/",
    "token.dat");

  auto movers_spx = session.get_movers(
    index::SPX, 
    direction::UP, 
    change_metric::PERCENT);

  cout << (nlohmann::json) movers_spx << endl;
  return 0;
}
