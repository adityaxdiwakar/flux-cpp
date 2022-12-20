#pragma once
#include <string> 
#include <optional>
#include <vector>

#include "nlohmann/json.hpp"

enum class strike {
  ITM,  /* In The Money */
  NTM,  /* Near The Money */
  OTM,  /* Out of the Money */
  SAK,  /* Strikes above Market */
  SBK,  /* Strikes below Market */
  SNK,  /* Strikes near Market */
  ALL   /* All Strikes */
};

enum class strategy {
  SINGLE, ANALYTICAL, COVERED, VERTICAL, CALENDAR, STRANGLE, STRADDLE,
  BUTTERFLY, CONDOR, DIAGONAL, COLLAR, ROLL
};

enum class contract {
  CALL, PUT
};

enum class month { 
  January, February, March, April, May, June, July, August, September,
  October, November, December };
void to_json(nlohmann::json&, const month&);
void from_json(const nlohmann::json&, month&);

enum class norm_opt {
  S, NS, ALL
};

struct analytical_query {
  double strat_vol;
  double strat_underlying_price;
  double strat_interest_rate;
  int strat_exp_days;
};

struct options_req {
  std::optional<contract> c;
  std::optional<int> num_strikes;
  std::optional<bool> include_quotes;
  std::optional<strategy> strat;
  std::optional<int> strike_interval;
  std::optional<strike> strike_filter;
  std::optional<std::string> from_date;
  std::optional<std::string> to_date;
  std::optional<analytical_query> analytical_query;
  std::optional<month> exp_month;
  std::optional<norm_opt> option_type;
};

const char* months_str(month) noexcept;
const char* strike_str(strike) noexcept;
const char* strategy_str(strike) noexcept;
const char* contract_str(contract) noexcept;
const char* norm_opt_str(norm_opt) noexcept;

enum class expiration_type { S, Q, R };
void to_json(nlohmann::json&, const expiration_type&);
void from_json(const nlohmann::json&, expiration_type&);

struct exp_map {
	contract put_call;
	std::string symbol;
	std::string description;
	std::string exchange_name;
	double bid;
	double ask;
	double last;
	double mark;
	int64_t bid_size;
	int64_t ask_size;
	std::string bid_ask_size;
	int64_t last_size;
	double high_price;
	double low_price;
	int64_t open_price;
	double close_price;
	int64_t total_volume;
	int64_t trade_time_in_long;
	int64_t quote_time_in_long;
	double net_change;
	double volatility;
	double delta;
	double gamma;
	double theta;
	double vega;
	double rho;
	int64_t open_interest;
	double time_value;
	double theoretical_option_value;
	int64_t theoretical_volatility;
	int64_t strike_price;
	int64_t expiration_date;
	int64_t days_to_expiration;
	expiration_type expiration_type;
	int64_t last_trading_day;
	int64_t multiplier;
	std::string settlement_type;
	std::string deliverable_note;
	double percent_change;
	double mark_change;
	double mark_percent_change;
	double intrinsic_value;
	bool non_standard;
	bool in_the_money;
	bool mini;
	bool penny_pilot;

	friend void to_json(nlohmann::json&, const exp_map&);
	friend void from_json(const nlohmann::json&, exp_map&);
};

struct underlying_quote {
	std::string symbol;
	std::string description;
	double change;
	double percent_change;
	double close;
	int64_t quote_time;
	int64_t trade_time;
	double bid;
	double ask;
	double last;
	double mark;
	double mark_change;
	double mark_percent_change;
	int64_t bid_size;
	int64_t ask_size;
	double high_price;
	double low_price;
	double open_price;
	int64_t total_volume;
	std::string exchange_name;
	double fifty_two_week_high;
	double fifty_two_week_low;
	bool delayed;

	friend void to_json(nlohmann::json&, const underlying_quote&);
	friend void from_json(const nlohmann::json&, underlying_quote&);
};

struct leg_option {
	std::string symbol;
	contract put_call_ind;
	std::string description;
	int64_t bid;
	double ask;
	std::string range;
	int64_t strike_price;
	int64_t total_volume;

	friend void to_json(nlohmann::json&, const leg_option&);
	friend void from_json(const nlohmann::json&, leg_option&);
};

struct option_strat {
	leg_option primary;
  std::optional<leg_option> secondary;
	std::string strategy_strike;
	double strategy_bid;
	double strategy_ask;

	friend void to_json(nlohmann::json&, const option_strat&);
	friend void from_json(const nlohmann::json&, option_strat&);
};

struct monthly_strat_list {
	enum month month;
	int64_t year;
	int64_t day;
	int64_t days_to_exp;
	enum month secondary_month;
	int64_t secondary_year;
	int64_t secondary_day;
	int64_t secondary_days_to_exp;
	contract type;
	contract secondary_type;
	std::vector<option_strat> strat_list;

	friend void to_json(nlohmann::json&, const monthly_strat_list&);
	friend void from_json(const nlohmann::json&, monthly_strat_list&);
};

using strike_options = std::vector<exp_map>;
using strike_ladder = std::unordered_map<std::string, strike_options>;
using option_calendar = std::unordered_map<std::string, strike_ladder>;

using list_of_months = std::vector<monthly_strat_list>;

struct chain {
  std::string symbol;
  std::string status;
  std::optional<underlying_quote> underlying;
  std::string strategy;
  int64_t interval;
  bool is_delayed;
  bool is_index;
  double interest_rate;
  double underlying_price;
  int64_t volatility;
  int64_t days_to_expiration;
  int64_t number_of_contracts;
  std::optional<option_calendar> put_cal;
  std::optional<option_calendar> call_cal;
  std::optional<list_of_months> month_lists;

	friend void to_json(nlohmann::json&, const chain&);
	friend void from_json(const nlohmann::json&, chain&);
};
