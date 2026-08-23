#pragma once

#include <string_view>

namespace hydra {
    enum class CsvPathStatus {
        Ok,          // existing, readable regular file with a .csv extension
        NotCsv,      // the extension is not ".csv"
        NotOpenable  // missing, not a regular file, or not readable
    };

    // Validates that `path` points to an existing, readable regular file with
    // a ".csv" extension. Never reads the file content, so it can be unit
    // tested without any CSV parsing.
    CsvPathStatus validate_csv_path(std::string_view path);
}
