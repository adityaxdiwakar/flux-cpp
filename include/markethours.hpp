#include <string>
#include <vector>

using hours_rsp_type = std::unordered_map<std::string, unordered_map<std::string, market_hours>>;

struct market_times {
  std::string start;
  std::string end;
};

struct session_hours {
  std::vector<market_times> pre_market;
  std::vector<market_times> regular_market;
  std::vector<market_times> post_market;
};

struct market_hours {
  std::string date;
  std::string market_type;
  std::string exchange;
  std::string category;
  std::string product;
  std::string product_name;
  bool is_open;
  session_hours session_hours;
};
