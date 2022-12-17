#include "nlohmann/json.hpp"
#include "quotes.hpp"

using namespace std;

void from_json(const nlohmann::json& j, quoted_instrument& q) {
  j.at("assetType").get_to(q.asset_type);
  j.at("assetMainType").get_to(q.asset_main_type);
  j.at("cusip").get_to(q.cusip);
  j.at("assetSubType").get_to(q.asset_sub_type);
  j.at("symbol").get_to(q.symbol);
  j.at("description").get_to(q.description);
  j.at("bidPrice").get_to(q.bid_price);
  j.at("bidSize").get_to(q.bid_size);
  j.at("bidId").get_to(q.bid_id);
  j.at("askPrice").get_to(q.ask_price);
  j.at("askSize").get_to(q.ask_size);
  j.at("askId").get_to(q.ask_id);
  j.at("lastPrice").get_to(q.last_price);
  j.at("lastSize").get_to(q.last_size);
  j.at("lastId").get_to(q.last_id);
  j.at("openPrice").get_to(q.open_price);
  j.at("highPrice").get_to(q.high_price);
  j.at("lowPrice").get_to(q.low_price);
  j.at("bidTick").get_to(q.bid_tick);
  j.at("closePrice").get_to(q.close_price);
  j.at("netChange").get_to(q.net_change);
  j.at("totalVolume").get_to(q.total_volume);
  j.at("quoteTimeInLong").get_to(q.quote_time_in_long);
  j.at("tradeTimeInLong").get_to(q.trade_time_in_long);
  j.at("mark").get_to(q.mark);
  j.at("exchange").get_to(q.exchange);
  j.at("exchangeName").get_to(q.exchange_name);
  j.at("marginable").get_to(q.marginable);
  j.at("shortable").get_to(q.shortable);
  j.at("volatility").get_to(q.volatility);
  j.at("digits").get_to(q.digits);
  j.at("52WkHigh").get_to(q.the_52_wk_high);
  j.at("52WkLow").get_to(q.the_52_wk_low);
  j.at("nAV").get_to(q.n_av);
  j.at("peRatio").get_to(q.pe_ratio);
  j.at("divAmount").get_to(q.div_amount);
  j.at("divYield").get_to(q.div_yield);
  j.at("divDate").get_to(q.div_date);
  j.at("securityStatus").get_to(q.security_status);
  j.at("regularMarketLastPrice").get_to(q.regular_market_last_price);
  j.at("regularMarketLastSize").get_to(q.regular_market_last_size);
  j.at("regularMarketNetChange").get_to(q.regular_market_net_change);
  j.at("regularMarketTradeTimeInLong").get_to(q.regular_market_trade_time_in_long);
  j.at("netPercentChangeInDouble").get_to(q.net_percent_change_in_double);
  j.at("markChangeInDouble").get_to(q.mark_change_in_double);
  j.at("markPercentChangeInDouble").get_to(q.mark_percent_change_in_double);
  j.at("regularMarketPercentChangeInDouble").get_to(q.regular_market_percent_change_in_double);
  j.at("delayed").get_to(q.delayed);
  j.at("realtimeEntitled").get_to(q.realtime_entitled);
}

void to_json(nlohmann::json& j, const quoted_instrument& q) {
  j = nlohmann::json{
    {"asset_type", q.asset_type},
    {"asset_main_type", q.asset_main_type},
    {"cusip", q.cusip},
    {"asset_sub_type", q.asset_sub_type},
    {"symbol", q.symbol},
    {"description", q.description},
    {"bid_price", q.bid_price},
    {"bid_size", q.bid_size},
    {"bid_id", q.bid_id},
    {"ask_price", q.ask_price},
    {"ask_size", q.ask_size},
    {"ask_id", q.ask_id},
    {"last_price", q.last_price},
    {"last_size", q.last_size},
    {"last_id", q.last_id},
    {"open_price", q.open_price},
    {"high_price", q.high_price},
    {"low_price", q.low_price},
    {"bid_tick", q.bid_tick},
    {"close_price", q.close_price},
    {"net_change", q.net_change}, {"total_volume", q.total_volume},
    {"quote_time_in_long", q.quote_time_in_long},
    {"trade_time_in_long", q.trade_time_in_long},
    {"mark", q.mark},
    {"exchange", q.exchange},
    {"exchange_name", q.exchange_name},
    {"marginable", q.marginable},
    {"shortable", q.shortable},
    {"volatility", q.volatility},
    {"digits", q.digits},
    {"the_52_wk_high", q.the_52_wk_high},
    {"the_52_wk_low", q.the_52_wk_low},
    {"n_av", q.n_av},
    {"pe_ratio", q.pe_ratio},
    {"div_amount", q.div_amount},
    {"div_yield", q.div_yield},
    {"div_date", q.div_date},
    {"security_status", q.security_status},
    {"regular_market_last_price", q.regular_market_last_price},
    {"regular_market_last_size", q.regular_market_last_size},
    {"regular_market_net_change", q.regular_market_net_change},
    {"regular_market_trade_time_in_long", q.regular_market_trade_time_in_long},
    {"net_percent_change_in_double", q.net_percent_change_in_double},
    {"mark_change_in_double", q.mark_change_in_double},
    {"mark_percent_change_in_double", q.mark_percent_change_in_double},
    {"regular_market_percent_change_in_double", q.regular_market_percent_change_in_double},
    {"delayed", q.delayed},
    {"realtime_entitled", q.realtime_entitled}
  };
}

void to_json(nlohmann::json& j, const unordered_map<string, quoted_instrument>& q) {
  for (const pair<string, quoted_instrument>& qi : q)
    j[qi.first] = (nlohmann::json) qi.second;
}

void from_json(const nlohmann::json& j, unordered_map<string, quoted_instrument>& q) {
  for (auto& entry: j.items())
    q[entry.key()] = entry.value().get<quoted_instrument>();
}
