#pragma once
#include "nlohmann/json.hpp"
#include <string>

enum class search_type {
  INSTRUMENT_SYMBOL_SEARCH,
  INSTRUMENT_SYMBOL_REGEX,
  INSTRUMENT_DESC_SEARCH,
  INSTRUMENT_DESC_REGEX,
};

const char* search_type_str(search_type) noexcept;

struct instrument {
  std::optional<std::string> cusip;
  std::string symbol;
  std::string description;
  std::string asset_type;
  std::string exchange;

  friend void from_json(const nlohmann::json&, instrument&);
  friend void to_json(nlohmann::json&, const instrument&);
};

void from_json(const nlohmann::json&, std::unordered_map<std::string, instrument>&);
void to_json(nlohmann::json&, const std::unordered_map<std::string, instrument>&);
