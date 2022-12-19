#include <string>
#include <vector>
#include <unordered_map>

#include "nlohmann/json.hpp"

enum class market_type {
  MARKET_EQUITY,
  MARKET_OPTION,
  MARKET_FUTURE,
  MARKET_BOND,
  MARKET_FOREX,
};


const char* get_str(market_type t);
const market_type get_market_type(std::string s);

struct market_times {
  std::string start;
  std::string end;

  friend void from_json(const nlohmann::json&, market_times&);
  friend void to_json(nlohmann::json&, const market_times&);
};

struct session_hours {
  std::optional<std::vector<market_times>> pre_market;
  std::optional<std::vector<market_times>> regular_market;
  std::optional<std::vector<market_times>> post_market;

  friend void from_json(const nlohmann::json&, session_hours&);
  friend void to_json(nlohmann::json&, const session_hours&);
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

  friend void from_json(const nlohmann::json&, market_hours&);
  friend void to_json(nlohmann::json&, const market_hours&);
};

struct markets_hours {
  std::optional<std::unordered_map<std::string, market_hours>> equity;
  std::optional<std::unordered_map<std::string, market_hours>> option;
  std::optional<std::unordered_map<std::string, market_hours>> future;
  std::optional<std::unordered_map<std::string, market_hours>> forex;
  std::optional<std::unordered_map<std::string, market_hours>> bond;

  friend void from_json(const nlohmann::json&, markets_hours&);
  friend void to_json(nlohmann::json&, const markets_hours&);
};
