#include "chains.hpp"

using namespace std;

const char *months_str(enum month m) noexcept {
  switch (m) {
    case month::January:    return "JAN";
    case month::February:   return "FEB";
    case month::March:      return "MAR";
    case month::April:      return "APR";
    case month::May:        return "MAY";
    case month::June:       return "JUN";
    case month::July:       return "JUL";
    case month::August:     return "AUG";
    case month::September:  return "SEP";
    case month::October:    return "OCT";
    case month::November:   return "NOV";
    case month::December:   return "DEC";
  };
}

const char *contract_str(enum contract c) noexcept {
  switch (c) {
    case contract::CALL:    return "CALL";
    case contract::PUT:     return "PUT";
  };
}

const char *strike_str(enum strike s) noexcept {
  switch (s) {
    case strike::ALL:       return "ALL";
    case strike::ITM:       return "ITM";
    case strike::OTM:       return "OTM";
    case strike::NTM:       return "NTM";
    case strike::SAK:       return "SAK";
    case strike::SNK:       return "SNK";
    case strike::SBK:       return "SBK";
  };
}

const char *strategy_str(enum strategy s) noexcept {
  switch (s) {
    case strategy::SINGLE:      return "SINGLE";
    case strategy::ANALYTICAL:  return "ANALYTICAL";
    case strategy::COVERED:     return "COVERED";
    case strategy::VERTICAL:    return "VERTICAL";
    case strategy::CALENDAR:    return "CALENDAR";
    case strategy::STRANGLE:    return "STRANGLE";
    case strategy::STRADDLE:    return "STRADDLE";
    case strategy::BUTTERFLY:   return "BUTTERFLY";
    case strategy::CONDOR:      return "CONDOR";
    case strategy::DIAGONAL:    return "DIAGONAL";
    case strategy::COLLAR:      return "COLLAR";
    case strategy::ROLL:        return "ROLL";
  }; 
}

const char *norm_opt_str(enum norm_opt o) noexcept {
  switch (o) {
    case norm_opt::S:     return "S";
    case norm_opt::NS:    return "NS";
    case norm_opt::ALL:   return "ALL";
  };
}

void to_json(nlohmann::json& j, const expiration_type& e) {
  switch (e) {
    case expiration_type::Q: j = "Q"; break;
    case expiration_type::R: j = "R"; break;
    case expiration_type::S: j = "S"; break;
    default: j = ""; break;
  }
}

void from_json(const nlohmann::json& j, expiration_type& e) {
  if      (j == "Q")  e = expiration_type::Q;
  else if (j == "R")  e = expiration_type::R;
  else if (j == "S")  e = expiration_type::S;
}

void to_json(nlohmann::json& j, const contract &c) {
  j = contract_str(c);
}

void from_json(const nlohmann::json& j, contract &c) {
  if      (j == "C" || j == "CALL")   c = contract::CALL;
  else if (j == "P" || j == "PUT")    c = contract::PUT;
}

