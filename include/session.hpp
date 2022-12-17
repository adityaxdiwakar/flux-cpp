#include <string>
#include <nlohmann/json.hpp>
#include "cpr/cpr.h"
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
    std::string get_access_token();
};
