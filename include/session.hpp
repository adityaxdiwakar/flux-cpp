#include <string>
#include <nlohmann/json.hpp>
#pragma once

class AmeritradeSession {
  private:
    std::string refresh;
    std::string consumer_key;
    std::string root_url;
    std::string access_token;

  public:
    AmeritradeSession(std::string refresh, std::string consumer_key, std::string root_url);
    AmeritradeSession();
    friend std::ostream& operator<<(std::ostream &os, const  AmeritradeSession& s);
    friend void to_json(nlohmann::json& j, const AmeritradeSession& s);
    void get_access_token();
};
