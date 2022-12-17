#include <string>
#include <nlohmann/json.hpp>
#include "cpr/cpr.h"
#include "quotes.hpp"
#pragma once

enum request_type {
  GET,
  POST
};

class AmeritradeSession {
  private:
    std::string refresh;
    std::string consumer_key;
    std::string root_url;
    std::string access_token;
    void init_access_token();

  public:
    AmeritradeSession(std::string refresh, std::string consumer_key, std::string root_url);
    AmeritradeSession();
    friend std::ostream& operator<<(std::ostream &os, const  AmeritradeSession& s);
    friend void to_json(nlohmann::json& j, const AmeritradeSession& s);

    // access token methods
    std::string get_access_token();

    // quoting methods 
    std::unordered_map<std::string, quoted_instrument> quote_securities(std::initializer_list<std::string_view>);
    quoted_instrument quote_security(std::string);
};
