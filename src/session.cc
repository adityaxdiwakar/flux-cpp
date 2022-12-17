#include <string>
#include <iostream>
#include <format>

#include "session.hpp"
#include "auth.hpp"
#include "quotes.hpp"

#include "cpr/cpr.h"
#include "nlohmann/json.hpp"

using namespace std;

/**
 * Construct an AmeritradeSession with neccesary information to initialize.
 *
 * @param a refresh token to generate access tokens
 * @param a consumer_key generated from the TDAmeritrade Developer portal
 * @param a root_url to make an API request (useful for /v1/ or /v2/ in future)
 */
AmeritradeSession::AmeritradeSession(string refresh, string consumer_key, string root_url) 
  : refresh(refresh),
    consumer_key(consumer_key),
    root_url(root_url) {

  init_access_token();
}

AmeritradeSession::AmeritradeSession() {}

/**
 * Set a JSON object with the representation of an AmeritradeSession.
 *
 * @param a JSON object to be written into
 * @param a constant (immutable) AmeritradeSession reference to JSON represent
 */
void to_json(nlohmann::json& j, const AmeritradeSession& s) {
  j = nlohmann::json {
    {"refresh", s.refresh},
    {"consumer_key", s.consumer_key},
    {"root_url", s.root_url}
  };
}

/**
 * Overload stream operator to print out an AmeritradeSession.
 *
 * @return a stream object with AmeritradeSession added
 */
ostream& operator<<(ostream &os, const AmeritradeSession& s) {
  cout << (nlohmann::json) s;
  return os;
}

/**
 * Dynamically initialize access token.
 *
 * This function initializes the access token and stores it as a private 
 * session field. TODO: This function only initializes or regenerates
 * a token if the token has expired.
 */
void AmeritradeSession::init_access_token() {
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

/**
 * Return a valid access token.
 *
 * This function will use an existing session object and return a valid access
 * token or regenerate one if the existing token has expired. This function
 * only needs to be called if a token is needed for external purposes, such
 * as connecting with fluxcpp-socket.
 *
 * @return a valid TDAmeritrade API access token
 */
string AmeritradeSession::get_access_token() {
  init_access_token();
  return access_token;
}

unordered_map<string, quoted_instrument> AmeritradeSession::quote_securities(initializer_list<std::string_view> securities) {
  return unordered_map<string, quoted_instrument>();
}

quoted_instrument AmeritradeSession::quote_security(string security) {
  return quoted_instrument{};
}
