#include <string>
#include <chrono>
#include <iostream>
#include <sys/stat.h>
#include <fstream>

#include "session.hpp"
#include "history.hpp"
#include "chains.hpp"
#include "auth.hpp"
#include "quotes.hpp"
#include "movers.hpp"
#include "instruments.hpp"

#include "cpr/cpr.h"
#include "nlohmann/json.hpp"

using namespace std;

namespace flux {
  /**
   * Construct a custom ApiException with a status code.
   *
   * @param a status code to represent the error
   */
  ApiException::ApiException(int code) : status_code(code) {}

  /**
   * A getter method to retrieve the status code from an exception.
   *
   * @return the status code associated with the exception
   */
  int ApiException::get_code() { return status_code; }

  /**
   * Construct an AmeritradeSession with neccesary information to initialize.
   *
   * @param a refresh token to generate access tokens
   * @param a consumer_key generated from the TDAmeritrade Developer portal
   * @param a root_url to make an API request (useful for /v1/ or /v2/ in future)
   */
  AmeritradeSession::AmeritradeSession(
      string refresh, 
      string consumer_key, 
      string root_url) 
    : refresh_(refresh)
    , consumer_key_(consumer_key)
    , root_url_(root_url) {

    this->init_access_token_();
  }

  /**
   * Construct an AmeritradeSession with an access token stat file.
   *
   * @param a refresh token to generate access tokens
   * @param a consumer_key generated from the TDAmeritrade Developer portal
   * @param a root_url to make an API request (useful for /v1/ or /v2/ in future)
   * @param an access token file to save generated tokens in and read from
   */
  AmeritradeSession::AmeritradeSession(
      string refresh, 
      string consumer_key, 
      string root_url,
      string token_file) 
    : refresh_(refresh)
    , consumer_key_(consumer_key)
    , root_url_(root_url)
    , token_file_(token_file) {

    this->init_access_token_();
  }

  /**
   * Set a JSON object with the representation of an AmeritradeSession.
   *
   * @param a JSON object to be written into
   * @param a constant (immutable) AmeritradeSession reference to JSON represent
   */
  void to_json(nlohmann::json& j, const AmeritradeSession& s) {
    j = {
      {"refresh", s.refresh_},
      {"consumer_key", s.consumer_key_},
      {"root_url", s.root_url_}
    };
  }

  /**
   * Overload stream operator to print out an AmeritradeSession.
   *
   * @param a stream object
   * @param an AmeritradeSession object to represent
   * @return a stream object with AmeritradeSession added
   */
  ostream& operator<<(ostream &os, const AmeritradeSession& s) {
    cout << (nlohmann::json) s;
    return os;
  }

  /**
   * Dynamically initialize access token.
   *
   * This function initializes the access token and stores it as a private 
   * session field. 
   */
  void AmeritradeSession::init_access_token_() {
    if (this->token_file_ != nullopt && this->read_saved_token_()) return;

    cpr::Payload req_payload = {
      {"grant_type", auth::gt_refresh_token},
      {"refresh_token", refresh_},
      {"client_id", consumer_key_ + "@AMER.OAUTHMAP"},
      {"redirect_uri", "http://127.0.0.1"}
    };

    cpr::Response r = cpr::Post(
        cpr::Url{root_url_ + "oauth2/token"}, 
        req_payload);

    if (r.status_code != 200) 
      throw ApiException(r.status_code);

    nlohmann::json j = nlohmann::json::parse(r.text);
    auto access_rsp = j.get<auth::oauth_rsp>();

    this->access_token_ = access_rsp.access_token;

    if (this->token_file_ != nullopt)
      this->write_access_token_();
  }

  /**
   * Read saved access token from file.
   *
   * @return true if token could be read, otherwise false
   */
  bool AmeritradeSession::read_saved_token_() {
    // santiy check this function is not called before checking token_file_
    if (this->token_file_ == nullopt) return false;

    struct stat sb;
    if (stat(this->token_file_.value().c_str(), &sb) != 0) {
      // file does not exist, we cannot read anything saved
      return false;
    }

    // check that the file is not more than 30 minutes old since edit
    using clock = chrono::system_clock;
    const auto mod_time = clock::from_time_t(sb.st_mtime);
    const auto now = clock::now();

    // cannot use saved token as it has expired
    if (now - mod_time > chrono::minutes(25)) return false;

    // create file stream, open it to the file, read it, and set access token
    ifstream f;
    f.open(this->token_file_.value());
    if (!f.is_open()) return false;

    stringstream rd_stream;
    rd_stream << f.rdbuf();
    f.close();

    this->access_token_ = rd_stream.str();
    return true;
  }

