#include "history.hpp"
#include "nlohmann/json.hpp"

void from_json(const nlohmann::json& j, candle& c) {
  j.at("open").get_to(c.open);
  j.at("close").get_to(c.close);
  j.at("low").get_to(c.low);
  j.at("high").get_to(c.high);
  j.at("volume").get_to(c.volume);
  j.at("datetime").get_to(c.datetime);
}

void to_json(nlohmann::json& j, const candle& c) {
  j = {
    {"open", c.open},
    {"close", c.close},
    {"low", c.low},
    {"high", c.high},
    {"volume", c.volume},
    {"datetiem", c.datetime},
  };
}

void from_json(const nlohmann::json& j, candle_list& c) {
  j.at("symbol").get_to(c.symbol);
  j.at("candles").get_to(c.candles);
}

void to_json(nlohmann::json& j, const candle_list& c) {
  j = {
    {"symbol", c.symbol},
    {"candles", c.candles},
  };
}
