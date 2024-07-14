#pragma once

#include "Config.hpp"
#include <string>
#include <format>

namespace Utils
{

    std::string VersionString()
    {
        return std::format("{}.{}.{}", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
    } 

}
