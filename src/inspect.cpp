#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <array>
#include "hydra/inspect.hpp"

namespace hydra {
    std::pair<double, std::string_view> get_file_size(std::string_view path) {
        std::error_code ec;
        constexpr double base = 1024.0;
        constexpr std::array<std::string_view, 4> units{
            "B", "KB", "MB", "GB"
        };

        const auto bytes = std::filesystem::file_size(std::filesystem::path{std::string(path)}, ec);
        if(ec) {
            return {0.00, units[0]};
        }

        double size = static_cast<double>(bytes);
        std::size_t unit_index = 0;
        while (size >= base && unit_index < units.size() - 1) {
            size /= base;
            ++unit_index;
        }

        return {size, units[unit_index]};
    }

    std::size_t count_csv_rows(std::string_view path) {
        std::ifstream file(std::string{path}, std::ios::binary);
        if(!file.is_open()) {
            return 0;
        }

        std::string line;
        if(!std::getline(file, line)) {
            return 0;
        }

        std::size_t rows = 0;
        while(std::getline(file, line)) {
            rows++;
        }

        return rows;
    }

    std::vector<std::string> get_csv_headers(std::string_view path) {
        std::ifstream file(std::string{path}, std::ios::binary);
        if(!file.is_open()) {
            return {};
        }

        std::string line;
        if(!std::getline(file, line)) {
            return {};
        }

        std::stringstream ss(line);
        std::string column;
        std::vector<std::string> headers;
        while(std::getline(ss, column, ',')) {
            headers.push_back(column);
        }

        return headers;
    }
}
