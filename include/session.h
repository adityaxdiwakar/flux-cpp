#include <string>
#pragma once

using namespace std;

class AmeritradeSession {
  private:
    string refresh;
    string consumer_key;
    string root_url;

  public:
    AmeritradeSession(string refresh, string consumer_key, string root_url);
    friend ostream& operator<<(ostream &os, const  AmeritradeSession& s);
};
