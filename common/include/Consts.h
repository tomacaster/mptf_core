#pragma once

#include <string_view>

#include "ProjectConfig.h"

namespace Consts
{
        constexpr const std::string_view APP_DIR_ENV = "\%GBARIC_HOME\%";
        constexpr const std::string_view PROJ_NAME = ProjectConfig::PROJECT_NAME;
};