#pragma once

#include <string_view>

namespace hydra {
    // True when `path` ends with ".csv" (case-insensitive).
    bool has_csv_extension(std::string_view path);

    // True when `path` exists on disk (any kind of entry).
    bool exists(std::string_view path);

    // True when `path` points to a directory entity on disk.
    bool is_directory(std::string_view path);

    // True when `path` is an existing regular file that can be opened for
    // reading. Never reads the file content.
    bool is_readable_file(std::string_view path);
}
