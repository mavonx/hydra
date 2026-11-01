#pragma once

#include <cstddef>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace hydra {
    // Returns human-readable file size: value and unit (B, KB, MB, or GB).
    std::pair<double, std::string_view> get_file_size(std::string_view path);

    // Counts total rows excluding the header line. Returns 0 if empty or header-only.
    std::size_t count_csv_rows(std::string_view path);

    // Returns a vector of column names parsed from the first line of the file.
    std::vector<std::string> get_csv_headers(std::string_view path);
}