  /**
   * Write newly generated access token to a file.
   */
  void AmeritradeSession::write_access_token_() {
    // santiy check this function is not called before checking token_file_
    if (this->token_file_ == nullopt) return;

    struct stat sb;
    if (stat(this->token_file_.value().c_str(), &sb) == 0) {
      // file does not exist, create it
      ofstream(this->token_file_.value());
    }

    ofstream f;
    f.open(this->token_file_.value());
    if (!f.is_open()) return;
    f << this->access_token_;
    f.close();
  }

  /**
   * Return a valid access token.
   *
   * This function will use an existing session object and return a valid access
   * token or regenerate one if the existing token has expired. This function
   * only needs to be called if a token is needed for external purposes, such
   * as connecting with fluxcpp-socket.
   *
   * @return a valid TDAmeritrade API access token
   */
  string AmeritradeSession::get_access_token() {
    init_access_token_();
    return access_token_;
  }

  /**
   * Quote a basket of securities.
   *
   * This function will make a request to TDAmeritrade to quote a basket of
   * securities and will return an unordered_map mapping tickers to quote
   * structs as defined in include/quotes.hpp.
   *
   * @param an initializer_list of securities to quote
   * @return an unordered_map mapping tickers to quote structs
   */
  unordered_map<string, quotes::quoted_instrument> AmeritradeSession::quote_securities(initializer_list<std::string_view> securities) {
    string ss = "";
    for (auto ticker : securities) {
      ss += ticker;
      ss += ',';
    }
    ss.pop_back();

    transform(ss.begin(), ss.end(), ss.begin(), ::toupper);
    auto req_params = cpr::Parameters{
      {"symbol", ss},
    };

    cpr::Response r = cpr::Get(
      cpr::Url{root_url_ + "marketdata/quotes"}, 
      cpr::Bearer{this->access_token_},
      req_params);

    if (r.status_code != 200) throw ApiException(r.status_code);

    nlohmann::json j = nlohmann::json::parse(r.text);
    return j.get<unordered_map<string, quotes::quoted_instrument>>();
  }

  /**
   * Quote a single security.
   *
   * This function calls AmeritradeSession::quote_securities with a single
   * security and indexes the unordered_map with the requested ticker to only
   * run a single quote struct.
   *
   * @param a single ticker to quote
   * @return a quote struct for the quote
   */
  quotes::quoted_instrument AmeritradeSession::quote_security(string security) {
    auto s = this->quote_securities({security});

    transform(security.begin(), security.end(), security.begin(), ::toupper);

    if (s.find(security) == s.end()) throw ApiException(API_NOT_FOUND);

    return s[security];
  }

  /**
   * Search for instruments through the API.
   *
   * This function searches for instruments through the API through one of
   * four different search types (search_type).
   *
   * @param the search parameter
   * @param the type of search to conduct (search_type)
   * @return a mapping from tickers to searched instruments (without fundamentals)
   */
  unordered_map<string, instruments::instrument> AmeritradeSession::search_instrument(string query, instruments::search_type type) {
    cpr::Parameters req_params = {
      {"symbol", query},
      {"projection", search_type_str(type)},
    };

    cpr::Response r = cpr::Get(
      cpr::Url{root_url_ + "instruments"}, 
      cpr::Bearer{this->access_token_},
      req_params);

    if (r.status_code != 200) throw ApiException(r.status_code);

    nlohmann::json j = nlohmann::json::parse(r.text);
    return j.get<unordered_map<string, instruments::instrument>>();
  }

  /**
   * Search for instrument fundamentals through the API.
   *
   * This function searches for instrument fundmanetals through the API through
   * a single symbol search term.
   *
   * @param the symbol parameter
   * @return an instrument struct including fundamentals data
   */
  instruments::instrument AmeritradeSession::get_fundamentals(string ticker) {
    transform(ticker.begin(), ticker.end(), ticker.begin(), ::toupper);

    cpr::Parameters req_params = {
      {"symbol", ticker},
      {"projection", "fundamental"}
    };

    cpr::Response r = cpr::Get(
      cpr::Url{root_url_ + "instruments"}, 
      cpr::Bearer{this->access_token_},
      req_params);

    if (r.status_code != 200) throw ApiException(r.status_code);

    nlohmann::json j = nlohmann::json::parse(r.text);
    auto s = j.get<unordered_map<string, instruments::instrument>>();
    if (s.find(ticker) == s.end()) throw ApiException(API_NOT_FOUND);

    return s[ticker];
  }

