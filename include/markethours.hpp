#include <string>
#include <vector>
#include <unordered_map>

#include "nlohmann/json.hpp"

namespace flux {
  namespace markets {
    enum class type {
      MARKET_EQUITY,
      MARKET_OPTION,
      MARKET_FUTURE,
      MARKET_BOND,
      MARKET_FOREX,
    };

    const char* get_str(type t);
    const type get_market_type(std::string s);

    struct times {
      std::string start;
      std::string end;

      friend void from_json(const nlohmann::json&, times&);
      friend void to_json(nlohmann::json&, const times&);
    };

    struct session_hours {
      std::optional<std::vector<times>> pre_market;
      std::optional<std::vector<times>> regular_market;
      std::optional<std::vector<times>> post_market;

      friend void from_json(const nlohmann::json&, session_hours&);
      friend void to_json(nlohmann::json&, const session_hours&);
    };

    struct single_hours {
      std::string date;
      std::string market_type;
      std::string exchange;
      std::string category;
      std::string product;
      std::string product_name;
      bool is_open;
      session_hours session_hours;

      friend void from_json(const nlohmann::json&, single_hours&);
      friend void to_json(nlohmann::json&, const single_hours&);
    };

    struct hours {
      std::optional<std::unordered_map<std::string, single_hours>> equity;
      std::optional<std::unordered_map<std::string, single_hours>> option;
      std::optional<std::unordered_map<std::string, single_hours>> future;
      std::optional<std::unordered_map<std::string, single_hours>> forex;
      std::optional<std::unordered_map<std::string, single_hours>> bond;

      friend void from_json(const nlohmann::json&, hours&);
      friend void to_json(nlohmann::json&, const hours&);
    };
  };
};
