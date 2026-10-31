#pragma once

#include <cstddef>
#include <string_view>
#include <string>
#include <vector>

namespace hydra {
    // Returns file size in Gigabytes (GB).
    double get_file_size_gb(std::string_view path);

    // Counts total rows excluding the header line. Returns 0 if empty or header-only.
    std::size_t count_csv_rows(std::string_view path);

    // Returns a vector of column names parsed from the first line of the file.
    std::vector<std::string> get_csv_headers(std::string_view path);
}
