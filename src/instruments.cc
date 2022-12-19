#include "nlohmann/json.hpp"
#include "instruments.hpp"

using namespace std;

void from_json(const nlohmann::json& j, instrument& i) {
  j.at("assetType").get_to(i.asset_type);
  j.at("symbol").get_to(i.symbol);
  j.at("description").get_to(i.description);
  j.at("exchange").get_to(i.exchange);

  if (j.count("cusip")) i.cusip = j.at("cusip").get<string>();
  if (j.count("fundamental")) i.fundamentals = j.at("fundamental").get<fundamentals>();
}

void to_json(nlohmann::json& j, const instrument& i) {
  j = {
    {"asset_type", i.asset_type},
    {"symbol", i.symbol},
    {"description", i.description},
    {"exchange", i.exchange},
  };
  
  if (i.cusip != std::nullopt) j["cusip"] = i.cusip.value();
  if (i.fundamentals != std::nullopt) j["fundamental"] = i.fundamentals.value();
}

void to_json(nlohmann::json& j, const unordered_map<string, instrument>& q) {
  for (const pair<string, instrument>& qi : q)
    j[qi.first] = qi.second;
}

void from_json(const nlohmann::json& j, unordered_map<string, instrument>& q) {
  for (auto& entry: j.items())
    q[entry.key()] = entry.value().get<instrument>();
}

const char* search_type_str(search_type e) noexcept
{
  switch (e)
  {
    case search_type::INSTRUMENT_SYMBOL_SEARCH: return "symbol-search";
    case search_type::INSTRUMENT_SYMBOL_REGEX: return "symbol-regex";
    case search_type::INSTRUMENT_DESC_SEARCH: return "desc-search";
    case search_type::INSTRUMENT_DESC_REGEX: return "desc-regex";
  }
}
