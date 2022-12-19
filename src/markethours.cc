#include "markethours.hpp"
#include "nlohmann/json.hpp"
#include <vector>

using namespace std;

void to_json(nlohmann::json& j, const market_times& sh) {
  j = {
    {"start", sh.start},
    {"end", sh.end}
  };
}

void from_json(const nlohmann::json& j, market_times& sh) {
  j.at("start").get_to(sh.start);
  j.at("end").get_to(sh.end);
}

void from_json(const nlohmann::json& j, session_hours& sh) {
  if (j.count("preMarket"))
    sh.pre_market = j.at("preMarket").get<vector<market_times>>();

  if (j.count("regularMarket"))
    sh.pre_market = j.at("regularMarket").get<vector<market_times>>();

  if (j.count("postMarket"))
    sh.pre_market = j.at("postMarket").get<vector<market_times>>();
}

void to_json(nlohmann::json& j, const session_hours& sh) {
  if (sh.pre_market != nullopt) 
    j["pre_market"] = sh.pre_market.value();
  if (sh.regular_market != nullopt) 
    j["regular_market"] = sh.regular_market.value();
  if (sh.post_market != nullopt) 
    j["post_market"] = sh.post_market.value();
}

void from_json(const nlohmann::json& j, market_hours& mh) {
  j.at("date").get_to(mh.date);
  j.at("marketType").get_to(mh.market_type);
  j.at("exchange").get_to(mh.exchange);
  j.at("category").get_to(mh.category);
  j.at("product").get_to(mh.product);
  j.at("productName").get_to(mh.product_name);
  j.at("isOpen").get_to(mh.is_open);
  j.at("sessionHours").get_to(mh.session_hours);
}

void to_json(nlohmann::json& j, const market_hours& mh) {
  j = {
    {"date", mh.date},
    {"market_type", mh.market_type},
    {"exchange", mh.exchange},
    {"category", mh.category},
    {"product", mh.product},
    {"product_name", mh.product_name},
    {"is_open", mh.is_open},
    {"session_hours", mh.session_hours},
  };
}

void from_json(const nlohmann::json& j, unordered_map<string, market_hours>& s) {
  for (auto& entry: j.items())
    s[entry.key()] = entry.value().get<market_hours>();
}

void to_json(nlohmann::json& j, const unordered_map<string, market_hours>& s) {
  for (const pair<string, market_hours>& si : s)
    j[si.first] = si.second;
}

void from_json(const nlohmann::json& j, markets_hours& s) {
  if (j.count("equity")) 
    s.equity = j.at("equity").get<unordered_map<string, market_hours>>();

  if (j.count("option")) 
    s.option = j.at("option").get<unordered_map<string, market_hours>>();

  if (j.count("future")) 
    s.future = j.at("future").get<unordered_map<string, market_hours>>();

  if (j.count("forex")) 
    s.forex = j.at("forex").get<unordered_map<string, market_hours>>();

  if (j.count("bond")) 
    s.bond = j.at("bond").get<unordered_map<string, market_hours>>();
}

void to_json(nlohmann::json& j, const markets_hours& s) {
  if (s.bond    != nullopt)   j["bond"]   = s.bond.value();
  if (s.future  != nullopt)   j["future"] = s.future.value();
  if (s.forex   != nullopt)   j["forex"]  = s.forex.value();
  if (s.option  != nullopt)   j["option"] = s.option.value();
  if (s.equity  != nullopt)   j["equity"] = s.equity.value();
}

const char* get_str(market_type t) {
  switch (t) {
    case market_type::MARKET_EQUITY:   return "equity";
    case market_type::MARKET_FUTURE:   return "future";
    case market_type::MARKET_OPTION:   return "option";
    case market_type::MARKET_BOND:     return "bond";
    case market_type::MARKET_FOREX:    return "forex";
  }
}

const market_type get_market_type(string s) {
  if (s == "equity")        return market_type::MARKET_EQUITY;
  else if (s == "bond")     return market_type::MARKET_BOND;
  else if (s == "forex")    return market_type::MARKET_FOREX;
  else if (s == "option")   return market_type::MARKET_OPTION;
  else                      return market_type::MARKET_FUTURE;
}
