#pragma once
#include <string>
#include "nlohmann/json.hpp"

namespace flux {
  namespace quotes {
    struct quoted_instrument {
      std::string asset_type;
      std::string asset_main_type;
      std::string cusip;
      std::string asset_sub_type;
      std::string symbol;
      std::string description;
      double bid_price;
      int64_t bid_size;
      std::string bid_id;
      double ask_price;
      int64_t ask_size;
      std::string ask_id;
      double last_price;
      int64_t last_size;
      std::string last_id;
      double open_price;
      double high_price;
      double low_price;
      std::string bid_tick;
      double close_price;
      double net_change;
      int64_t total_volume;
      int64_t quote_time_in_long;
      int64_t trade_time_in_long;
      double mark;
      std::string exchange;
      std::string exchange_name;
      bool marginable;
      bool shortable;
      double volatility;
      int64_t digits;
      double the_52_wk_high;
      double the_52_wk_low;
      int64_t n_av;
      double pe_ratio;
      double div_amount;
      double div_yield;
      std::string div_date;
      std::string security_status;
      double regular_market_last_price;
      int64_t regular_market_last_size;
      double regular_market_net_change;
      int64_t regular_market_trade_time_in_long;
      double net_percent_change_in_double;
      double mark_change_in_double;
      double mark_percent_change_in_double;
      double regular_market_percent_change_in_double;
      bool delayed;
      bool realtime_entitled;

      friend void from_json(const nlohmann::json&, quoted_instrument&);
      friend void to_json(nlohmann::json&, const quoted_instrument&);
    };

    void from_json(const nlohmann::json&, std::unordered_map<std::string, quoted_instrument>&);
    void to_json(nlohmann::json&, const std::unordered_map<std::string, quoted_instrument>&);
  };
};
