#include "session.h"
#include <string>
#include <iostream>

using namespace std;

AmeritradeSession::AmeritradeSession(string refresh, string consumer_key, string root_url) 
  : refresh(refresh),
    consumer_key(consumer_key),
    root_url(root_url) {}

ostream& operator<<(ostream &os, const AmeritradeSession& s) {
  cout << "{refresh: " << s.refresh;
  cout << ", consumer: " << s.consumer_key;
  cout << ", root_url: " << s.root_url;
  cout << "}";

  return os;
}
