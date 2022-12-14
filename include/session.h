#pragma once
#include <string>
using namespace std;

class AmeritradeSession;

class AmeritradeSession {
  private:
    string refresh;
    string consumer_key;
    string root_url;

  public:
    AmeritradeSession(std::string refresh, std::string consumer_key, std::string root_url);
    friend ostream& operator<<(ostream &os, const  AmeritradeSession& s);
};
