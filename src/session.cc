#include <string>
#include <iostream>
#include <format>
#include "cpr/cpr.h"

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
  auto req_payload = cpr::Payload{
    {"grant_type", gt_refresh_token},
    {"refresh_token", refresh},
    {"client_id", consumer_key + "@AMER.OAUTHMAP"},
    {"redirect_uri", "http://127.0.0.1"}
  };

  cpr::Response r = cpr::Post(cpr::Url{root_url + "oauth2/token"}, req_payload);
}
