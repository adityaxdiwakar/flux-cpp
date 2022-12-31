#pragma once
#include <string>

#include "nlohmann/json.hpp"

namespace flux {
  namespace movers {
    enum class index          { COMPX, DJI, SPX };
    enum class change_metric  { RAW, PERCENT };
    enum class direction      { UP, DOWN };

    struct mover {
      std::string description;
      std::string symbol;

      double change;
      double last;
      int64_t total_volume;

      direction direction;

      friend void from_json(const nlohmann::json&, mover&);
      friend void to_json(nlohmann::json&, const mover&);
    };
  };
};
