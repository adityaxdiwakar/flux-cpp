#pragma once

#include <string>
#include <vector>
#include "nlohmann/json.hpp"

namespace historical {
  struct candle {
    double open;
    double high;
    double low;
    double close;

    int64_t volume;
    int64_t datetime;

    friend void from_json(const nlohmann::json&, candle&);
    friend void to_json(nlohmann::json&, const candle&);
  };

  struct candle_list {
    std::string symbol;
    std::vector<candle> candles;

    friend void from_json(const nlohmann::json&, candle_list&);
    friend void to_json(nlohmann::json&, const candle_list&);
  };

  enum class period_type {
    DAY, MONTH, YEAR, YTD
  };

  namespace internal {
    enum times {
      MINUTE, DAILY, WEEKLY, MONTHLY, DAY, MONTH, YEAR, YTD
    };

    template<times T>
    class ParameterizedTime { 
      private:
        int period_; 

      public:
        ParameterizedTime(int num);
        const char* to_type() noexcept; 
        int to_num();
    };
  }

  namespace period {
    using Day = internal::ParameterizedTime<internal::DAY>;
    using Month = internal::ParameterizedTime<internal::MONTH>;
    using Year = internal::ParameterizedTime<internal::YEAR>;
    using Ytd = internal::ParameterizedTime<internal::YTD>;
  }

  namespace frequency {
    using Minute = internal::ParameterizedTime<internal::MINUTE>;
    using Daily = internal::ParameterizedTime<internal::DAILY>;
    using Weekly = internal::ParameterizedTime<internal::WEEKLY>;
    using Monthly = internal::ParameterizedTime<internal::MONTHLY>;
  }
};