void to_json(nlohmann::json& j, const exp_map& e) {
	j = {
		{"put_call", e.put_call},
		{"symbol", e.symbol},
		{"description", e.description},
		{"exchange_name", e.exchange_name},
		{"bid", e.bid},
		{"ask", e.ask},
		{"last", e.last},
		{"mark", e.mark},
		{"bidSize", e.bid_size},
		{"askSize", e.ask_size},
		{"bid_ask_size", e.bid_ask_size},
		{"last_size", e.last_size},
		{"high_price", e.high_price},
		{"low_price", e.low_price},
		{"open_price", e.open_price},
		{"close_price", e.close_price},
		{"total_volume", e.total_volume},
		{"trade_time_in_long", e.trade_time_in_long},
		{"quote_time_in_long", e.quote_time_in_long},
		{"net_change", e.net_change},
		{"volatility", e.volatility},
		{"delta", e.delta},
		{"gamma", e.gamma},
		{"theta", e.theta},
		{"vega", e.vega},
		{"rho", e.rho},
		{"open_interest", e.open_interest},
		{"timeValue", e.time_value},
		{"theoretical_option_value", e.theoretical_option_value},
		{"theoretical_volatility", e.theoretical_volatility},
		{"strike_price", e.strike_price},
		{"expiration_date", e.expiration_date},
		{"days_to_expiration", e.days_to_expiration},
		{"expiration_type", e.expiration_type},
		{"last_trading_day", e.last_trading_day},
		{"multiplier", e.multiplier},
		{"settlement_type", e.settlement_type},
		{"deliverable_note", e.deliverable_note},
		{"percent_change", e.percent_change},
		{"mark_change", e.mark_change},
		{"mark_percent_change", e.mark_percent_change},
		{"intrinsic_value", e.intrinsic_value},
		{"non_standard", e.non_standard},
		{"in_the_money", e.in_the_money},
		{"mini", e.mini},
		{"penny_pilot", e.penny_pilot}
	};
}

void from_json(const nlohmann::json& j, exp_map& e) {
	j.at("putCall").get_to(e.put_call);
	j.at("symbol").get_to(e.symbol);
	j.at("description").get_to(e.description);
	j.at("exchangeName").get_to(e.exchange_name);
	j.at("bid").get_to(e.bid);
	j.at("ask").get_to(e.ask);
	j.at("last").get_to(e.last);
	j.at("mark").get_to(e.mark);
	j.at("bidSize").get_to(e.bid_size);
	j.at("askSize").get_to(e.ask_size);
	j.at("bidAskSize").get_to(e.bid_ask_size);
	j.at("lastSize").get_to(e.last_size);
	j.at("highPrice").get_to(e.high_price);
	j.at("lowPrice").get_to(e.low_price);
	j.at("openPrice").get_to(e.open_price);
	j.at("closePrice").get_to(e.close_price);
	j.at("totalVolume").get_to(e.total_volume);
	j.at("tradeTimeInLong").get_to(e.trade_time_in_long);
	j.at("quoteTimeInLong").get_to(e.quote_time_in_long);
	j.at("netChange").get_to(e.net_change);
	j.at("volatility").get_to(e.volatility);
	j.at("delta").get_to(e.delta);
	j.at("gamma").get_to(e.gamma);
	j.at("theta").get_to(e.theta);
	j.at("vega").get_to(e.vega);
	j.at("rho").get_to(e.rho);
	j.at("openInterest").get_to(e.open_interest);
	j.at("timeValue").get_to(e.time_value);
	j.at("theoreticalOptionValue").get_to(e.theoretical_option_value);
	j.at("theoreticalVolatility").get_to(e.theoretical_volatility);
	j.at("strikePrice").get_to(e.strike_price);
	j.at("expirationDate").get_to(e.expiration_date);
	j.at("daysToExpiration").get_to(e.days_to_expiration);
	j.at("expirationType").get_to(e.expiration_type);
	j.at("lastTradingDay").get_to(e.last_trading_day);
	j.at("multiplier").get_to(e.multiplier);
	j.at("settlementType").get_to(e.settlement_type);
	j.at("deliverableNote").get_to(e.deliverable_note);
	j.at("percentChange").get_to(e.percent_change);
	j.at("markChange").get_to(e.mark_change);
	j.at("markPercentChange").get_to(e.mark_percent_change);
	j.at("intrinsicValue").get_to(e.intrinsic_value);
	j.at("nonStandard").get_to(e.non_standard);
	j.at("inTheMoney").get_to(e.in_the_money);
	j.at("mini").get_to(e.mini);
	j.at("pennyPilot").get_to(e.penny_pilot);
}

