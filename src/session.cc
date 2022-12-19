#include <string>
#include <iostream>
#include <format>

#include "session.hpp"
#include "auth.hpp"
#include "quotes.hpp"
#include "instruments.hpp"

#include "cpr/cpr.h"
#include "nlohmann/json.hpp"

using namespace std;

/**
 * Construct a custom ApiException with a status code.
 *
 * @param a status code to represent the error
 */
ApiException::ApiException(int code) : status_code(code) {}

/**
 * A getter method to retrieve the status code from an exception.
 *
 * @return the status code associated with the exception
 */
int ApiException::get_code() { return status_code; }

/**
 * Construct an AmeritradeSession with neccesary information to initialize.
 *
 * @param a refresh token to generate access tokens
 * @param a consumer_key generated from the TDAmeritrade Developer portal
 * @param a root_url to make an API request (useful for /v1/ or /v2/ in future)
 */
AmeritradeSession::AmeritradeSession(
    string refresh, 
    string consumer_key, 
    string root_url) 
  : refresh_(refresh),
    consumer_key_(consumer_key),
    root_url_(root_url) {

  this->init_access_token_();
}

/**
 * Construct an AmeritradeSession with an access token stat file.
 *
 * @param a refresh token to generate access tokens
 * @param a consumer_key generated from the TDAmeritrade Developer portal
 * @param a root_url to make an API request (useful for /v1/ or /v2/ in future)
 * @param an access token file to save generated tokens in and read from
 */
AmeritradeSession::AmeritradeSession(
    string refresh, 
    string consumer_key, 
    string root_url,
    string access_token) 
  : access_token_(access_token) {

  AmeritradeSession(refresh, consumer_key, root_url);
}

/**
 * Set a JSON object with the representation of an AmeritradeSession.
 *
 * @param a JSON object to be written into
 * @param a constant (immutable) AmeritradeSession reference to JSON represent
 */
void to_json(nlohmann::json& j, const AmeritradeSession& s) {
  j = {
    {"refresh", s.refresh_},
    {"consumer_key", s.consumer_key_},
    {"root_url", s.root_url_}
  };
}

/**
 * Overload stream operator to print out an AmeritradeSession.
 *
 * @param a stream object
 * @param an AmeritradeSession object to represent
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
void AmeritradeSession::init_access_token_() {
  cpr::Payload req_payload = {
    {"grant_type", gt_refresh_token},
    {"refresh_token", refresh_},
    {"client_id", consumer_key_ + "@AMER.OAUTHMAP"},
    {"redirect_uri", "http://127.0.0.1"}
  };

  cpr::Response r = cpr::Post(
      cpr::Url{root_url_ + "oauth2/token"}, 
      req_payload);

  if (r.status_code != 200) 
    throw ApiException(r.status_code);

  nlohmann::json j = nlohmann::json::parse(r.text);
  auto access_rsp = j.get<oauth_rsp>();

  this->access_token_ = access_rsp.access_token;
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
  init_access_token_();
  return access_token_;
}

/**
 * Quote a basket of securities.
 *
 * This function will make a request to TDAmeritrade to quote a basket of
 * securities and will return an unordered_map mapping tickers to quote
 * structs as defined in include/quotes.hpp.
 *
 * @param an initializer_list of securities to quote
 * @return an unordered_map mapping tickers to quote structs
 */
unordered_map<string, quoted_instrument> AmeritradeSession::quote_securities(initializer_list<std::string_view> securities) {
  string ss = "";
  for (auto ticker : securities) {
    ss += ticker;
    ss += ',';
  }
  ss.pop_back();

  transform(ss.begin(), ss.end(), ss.begin(), ::toupper);
  auto req_params = cpr::Parameters{
    {"symbol", ss},
  };

  cpr::Response r = cpr::Get(
    cpr::Url{root_url_ + "marketdata/quotes"}, 
    cpr::Bearer{this->access_token_},
    req_params);

  if (r.status_code != 200) throw ApiException(r.status_code);

  nlohmann::json j = nlohmann::json::parse(r.text);
  return j.get<unordered_map<string, quoted_instrument>>();
}

