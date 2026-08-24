#pragma once

#include <cstddef>
#include <string_view>

namespace hydra {
    // Returns file size in Gigabytes (GB).
    double get_file_size_gb(std::string_view path);

    // Counts total rows excluding the header line. Returns 0 if empty or header-only.
    std::size_t count_csv_rows(std::string_view path);
}