void to_json(nlohmann::json& j, const underlying_quote& q) {
	j = {
		{"symbol", q.symbol},
		{"description", q.description},
		{"change", q.change},
		{"percent_change", q.percent_change},
		{"close", q.close},
		{"quote_time", q.quote_time},
		{"trade_time", q.trade_time},
		{"bid", q.bid},
		{"ask", q.ask},
		{"last", q.last},
		{"mark", q.mark},
		{"mark_change", q.mark_change},
		{"mark_percent_change", q.mark_percent_change},
		{"bid_size", q.bid_size},
		{"ask_size", q.ask_size},
		{"high_price", q.high_price},
		{"low_price", q.low_price},
		{"open_price", q.open_price},
		{"total_volume", q.total_volume},
		{"exchange_name", q.exchange_name},
		{"fifty_two_week_high", q.fifty_two_week_high},
		{"fifty_two_week_low", q.fifty_two_week_low},
		{"delayed", q.delayed},
	};
}

void from_json(const nlohmann::json& j, underlying_quote& q) {
	j.at("symbol").get_to(q.symbol);
	j.at("description").get_to(q.description);
	j.at("change").get_to(q.change);
	j.at("percentChange").get_to(q.percent_change);
	j.at("close").get_to(q.close);
	j.at("quoteTime").get_to(q.quote_time);
	j.at("tradeTime").get_to(q.trade_time);
	j.at("bid").get_to(q.bid);
	j.at("ask").get_to(q.ask);
	j.at("last").get_to(q.last);
	j.at("mark").get_to(q.mark);
	j.at("markChange").get_to(q.mark_change);
	j.at("markPercentChange").get_to(q.mark_percent_change);
	j.at("bidSize").get_to(q.bid_size);
	j.at("askSize").get_to(q.ask_size);
	j.at("highPrice").get_to(q.high_price);
	j.at("lowPrice").get_to(q.low_price);
	j.at("openPrice").get_to(q.open_price);
	j.at("totalVolume").get_to(q.total_volume);
	j.at("exchangeName").get_to(q.exchange_name);
	j.at("fiftyTwoWeekHigh").get_to(q.fifty_two_week_high);
	j.at("fiftyTwoWeekLow").get_to(q.fifty_two_week_low);
	j.at("delayed").get_to(q.delayed);
}

void to_json(nlohmann::json& j, const leg_option& o) {
	j = {
		{"symbol", o.symbol},
		{"put_call_ind", o.put_call_ind},
		{"description", o.description},
		{"bid", o.bid},
		{"ask", o.ask},
		{"range", o.range},
		{"strike_price", o.strike_price},
		{"total_volume", o.total_volume}
	};
}

void from_json(const nlohmann::json& j, leg_option& o) {
	j.at("symbol").get_to(o.symbol);
	j.at("putCallInd").get_to(o.put_call_ind);
	j.at("description").get_to(o.description);
	j.at("bid").get_to(o.bid);
	j.at("ask").get_to(o.ask);
	j.at("range").get_to(o.range);
	j.at("strikePrice").get_to(o.strike_price);
	j.at("totalVolume").get_to(o.total_volume);
}

void to_json(nlohmann::json& j, const chain& c) {
	j = {
		{"symbol", c.symbol},
		{"status", c.status},
		{"strategy", c.strategy},
		{"interval", c.interval},
		{"is_delayed", c.is_delayed},
		{"is_index", c.is_index},
		{"interest_rate", c.interest_rate},
		{"underlying_price", c.underlying_price},
		{"volatility", c.volatility},
		{"days_to_expiration", c.days_to_expiration},
		{"number_of_contracts", c.number_of_contracts},
	};

  if (c.underlying != nullopt) j["underlying"] = c.underlying.value();
  if (c.put_cal != nullopt) j["put_cal"] = c.put_cal.value();
  if (c.call_cal != nullopt) j["call_cal"] = c.call_cal.value();
  if (c.month_lists != nullopt) j["month_lists"] = c.month_lists.value();
}