  /**
   * Return market hours for specified markets.
   *
   * This function returns market hours returned by the API for the markets
   * specified on the date provided.
   *
   * @param a list of markets to get hours for
   * @param a date to get pre, regular, and post market hours for
   * @return a market_hours_rsp struct
   */
  markets::hours AmeritradeSession::get_market_hours(vector<markets::type> markets, string date) {
    // convert the markets to strings
    vector<string> markets_str;
    for (auto& market : markets)
      markets_str.emplace_back(get_str(market));

    // capitalize all the markets for parameters
    for (auto& market_str : markets_str)
      transform(
        market_str.begin(), 
        market_str.end(), market_str.begin(), 
        ::toupper);

    // implode the vector of strings with a comma
    string ss = "";
    for (auto market : markets_str) {
      ss += market;
      ss += ',';
    }
    ss.pop_back();

    cpr::Parameters req_params = {
      {"markets", ss},
      {"date", date}
    };

    cpr::Response r = cpr::Get(
      cpr::Url{root_url_ + "marketdata/hours"}, 
      cpr::Bearer{this->access_token_},
      req_params);

    if (r.status_code != 200) throw ApiException(r.status_code);

    nlohmann::json j = nlohmann::json::parse(r.text);
    return j.get<markets::hours>();
  }

  /**
   * Return the top movers of an index for either direction of either value or
   * percentage.
   *
   * @param index to get the top movers from
   * @param direction (direction::UP or direction::DOWN) for movers
   * @param whether to get movers by percent of raw value
   */
  vector<movers::mover> AmeritradeSession::get_movers(enum movers::index i, enum movers::direction d, enum movers::change_metric c) {
    string d_str = i == movers::index::COMPX ? "$COMPX" : (i == movers::index::SPX ? "$SPX.X" : "$DJI");

    cpr::Parameters req_params = {
      {"direction", d == movers::direction::UP ? "up" : "down"},
      {"change", c == movers::change_metric::RAW ? "value" : "percent"},
    };

    string idx_str = i == movers::index::COMPX ? "$COMPX" : (i == movers::index::SPX ? "$SPX.X" : "$DJI");
    cpr::Response r = cpr::Get(
      cpr::Url{root_url_ + "marketdata/" + idx_str + "/movers"}, 
      cpr::Bearer{this->access_token_},
      req_params);

    if (r.status_code != 200) throw ApiException(r.status_code);

    nlohmann::json j = nlohmann::json::parse(r.text);
    return j.get<vector<movers::mover>>();
  }

  /**
   * Return an option chain.
   */
  chains::chain AmeritradeSession::get_options(string symbol, optional<chains::options_req> request_opt) {
    transform(symbol.begin(), symbol.end(), symbol.begin(), ::toupper);

    cpr::Parameters req_params = {
      {"symbol", symbol},
    };

    if (request_opt != nullopt) {
      auto request = request_opt.value();

      if (request.contract != nullopt)
        req_params.Add({"contractType", contract_str(request.contract.value())});

      if (request.num_strikes != nullopt)
        req_params.Add({"strikeCount", to_string(request.num_strikes.value())});

      if (request.include_quotes != nullopt) 
        req_params.Add({"includeQuotes", request.num_strikes.value() ? "TRUE" : "FALSE"});

      if (request.strat != nullopt)
        req_params.Add({"strategy", strategy_str(request.strat.value())});

      if (request.strike_interval != nullopt)
        req_params.Add({"interval", to_string(request.strike_interval.value())});

      if (request.strike_price != nullopt)
        req_params.Add({"strike", to_string(request.strike_price.value())});

      if (request.strike_filter != nullopt)
        req_params.Add({"range", strike_str(request.strike_filter.value())});

      if (request.from_date != nullopt)
        req_params.Add({"fromDate", request.from_date.value()});

      if (request.to_date != nullopt)
        req_params.Add({"toDate", request.to_date.value()});

      if (request.analytical_query != nullopt) {
        if (request.analytical_query.value().vol != nullopt)
          req_params.Add({"volatility", to_string(request.analytical_query.value().vol.value())});

        if (request.analytical_query.value().underlying_price != nullopt)
          req_params.Add({"underlyingPrice", to_string(request.analytical_query.value().underlying_price.value())});

        if (request.analytical_query.value().interest_rate != nullopt)
          req_params.Add({"interestRate", to_string(request.analytical_query.value().interest_rate.value())});

        if (request.analytical_query.value().exp_days != nullopt)
          req_params.Add({"daysToExpiration", to_string(request.analytical_query.value().exp_days.value())});
      }

      if (request.exp_month != nullopt)
        req_params.Add({"expMonth", months_str(request.exp_month.value())});

      if (request.option_type != nullopt)
        req_params.Add({"optionType", norm_opt_str(request.option_type.value())});
    }


    cpr::Response r = cpr::Get(
      cpr::Url{root_url_ + "marketdata/chains"},
      cpr::Bearer{this->access_token_},
      req_params);

    if (r.status_code != 200) throw ApiException(r.status_code);

    nlohmann::json j = nlohmann::json::parse(r.text);
    return j.get<chains::chain>();
  }

