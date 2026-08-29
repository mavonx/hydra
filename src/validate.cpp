#include <algorithm>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <string>

#include "hydra/validate.hpp"

namespace hydra {
    namespace {
        constexpr std::string_view kCsvSuffix = ".csv";
    }

    bool has_csv_extension(std::string_view path) {
        if (path.size() < kCsvSuffix.size()) {
            return false;
        }
        const std::string_view tail = path.substr(path.size() - kCsvSuffix.size());
        return std::equal(tail.begin(), tail.end(), kCsvSuffix.begin(),
                          [](char lhs, char rhs) {
                              return std::tolower(static_cast<unsigned char>(lhs)) == rhs;
                          });
    }

    bool exists(std::string_view path) {
        std::error_code ec;
        return std::filesystem::exists(std::filesystem::path{std::string(path)}, ec);
    }

    bool is_directory(std::string_view path) {
        const std::filesystem::path dir_path{std::string(path)};
        std::error_code ec;
        return std::filesystem::is_directory(dir_path, ec) && !ec;
    }

    bool is_readable_file(std::string_view path) {
        const std::filesystem::path file_path{std::string(path)};

        std::error_code ec;
        if (!std::filesystem::is_regular_file(file_path, ec) || ec) {
            return false;
        }

        // is_regular_file only checks the type; readability requires an
        // actual open attempt (permissions, ACLs, ...).
        std::ifstream probe(file_path);
        return probe.good();
    }
}
