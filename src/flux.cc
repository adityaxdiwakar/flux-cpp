#include <iostream>
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
  auto search = session.search_instrument("Apple", search_type::INSTRUMENT_DESC_SEARCH);

  cout << (nlohmann::json) search << endl;
  return 0;
}
