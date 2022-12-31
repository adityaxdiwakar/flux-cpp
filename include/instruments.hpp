#pragma once
#include "nlohmann/json.hpp"
#include <string>

namespace flux {
  namespace instruments {
    enum class search_type {
      INSTRUMENT_SYMBOL_SEARCH,
      INSTRUMENT_SYMBOL_REGEX,
      INSTRUMENT_DESC_SEARCH,
      INSTRUMENT_DESC_REGEX,
    };

    const char* search_type_str(search_type) noexcept;

    struct fundamentals {
      std::string symbol;
      double high52;
      double low52;
      double dividend_amount;
      double dividend_yield;
      std::string dividend_date;
      double pe_ratio;
      double peg_ratio;
      double pb_ratio;
      double pr_ratio;
      double pcf_ratio;
      double gross_margin_ttm;
      double gross_margin_mrq;
      double net_profit_margin_ttm;
      double net_profit_margin_mrq;
      double operating_margin_ttm;
      double operating_margin_mrq;
      double return_on_equity;
      double return_on_assets;
      double return_on_investment;
      double quick_ratio;
      double current_ratio;
      double interest_coverage;
      double total_debt_to_capital;
      double lt_debt_to_equity;
      double total_debt_to_equity;
      double eps_ttm;
      double eps_change_percent_ttm;
      double eps_change_year;
      int64_t eps_change;
      int64_t rev_change_year;
      double rev_change_ttm;
      double rev_change_in;
      int64_t shares_outstanding;
      double market_cap_float;
      int64_t market_cap;
      int64_t book_value_per_share;
      int64_t short_int_to_float;
      int64_t short_int_day_to_cover;
      int64_t div_growth_rate3_year;
      double dividend_pay_amount;
      std::string dividend_pay_date;
      double beta;
      int64_t vol1_day_avg;
      int64_t vol10_day_avg;
      int64_t vol3_month_avg;

      friend void from_json(const nlohmann::json&, fundamentals&);
      friend void to_json(nlohmann::json&, const fundamentals&);
    };

    struct instrument {
      std::optional<std::string> cusip;
      std::string symbol;
      std::string description;
      std::string asset_type;
      std::string exchange;
      std::optional<fundamentals> fundamentals;

      friend void from_json(const nlohmann::json&, instrument&);
      friend void to_json(nlohmann::json&, const instrument&);
    };

    void from_json(const nlohmann::json&, std::unordered_map<std::string, instrument>&);
    void to_json(nlohmann::json&, const std::unordered_map<std::string, instrument>&);
  };
};
