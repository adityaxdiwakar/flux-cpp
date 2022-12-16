#include <string>
#pragma once

class AmeritradeSession {
  private:
    std::string refresh;
    std::string consumer_key;
    std::string root_url;
    std::string access_token;

  public:
    AmeritradeSession(std::string refresh, std::string consumer_key, std::string root_url);
    friend std::ostream& operator<<(std::ostream &os, const  AmeritradeSession& s);
    void get_access_token();
};