  chains::chain AmeritradeSession::get_options(string symbol) {
    return this->get_options(symbol, nullopt);
  }

  /**
   * Get historical price of security.
   *
   * @param the symbol to get historical price for
   * @param parameterized period
   * @param parameterized frequency
   * @param start date for pricing to start (in ms since epoch)
   * @param end date for pricing to end (in ms since epoch)
   * @return a list of candles with the symbol included
   */
  template<historical::internal::times T, historical::internal::times U>
  vector<historical::candle> AmeritradeSession::get_historical(std::string symbol,
      optional<historical::internal::ParameterizedTime<T>> period,
      historical::internal::ParameterizedTime<U> frequency, 
      optional<int64_t> start, optional<int64_t> end,
      bool extended) {

    transform(symbol.begin(), symbol.end(), symbol.begin(), ::toupper);

    cpr::Parameters req_params = {
      {"frequencyType", frequency.to_type()},
      {"frequency", to_string(frequency.to_num())},
    };

    if (period != nullopt) {
      req_params.Add({"periodType", period.value().to_type()});
      req_params.Add({"period", to_string(period.value().to_num())});
    }

    if (start != nullopt)
      req_params.Add({"startDate", to_string(start.value())});

    if (end != nullopt)
      req_params.Add({"endDate", to_string(end.value())});

    if (extended)
      req_params.Add({"nextExtendedHoursData", extended ? "true" : "false"});

    cpr::Response r = cpr::Get(
      cpr::Url{root_url_ + "marketdata/" + symbol + "/pricehistory"},
      cpr::Bearer{this->access_token_},
      req_params);

    if (r.status_code != 200) throw ApiException(r.status_code);

    nlohmann::json j = nlohmann::json::parse(r.text);
    return j.get<historical::candle_list>().candles;
  }

  // period::Day
  // frequency::Minute
  template vector<historical::candle> AmeritradeSession::get_historical(std::string,
      optional<historical::period::Day>, historical::frequency::Minute,
      optional<int64_t>, optional<int64_t>, bool);

  // period::Month
  // frequency::Daily
  template vector<historical::candle> AmeritradeSession::get_historical(std::string,
      optional<historical::period::Month>, historical::frequency::Daily,
      optional<int64_t>, optional<int64_t>, bool);
  // frequency::Weekly
  template vector<historical::candle> AmeritradeSession::get_historical(std::string,
      optional<historical::period::Month>, historical::frequency::Weekly,
      optional<int64_t>, optional<int64_t>, bool);

  // period::Year
  // frequency::Daily
  template vector<historical::candle> AmeritradeSession::get_historical(std::string,
      optional<historical::period::Year>, historical::frequency::Daily,
      optional<int64_t>, optional<int64_t>, bool);
  // frequency::Weekly
  template vector<historical::candle> AmeritradeSession::get_historical(std::string,
      optional<historical::period::Year>, historical::frequency::Weekly,
      optional<int64_t>, optional<int64_t>, bool);
  // frequency::Monthly
  template vector<historical::candle> AmeritradeSession::get_historical(std::string,
      optional<historical::period::Year>, historical::frequency::Monthly,
      optional<int64_t>, optional<int64_t>, bool);

  // period::Ytd
  // frequency::Daily
  template vector<historical::candle> AmeritradeSession::get_historical(std::string,
      optional<historical::period::Ytd>, historical::frequency::Daily,
      optional<int64_t>, optional<int64_t>, bool);
  // frequency::Weekly
  template vector<historical::candle> AmeritradeSession::get_historical(std::string,
      optional<historical::period::Ytd>, historical::frequency::Weekly,
      optional<int64_t>, optional<int64_t>, bool);
};
