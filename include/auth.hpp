#include <string>
#include "nlohmann/json.hpp"
#pragma once

const std::string gt_refresh_token = "refresh_token";

struct access_token_struct {
  std::string grant_type;
  std::string refresh_token;
  std::string client_id;
  std::string redirect_uri;

  NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(access_token_struct, grant_type, refresh_token, client_id, redirect_uri);
};
