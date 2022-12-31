#include "history.hpp"
#include "nlohmann/json.hpp"

namespace flux {
  namespace historical {
    void from_json(const nlohmann::json& j, candle& c) {
      j.at("open").get_to(c.open);
      j.at("close").get_to(c.close);
      j.at("low").get_to(c.low);
      j.at("high").get_to(c.high);
      j.at("volume").get_to(c.volume);
      j.at("datetime").get_to(c.datetime);
    }

    void to_json(nlohmann::json& j, const candle& c) {
      j = {
        {"open", c.open},
        {"close", c.close},
        {"low", c.low},
        {"high", c.high},
        {"volume", c.volume},
        {"datetiem", c.datetime},
      };
    }

    void from_json(const nlohmann::json& j, candle_list& c) {
      j.at("symbol").get_to(c.symbol);
      j.at("candles").get_to(c.candles);
    }

    void to_json(nlohmann::json& j, const candle_list& c) {
      j = {
        {"symbol", c.symbol},
        {"candles", c.candles},
      };
    }

    namespace internal {
      template<times T>
      ParameterizedTime<T>::ParameterizedTime(int period) : period_(period) {}

      template<times T>
      int ParameterizedTime<T>::to_num() {
        return this ->period_;
      }

      template<times T>
      const char* ParameterizedTime<T>::to_type() noexcept {
        switch (T) {
          case DAY: return "day";
          case MONTH: return "month";
          case YTD: return "ytd";
          case YEAR: return "year";
          case MINUTE: return "minute";
          case DAILY: return "daily";
          case WEEKLY: return "weekly";
          case MONTHLY: return "monthly";
        };
      }

      template class ParameterizedTime<DAY>;
      template class ParameterizedTime<MONTH>;
      template class ParameterizedTime<YTD>;
      template class ParameterizedTime<YEAR>;
      template class ParameterizedTime<MINUTE>;
      template class ParameterizedTime<DAILY>;
      template class ParameterizedTime<WEEKLY>;
      template class ParameterizedTime<MONTHLY>;
    };
  };
};
