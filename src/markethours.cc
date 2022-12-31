#include "markethours.hpp"
#include "nlohmann/json.hpp"
#include <vector>

using namespace std;

namespace flux {
  namespace markets {
    void to_json(nlohmann::json& j, const times& sh) {
      j = {
        {"start", sh.start},
        {"end", sh.end}
      };
    }

    void from_json(const nlohmann::json& j, times& sh) {
      j.at("start").get_to(sh.start);
      j.at("end").get_to(sh.end);
    }

    void from_json(const nlohmann::json& j, session_hours& sh) {
      if (j.count("preMarket"))
        sh.pre_market = j.at("preMarket").get<vector<times>>();

      if (j.count("regularMarket"))
        sh.pre_market = j.at("regularMarket").get<vector<times>>();

      if (j.count("postMarket"))
        sh.pre_market = j.at("postMarket").get<vector<times>>();
    }

    void to_json(nlohmann::json& j, const session_hours& sh) {
      if (sh.pre_market != nullopt) 
        j["pre_market"] = sh.pre_market.value();
      if (sh.regular_market != nullopt) 
        j["regular_market"] = sh.regular_market.value();
      if (sh.post_market != nullopt) 
        j["post_market"] = sh.post_market.value();
    }

    void from_json(const nlohmann::json& j, single_hours& mh) {
      j.at("date").get_to(mh.date);
      j.at("marketType").get_to(mh.market_type);
      j.at("exchange").get_to(mh.exchange);
      j.at("category").get_to(mh.category);
      j.at("product").get_to(mh.product);
      j.at("productName").get_to(mh.product_name);
      j.at("isOpen").get_to(mh.is_open);
      j.at("sessionHours").get_to(mh.session_hours);
    }

    void to_json(nlohmann::json& j, const single_hours& mh) {
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

    void from_json(const nlohmann::json& j, unordered_map<string, single_hours>& s) {
      for (auto& entry: j.items())
        s[entry.key()] = entry.value().get<single_hours>();
    }

    void to_json(nlohmann::json& j, const unordered_map<string, single_hours>& s) {
      for (const pair<string, single_hours>& si : s)
        j[si.first] = si.second;
    }

    void from_json(const nlohmann::json& j, hours& s) {
      if (j.count("equity")) 
        s.equity = j.at("equity").get<unordered_map<string, single_hours>>();

      if (j.count("option")) 
        s.option = j.at("option").get<unordered_map<string, single_hours>>();

      if (j.count("future")) 
        s.future = j.at("future").get<unordered_map<string, single_hours>>();

      if (j.count("forex")) 
        s.forex = j.at("forex").get<unordered_map<string, single_hours>>();

      if (j.count("bond")) 
        s.bond = j.at("bond").get<unordered_map<string, single_hours>>();
    }

    void to_json(nlohmann::json& j, const hours& s) {
      if (s.bond    != nullopt)   j["bond"]   = s.bond.value();
      if (s.future  != nullopt)   j["future"] = s.future.value();
      if (s.forex   != nullopt)   j["forex"]  = s.forex.value();
      if (s.option  != nullopt)   j["option"] = s.option.value();
      if (s.equity  != nullopt)   j["equity"] = s.equity.value();
    }

    const char* get_str(type t) {
      switch (t) {
        case type::MARKET_EQUITY:   return "equity";
        case type::MARKET_FUTURE:   return "future";
        case type::MARKET_OPTION:   return "option";
        case type::MARKET_BOND:     return "bond";
        case type::MARKET_FOREX:    return "forex";
      }
    }

    const type get_market_type(string s) {
      if (s == "equity")        return type::MARKET_EQUITY;
      else if (s == "bond")     return type::MARKET_BOND;
      else if (s == "forex")    return type::MARKET_FOREX;
      else if (s == "option")   return type::MARKET_OPTION;
      else                      return type::MARKET_FUTURE;
    }
  };
};
