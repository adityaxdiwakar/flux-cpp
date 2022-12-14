#include "session.h"
#include <string>
#include <iostream>

using namespace std;

AmeritradeSession::AmeritradeSession(std::string refresh, std::string consumer_key, std::string root_url) 
  : refresh(refresh),
    consumer_key(consumer_key),
    root_url(root_url) {}



ostream& operator<<(ostream &os, const AmeritradeSession& s) {
  cout << "{\n\trefresh: " << s.refresh << endl;
  cout << "\tconsumer: " << s.consumer_key << endl;
  cout << "\troot_url: " << s.root_url << endl;
  cout << "}";

  return os;
}