/**
 * Quote a single security.
 *
 * This function calls AmeritradeSession::quote_securities with a single
 * security and indexes the unordered_map with the requested ticker to only
 * run a single quote struct.
 *
 * @param a single ticker to quote
 * @return a quote struct for the quote
 */
quoted_instrument AmeritradeSession::quote_security(string security) {
  auto s = this->quote_securities({security});

  transform(security.begin(), security.end(), security.begin(), ::toupper);

  if (s.find(security) == s.end()) throw ApiException(API_NOT_FOUND);

  return s[security];
}

/**
 * Search for instruments through the API.
 *
 * This function searches for instruments through the API through one of
 * four different search types (search_type).
 *
 * @param the search parameter
 * @param the type of search to conduct (search_type)
 * @return a mapping from tickers to searched instruments (without fundamentals)
 */
unordered_map<string, instrument> AmeritradeSession::search_instrument(string query, search_type type) {
  cpr::Parameters req_params = {
    {"symbol", query},
    {"projection", search_type_str(type)},
  };

  cpr::Response r = cpr::Get(
    cpr::Url{root_url_ + "instruments"}, 
    cpr::Bearer{this->access_token_},
    req_params);

  if (r.status_code != 200) throw ApiException(r.status_code);

  nlohmann::json j = nlohmann::json::parse(r.text);
  return j.get<unordered_map<string, instrument>>();
}

/**
 * Search for instrument fundamentals through the API.
 *
 * This function searches for instrument fundmanetals through the API through
 * a single symbol search term.
 *
 * @param the symbol parameter
 * @return an instrument struct including fundamentals data
 */
instrument AmeritradeSession::get_fundamentals(string ticker) {
  transform(ticker.begin(), ticker.end(), ticker.begin(), ::toupper);

  cpr::Parameters req_params = {
    {"symbol", ticker},
    {"projection", "fundamental"}
  };

  cpr::Response r = cpr::Get(
    cpr::Url{root_url_ + "instruments"}, 
    cpr::Bearer{this->access_token_},
    req_params);

  if (r.status_code != 200) throw ApiException(r.status_code);

  nlohmann::json j = nlohmann::json::parse(r.text);
  auto s = j.get<unordered_map<string, instrument>>();
  if (s.find(ticker) == s.end()) throw ApiException(API_NOT_FOUND);

  return s[ticker];
}

/**
 * Return market hours for specified markets.
 *
 * This function returns market hours returned by the API for the markets
 * specified on the date provided.
 *
 * @param a list of markets to get hours for
 * @param a date to get pre, regular, and post market hours for
 * @return a market_hours_rsp struct
 */
markets_hours AmeritradeSession::get_market_hours(vector<market_type> markets, string date) {
  // convert the markets to strings
  vector<string> markets_str;
  for (auto& market : markets)
    markets_str.emplace_back(get_str(market));

  // capitalize all the markets for parameters
  for (auto& market_str : markets_str)
    transform(
      market_str.begin(), 
      market_str.end(), market_str.begin(), 
      ::toupper);

  // implode the vector of strings with a comma
  string ss = "";
  for (auto market : markets_str) {
    ss += market;
    ss += ',';
  }
  ss.pop_back();

  cpr::Parameters req_params = {
    {"markets", ss},
    {"date", date}
  };

  cpr::Response r = cpr::Get(
    cpr::Url{root_url_ + "marketdata/hours"}, 
    cpr::Bearer{this->access_token_},
    req_params);

  if (r.status_code != 200) throw ApiException(r.status_code);

  nlohmann::json j = nlohmann::json::parse(r.text);
  return j.get<markets_hours>();
}
