#pragma once

#include <vector>
#include <stdexcept>
#include <fstream>
#include <string>

#include "../../app/ApplicationInfo.hpp"

std::vector<char>	readFile(const std::string& filename);
