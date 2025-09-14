#pragma once

#include <string_view>
#include <string>
#include <format>

#include "ProjectConfig.h"

namespace Consts
{
        constexpr const std::string_view PROJ_NAME = ProjectConfig::PROJECT_NAME;
        inline const std::string APP_DIR_ENV = std::format("\%{}_HOME\%", PROJ_NAME);
};