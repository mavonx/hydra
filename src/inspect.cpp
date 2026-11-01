#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <utility>

#include "hydra/inspect.hpp"

namespace hydra {
    namespace {
        std::pair<double, std::string_view> size_with_unit(std::uintmax_t bytes) {
            if (bytes < 1024ULL) {
                return {static_cast<double>(bytes), "B"};
            }
            const double kb = static_cast<double>(bytes) / 1024.0;
            if (kb < 1024.0) {
                return {kb, "KB"};
            }
            const double mb = kb / 1024.0;
            if (mb < 1024.0) {
                return {mb, "MB"};
            }
            return {mb / 1024.0, "GB"};
        }
    }

    std::pair<double, std::string_view> get_file_size(std::string_view path) {
        std::error_code ec;
        const auto bytes = std::filesystem::file_size(std::filesystem::path{std::string(path)}, ec);
        if (ec) {
            return {0.0, "B"};
        }
        return size_with_unit(bytes);
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
