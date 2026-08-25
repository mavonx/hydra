#include <filesystem>
#include <fstream>
#include <string>

#include "hydra/inspect.hpp"

namespace hydra {
    double get_file_size_gb(std::string_view path) {
        std::error_code ec;
        const auto bytes = std::filesystem::file_size(std::filesystem::path{std::string(path)}, ec);
        if(ec) {
            return 0.00;
        }

        // 1 GB = 1024 * 1024 * 1024 bytes
        return static_cast<double>(bytes) / (1024.0 * 1024.0 * 1024.0);
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
}
