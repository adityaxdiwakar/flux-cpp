#include <string>
#include <iostream>
#include <format>

#include "session.hpp"
#include "auth.hpp"

using namespace std;

AmeritradeSession::AmeritradeSession(string refresh, string consumer_key, string root_url) 
  : refresh(refresh),
    consumer_key(consumer_key),
    root_url(root_url) {}

ostream& operator<<(ostream &os, const AmeritradeSession& s) {
  cout << "{refresh: " << s.refresh;
  cout << ", consumer: " << s.consumer_key;
  cout << ", root_url: " << s.root_url;
  cout << "}";

  return os;
}

void AmeritradeSession::get_access_token() {
  auto payload = access_token_struct{
    .grant_type="refresh_token",
    .refresh_token=refresh,
    .client_id=consumer_key + string("@AMER.OAUTHMAP"),
    .redirect_uri=string("http://127.0.0.1"),
  };

  nlohmann::json j = payload; // implicit json conversion
  cout << j << endl;
}
