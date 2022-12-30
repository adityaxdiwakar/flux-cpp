#include <string>
#include <nlohmann/json.hpp>
#include "cpr/cpr.h"
#include "quotes.hpp"
#include "instruments.hpp"
#include "markethours.hpp"
#include "chains.hpp"
#include "movers.hpp"
#include "history.hpp"
#pragma once

class AmeritradeSession {
  private:
    std::string refresh_;
    std::string consumer_key_;
    std::string root_url_;
    std::string access_token_;
    std::optional<std::string> token_file_;
    void init_access_token_();
    void write_access_token_();
    bool read_saved_token_();

    // historical price method 
    template<historical::internal::times T, historical::internal::times U>
    std::vector<historical::candle> get_historical(std::string,
        std::optional<historical::internal::ParameterizedTime<T>>,
        historical::internal::ParameterizedTime<U>, 
        std::optional<int64_t> start, std::optional<int64_t> end,
        bool extended);

  public:
    AmeritradeSession(std::string, std::string, std::string);
    AmeritradeSession(std::string, std::string, std::string, std::string);

    // friend methods for overloading operations (json cast, streaming)
    friend std::ostream& operator<<(std::ostream&, const  AmeritradeSession&);
    friend void to_json(nlohmann::json&, const AmeritradeSession&);

    // access token methods
    std::string get_access_token();

    // quoting methods 
    std::unordered_map<std::string, quoted_instrument> quote_securities(std::initializer_list<std::string_view>);
    quoted_instrument quote_security(std::string);

    // search methods
    std::unordered_map<std::string, instrument> search_instrument(std::string, search_type);
    instrument get_fundamentals(std::string);

    // market hour method
    markets_hours get_market_hours(std::vector<market_type>, std::string);
    
    // movers method
    std::vector<mover> get_movers(enum index, enum direction, enum change_metric);

    // options chain method
    chain get_options(std::string, std::optional<options_req>);
    chain get_options(std::string);
    
    // historical price method 
    template<historical::internal::times T, historical::internal::times U>
    std::vector<historical::candle> get_historical(std::string symbol,
        historical::internal::ParameterizedTime<T> period,
        historical::internal::ParameterizedTime<U> frequency, 
        bool extended) {
      return this->get_historical(symbol, std::make_optional(period), frequency, std::nullopt, std::nullopt, extended);
    }

    template<historical::internal::times U>
    std::vector<historical::candle> get_historical(std::string symbol,
        historical::internal::ParameterizedTime<U> frequency, 
        int64_t start, int64_t end,
        bool extended) {
      return this->get_historical(symbol, std::nullopt, frequency, start, end, extended);
    }

    template<historical::internal::times T, historical::internal::times U>
    std::vector<historical::candle> get_historical(std::string symbol,
        historical::internal::ParameterizedTime<T> period,
        historical::internal::ParameterizedTime<U> frequency) {
      return this->get_historical(symbol, std::make_optional(period), frequency, std::nullopt, std::nullopt, false);
    }

    template<historical::internal::times U>
    std::vector<historical::candle> get_historical(std::string symbol,
        historical::internal::ParameterizedTime<U> frequency,
        int64_t start, int64_t end) {
      return this->get_historical(symbol, std::nullopt, frequency, start, end, false);
    }
};

/**
 * Custom exception type for API errors.
 */
class ApiException : public std::exception {
  private:
    int status_code;

  public: 
    ApiException(int code);
    int get_code();
};

enum api_errors {
  API_BAD_REQUEST = 400,
  API_UNAUTHD = 401,
  API_FORBIDDEN = 403,
  API_NOT_FOUND = 404,
  API_MISC_QUERY = 406
};
