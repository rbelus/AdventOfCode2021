#pragma once

#include <filesystem>
#include <functional>

// Open file at path and execute fnc for each line in the file.
void ParseLinesInFile(const std::filesystem::path& path, const std::function<void(std::string&)>& fnc);
uint16_t CountLinesInFile(const std::filesystem::path& path);

