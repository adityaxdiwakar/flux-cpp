#include <string>
#include <iostream>
#include <format>

#include "session.hpp"
#include "auth.hpp"

#include "cpr/cpr.h"
#include "nlohmann/json.hpp"

using namespace std;

AmeritradeSession::AmeritradeSession(string refresh, string consumer_key, string root_url) 
  : refresh(refresh),
    consumer_key(consumer_key),
    root_url(root_url) {}

AmeritradeSession::AmeritradeSession() {}

void to_json(nlohmann::json& j, const AmeritradeSession& s) {
  j = nlohmann::json {
    {"refresh", s.refresh},
    {"consumer_key", s.consumer_key},
    {"root_url", s.root_url}
  };
}

ostream& operator<<(ostream &os, const AmeritradeSession& s) {
  cout << (nlohmann::json) s;

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

  nlohmann::json j = nlohmann::json::parse(r.text);
  auto access_rsp = j.get<oauth_rsp>();

  this->access_token = access_rsp.access_token;
}
