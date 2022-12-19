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
    "https://api.tdameritrade.com/v1/");
  auto q = session.quote_securities({"AAPL"});
  auto funs = session.get_fundamentals("AAPL");
  auto hours = session.get_market_hours(
    vector<market_type>{
      market_type::MARKET_OPTION, 
      market_type::MARKET_EQUITY,
      market_type::MARKET_BOND,
      market_type::MARKET_FUTURE
    }, "2022-12-19");

  cout << (nlohmann::json) hours << endl;
  return 0;
}
