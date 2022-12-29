#include <string>
#include <vector>
#include "nlohmann/json.hpp"

struct candle {
  double open;
  double high;
  double low;
  double close;

  int64_t volume;
  int64_t datetime;

  friend void from_json(const nlohmann::json&, candle&);
  friend void to_json(nlohmann::json&, const candle&);
};

struct candle_list {
  std::string symbol;
  std::vector<candle> candles;

  /* bool empty; // checked in json */

  friend void from_json(const nlohmann::json&, candle_list&);
  friend void to_json(nlohmann::json&, const candle_list&);
};
