#pragma once

#include <string_view>

namespace hydra {
    // True when `path` ends with ".csv" (case-insensitive).
    bool has_csv_extension(std::string_view path);

    // True when `path` exists on disk (any kind of entry).
    bool file_exists(std::string_view path);

    // True when `path` is an existing regular file that can be opened for
    // reading. Never reads the file content.
    bool is_readable_file(std::string_view path);
}
