#include <string>
#include <nlohmann/json.hpp>
#include "cpr/cpr.h"
#include "quotes.hpp"
#include "instruments.hpp"
#pragma once

class AmeritradeSession {
  private:
    std::string refresh;
    std::string consumer_key;
    std::string root_url;
    std::string access_token;
    void init_access_token();

  public:
    AmeritradeSession(std::string, std::string, std::string);
    AmeritradeSession();
    friend std::ostream& operator<<(std::ostream&, const  AmeritradeSession&);
    friend void to_json(nlohmann::json&, const AmeritradeSession&);

    // access token methods
    std::string get_access_token();

    // quoting methods 
    std::unordered_map<std::string, quoted_instrument> quote_securities(std::initializer_list<std::string_view>);
    quoted_instrument quote_security(std::string);

    // search methods
    std::unordered_map<std::string, instrument> search_instrument(std::string, search_type);
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