void from_json(const nlohmann::json& j, chain& c) {
	j.at("symbol").get_to(c.symbol);
	j.at("status").get_to(c.status);
	j.at("strategy").get_to(c.strategy);
	j.at("interval").get_to(c.interval);
	j.at("isDelayed").get_to(c.is_delayed);
	j.at("isIndex").get_to(c.is_index);
	j.at("interestRate").get_to(c.interest_rate);
	j.at("underlyingPrice").get_to(c.underlying_price);
	j.at("volatility").get_to(c.volatility);
	j.at("daysToExpiration").get_to(c.days_to_expiration);
	j.at("numberOfContracts").get_to(c.number_of_contracts);

  if (j.count("underlying") && !j.at("underlying").is_null())
    c.underlying = j.at("underlying").get<underlying_quote>();

  if (j.count("monthlyStrategyList"))
    c.month_lists = j.at("monthlyStrategyList").get<list_of_months>();

  if (j.count("putExpDateMap"))
    c.put_cal = j.at("putExpDateMap").get<option_calendar>();

  if (j.count("callExpDateMap"))
    c.call_cal = j.at("callExpDateMap").get<option_calendar>();
}

void to_json(nlohmann::json& j, const option_strat& o) {
  j = {
    {"primary", o.primary},
    {"strategy_strike", o.strategy_strike},
    {"strategy_bid", o.strategy_bid},
    {"strategy_ask", o.strategy_ask},
  };

  if (o.secondary != nullopt) j["secondary"] = o.secondary.value();
}

void from_json(const nlohmann::json& j, option_strat& o) {
  j.at("primary").get_to(o.primary);
  j.at("strategyStrike").get_to(o.strategy_strike);
  j.at("strategyBid").get_to(o.strategy_bid);
  j.at("strategyAsk").get_to(o.strategy_ask);

  if (j.count("secondary")) 
    o.secondary = j.at("secondary").get<leg_option>();
}

void to_json(nlohmann::json& j, const month& m) {
	j = months_str(m);
}

void from_json(const nlohmann::json& j, month& m) {
	if      (j == "Jan")  m = month::January;
	else if (j == "Feb")  m = month::February;
	else if (j == "Mar")  m = month::March;
	else if (j == "Apr")  m = month::April;
	else if (j == "May")  m = month::May;
	else if (j == "Jun") 	m = month::June;
	else if (j == "Jul")	m = month::July;
	else if (j == "Aug")	m = month::August;
	else if (j == "Sep")	m = month::September;
	else if (j == "Oct")	m = month::October;
	else if (j == "Nov")	m = month::November;
	else if (j == "Dec")	m = month::December;
}

void to_json(nlohmann::json& j, const monthly_strat_list& msl) {
  j = {
    {"month", msl.month},
    {"year", msl.year},
    {"day", msl.day},
    {"days_to_exp", msl.days_to_exp},
    {"secondary_month", msl.secondary_month},
    {"secondary_year", msl.secondary_year},
    {"secondary_day", msl.secondary_day},
    {"secondary_days_to_exp", msl.secondary_days_to_exp},
    {"type", msl.type},
    {"secondary_type", msl.secondary_type},
    {"strat_list", msl.strat_list},
  };
}

void from_json(const nlohmann::json& j, monthly_strat_list& msl) {
  j.at("year").get_to(msl.year);
  j.at("month").get_to(msl.month);
  j.at("day").get_to(msl.day);
  j.at("daysToExp").get_to(msl.days_to_exp);

  j.at("secondaryYear").get_to(msl.secondary_year);
  j.at("secondaryMonth").get_to(msl.secondary_month);
  j.at("secondaryDay").get_to(msl.secondary_day);
  j.at("secondaryDaysToExp").get_to(msl.secondary_days_to_exp);

  j.at("type").get_to(msl.type);
  j.at("secondaryType").get_to(msl.secondary_type);

  j.at("optionStrategyList").get_to(msl.strat_list);
}
