#include "movers.hpp"

void from_json(const nlohmann::json& j, mover& m) {
  j.at("change").get_to(m.change);
  j.at("description").get_to(m.description);
  j.at("last").get_to(m.last);
  j.at("symbol").get_to(m.symbol);
  j.at("totalVolume").get_to(m.total_volume);

  m.direction = j["direction"] == "up" ? direction::UP : direction::DOWN;
}

void to_json(nlohmann::json& j, const mover& m) {
  j = {
    {"change", m.change},
    {"description", m.description},
    {"last", m.last},
    {"symbol", m.symbol},
    {"total_volume", m.total_volume},
    {"direction", m.direction == direction::UP ? "up" : "down"},
  };
}
